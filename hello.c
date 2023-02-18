#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846
double func(double** my_array, int len)
{
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
    double sum = 0;
#pragma acc data copyout(temp[:len], sum) 
    {
#pragma acc parallel
        {
#pragma acc loop
            {
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
    }
    *my_array = temp;
    return sum;
}

int main()
{
    double** array = (double**)malloc(sizeof(double**));
    printf("%lf", func(array, N));
    free(*array);
    return 0;
}
