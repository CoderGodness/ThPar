#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
#define N 10000000
#define M_PI 3.14159265358979323846
void func(double** my_array, int len)
{
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
#pragma acc parallel num_gangs(4882) num_workers(128) vector_length(8) copyout(temp[0:len])
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
#pragma acc parallel num_gangs(4882) num_workers(128) vector_length(8) copyin(temp[:len])
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
    clock_t begin = clock();
    double** array = (double**)malloc(sizeof(double**));
    func(array, N);
    printf("%lf\n", summ(array, N));
    free(*array);
    clock_t end = clock();
    printf("The elapsed time is %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
