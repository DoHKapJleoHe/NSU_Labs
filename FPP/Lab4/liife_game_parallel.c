#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 6
#define MAX_ITERATIONS 4096 

void print(int* matrix, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			printf("%d ", matrix[i * length + j]);
		}
		printf("\n");
	}
}


int main(int argc, char* argv[])
{
	int ProcNum, ProcRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int** proc_states = (int**)malloc(MAX_ITERATIONS * sizeof(int*));
	int* initial_state = (int*)malloc(SIZE * SIZE * sizeof(int));
	int* flags = (int*)malloc(MAX_ITERATIONS * sizeof(int));
	if (proc_states == NULL || initial_state == NULL || flags == NULL)
	{
		printf("No mem\n");
		return 0;
	}
	
	int min_lines = SIZE / ProcNum;
	int processes_with_etra_lines = SIZE % ProcNum;
	int* send_counts = (int*)malloc(ProcNum * sizeof(int));
	int* displs = (int*)malloc(ProcNum * sizeof(int));
	int displace = 0;

	for (int p = 0; p < ProcNum; p++)
	{
		if (p < processes_with_etra_lines)
			send_counts[p] = SIZE * (min_lines + 1);
		else
			send_counts[p] = SIZE * min_lines;

		displs[p] = displace;
		displace += send_counts[p];
	}

	int length = send_counts[ProcRank]; // number of elements in each process
	int height = send_counts[ProcRank] / SIZE;

	int* cur_state = (int*)malloc(length * sizeof(int));

	//Making initial state called "Glider"
	if (ProcRank == 0)
	{
		for (int i = 0; i < SIZE * SIZE; i++)
		{
			initial_state[i] = 0;
		}


		/*
				0 1 0 0 0
				0 0 1 0 0
				1 1 1 0 0
				0 0 0 0 0
				0 0 0 0 0
		*/

		initial_state[0 * SIZE + 1] = 1;
		initial_state[1 * SIZE + 2] = 1;
		initial_state[2 * SIZE + 0] = 1;
		initial_state[2 * SIZE + 1] = 1;
		initial_state[2 * SIZE + 2] = 1;
	}

	MPI_Scatterv(initial_state, send_counts, displs, MPI_INT, cur_state, length, MPI_INT, 0, MPI_COMM_WORLD);

	int* top_line = (int*)malloc(SIZE * sizeof(int));
	int* bottom_line = (int*)malloc(SIZE * sizeof(int));

	for (int iter = 0; iter < MAX_ITERATIONS; iter++)
	{
		proc_states[iter] = cur_state; // put the pointer to the curent state in all_states(saved it) 
		cur_state = (int*)malloc(length * sizeof(int));
		if (cur_state == NULL)
		{
			printf("No mem\n");
			return 0;
		}

		/*
			nubers define checking order

			1 3 3 3 3 2
			7 9 9 9 9 8
			7 9 9 9 9 8
			7 9 9 9 9 8
			7 9 9 9 9 8
			4 6 6 6 6 5
		*/

		// when sending a top line frob ProcRank, we recive a bottom line for process with ProcRank - 1 
		MPI_Request send_top, receive_bottom, send_bottom, receive_top;

		MPI_Isend(&proc_states[iter][0], SIZE, MPI_INT, (ProcRank - 1)%ProcNum, 1, MPI_COMM_WORLD, &send_top); 
		MPI_Isend(&proc_states[iter][SIZE * (SIZE - 1)], SIZE, MPI_INT, (ProcRank + 1)%ProcNum, 2, MPI_COMM_WORLD, &send_bottom);
		MPI_Irecv(bottom_line, SIZE, MPI_INT, (ProcRank + 1)%ProcNum, 1, MPI_COMM_WORLD, &receive_bottom);
		MPI_Irecv(top_line, SIZE, MPI_INT, (ProcRank - 1)%ProcNum, 2, MPI_COMM_WORLD, &receive_top);

		int neighbours = 0;

		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				neighbours = 0;
				if (j == 0) // checking everything between (0, 0) and (SIZE-1, 0)	(7)
				{
					neighbours += proc_states[iter][(i - 1) * SIZE + (SIZE - 1)]; //here we have periodicity
					neighbours += proc_states[iter][(i - 1) * SIZE + j];
					neighbours += proc_states[iter][(i - 1) * SIZE + (j + 1)];
					neighbours += proc_states[iter][i * SIZE + (SIZE - 1)]; // here we have periodicity
					neighbours += proc_states[iter][i * SIZE + (j + 1)];
					neighbours += proc_states[iter][(i + 1) * SIZE + (SIZE - 1)]; // here we have periodicity
					neighbours += proc_states[iter][(i + 1) * SIZE + j];
					neighbours += proc_states[iter][(i + 1) * SIZE + (j + 1)];
				}
				else if (j == SIZE - 1)  // checking everything between (0, SIZE-1) and (SIZE-1, SIZE-1)	(8)
				{
					neighbours += proc_states[iter][(i - 1) * SIZE + (j - 1)];
					neighbours += proc_states[iter][(i - 1) * SIZE + j];
					neighbours += proc_states[iter][(i - 1) * SIZE + 0];
					neighbours += proc_states[iter][i * SIZE + (j - 1)];
					neighbours += proc_states[iter][i * SIZE + 0];
					neighbours += proc_states[iter][(i + 1) * SIZE + (j - 1)];
					neighbours += proc_states[iter][(i + 1) * SIZE + j];
					neighbours += proc_states[iter][(i + 1) * SIZE + 0];
				}
				else // checking eveything in the center of the matrix	(9)
				{
					// counting bumber of alive neighbours by adding its value to "neighbours"
					neighbours += proc_states[iter][(i - 1) * SIZE + (j - 1)];
					neighbours += proc_states[iter][(i - 1) * SIZE + j];
					neighbours += proc_states[iter][(i - 1) * SIZE + (j + 1)];
					neighbours += proc_states[iter][i * SIZE + (j - 1)];
					neighbours += proc_states[iter][i * SIZE + (j + 1)];
					neighbours += proc_states[iter][(i + 1) * SIZE + (j - 1)];
					neighbours += proc_states[iter][(i + 1) * SIZE + j];
					neighbours += proc_states[iter][(i + 1) * SIZE + (j + 1)];

				}

				if (proc_states[iter][i * SIZE + j] == 0)
				{
					if (neighbours == 3)
						cur_state[i * SIZE + j] = 1;
				}
				else
				{
					if (neighbours < 2 || neighbours > 3)
						cur_state[i * SIZE + j] = 0;
				}
			}
		}

		MPI_Wait(&receive_top, NULL);

		for (int j = 0; j < SIZE; j++)
		{
			neighbours = 0;

			if (j == 0) // checking (0, 0)    (1)
			{
				neighbours += top_line[SIZE - 1];
				neighbours += top_line[0];
				neighbours += top_line[j + 1];
				neighbours += proc_states[iter][0 * SIZE + (SIZE - 1)];
				neighbours += proc_states[iter][0 * SIZE + (j + 1)];
				neighbours += proc_states[iter][(0 + 1) * SIZE + (SIZE - 1)];
				neighbours += proc_states[iter][(0 + 1) * SIZE + j];
				neighbours += proc_states[iter][(0 + 1) * SIZE + (j + 1)];
			}
			else if (j == SIZE - 1)  // checking (0, SIZE-1)  (2)
			{
				neighbours += top_line[j - 1];
				neighbours += top_line[j];
				neighbours += top_line[0];
				neighbours += proc_states[iter][0 * SIZE + (j - 1)];
				neighbours += proc_states[iter][0 * SIZE + 0];
				neighbours += proc_states[iter][(0 + 1) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(0 + 1) * SIZE + j];
				neighbours += proc_states[iter][(0 + 1) * SIZE + 0];

			}
			else // checking eveything between (0, 0) and (0, SIZE-1)  (3)
			{
				neighbours += top_line[j - 1];
				neighbours += top_line[j];
				neighbours += top_line[j + 1];
				neighbours += proc_states[iter][0 * SIZE + (j - 1)];
				neighbours += proc_states[iter][0 * SIZE + (j + 1)];
				neighbours += proc_states[iter][(0 + 1) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(0 + 1) * SIZE + j];
				neighbours += proc_states[iter][(0 + 1) * SIZE + (j + 1)];
			}

			if (proc_states[iter][0 * SIZE + j] == 0)
			{
				if (neighbours == 3)
					cur_state[0 * SIZE + j] = 1;
			}
			else
			{
				if (neighbours < 2 || neighbours > 3)
					cur_state[0 * SIZE + j] = 0;
			}
		}

		MPI_Wait(&receive_bottom, NULL);

		for (int j = 0; j < SIZE; j++)
		{
			neighbours = 0;

			if (j == 0) // checking (SIZE-1 , 0)	(4)
			{
				// (height - 1) - number of rows in each process( -1 because we count from 0)
				neighbours += proc_states[iter][(height - 2) * SIZE + (SIZE - 1)];
				neighbours += proc_states[iter][(height - 2) * SIZE + j];
				neighbours += proc_states[iter][(height - 2) * SIZE + (j + 1)];
				neighbours += proc_states[iter][(height - 1) * SIZE + (SIZE - 1)];
				neighbours += proc_states[iter][(height - 1) * SIZE + (j + 1)];
				neighbours += bottom_line[SIZE - 1];
				neighbours += bottom_line[j];
				neighbours += bottom_line[j + 1];
			}
			else if (j == SIZE - 1)  // checking (SIZE-1, SIZE-1)	(5)
			{
				neighbours += proc_states[iter][(height - 2) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(height - 2) * SIZE + j];
				neighbours += proc_states[iter][(height - 2) * SIZE + 0];
				neighbours += proc_states[iter][(height - 1) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(height - 1) * SIZE + 0];
				neighbours += bottom_line[j - 1];
				neighbours += bottom_line[j];
				neighbours += bottom_line[0];
			}				  
			else // checking eveything between (SIZE-1, 0) and (SIZE-1, SIZE-1)		(6)
			{
				neighbours += proc_states[iter][(height - 2) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(height - 2) * SIZE + j];
				neighbours += proc_states[iter][(height - 2) * SIZE + (j + 1)];
				neighbours += proc_states[iter][(height - 1) * SIZE + (j - 1)];
				neighbours += proc_states[iter][(height - 1) * SIZE + (j + 1)];
				neighbours += bottom_line[j - 1];
				neighbours += bottom_line[j];
				neighbours += bottom_line[j + 1];
			}

			if (proc_states[iter][(height - 1) * SIZE + j] == 0)
			{
				if (neighbours == 3)
					cur_state[(height - 1) * SIZE + j] = 1;
			}
			else
			{
				if (neighbours < 2 || neighbours > 3)
					cur_state[(height - 1) * SIZE + j] = 0;
			}
		}

		MPI_Wait(&send_bottom, NULL);
		MPI_Wait(&send_top, NULL);

		for (int back_step = iter; back_step >= 0; back_step--)
		{
			flags[back_step] = 1;
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (cur_state[i * SIZE + j] != proc_states[back_step][i * SIZE + j])
					{
						flags[back_step] = 0;
						break;
					}
				}
				if (flags[back_step] == 0)
					break;
			}
		}

		MPI_Allreduce(flags, MPI_IN_PLACE, MAX_ITERATIONS, MPI_INT, MPI_LAND, MPI_COMM_WORLD);

		int check = 0;
		for (int i = 0; i < iter; i++)
		{
			if (flags[i] == 1)
			{
				check = 1;
				break;
			}
		}
		
		if (check == 1)
			break;
	}

	print(cur_state, SIZE);

	MPI_Finalize();
	return 0;
}
