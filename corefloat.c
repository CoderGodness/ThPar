#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>
#define N 10000000
#define M_PI 3.14159265358979323846
void func(float** my_array, int len)
{
    float x = 2 * M_PI / N;
    float* temp = (float*)malloc(sizeof(float) * len);
      for (int i = 0; i < len; ++i)
      {
          temp[i] = sin(i * x);
      }
    *my_array = temp;
}
float summ(float** my_array, int len)
{
    float sum = 0;
    float* temp = *my_array;
			for (int i = 0; i < len; ++i)
			{
					sum += temp[i];
			}
    return sum;
}

int main()
{
 		clock_t begin = clock();
    float** array = (float**)malloc(sizeof(float**));
    func(array, N);
    printf("%lf\n", summ(array, N));
    free(*array);
		clock_t end = clock();
		printf("The elapsed time is %f seconds", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
