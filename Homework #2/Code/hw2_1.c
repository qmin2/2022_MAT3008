#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include <time.h>

void succint_codes(float (*func)(float (*bessel)(float), float, float, float), 
float (*bessel)(float), float *xb1, float *xb2, float xacc, int num_roots)
{
    // *func == rtbis.c, rtflsp.c, rtsec.c, rtnewt.c, rtsafe.c
    //xb1 and xb2 are array
    double duration = 0;
    time_t start, end;

    for (int i = 1; i <= num_roots; i++)
    {
        start = clock();
        float roots = (*func)(bessel, xb1[i], xb2[i], xacc);
        end = clock();
        printf("Root%d = %f\n", i, roots);
        duration += (double)(end - start);
        // maximum iteration 출력 추가하기
    }
    printf("total_time %f\n", duration/CLOCKS_PER_SEC);
    printf("\n");
}

void newton_raphson(float x, float* f, float* df)
{
    *f = bessj0(x);
    *df = (-1) * bessj1(x);
    return;
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

    printf("=====Bisection=====\n");
    succint_codes(rtbis, bessj0, xb1, xb2, 1e-6, num_roots);
    printf("=====Linear interpolation=====\n");
    succint_codes(rtflsp, bessj0, xb1, xb2, 1e-6, num_roots);
    printf("=====Secant=====\n");
    succint_codes(rtsec, bessj0, xb1, xb2, 1e-6, num_roots);
    printf("=====Newton-Raphson=====\n");
    succint_codes(rtnewt, newton_raphson, xb1, xb2, 1e-6, num_roots);
    printf("=====Newton with bracketing=====\n");
    succint_codes(rtsafe, newton_raphson, xb1, xb2, 1e-6, num_roots);


    return 0;
}