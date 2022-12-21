#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include "../../NRs/ansi/other/nrutil.h"
#include <time.h>

#include <string.h>
#include <stdlib.h>


void read_data(int num, float (*input1)[3], float (*output1)[1], float (*output2)[1], char* name){
    FILE *fp;
    fp = fopen(name, "r");
    for (int i = 0; i < 77; i++)
            fscanf(fp, "%f %f %f %f ", &input1[i][0], &input1[i][1], &output1[i][0], &output2[i][0]);
    fclose(fp);
}

void gaussj(float **a, int n, float **b, int m);

void fitting(float (*X)[3], float (*y)[1])
{

    float **X_t_mul_X = calloc(3 + 1, sizeof(float *));
    for (int i = 0; i <= 3; i++) {
        X_t_mul_X[i] = calloc(3 + 1, sizeof(float));
    }
    float **X_t_mul_y = calloc(3 + 1, sizeof(float *));
    for (int i = 0; i <= 3; i++) {
        X_t_mul_y[i] = calloc(3 + 1, sizeof(float));
    }

    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++){
            X_t_mul_X[i][j] = 0;
			for(int k = 0; k < 77; k++)
				X_t_mul_X[i][j] += X[k][i-1] * X[k][j-1];
        }
    
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 1; j++){
            X_t_mul_y[i][j] = 0;
		    for(int k = 0; k < 77; k++)
			    X_t_mul_y[i][j] += X[k][i-1] * y[k][j-1];
        }

    gaussj(X_t_mul_X, 3, X_t_mul_y, 1);

    for (int i = 1; i <= 3; i++)
        {
            printf("%f ", X_t_mul_y[i][1]);
            printf("\n");
        }

    //free
    for (int i = 1; i <= 3; i++)
        free(X_t_mul_X[i]);
    free(X_t_mul_X);
    for (int i = 1; i <= 3; i++)
        free(X_t_mul_y[i]);
    free(X_t_mul_y);
}


int main() {
    float input1[77][3];  // x   절편을 한번에 처리
    float input1_tp[3][77];

    float output1[77][1];  // y
    float output2[77][1];  // y
    for (int i = 0; i < 77; i++)
    {
        input1[i][2] = 1;
    }

    printf("=============fitdata1=============\n");
    read_data(77, input1, output1, output2, "fitdata/fitdata1.dat");
    fitting(input1, output1);
    fitting(input1, output2);

    printf("=============fitdata2=============\n");
    read_data(77, input1, output1, output2, "fitdata/fitdata2.dat");
    fitting(input1, output1);
    fitting(input1, output2);

    printf("=============fitdata3=============\n");
    read_data(77, input1, output1, output2, "fitdata/fitdata3.dat");
    fitting(input1, output1);
    fitting(input1, output2);

    return 0;
}