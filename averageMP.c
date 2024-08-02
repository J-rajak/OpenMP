#include <stdio.h>
#define MAX 1000

void main()
{
    double average = 0.0, A[MAX];

    int i;

    #pragma omp parallel for reduction(+:average)
    for (i = 0; i < MAX; i++)
    {
        A[i] = (double)i;
        average += A[i];
    }
    average = average / MAX;
    printf("Average = %lf\n", average);
}