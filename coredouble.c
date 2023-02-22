#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
void fill(double* arr, int len)
{
    double x = 2 * M_PI / len;
    #pragma acc enter data create(arr[0:len])
    
    #pragma acc parallel num_gangs(2048) vector_length(256)
    {
        for (int i = 0; i < len; ++i)
        {
            arr[i] = sin(i * x);
        }
    }
}
double summ(double* arr, int len)
{
    double sum = 0;
    
    #pragma acc parallel num_gangs(2048) vector_length(256)
    {
        for (int i = 0; i < len; ++i)
        {
            sum += arr[i];
        }
    }
    
    #pragma acc exit data delete(arr[0:len])
    
    return sum;
}

int main()
{
    clock_t begin = clock();
    int len = 10000000;

    double* arr = (double*)malloc(sizeof(double) * len);
    fill(arr, len);
    printf("%lf", summ(arr, len));
    free(arr);
    clock_t end = clock();
    printf("\nProgram running time = %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
