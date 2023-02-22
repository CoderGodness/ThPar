#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
clock_t beginfill;
clock_t endfill;
clock_t beginsum;
clock_t endsum;
void fill(double* arr, int len)
{
    beginfill = clock();
    double x = 2 * M_PI / len;
    
    #pragma acc enter data create(arr[0:len])
    
    #pragma acc parallel num_gangs(2048) vector_length(256)
    {
        for (int i = 0; i < len; ++i)
        {
            arr[i] = sin(i * x);
        }
    }
    clock_t endfill = clock();
}
double summ(double* arr, int len)
{
    beginsum = clock();
    double sum = 0;
    
    #pragma acc parallel num_gangs(2048) vector_length(256)
    {
        for (int i = 0; i < len; ++i)
        {
            sum += arr[i];
        }
    }
    
    #pragma acc exit data delete(arr[0:len])
    
    endsum = clock();
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
     printf("\nFill cycle running time = %lf seconds", (double)(endfill - beginfill) / CLOCKS_PER_SEC);
    printf("\nSum cycle running time = %lf seconds", (double)(endsum - beginsum) / CLOCKS_PER_SEC);
    return 0;
}
