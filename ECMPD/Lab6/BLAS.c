#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#ifdef __INTEL_COMPILER
  #include<mkl_cblas.h>
#else
  #include<cblas.h>
#endif


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


void trans_matrix(float* matrix, int N, float* transp_matrix, float* ed_matrix)
{
 cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, matrix, N, ed_matrix, N, 0.0, transp_matrix, N);;
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

void calc_B(float* B, float* transp_matrix,float* ed_matrix, float max_summ_stolb, float max_summ_stroky, int N)
{
    float proisvedenie = max_summ_stolb * max_summ_stroky;

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0 / proisvedenie, transp_matrix, N, ed_matrix, N, 0.0, B, N);
}

void calc_razlojenie(float* ed_matrix, float* R, float* R_v_stepeni, float* A_obratnoe, int N, int M)
{
    // Є« ¤г ў A_obratnoe бг¬¬г ¬ ваЁжл ed_matrix Ё ¬ ваЁжл R
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, ed_matrix, N, ed_matrix, N, 0.0, A_obratnoe, N);  // added ed_matrix to A_obratnoe
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R, N, ed_matrix, N, 1.0, A_obratnoe, N); // added R to A_obratnoe 
    ////////////////////////////////////////////////////////

    float* temp = (float*)malloc(N * N * sizeof(float));
    // Є®ЇЁаго ў temp ¬ ваЁжг R
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R, N, ed_matrix, N, 0.0, temp, N); ; 
    /////////////////////////// 

    while (M > 1)
    {
        memset(R_v_stepeni, 0, N * N * sizeof(float));
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R, N, temp, N, 1.0, R_v_stepeni, N); // ЇҐаҐ¬­®¦ о R Ё temp Ё Є« ¤г ў R_v_stepeni
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R_v_stepeni, N, ed_matrix, N, 0, temp, N); // Є®ЇЁаго ў temp R_v_stepeni
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R_v_stepeni, N, ed_matrix, N, 1.0, A_obratnoe, N);
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
    trans_matrix(matrix, N, transp_matrix, ed_matrix);

    float max_summ_stolb = 0;
    float max_summ_stroky = 0;

    max_summ_stolb = calc_max_summ_stolb(matrix, N);
    max_summ_stroky = calc_max_summ_stroky(matrix, N);

    float* B = (float*)malloc(N * N * sizeof(float));
    calc_B(B ,transp_matrix, ed_matrix, max_summ_stolb, max_summ_stroky, N);

    /*calculating R...... /./\( .. . .. )/\.\  */

    /* i will reuse trans_matrix cause it is not used now */
    memset(transp_matrix, 0, N * N * sizeof(float));
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, B, N, matrix, N, 0.0, transp_matrix, N);

    float* R = (float*)malloc(N * N * sizeof(float));
    memset(R, 0, N * N * sizeof(float));               
    //Є« ¤г ў R а §­®бвм ¬Ґ¦¤г ¬ ваЁж ¬Ё ed_matrix Ё  transp_matrix 
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, ed_matrix, N, ed_matrix, N, 1.0, R, N);  // Є« ¤г ў R Ґ¤Ё­Ёз­го ¬ ваЁжг
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, -1.0, transp_matrix, N, ed_matrix, N, 1.0, R, N);
    /*####################################################*/

    float* A_obratnoe = (float*)malloc(N * N * sizeof(float));
    float* R_v_stepeni = (float*)malloc(N * N * sizeof(float));
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, R, N, ed_matrix, N, 0.0, R_v_stepeni, N);

    calc_razlojenie(ed_matrix, R, R_v_stepeni, A_obratnoe, N, M);  

    float* temp_1 = (float*)malloc(N * N * sizeof(float));
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, A_obratnoe, N, B, N, 0.0, temp_1, N);
    //print_matrix(temp_1, N);
    free(temp_1);
    free(matrix);
    free(ed_matrix);
    free(transp_matrix);
    free(A_obratnoe);
    free(R);
    free(R_v_stepeni);
}
