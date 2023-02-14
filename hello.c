#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000

void func(double** my_array, int len)
{
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
    for (int i = 0; i < len; ++i)
    {
        temp[i] = sin(i*x);
    }
    *my_array = temp;
}
double summ(double** my_array, int len)
{
    double sum = 0;
    double* temp = *my_array;
    for (int i = 0; i < len; ++i)
    {
        sum += temp[i];
    }
    return sum;
}

int main()
{
    double** array = (double**)malloc(sizeof(double**));
    long long len = N;
    func(array, len);
    double sum = summ(array, len);
    printf("%lf", sum);
    return 0;
}
