#include <stdio.h>
#include <stdlib.h>

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

	printf("\n");
}


int main()
{
	int** all_states = (int**)malloc(MAX_ITERATIONS * sizeof(int*));
	int* cur_state = (int*)malloc(SIZE * SIZE * sizeof(int));
	if (all_states == NULL || cur_state == NULL) 
	{
		printf("No heap for you cumlord\n");
		return 0;
	}
	
	//Making first state called "Glider"
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		cur_state[i] = 0;
	}

	/*
			0 1 0 0 0
			0 0 1 0 0
			1 1 1 0 0
			0 0 0 0 0
			0 0 0 0 0
	*/

	cur_state[0 * SIZE + 1] = 1;
	cur_state[1 * SIZE + 2] = 1;
	cur_state[2 * SIZE + 0] = 1;
	cur_state[2 * SIZE + 1] = 1;
	cur_state[2 * SIZE + 2] = 1;
	
	print(cur_state, SIZE);
	
	for (int iter = 0; iter < MAX_ITERATIONS; iter++)
	{
		all_states[iter] = cur_state; // put the pointer to the curent state in all_states(saved it) 
		cur_state = (int*)malloc(SIZE * SIZE * sizeof(int));
		if (cur_state == NULL)
		{
			printf("No heap for you shitfuck\n");
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

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				int neighbours = 0;

				if (i == 0) // checking first row
				{
					if (j == 0) // checking (0, 0)    (1)
					{
						neighbours += all_states[iter][(SIZE - 1) * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + 0];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][i * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][i * SIZE + (j + 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + j];
						neighbours += all_states[iter][(i + 1) * SIZE + (j + 1)];
					}
					else if (j == SIZE - 1)  // checking (0, SIZE-1)  (2)
					{
						neighbours += all_states[iter][(SIZE - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + j];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + 0];
						neighbours += all_states[iter][i * SIZE + (j - 1)];
						neighbours += all_states[iter][i * SIZE + 0];
						neighbours += all_states[iter][(i + 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + j];
						neighbours += all_states[iter][(i + 1) * SIZE + 0];

					}
					else // checking eveything between (0, 0) and (0, SIZE-1)  (3)
					{
						neighbours += all_states[iter][(SIZE - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + j];
						neighbours += all_states[iter][(SIZE - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][i * SIZE + (j - 1)];
						neighbours += all_states[iter][i * SIZE + (j + 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + j];
						neighbours += all_states[iter][(i + 1) * SIZE + (j + 1)];
					}
				}
				else if (i == SIZE-1) // checking the last row
				{
					if (j == 0) // checking (SIZE-1 , 0)	(4)
					{
						neighbours += all_states[iter][(i - 1) * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][(i - 1) * SIZE + j];
						neighbours += all_states[iter][(i - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][i * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][i * SIZE + (j + 1)];
						neighbours += all_states[iter][0 * SIZE + (SIZE - 1)];
						neighbours += all_states[iter][0 * SIZE + j];
						neighbours += all_states[iter][0 * SIZE + (j + 1)];
					}
					else if (j == SIZE - 1)  // checking (SIZE-1, SIZE-1)	(5)
					{
						neighbours += all_states[iter][(i - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i - 1) * SIZE + j];
						neighbours += all_states[iter][(i - 1) * SIZE + 0];
						neighbours += all_states[iter][i * SIZE + (j - 1)];
						neighbours += all_states[iter][i * SIZE + 0];
						neighbours += all_states[iter][0 * SIZE + (j - 1)];
						neighbours += all_states[iter][0 * SIZE + j];
						neighbours += all_states[iter][0 * SIZE + 0];
					}
					else // checking eveything between (SIZE-1, 0) and (SIZE-1, SIZE-1)		(6)
					{
						neighbours += all_states[iter][(i - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i - 1) * SIZE + j];
						neighbours += all_states[iter][(i - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][i * SIZE + (j - 1)];
						neighbours += all_states[iter][i * SIZE + (j + 1)];
						neighbours += all_states[iter][0 * SIZE + (j - 1)];
						neighbours += all_states[iter][0 * SIZE + j];
						neighbours += all_states[iter][0 * SIZE + (j + 1)];
					}
				}
				else // checking everything else
				{
					if (j == 0) // checking everything between (0, 0) and (SIZE-1, 0)	(7)
					{
						neighbours += all_states[iter][(i - 1) * SIZE + (SIZE - 1)]; //here we have periodicity
						neighbours += all_states[iter][(i - 1) * SIZE + j];
						neighbours += all_states[iter][(i - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][i * SIZE + (SIZE - 1)]; // here we have periodicity
						neighbours += all_states[iter][i * SIZE + (j + 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + (SIZE - 1)]; // here we have periodicity
						neighbours += all_states[iter][(i + 1) * SIZE + j]; 
						neighbours += all_states[iter][(i + 1) * SIZE + (j + 1)];
					}
					else if (j == SIZE - 1)  // checking everything between (0, SIZE-1) and (SIZE-1, SIZE-1)	(8)
					{
						neighbours += all_states[iter][(i - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i - 1) * SIZE +       j];
						neighbours += all_states[iter][(i - 1) * SIZE +		  0];
						neighbours += all_states[iter][ i      * SIZE + (j - 1)];
						neighbours += all_states[iter][ i      * SIZE +		  0];
						neighbours += all_states[iter][(i + 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i + 1) * SIZE +       j];
						neighbours += all_states[iter][(i + 1) * SIZE +		  0];
					}
					else // checking eveything in the center of the matrix	(9)
					{
						// counting bumber of alive neighbours by adding its value to "neighbours"
						neighbours += all_states[iter][(i - 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i - 1) * SIZE +  j     ];
						neighbours += all_states[iter][(i - 1) * SIZE + (j + 1)];
						neighbours += all_states[iter][ i	   * SIZE + (j - 1)];
						neighbours += all_states[iter][ i      * SIZE + (j + 1)];
						neighbours += all_states[iter][(i + 1) * SIZE + (j - 1)];
						neighbours += all_states[iter][(i + 1) * SIZE +  j     ];
						neighbours += all_states[iter][(i + 1) * SIZE + (j + 1)];
						
					}
				}


				if (all_states[iter][i * SIZE + j] == 0)
				{
					if (neighbours == 3)
						cur_state[i * SIZE + j] = 1;
				}
				else
				{
					if (neighbours >= 2 && neighbours <= 3)
						cur_state[i * SIZE + j] = 1;
				}
			}
		}

		print(cur_state, SIZE);

		int check = 1;

		for (int back_step = iter; back_step >= 0; back_step--)
		{
			check = 0;

			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (cur_state[i * SIZE + j] != all_states[back_step][i * SIZE + j])
					{
						check = 1;
						break;
					}
				}
				if (check == 1)
					break;
			}
			if (check == 0)
				break;
		}
		if (check == 0)
			break;
	}

	return 0;
}
