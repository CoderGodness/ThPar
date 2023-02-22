#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 

int main()
{
    clock_t begin = clock();
    int len = 10000000;
    float x = 2 * M_PI / len;
    float* arr = (float*)malloc(sizeof(float) * len);
    float sum = 0;
    clock_t beginfill = clock();
    for (int i = 0; i < len; ++i)
    {
        arr[i] = sinf(i * x);
    }
    clock_t endfill = clock();

    clock_t beginsum = clock();
    for (int i = 0; i < len; ++i)
    {
        sum += arr[i];
    }
    clock_t endsum = clock();
    free(arr);
    clock_t end = clock();
    printf("%f",sum);
    printf("\nProgram running time = %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("\nFill cycle running time = %lf seconds", (double)(endfill - beginfill) / CLOCKS_PER_SEC);
    printf("\nSum cycle running time = %lf seconds", (double)(endsum - beginsum) / CLOCKS_PER_SEC);
    return 0;
}
