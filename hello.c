#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846
void func(double** my_array, int len)
{
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
#pragma acc parallel vector_length(196) copyout(temp[:len])
{
#pragma acc loop gang vector
{
                for (int i = 0; i < len; ++i)
                {
                    temp[i] = sin(i * x);
                }
}
}
    *my_array = temp;
}
double summ(double** my_array, int len)
{
    double sum = 0;
    double* temp = *my_array;
#pragma acc parallel vector_length(196) copyout(sum) copyin(temp[:len])
{
#pragma acc loop gang vector
{
                for (int i = 0; i < len; ++i)
                {
                    sum += temp[i];
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
