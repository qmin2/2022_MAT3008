#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include "../../NRs/ansi/other/nrutil.h"
#include <time.h>

void q1(int n, float **A, float *b) //n = dimension   gauss-jordan
{
    float **temp_A = calloc(n + 1, sizeof(float *));
    for (int i = 1; i <= n; i++) {
        temp_A[i] = calloc(n + 1, sizeof(float));
        memcpy(temp_A[i], A[i], (n + 1) * sizeof(float));
    }
    float **temp_b = calloc(n + 1, sizeof(float *));
    for (int i = 1; i <= n; i++) {
        temp_b[i] = calloc(n + 1, sizeof(float));
        temp_b[i][1] = b[i];
    }
    
    gaussj(temp_A, n, temp_b, 1);
    for (int i = 1; i <= n; i++){
        printf("%f ", temp_b[i][1]);
    }
    printf("\n");
    

    //free
    for (int i = 1; i <= n; i++)
        free(temp_A[i]);
    free(temp_A);
    for (int i = 1; i <= n; i++)
        free(temp_b[i]);
    free(temp_b);

    return;
}

void q2(int n, float **A, float *b) // LU decomposition
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
    int *indx = calloc(n + 1, sizeof(int));
    ludcmp(temp_A, n, indx, &d);
    lubksb(temp_A, n, indx, temp_b);

    for (int i = 1; i <= n;  i++)
        printf("%f ", temp_b[i]);
    
    printf("\n");

    //free
    for (int i = 1; i <= n; i++)
        free(temp_A[i]);
    free(temp_A);
    free(temp_b);

    return;
}

void q3(int N, float **A, float *b, float *sol){
    //make space
    int M = 1;
    float **temp_A = calloc(N+1, sizeof(float*));
    for (int i = 1; i <= N ; i++){
        temp_A[i] = calloc(N+1, sizeof(float*));
        memcpy(temp_A[i], A[i], (N+1)*sizeof(float));
    }
    float **V = calloc(N+1, sizeof(float*));
    for (int i =1; i<=N ; i++){
        V[i] = calloc(N+1, sizeof(float));
    }

    sol = calloc(N + 1, sizeof(float));
    float *w;
    w = calloc(N + 1, sizeof(float));

    svdcmp(temp_A, N, N, w, V);

    float *temp = calloc(N+1, sizeof(float*));
    for (int i=1; i<=N; i++){
        temp[i] = 0.0;
        for(int j=1; j<=N; j++){
            temp[i] += temp_A[j][i]*b[j];
        }
        temp[i] = temp[i]*(1/w[i]);
    }
    
    for (int i=1; i<=N; i++){
        sol[i] = 0;
        for (int j=1; j<=N; j++){
            sol[i] += V[i][j]*temp[j];
        }
        printf("%f ",sol[i]);
    }
    printf("\n");


    // free
    for (int i = 1; i<=N; i++){
        free(temp_A[i]);
    }
    free(temp_A);
    free(temp);   
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

    // solve problem 1
    printf("########## Using Gauss-Jordan Elimination ##########\n");
    // printf("Answers for A1\n");
    //q1(4, A1, b1);  //A1 is singular
    printf("Answers for A2\n");

    double duration = 0;
    time_t start, end;


    start = clock();
    q1(5, A2, b2);
    printf("Answers for A3\n");
    q1(6, A3, b3);
    end = clock();
    duration += (double)(end - start);
    printf("total_time %f\n", duration/CLOCKS_PER_SEC);
    printf("\n");

    // solve problem 2
    printf("########## Using LU decomposition ##########\n");
    printf("Answers for A1\n");
    q2(4, A1, b1);
    printf("Answers for A2\n");

    duration = 0;
    start = clock();
    q2(5, A2, b2);
    printf("Answers for A3\n");
    q2(6, A3, b3);
    end = clock();
    duration += (double)(end - start);
    printf("total_time %f\n", duration/CLOCKS_PER_SEC);
    printf("\n");


    // solve qeustion3
    float *sol;
    printf("########## Using svd ##########\n");
    printf("Answers for A1\n");
    q3(4, A1, b1, sol);
    printf("Answers for A2\n");
    duration = 0;
    start = clock();
    q3(5, A2, b2, sol);
    printf("Answers for A3\n");
    q3(6, A3, b3, sol);
    end = clock();
    duration += (double)(end - start);
    printf("total_time %f\n", duration/CLOCKS_PER_SEC);
    printf("\n");
    


    return 0;
}