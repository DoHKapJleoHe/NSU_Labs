#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<memory.h>
#include<math.h>
#include<omp.h>
#include<time.h>

void MatrixMultiplication(double* A, double* B, double* Resultat, int N)
{
    #pragma omp for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Resultat[i] += A[i * N + j] * B[j];
        }
    }
}

void MatrixSubtraction(double* A, double* B, double* Resultat, int N)
{
    #pragma omp for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Resultat[i] = A[i] - B[i];
        }
    }
}

void MatrixAddition(double* A, double* B, double* Resultat, int N)
{
    #pragma omp for
    for (int i = 0; i < N; i++)
    {
        Resultat[i] = A[i] + B[i];
    }
}

double Scalar(double* A, double* B, int size)
{
    double scal = 0;
    #pragma omp for reduction(+:scal)
    for (int i = 0; i < size; i++)
    {
        scal += A[i] * B[i];
    }

    return scal;
}

void clear(double* array, int N)
{
    #pragma omp for
    for (int i = 0; i < N; i++)
    {
        array[i] = 0;
    }
}

void print(double* array, int length)
{
    #pragma omp for
    for (int i = 0; i < length; i++)
    {
        printf("%lf ", array[i]);
    }
    printf("\n");
}

int main()
{
    
    printf("Starting programm....\n");
    int N = 10000;
    double e = 1e-5;

    double* A = (double*)malloc(N * N * sizeof(double));
    double* b = (double*)malloc(N * sizeof(double));
    double* u = (double*)malloc(N * sizeof(double));
    if (A == NULL || b == NULL || u == NULL)
        return -1;

    memset(b, 0, N * sizeof(double));
    for (int i = 0; i < N; i++)
    {
        b[i] = sin(i);
    }
    //////////Filled matrix A//////////
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                A[i * N + j] = sin(i) + N;
            }
            else
            {
                A[i * N + j] = cos(i + j);
            }
        }
    }
    
    double start_time = omp_get_wtime();

    double* x_prev = (double*)calloc(N, sizeof(double));
    double* x_next = (double*)calloc(N, sizeof(double));

    double* r_prev = (double*)calloc(N, sizeof(double));
    double* r_next = (double*)calloc(N, sizeof(double));

    double* z_prev = (double*)calloc(N, sizeof(double));
    double* z_next = (double*)calloc(N, sizeof(double));
    double alfa = 0;
    double betta = 0;

    double* Az_prev = (double*)calloc(N, sizeof(double));
    double* temp = (double*)malloc(N * sizeof(double));
    if (temp == NULL || Az_prev == NULL || z_prev == NULL || z_next == NULL || r_next == NULL || x_next == NULL || x_prev == NULL || r_prev == NULL)
        return 0;
    memset(temp, 0, N * sizeof(double));
    memset(r_prev, 0, N * sizeof(double));
    memset(z_prev, 0, N * sizeof(double));

    int count = 0;
    double check, check1;
    #pragma omp parallel num_threads(8)
    {
        ////////////initial values//////////////////////////////////////////////////////////////////
        MatrixMultiplication(A, x_prev, temp, N); // what, with what, to where, size of matrix
        MatrixSubtraction(b, temp, r_prev, N); // from what, what, to where, size of matrix
        memcpy(z_prev, r_prev, N * sizeof(double));
        ////////////////////////////////////////////////////////////////////////////////////////////

        bool ex = true;
        #pragma omp single
        check = 0;  //= CalcNorm(b, N) * e; 
        #pragma omp single       
        check1 = 0;
        #pragma omp for reduction(+:check)
        for (int i = 0; i < N; i++)
        {
            check += b[i] * b[i];
        }
        check = sqrt(check);

        while (ex)
        {
            count++;

            clear(z_next, N);
            clear(r_next, N);
            clear(x_next, N);

            //////////////Calculating Alfa//////////////
            clear(temp, N);
            MatrixMultiplication(A, z_prev, Az_prev, N);

            double r_prev_scalar = Scalar(r_prev, r_prev, N);
            /*printf("r_prev_scalar %lf", r_prev_scalar);*/
            double Az_prev_z_prev_scalar = Scalar(Az_prev, z_prev, N);
            alfa = r_prev_scalar / Az_prev_z_prev_scalar;
            /////////////////////////////////////////////////

            ///////////////Calculating x_next////////////////
            clear(temp, N);

            #pragma omp for
            for (int i = 0; i < N; i++)
            {
                temp[i] = z_prev[i] * alfa;
            }

            MatrixAddition(x_prev, temp, x_next, N);
            /////////////////////////////////////////////////

            ///////////////Calculating r_next////////////////
            clear(temp, N);

            #pragma omp for
            for (int i = 0; i < N; i++)
            {
                temp[i] = Az_prev[i] * alfa;
            }

            MatrixSubtraction(r_prev, temp, r_next, N);
            /////////////////////////////////////////////////

            //////////////Calculating Betta_next/////////////
            betta = Scalar(r_next, r_next, N) / Scalar(r_prev, r_prev, N);

            /////////////////////////////////////////////////

            ///////////////Calculating z_next////////////////
            memset(temp, 0, N * sizeof(double));

            #pragma omp for
            for (int i = 0; i < N; i++)
            {
                temp[i] = z_prev[i] * betta;
            }
            
            MatrixAddition(r_next, temp, z_next, N);
            /////////////////////////////////////////////////
            check1 = 0;
            #pragma omp for reduction(+:check1)
            for (int i = 0; i < N; i++)
            {
                check1 += r_next[i] * r_next[i];
            }
            check1 = sqrt(check1);
            if (check1 < check || count > 10)
            {
                ex = false;
            }
            else
            {
                #pragma omp for
                for (int i = 0; i < N; i++)
                {
                    z_prev[i] = z_next[i];
                    x_prev[i] = x_next[i];
                    r_prev[i] = r_next[i];
                }
            }

        }
    }
    double end_time = omp_get_wtime();

    printf("Result: \n");
    printf("Time: %lf \n", end_time - start_time);
    printf("Iterations count: %d\n", count);
   // print(x_next, N);

    free(A);
    free(b);
    free(Az_prev);
    free(x_next);
    free(x_prev);
    return 0;
}
