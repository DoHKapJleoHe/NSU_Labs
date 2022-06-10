#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<stdbool.h>
#include<math.h>

void MatrixMultiplicationMPI(double* A, double* B, double* Resultat, int N, int M, int K)
{
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			for (int j = 0; j < K; j++)
			{
				Resultat[i * K + j] += A[i * M + k] * B[k * K + j];
			}
		}
	}
}

void MatrixSubtractionMPI(double* A, double* B, double* Resultat, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Resultat[i] = A[i] - B[i];
		}
	}
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

double CalcNorm(double* A, int N)
{
	double norm = 0;

	for (int i = 0; i < N; i++)
	{
		norm += (A[i] * A[i]);
	}

	norm = sqrt(norm);

	return norm;
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
	int N = 8000;
	int ProcRank, ProcNum;
	double e = 1e-10, start_time, end_time;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	start_time = MPI_Wtime();

	double* A = NULL;
	double* x = (double*)malloc(N * sizeof(double));
	double* b = (double*)malloc(N * sizeof(double));
	if (x == NULL || b == NULL)
	{
		printf("Couldn't allocate memory for x or b");
		return 0;
	}
	if (ProcRank == 0)
	{
		A = (double*)malloc(N * N * sizeof(double));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i == j)
				{
					A[i * N + j] = 1000,45;
				}
				else
				{
					A[i * N + j] = 0,45;
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			x[i] = 0;
			b[i] = 0,32;
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

	int offsetA = 0;
	for (int i = 0; i < ProcNum; i++)
	{
		sendcounts_A[i] = LinesPerProcess * N;
		offsetA += sendcounts_A[i];

		sendcounts_vec[i] = sendcounts_A[i] / N;
	}

	double* A_part = (double*)malloc(sendcounts_A[ProcRank] * sizeof(double));
	if (A_part == NULL)
		return 0;

	MPI_Scatter(A, sendcounts_A[ProcRank], MPI_DOUBLE, A_part, sendcounts_A[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	double* r_part_prev = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* z_part_prev = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* z_part_next = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* r_part_next = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* temp = (double*)malloc(N * sizeof(double));
	double* temp_part = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));
	double* Az = (double*)malloc(sendcounts_vec[ProcRank] * sizeof(double));

	if (r_part_next == NULL || z_part_next == NULL || r_part_prev == NULL || z_part_prev == NULL || temp == NULL || temp_part == NULL || Az == NULL)
	{
		printf("Couldn't allocate memory for parts");
		return 0;
	}

	clear(r_part_prev, sendcounts_vec[ProcRank]);
	clear(z_part_prev, sendcounts_vec[ProcRank]);
	clear(r_part_next, sendcounts_vec[ProcRank]);
	clear(z_part_next, sendcounts_vec[ProcRank]);
	clear(temp, N);
	clear(temp_part, sendcounts_vec[ProcRank]);
	clear(Az, sendcounts_vec[ProcRank]);

	MatrixMultiplicationMPI(A_part, x, temp_part, sendcounts_A[ProcRank] / N, sendcounts_vec[ProcRank], 1);
	MPI_Allgather(temp_part, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
	for (int i = 0; i < N; i++)
	{
		temp[i] = b[i] - temp[i];
	}
	
	MPI_Scatter(temp, sendcounts_vec[ProcRank], MPI_DOUBLE, temp_part, sendcounts_vec[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	memcpy(r_part_prev, temp_part, sendcounts_vec[ProcRank] * sizeof(double));
	memcpy(z_part_prev, r_part_prev, sendcounts_vec[ProcRank] * sizeof(double));

	bool ex = true;
	int count = 0;
	double chislitel = 0, znamenatel = 0, alpha = 0, betta = 0;
	double check = CalcNorm(b, N) * e;
	while (ex)
	{
		count++;
		clear(z_part_next, sendcounts_vec[ProcRank]);
		clear(r_part_next, sendcounts_vec[ProcRank]);
		clear(temp, N);
		clear(temp_part, sendcounts_vec[ProcRank]);

		MPI_Allgather(z_part_prev, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		MatrixMultiplicationMPI(A_part, temp, Az, sendcounts_A[ProcRank] / N, N, 1);
		znamenatel = Scalar(z_part_prev, Az, sendcounts_vec[ProcRank]); // (A*z_part,z_part)
		MPI_Allreduce(MPI_IN_PLACE, &znamenatel, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		clear(temp, N);

		MPI_Allgather(r_part_prev, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		chislitel = Scalar(temp, temp, N); //(r_part_prev,r_part_prev)
		alpha = chislitel / znamenatel;

		clear(temp, N);
		clear(temp_part, sendcounts_vec[ProcRank]);
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			temp_part[i] = z_part_prev[i] * alpha;
		}
		MPI_Allgather(temp_part, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		for (int i = 0; i < N; i++)
		{
			x[i] = x[i] + temp[i];
		}
		
		clear(temp, N);
		clear(temp_part, sendcounts_vec[ProcRank]);
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			temp_part[i] = alpha * Az[i];
		}
		MatrixSubtractionMPI(r_part_prev, temp_part, r_part_next, sendcounts_vec[ProcRank]);
		
		clear(temp, N);
		MPI_Allgather(r_part_next, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		chislitel = Scalar(temp, temp, N); 
		clear(temp, N);
		MPI_Allgather(r_part_prev, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		znamenatel = Scalar(temp, temp, N);
		betta = chislitel / znamenatel;

		clear(temp_part, sendcounts_vec[ProcRank]);
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			temp_part[i] = z_part_prev[i] * betta;
		}
		for (int i = 0; i < sendcounts_vec[ProcRank]; i++)
		{
			z_part_next[i] = r_part_next[i] + temp_part[i];
		}
		
		clear(temp, N);
		MPI_Allgather(r_part_next, sendcounts_vec[ProcRank], MPI_DOUBLE, temp, sendcounts_vec[ProcRank], MPI_DOUBLE, MPI_COMM_WORLD);
		if (CalcNorm(temp, N) < check || count > 500)
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
		printf("Iterations: %d\n", count);
		printf("Time taken: %lf\n", end_time - start_time);
		print(x, 4);
		printf("\n");
	}
	if (ProcRank == 0)
	{
		free(A);
	}
	free(b);
	free(x);

	MPI_Finalize();
	return 0;
}
