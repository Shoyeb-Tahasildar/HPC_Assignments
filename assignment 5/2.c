#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    int i, j, k, N;
    printf("Enter size = ");
    scanf("%d", &N);
    int A[N][N];
    int B[N][N];
    int C[N][N];
    clock_t st = clock();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i + j;
            C[i][j] = 0;
        }
    }
    printf("\nMatrix\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
#pragma omp parallel for private(i, j, k) shared(A, B, C) num_threads(4)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printf("\nAnswer\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {

            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }
    clock_t et = clock();
    double elapsed_time = (double)(et - st) / CLOCKS_PER_SEC;
    double elapsed_miliseconds = elapsed_time * 1000;
    printf("\nTime taken: %f miliseconds", elapsed_miliseconds);
    printf("\nTime taken: %f seconds\n", elapsed_time);
}
