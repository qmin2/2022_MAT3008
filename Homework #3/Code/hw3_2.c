#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include <time.h>

void iter_improve(int n, float **A, float *b)
{
    float **temp_A = calloc(n + 1, sizeof(float *));
    for (int i = 1; i <= n; i++) {
        temp_A[i] = calloc(n + 1, sizeof(float));
        memcpy(temp_A[i], A[i], (n + 1) * sizeof(float));
    }
    float *temp_b = calloc(n + 1, sizeof(float));
    for (int i = 1; i <= n; i++) {
        temp_b[i] = b[i];
    }
    float d;
    int *indx = calloc(n + 1, sizeof(int *));
    ludcmp(temp_A, n, indx, &d);
    lubksb(temp_A, n, indx, temp_b);
    for (int i = 1; i <= n;  i++)
        printf("%.25f ", temp_b[i]);
    printf("\n");
    printf("Is it improved?? \n");

    for (int i = 0; i < 5; i++){
        mprove(A, temp_A, n, indx, b, temp_b);
        for (int i = 1; i <= n;  i++)
            printf("%.25f ", temp_b[i]);
        printf("\n");
    }
   
    printf("\n");


    //free
    for (int i = 1; i <= n; i++)
        free(temp_A[i]);
    free(temp_A);
    free(temp_b);

    return;

}

void read_matrix(FILE *fp, float **A, float *b)
{
    int N, M;  // n x m matrix
    fscanf(fp, "%d %d", &N, &M);
    
    // 첫번째 원소 위치를 (1,1)로 표기 위함. 
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            fscanf(fp, "%f", &A[i][j]);
            
    for (int i = 1; i <= N; i++)
        fscanf(fp, "%f", &b[i]);  //&b[i] 아 scanf니까 주솟값이다,, ㅋ
    return;
}
int main()
{
    float **A1, **A2, **A3;
    float *b1, *b2, *b3;

    A1 = calloc(5, sizeof(float *));
    for (int i = 1; i <= 4; i++)
        A1[i] = calloc(5, sizeof(float));
    A2 = calloc(6, sizeof(float *));
    for (int i = 1; i <= 5; i++)
        A2[i] = calloc(6, sizeof(float));
    A3 = calloc(7, sizeof(float *));
    for (int i = 1; i <= 6; i++)
        A3[i] = calloc(7, sizeof(float));
    b1 = calloc(5, sizeof(float *));
    b2 = calloc(6, sizeof(float *));
    b3 = calloc(7, sizeof(float *));
    
    // read the matrix, define A1, A2, A3, b1, b2, b3
    FILE *fp1, *fp2, *fp3;

    fp1 = fopen("../lineq_dat/lineq1.dat", "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", "lineq1.data");
    }
    fp2 = fopen("../lineq_dat/lineq2.dat", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", "lineq2.data");
    }
    fp3 = fopen("../lineq_dat/lineq3.dat", "r");
    if (fp3 == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", "lineq3.data");
    }
    
    read_matrix(fp1, A1, b1);
    read_matrix(fp2, A2, b2);
    read_matrix(fp3, A3, b3);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    //iter_improve(4, A1, b1);
    iter_improve(5, A2, b2); // 왜 cycle이지?
    printf("=======\n");
    iter_improve(6, A3, b3);

    return 0;
}