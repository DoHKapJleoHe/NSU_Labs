#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<memory.h>
#include<math.h>
#include<mpi.h>

void MatrixMultiplicationMPI(double* A, double* B, double* Resultat, int N, int M, int K)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < K; k++)
			{
				Resultat[j * K + k] += A[i * N + j] * B[i * K + k];
			}
		}
	}
}

void MatrixAdditionMPI(double* A, double* B, double* Resultat, int N)
{
	for (int i = 0; i < N; i++)
	{
		Resultat[i] = A[i] + B[i];
	}
}

double CalcNorm(double* A, int length)
{
	double norm = 0;

	for (int i = 0; i < length; i++)
	{
		norm += (A[i] * A[i]);
	}

	norm = sqrt(norm);

	return norm;
}

double Scalar(double* A, double* B, int size)
{
	double scal = 0;
	for (int i = 0; i < size; i++)
	{
		scal += A[i] * B[i];
	}

	return scal;
}

void clear(double* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		array[i] = 0;
	}
}

void print(double* vector, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%lf ", vector[i]);
	}
	printf("\n");
}


int main(int argc, char* argv[])
{
	int ProcNum,
		ProcRank;
	int N = 8000;
	double e = 1e-5, start_time, end_time;
	
	MPI_Init(&argc, &argv);
	start_time = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); 

	double* A = NULL;
	double* b = NULL;
	double* x = NULL;

	if (ProcRank == 0)
	{
		A = (double*)malloc(N * N * sizeof(double));
		b = (double*)malloc(N * sizeof(double));
		x = (double*)malloc(N * sizeof(double));
		if (A == NULL || b == NULL || x == NULL)
			return -1;

		clear(b, N);
		clear(A, N * N);

		for (int i = 0; i < N; i++)
		{
			x[i] = 0.0;
			b[i] = N + 1.0;
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i == j)
				{
					A[i * N + j] = 2;
				}
				else
				{
					A[i * N + j] = 1;
				}
			}
		}
	}

	int LinesPerProcess = N / ProcNum;
	int* sendcounts_A = (int*)malloc(ProcNum * sizeof(int));
	int* sendcounts_vec = (int*)malloc(ProcNum * sizeof(int));
	if (sendcounts_A == NULL || sendcounts_vec == NULL)
	{
		printf("Couldn't allocate memory for sendcounts and displs");
		return -1;
	}

	for (int i = 0; i < ProcNum; i++)
	{
		sendcounts_A[i] = LinesPerProcess * N;

		sendcounts_vec[i] = sendcounts_A[i] / N;
	}

	double* A_part = (double*)malloc(sendcounts_A[ProcRank] * sizeof(double));
	double* b_part = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* x_part = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));

	if (A_part == NULL || b_part == NULL || x_part == NULL)
		return -1;

	MPI_Scatter(A, sendcounts_A[ProcRank], MPI_DOUBLE, A_part, sendcounts_A[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, sendcounts_vec[ProcRank], MPI_DOUBLE, b_part, sendcounts_vec[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(x, sendcounts_vec[ProcRank], MPI_DOUBLE, x_part, sendcounts_vec[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	double* r_part_prev = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* r_part_next = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* z_part_prev = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* z_part_next = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* temp = (double*)malloc(N * sizeof(double));
	double* temp1 = (double*)malloc(N * sizeof(double));
	double* temp_part = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));

	if (r_part_prev == NULL || r_part_next == NULL || z_part_prev == NULL || z_part_next == NULL || temp == NULL || temp1 == NULL || temp_part == NULL)
		return -1;

	// Multiplying part of A and part vector: 
	//			a b c	r	a*r + d*r + j*r
	//			d e f * t = 	b*t + e*t + k*t
	//			j k l	x	c*x + f*x + l*x
	//
	clear(temp, N);
	clear(temp1, N);
	MatrixMultiplicationMPI(A_part, x_part, temp, N, sendcounts_vec[ProcRank], 1); // only part of full vector
	MPI_Allreduce(temp, temp1, N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Scatter(temp1, sendcounts_vec[ProcRank], MPI_DOUBLE, temp_part, sendcounts_vec[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
	{
		r_part_prev[i] = b_part[i] - temp_part[i];
	}
	memcpy(z_part_prev, r_part_prev, sendcounts_vec[ProcRank] * sizeof(double));
	bool ex = true;
	double alpha = 0, betta = 0;
	clear(temp, N);
	MPI_Allgather(b_part, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
	double check = CalcNorm(temp, N) * e, chec1 = 0;
	int iterations = 0;
	double chislitel = 0, znamenatel = 0;
	while (ex)
	{
		iterations++;
		clear(temp, N);
		clear(temp1, N);
		clear(r_part_next, N);
		clear(z_part_next, N);
		
		MPI_Allgather(r_part_prev, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);

		chislitel = Scalar(temp, temp, N);

		clear(temp, N);
		MatrixMultiplicationMPI(A_part, z_part_prev, temp1, N, sendcounts_vec[ProcRank], 1);  //part of full vector
		MPI_Allgather(z_part_prev, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD); 
		
		znamenatel = Scalar(temp1, temp, N);
		MPI_Allreduce(MPI_IN_PLACE, &znamenatel, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		
		alpha = chislitel / znamenatel;
		
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			temp_part[i] = z_part_prev[i] * alpha;
		}
		MatrixAdditionMPI(x_part, temp_part, x_part, sendcounts_vec[ProcRank]);
		
		clear(temp_part, sendcounts_vec[ProcRank]);
		clear(temp, N);
		for (int i = 0; i < N; i++)
		{
			temp1[i] = temp1[i] * alpha;
		}
		MPI_Allreduce(temp1, temp, N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		MPI_Scatter(temp, sendcounts_vec[ProcRank], MPI_DOUBLE, temp_part, sendcounts_vec[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			r_part_next[i] = r_part_prev[i] - temp_part[i];
		}

		clear(temp, N);
		clear(temp1, N);
		MPI_Allgather(r_part_next, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		chec1 = CalcNorm(temp, N);
		betta = Scalar(temp, temp, N) / chislitel;
		
		clear(temp_part, N);
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			temp_part[i] = z_part_prev[i] * betta;
		}
		MatrixAdditionMPI(r_part_next, temp_part, z_part_next, sendcounts_vec[ProcRank]); // once was a strange error that did not happened in future
		
		if (chec1 < check || iterations > 100)
		{
			ex = false;
		}
		else
		{
			for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
			{
				z_part_prev[i] = z_part_next[i];
				r_part_prev[i] = r_part_next[i];
			}
		}
	}
	
	end_time = MPI_Wtime();
	
	
	if (ProcRank == 0)
	{
		print(x_part, 2);
		printf("Iterations: %d\n", iterations);
		printf("Time taken: %lf\n", end_time - start_time);
		printf("\n");
	}

	if (ProcRank == 0)
	{
		free(A);
		free(b);
		free(x);
	}
	free(x_part);
	free(r_part_prev);
	free(r_part_next);
	free(z_part_prev);
	free(z_part_prev);
	free(temp);
	free(temp1);
	free(temp_part);
	free(A_part);
	free(b_part);
	
	MPI_Finalize();
	return 0;
}
