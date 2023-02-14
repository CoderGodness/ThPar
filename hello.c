#define _USE_MATH_DEFINES
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define N 10000000
//
//void func(double** my_array, int len)
//{
//    double x = 2 * M_PI / N;
//    double* temp = (double*)malloc(sizeof(double) * len);
//    #pragma acc data create(temp[:len]) copy(len,x)//copy(sum) copyin(temp)
//    #pragma acc kernels
//    {
//        for (int i = 0; i < len; ++i)
//        {
//            temp[i] = sin(i * x);
//        }
//    }
//    *my_array = temp;
//}
//double summ(double** my_array, int len)
//{
//    double sum = 0;
//    double* temp = *my_array;
//    #pragma acc data create(sum) copy(temp[:len], len)
//    #pragma acc kernels
//    {
//        for (int i = 0; i < len; ++i)
//        {
//            sum += temp[i];
//        }
//    }
//    return sum;
//}

int main()
{
    //double** array = (double**)malloc(sizeof(double**));
    long long len = N;
    double x = 2 * M_PI / N;
    double* temp = (double*)malloc(sizeof(double) * len);
    #pragma acc data copyout(temp[:len]) copyin(len,x)
    {
        #pragma acc kernels
        {
            for (int i = 0; i < len; ++i)
            {
                temp[i] = sin(i * x);
            }
        }
    }
    double sum = 0;
    #pragma acc data copyout(sum) copyin(temp[:len], len)
    {
        #pragma acc kernels
        {
            for (int i = 0; i < len; ++i)
            {
                sum += temp[i];
            }
        }
    }
    printf("%lf", sum);
    free(temp);
    return 0;
}
