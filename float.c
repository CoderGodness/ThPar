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
    #pragma acc data create(arr[0:len]) copyout(sum)
    {
        #pragma acc parallel num_gangs(2048) vector_length(256)
        {
            for (int i = 0; i < len; ++i)
            {
                arr[i] = sinf(i * x);
            }
        }
        #pragma acc parallel num_gangs(2048) vector_length(256)
        {
            for (int i = 0; i < len; ++i)
            {
                sum += arr[i];
            }
        }
    }
    free(arr);
    clock_t end = clock();
    printf("%f",sum);
    printf("\nThe elapsed time is %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
