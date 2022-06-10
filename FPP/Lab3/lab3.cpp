#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

void print(double* matrix, int rows, int cols) 
{
    for (int i = 0; i < rows; i++)
    {
	    for (int j = 0; j < cols; j++) 
	    {
	      printf("%lf ", matrix[i * cols + j]);
	    }
	    printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int rank, number;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number);

    // size of lattice
    int p1 = 2,
      	p2 = 4;

    int ndims = 2; // dimension of topology
    int dims[2] = {p1, p2}; // number of processes on each coordinate
    int periods[2] = {0, 0}; // periodicity of topology. it means that ends of each sequences of proceses(computers) are not neighbours
    int reorder = 0; // ranks are similar to ranks from COMM_WORLD
    MPI_Comm new_topology_comm; // communicator of new topology
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &new_topology_comm);

    int n1 = 4000, n2 = 4000, n3 = 4000; // matrix dimensions

    double* A = NULL;
    double* B = NULL;
    double* C = NULL;

    int coords[2]; //coordinates of process in new topology
    MPI_Comm_rank(new_topology_comm, &rank);
    MPI_Cart_coords(new_topology_comm, rank, ndims, coords);
    if(coords[0] == 0 && coords[1] == 0)
    {
    	A = (double*)malloc(n1 * n2 * sizeof(double)); // n1 - rows, n2 - columns
	    B = (double*)malloc(n2 * n3 * sizeof(double));
	    C = (double*)malloc(n1 * n3 * sizeof(double));

	for (int i = 0; i < n1; i++)
	{
	    for (int j = 0; j < n2; j++)
	    {
		    A[i * n2 + j] = sin(i) + cos(j);
	    }
	}

	for (int i = 0; i < n2; i++)
	{
	    for (int j = 0; j < n3; j++)
	    {
		    B[i * n3 + j] = sin(i + j);
	    }
	}
    }
    
    start = MPI_Wtime();
    
    MPI_Comm col, row; // communicators for rows and columns of new topology
    int remain_dims[2] = {0, 1};
    MPI_Cart_sub(new_topology_comm, remain_dims, &row);// create rows
    remain_dims[0] = 1;
    remain_dims[1] = 0;
    MPI_Cart_sub(new_topology_comm, remain_dims, &col);// create columns

    int part_A = n1 / p1,
      	part_B = n3 / p2;

    double* A_part = (double*)malloc(part_A * n2 * sizeof(double));
    double* B_part = (double*)malloc(part_B * n2 * sizeof(double));
    double* C_part = (double*)malloc(part_B * part_A * sizeof(double));

    //scattering A_part to processes of first column of topology
    if (coords[1] == 0)
    {
	    MPI_Scatter(A, part_A, MPI_DOUBLE, A_part, part_A, MPI_DOUBLE, 0, col); // distributing A by columns
    }

    //from each row of of row-communicator we call bcast to copy A_part to other processes in rows
    //  * --> + --> +
    //  * --> + --> +
    //  * --> + --> +

    MPI_Bcast(A_part, part_A * n2, MPI_DOUBLE, 0, row); // not sure about second argument

    /*
	    |........|........|........| - usual double in memory

	    MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype old_type, MPI_Datatype* new_type);


	    |-DOUBLE-|-DOUBLE-|   |-DOUBLE-|-DOUBLE-|	|-DOUBLE-|-DOUBLE-|

	    |........|........|...|........|........|...|........|........|... count = 3, blocklength = 2, stride = "depends of task"

	    |---blockLegth----|
	    |-------stride--------|
    */

    MPI_Datatype B_column;
    MPI_Type_vector(n2, 1, n3, MPI_DOUBLE, &B_column);
    MPI_Type_commit(&B_column);
    /*
	    When we create a buffer, we actually create a pointer to a memory cell from which memory was allocated
	    and when we want to get each element of buffer we jump in memory from pointer + <datatype> * <number of element in buffer>.
	    I created a datatype that helps to jump from one vertice of matrix to another: if we have 3x3 matrix then this datatype will 
	    shift pointer to +0 +3 +6 +9. But there is a problem: with this datatype scatter will think that next column will be after the 
	    the end of first column and it's not right. I want scatter to think that next vertice of column goes right after vertice of first column.
	    Thats why i need to use MPI_Type_create_resized();
    */

    MPI_Datatype B_column_resized;
    MPI_Type_create_resized(B_column, 0, sizeof(double), &B_column_resized); // in fact third argumnt defines offset betwin vertices of columns
    MPI_Type_commit(&B_column_resized);

    /*
	    Now i need to create another datatype, but for part of matrix because in part we have another length betwin vertices of columns
    */

    MPI_Datatype B_part_column, B_part_column_resized;
    MPI_Type_vector(n2, 1, part_B, MPI_DOUBLE, &B_part_column);
    MPI_Type_commit(&B_part_column);

    MPI_Type_create_resized(B_part_column, 0, sizeof(double), &B_part_column_resized);
    MPI_Type_commit(&B_part_column_resized);


    if (coords[0] == 0)
	    MPI_Scatter(B, part_B, B_column_resized, B_part, part_B, B_part_column_resized, 0, row);

    MPI_Bcast(B_part, part_B * n2, B_part_column_resized, 0, col); // not sure about second argument

    // Multiplying parts of A and B matrices
    for (int i = 0; i < part_A; i++)
    {
	    for (int j = 0; j < n2; j++)
	    {
	      for (int k = 0; k < part_B; k++)
	      {
		      C_part[i * part_A  + k] += A_part[i * n2 + j] * B_part[j * part_B + k];
	      }
    	}
    }

    MPI_Datatype result;
    MPI_Type_vector(part_A, part_B, n3, MPI_DOUBLE, &result);
    MPI_Type_commit(&result);

    MPI_Datatype result_resized;
    MPI_Type_create_resized(result, 0, part_B * sizeof(double), &result_resized);
    MPI_Type_commit(&result_resized);

    // now i need to gather parts
    int num[p1 * p2], displs[p1 * p2];
    for (int i = 0; i < p1; i++) 
    {
	    for (int j = 0; j < p2; j++)
	    {
	      num[i * p2 + j] = 1;
	      displs[i * p2 + j] = i * p2 * part_A + j;
	    }
    }

    MPI_Gatherv(C_part, part_A * part_B, MPI_DOUBLE, C, num, displs, MPI_DOUBLE, 0, new_topology_comm);
    end = MPI_Wtime();

    if (rank == 0) 
    {
	    printf("RESULT\n");
	    print(C, n1, n3);
    }
    
    printf("Time: %lf\n", end - start);

    if (rank == 0) 
    {
	    printf("Time");
	    printf("%lf\n", end-start);
    }

    if (rank == 0) 
    {
	    free(A);
	    free(B);
	    free(C);
    }
  
    free(A_part);
    free(B_part);
    free(C_part);

    MPI_Type_free(&B_column);
    MPI_Type_free(&B_column_resized);
    MPI_Type_free(&result_resized);
    MPI_Type_free(&B_part_column);
    MPI_Type_free(&B_part_column_resized);
    MPI_Type_free(&result);

    MPI_Finalize();
    return 0;
}
