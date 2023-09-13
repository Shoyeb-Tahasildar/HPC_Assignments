#include <stdio.h>
#include <time.h>
#include <omp.h>
int main()
{
    long n = 0;
    printf("\nEnter number = ");
    scanf("%d", &n);
    int ans[n];
    int f1 = 1;
    int f2 = 1;
    clock_t st = clock();
    printf("%d %d ", f1, f2);
#pragma omp parallel for schedule(guided, 4) num_threads(8)
    for (int i = 2; i <= n; i++)
    {
#pragma omp critical
        {
            int f3 = f1 + f2;
            printf("%d ", f3);
            f1 = f2;
            f2 = f3;
        }
    }
    clock_t et = clock();
    double elapsed_time = (double)(et - st) / CLOCKS_PER_SEC;
    double elapsed_miliseconds = elapsed_time * 1000;
    printf("\nTime taken: %f miliseconds", elapsed_miliseconds);
    printf("\nTime taken: %f seconds\n", elapsed_time);
    return 0;
}
