#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
clock_t beginfill;
clock_t endfill;
clock_t beginsum;
clock_t endsum;
int main()
{
    clock_t begin = clock();
    int len = 10000000;
    double x = 2 * M_PI / len;
    double* arr = (double*)malloc(sizeof(double) * len);
    double sum = 0;
    #pragma acc data create(arr[0:len]) copyout(sum)
    {
        beginfill = clock();
        #pragma acc parallel num_gangs(2048) vector_length(256)
        {
            for (int i = 0; i < len; ++i)
            {
                arr[i] = sin(i * x);
            }
        }
        endfill = clock();
    
        beginsum = clock();
        #pragma acc parallel num_gangs(2048) vector_length(256)
        {
            for (int i = 0; i < len; ++i)
            {
                sum += arr[i];
            }
        }
        endsum = clock();
    }
    free(arr);
    clock_t end = clock();
    printf("%lf",sum);
    printf("\nThe elapsed time is %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
     printf("\nFill cycle running time = %lf seconds", (double)(endfill - beginfill) / CLOCKS_PER_SEC);
    printf("\nSum cycle running time = %lf seconds", (double)(endsum - beginsum) / CLOCKS_PER_SEC);
    return 0;
}
