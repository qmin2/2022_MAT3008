#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include <time.h>

void inv_matrix(int N, float **A)
{
    float **temp_A = calloc(N+1, sizeof(float *));
    for (int i = 1; i<=N; i++) {
        temp_A[i] = calloc(N+1, sizeof(float));
        memcpy(temp_A[i], A[i], (N+1) * sizeof(float));
    }
    float **inv_A = calloc(N+1, sizeof(float *));
    for (int i = 1; i<=N; i++) {
        inv_A[i] = calloc(N+1, sizeof(float));
    }
    float d;
    int *indx = calloc(N+1, sizeof(int));
    float *col = calloc(N+1, sizeof(float));

    ludcmp(temp_A, N, indx, &d);

    for (int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            col[j]=0.0;
        }
        col[i]=1.0;
        lubksb(temp_A, N, indx, col);
        for (int j=1;j<=N;j++){
            inv_A[j][i] = col[j];
        }
    }

    printf("inverse matrix\n");
    for (int i = 1; i <= N; i++)
    {
        for(int j=1; j<=N; j++){
            printf("%f\t",inv_A[i][j]);
        }
        printf("\n");
    }

    printf("determinant\n");
    float det = 1;
    for (int j = 1; j <= N; j++)
        det *= temp_A[j][j];
    printf("%f\n", det*d);

    
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
    printf("Answers for A1\n");
    inv_matrix(4, A1);
    printf("Answers for A2\n");
    inv_matrix(5, A2);
    printf("Answers for A3\n");
    inv_matrix(6, A3);

    return 0;
}