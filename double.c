#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
#define N 10000000
#define M_PI 3.14159265358979323846

int main()
{
    clock_t begin = clock();
    int len = N;
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
    double sum = 0;
    #pragma acc data create(temp[0:len]) copyout(sum)
    {
        #pragma acc kernels
        {
            for (int i = 0; i < len; ++i)
            {
                temp[i] = sin(i * x);
            }
        }
    
        #pragma acc kernels
        {
            for (int i = 0; i < len; ++i)
            {
                sum += temp[i];
            }
        }
    }
    free(temp);
    clock_t end = clock();
    printf("%d",sum);
    printf("The elapsed time is %lf seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
