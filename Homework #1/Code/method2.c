#include <stdio.h>

void get_eps(){
    float f_eps = 1;
    double d_eps = 1;
    int f_step = 0;
    int d_step = 0;
    
    while (1 + f_eps != 1)
    {
        f_eps /= 2;
        f_step++;
    }
    printf("%.60f, %d\n", f_eps*2, f_step);


    while (1 + d_eps != 1){
        d_eps /= 2;
        d_step++;
    }
    printf("%.60f, %d\n", d_eps*2, d_step );
}

int main()
{
    get_eps();
    return 0;
}