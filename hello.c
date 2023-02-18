#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846
int main()
{
    double x = 2 * M_PI / N;
    int len = N;
    double* temp = (double*)malloc(sizeof(double) * len);
#pragma acc parallel num_gangs(2048) vector_length(224) copyout(temp[:len])
    {
#pragma acc loop gang vector
        {
            for (int i = 0; i < len; ++i)
            {
                temp[i] = sin(i * x);
            }
        }
    }
    double sum = 0;
#pragma acc parallel num_gangs(2048) vector_length(224) copyout(sum) copyin(temp[:len])
    {
#pragma acc loop gang vector
        {
            for (int i = 0; i < len; ++i)
            {
                sum += temp[i];
            }
        }
    }
    printf("%lf", sum);
    return 0;
}
