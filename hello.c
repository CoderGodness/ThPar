#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846

int main()
{
    //double** array = (double**)malloc(sizeof(double**));
    double x = 2 * M_PI / N;
    double sum = 0;
    int len = N;
#pragma acc parallel num_gangs(2048) vector_length(224)  copyout(sum) 
    {
#pragma acc loop gang vector
        {
            double* temp = (double*)malloc(sizeof(double) * len);
            for (int i = 0; i < len; ++i)
            {
                temp[i] = sin(i * x);
            }

            for (int i = 0; i < len; ++i)
            {
                sum += temp[i];
            }
        }

    }
    printf("%lf", sum);
    return 0;
}
