#include <stdio.h>
#include "../../NRs/ansi/other/nr.h"
#include "../../NRs/ansi/other/nrutil.h"
#include <time.h>

#include <string.h>
#include <stdlib.h>

float ran0(long *idum);
float gasdev(long *idum);

int n = 1000;
int n1 = 100;
int n2 = 10000;
int n3 = 100000;
int a = -3; // upper bound
int b = 2; // lower bound
float m = 0.5; // mean
float s = 1.5; // std

void write_random_nums(int num, float* array, char* name){
    FILE *fp;
    fp = fopen(name, "w");
    for (int i = 0; i < num; i++)
        fprintf(fp, "%f\n", array[i]);
    fclose(fp);
}

int main() {
    float uniform_samples[100000];
    float gaussian_samples[100000];

    long idum_uniform = time(NULL);
    long idum_gauss = time(NULL);

    // uniform
    for (int i = 0; i < n; i++)
        uniform_samples[i] = (b-a)*ran0(&idum_uniform)+a ; 
    
    //gaussian
    for (int i = 0; i < n; i++)
        gaussian_samples[i] = s*gasdev(&idum_gauss) + m;

    write_random_nums(n, uniform_samples, "rand_1000_uniform.txt");
    write_random_nums(n, gaussian_samples, "rand_1000_gauss.txt");


    // uniform
    for (int i = 0; i < n1; i++)
        uniform_samples[i] = (b-a)*ran0(&idum_uniform)+a ; 
    
    //gaussian
    for (int i = 0; i < n1; i++)
        gaussian_samples[i] = s*gasdev(&idum_gauss) + m;

    write_random_nums(n1, uniform_samples, "rand_100_uniform.txt");
    write_random_nums(n1, gaussian_samples, "rand_100_gauss.txt");

    // uniform
    for (int i = 0; i < n2; i++)
        uniform_samples[i] = (b-a)*ran0(&idum_uniform)+a ; 
    
    //gaussian
    for (int i = 0; i < n2; i++)
        gaussian_samples[i] = s*gasdev(&idum_gauss) + m;

    write_random_nums(n2, uniform_samples, "rand_10000_uniform.txt");
    write_random_nums(n2, gaussian_samples, "rand_10000_gauss.txt");


    // uniform
    for (int i = 0; i < n3; i++)
        uniform_samples[i] = (b-a)*ran0(&idum_uniform)+a ; 
    
    //gaussian
    for (int i = 0; i < n3; i++)
        gaussian_samples[i] = s*gasdev(&idum_gauss) + m;

    write_random_nums(n3, uniform_samples, "rand_100000_uniform.txt");
    write_random_nums(n3, gaussian_samples, "rand_100000_gauss.txt");

    return 0;
}