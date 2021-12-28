#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<xmmintrin.h>

typedef float v4sf __attribute__((vector_size(4 * sizeof(float))));

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
    v4sf* vector_B;
    v4sf* vector_transp_matrix;

    float znamenatel = max_summ_stolb * max_summ_stroky;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N/4; j++)
        {
            vector_B = (v4sf*)&B[i * N + j*4];
	    vector_transp_matrix = (v4sf*)&transp_matrix[i * N + j * 4];
            *vector_B = *vector_transp_matrix / znamenatel;
        }
    }
}

void multiply_matrix(float* A, float* B, float* C, int N)
{  
   memset(C, 0, N * N * sizeof(float));
   v4sf* vector_B;
   v4sf* vector_C;

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++) 
        {
            for (int j = 0; j < N/4; j++) 
            {
		vector_B = (v4sf*)&B[k * N + j * 4]; // ў ¤ ­­л© ўҐЄв®а п Є« ¤г гЄ § вҐ«м ­  пзҐ©Єг Ї ¬пвЁ, ®вЄг¤  Ўг¤Ґв Ўа вмбп 4 §­ зҐ­Ёп ¬ ббЁў 
		vector_C = (v4sf*)&C[i * N + j * 4];
                *vector_C += A[i * N + k] * (*vector_B);
            }
        }
    }
}

void calc_razlojenie(float* ed_matrix, float* R, float* R_v_stepeni, float* A_obratnoe, int N, int M)
{
    v4sf* vector_ed_matrix;
    v4sf* vector_A_obratnoe;
    v4sf* vector_R;
    v4sf* vector_R_v_stepeni;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N/4; j++)
        {
            vector_A_obratnoe = (v4sf*)&A_obratnoe[i * N + j*4];
            vector_R = (v4sf*)&R[i * N + j*4];
            vector_ed_matrix = (v4sf*)&ed_matrix[i * N + j*4];
            *vector_A_obratnoe = *vector_ed_matrix + *vector_R;
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

        for (int i = 0; i < N; i++) // Є®ЇЁаго ў вҐ¬Ї в®, зв® Ўл«® ў а_ў_бвҐЇҐ­Ё
        {
            for (int j = 0; j < N; j++)
            {
                temp[i * N + j] = R_v_stepeni[i * N + j];
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N/4; j++)
            {
               vector_A_obratnoe = (v4sf*)&A_obratnoe[i * N + j*4];
               vector_R_v_stepeni = (v4sf*)&R_v_stepeni[i * N + j*4];
               *vector_A_obratnoe += *vector_R_v_stepeni;
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

    for (int i = 0; i < N * N; i++)
    {
        matrix[i] = (i+1) % 5; /* ЎҐаг ®бв в®Є ®в ¤Ґ«Ґ­Ёп, зв®Ўл ®ЇаҐ¤Ґ«ЁвҐ«м ¬ ваЁжл ­Ґ Ўл« а ўҐ­ ­г«о*/
    }

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

    /*calculating R....*/

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

    /*####################################################*/

    float* A_obratnoe = (float*)malloc(N * N * sizeof(float));
    float* R_v_stepeni = (float*)malloc(N * N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            R_v_stepeni[i * N + j] = R[i * N + j];
        }
    }
    calc_razlojenie(ed_matrix, R, R_v_stepeni, A_obratnoe, N, M);

    float* temp_1 = (float*)malloc(N * N * sizeof(float));
    multiply_matrix(A_obratnoe, B, temp_1, N);
    //print_matrix(temp_1, N);
    free(temp_1);
    free(matrix);
    free(ed_matrix);
    free(transp_matrix);
    free(A_obratnoe);
    free(R);
    free(R_v_stepeni);
}
