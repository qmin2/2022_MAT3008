#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include <time.h>
#define MAXIT 30

int i;
int sign(float n)
{
    if (n<0)
        return -1;
    else if (n==0)
        return 0;
    else
        return 1;
}
float muller(float p0, float p1, float p2, float xacc)
{
    void nrerror(char error_text[]);

    float res;
 
    for (i = 1; i<= MAXIT; i++)
    {
        float f0 = bessj0(p0);
        float f1 = bessj0(p1);
        float f2 = bessj0(p2);
        float d1 = f0 - f2;
        float d2 = f1 - f2;
        float h1 = p0 - p2;
        float h2 = p1 - p2;
        float h3 = p0 - p1;
        float c = f2;
        float b = (((d2*pow(h1, 2)) - (d1*pow(h2, 2)))
                    / (h1*h2*h3));
        float a = (((d1*h2) - (d2*h1))/(h1*h2*h3));
        float dx = ((-2*c) / (b + sign(b)*fabs(sqrt(b*b-4*a*c))));
 
        res = p2 + dx;
        if (fabs(dx) < xacc)
        {
            return res;
        }
            
        p0 = p1;
        p1 = p2;
        p2 = res;
    }
    nrerror("Maximum number of iterations exceeded in muller");
    return 0.0;
}



void newton_raphson(float x, float* f, float* df)
{
    *f = bessy0(x);
    *df = (-1) * bessy1(x);
    return;
}

void non_linear(float* xb1, float* xb2, int num_roots)
{
    double duration = 0;
    time_t start, end;

    for (int i = 1; i <= num_roots; i++)
    {
        start = clock();
        float roots = rtsafe(newton_raphson, xb1[i], xb2[i], 1e-6);
        end = clock();
        printf("Root%d = %f\n", i, roots);
        duration += (double)(end - start);
        // maximum iteration 출력 추가하기
    }
    printf("total_time %f\n", duration/CLOCKS_PER_SEC);
    printf("\n");

}

int main()
{
    float x1 = 1.0;
    float x2 = 10.0;
    int N = 100; // not mentioned ;;
    int num_roots = 10;
    float xb1[10];
    float xb2[10];
    zbrak(bessj0, x1, x2, N, xb1, xb2,&num_roots);

    printf("=====Muller=====\n");
    double duration = 0;
    time_t start, end;
    for (int i = 1; i <= num_roots; i++)
    {
        start = clock();
        float roots = muller(xb1[i], (xb1[i] + xb2[i]) / 2, xb2[i], 1e-6);
        end = clock();
        printf("Root%d = %f\n", i, roots);
        duration += (double)(end - start);
    }
    printf("num of iterations = %d\n", i);
    printf("total_time = %f\n", duration / CLOCKS_PER_SEC);

    printf("=====interesting nonlinear equation=====\n");
    num_roots = 10;
    zbrak(bessy0, x1, x2, N, xb1, xb2, &num_roots);
    non_linear(xb1, xb2, num_roots);
}