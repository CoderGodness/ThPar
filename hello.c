#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 5000000
#define M_PI 3.14159265358979323846
void func(double* my_array, int len)
{
    double x = 2 * M_PI / N / 2;
    my_array = (double*)malloc(sizeof(double) * len);
    #pragma acc data copyin(len,x) copyout(my_array[:len]) 
    {
        #pragma acc parallel
        {
            #pragma acc loop
            {
                for (int i = 0; i < len; ++i)
                {
                    my_array[i] = sin(i * x);
                }
            }
        }
    }
}
double summ(double* my_array, int len)
{
    double sum = 0;
    #pragma acc data copyout(sum) copyin(len, my_array[:len])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            {
                for (int i = 0; i < len; ++i)
                {
                    sum += my_array[i];
                }
            }
        }
    }
    return sum;
}

int main()
{
    double* array = (double*)malloc(sizeof(double*));
    func(array, N);
    printf("%lf", summ(array, N));
    free(*array);
    return 0;
}
