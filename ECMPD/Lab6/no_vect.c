#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>



void print_matrix(float* matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f ", matrix[i * N + j]);
        }
        printf("\n");
    }
}


void trans_matrix(float* matrix, int N, float* transp_matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            transp_matrix[j * N + i] = matrix[i * N + j];
        }
    }
}

float calc_max_summ_stolb(float* matrix, int N)
{
    float max = 0;
    float current_max = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            current_max += abs(matrix[j * N + i]);
        }
        if (current_max > max)
            max = current_max;
        current_max = 0;
    }
    return max;
}

float calc_max_summ_stroky(float* matrix, int N)
{
    float max = 0;
    float current_max = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            current_max += abs(matrix[i * N + j]);
        }
        if (current_max > max)
            max = current_max;
        current_max = 0;
    }
    return max;
}

void calc_B(float* B, float* transp_matrix, float max_summ_stolb, float max_summ_stroky, int N)
{
    float proisvedenie = max_summ_stolb * max_summ_stroky;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i * N + j] = transp_matrix[i * N + j] / proisvedenie;
        }
    }
}

void multiply_matrix(float* A, float* B, float* transp_matrix, int N)
{
    memset(transp_matrix, 0, N * N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            for (int k = 0; k < N; k++) 
            {
                transp_matrix[i * N + k] += (A[i * N + j] * B[j * N + k]);
            }
        }
    }
}

void calc_razlojenie(float* ed_matrix, float* R, float* R_v_stepeni, float* A_obratnoe, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A_obratnoe[i * N + j] = ed_matrix[i * N + j] + R[i * N + j];
        }
    }

    float* temp = (float*)malloc(N * N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp[i * N + j] = R[i * N + j];
        }
    }

    while (M > 1)
    {
        memset(R_v_stepeni, 0, N * N * sizeof(float));
        multiply_matrix(R, temp, R_v_stepeni, N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                temp[i * N + j] = R_v_stepeni[i * N + j];
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
               A_obratnoe[i * N + j] += R_v_stepeni[i * N + j];
            }
        }
        M--;
    }
   
    free(temp);
}

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    float* matrix = (float*)malloc(N * N * sizeof(float));
    float kekw = 0;

    for (int i = 0; i < N * N; i++)
    {
        matrix[i] = (i+1) % 5;
    }

   /* printf("First Matrix \n");
    print_matrix(matrix, N);
    printf("\n");*/

    float* ed_matrix = (float*)malloc(N * N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == i)
            {
                ed_matrix[i * N + j] = 1;
            }
            else
            {
                ed_matrix[i * N + j] = 0;
            }
        }
    }

    float* transp_matrix = (float*)malloc(N * N * sizeof(float));
    trans_matrix(matrix, N, transp_matrix);

    float max_summ_stolb = 0;
    float max_summ_stroky = 0;

    max_summ_stolb = calc_max_summ_stolb(matrix, N);
    max_summ_stroky = calc_max_summ_stroky(matrix, N);

    float* B = (float*)malloc(N * N * sizeof(float));
    calc_B(B ,transp_matrix, max_summ_stolb, max_summ_stroky, N);

    /*calculating R...... /./\( .. . .. )/\.\  */

    /* i will reuse trans_matrix cause it is not used now */
    memset(transp_matrix, 0, N * N * sizeof(float));
    multiply_matrix(B, matrix, transp_matrix, N);

    float* R = (float*)malloc(N * N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            R[i * N + j] = ed_matrix[i * N + j] - transp_matrix[i * N + j];
        }
    }

    float* A_obratnoe = (float*)malloc(N * N * sizeof(float));
    float* R_v_stepeni = (float*)malloc(N * N * sizeof(float));

    calc_razlojenie(ed_matrix, R, R_v_stepeni, A_obratnoe, N, M);
    float* temp_1 = (float*)malloc(N * N * sizeof(float));
    multiply_matrix(A_obratnoe, B, temp_1, N);
    print_matrix(temp_1, N);
    free(temp_1);
    free(matrix);
    free(ed_matrix);
    free(transp_matrix);
    free(A_obratnoe);
    free(R);
    free(R_v_stepeni);
}
