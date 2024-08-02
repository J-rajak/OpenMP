#include <stdio.h>
#include <omp.h>
#define M 4
#define N 3

int main()
{
    int A[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    int B[N][M] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    int C[M][M];

#pragma omp parallel for collapse(2)
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Printing the result matrix C
    printf("Resultant Matrix C:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
