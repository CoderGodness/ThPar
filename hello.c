#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 5000000
void func(double** my_array, int len)
{
    double x = 2 * M_PI / N / 2;
    double* temp = (double*)malloc(sizeof(double) * len);
#pragma acc data copyin(len,x) copyout(temp[:len]) 
    {
#pragma acc parallel
        {
#pragma acc loop
            {
                for (int i = 0; i < len; ++i)
                {
                    temp[i] = sin(i * x);
                }
            }
        }
    }
    *my_array = temp;
}
double summ(double** my_array, int len)
{
    double sum = 0;
    double* temp = *my_array;
#pragma acc data copyout(sum) copyin(len, temp[:len])
    {
#pragma acc parallel
        {
#pragma acc loop
            {
                for (int i = 0; i < len; ++i)
                {
                    sum += temp[i];
                }
            }
        }
    }
    return sum;
}

int main()
{
    double** array = (double**)malloc(sizeof(double**));
    func(array, N);
    printf("%lf", summ(array, N));
    free(*array);
    return 0;
}
