#include <stdio.h>
#include <omp.h>

int main()
{
    int dimention;

    printf("Enter dimention for matrix = ");
    scanf("%d", &dimention);

    // Serial Code
    int m1[dimention][dimention];
    int count = 0;
    printf("\nSerial\n");

    double start_time_serial = omp_get_wtime();
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            m1[i][j] = ++count;
            printf("%d\t", m1[i][j]);
        }
        printf("\n");
    }
    int sum = 0;
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            if (i > j)
                sum += m1[i][j];
        }
    }

    int sum2 = 0;
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            if (j < dimention - i)
                continue;
            else
                sum2 += m1[i][j];
        }
    }
    double end_time_serial = omp_get_wtime();
    printf("\nLeft Lower Triangle Sum = %d", sum);
    printf("\nRight Lower Triangle Sum = %d", sum2);
    printf("\nTwo Lower Triangles Sum = %d", (sum + sum2));
    // Parallel code count=0; printf("\nParallel\n");
    double start_time_parallel = omp_get_wtime();
#pragma omp parallel for ordered num_threads(8)
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            m1[i][j] = ++count;
            printf("%d\t", m1[i][j]);
        }
        printf("\n");
    }

    sum = 0;
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            if (i > j)
                sum += m1[i][j];
        }
    }

    sum2 = 0;
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < dimention; i++)
    {
        for (int j = 0; j < dimention; j++)
        {
            if (j < dimention - i)
                continue;
            else
                sum2 += m1[i][j];
        }
    }
    double end_time_parallel = omp_get_wtime();

    printf("\nLeft Lower Triangle Sum = %d", sum);
    printf("\nRight Lower Triangle Sum = %d", sum2);
    printf("\nTwo Lower Triangles Sum = %d", (sum + sum2));
    printf("\n\nSerial Method Time: %f seconds\n", (end_time_serial - start_time_serial));
    printf("\nParallel Method Time: %f seconds\n\n", (end_time_parallel - start_time_parallel));

    return 0;
}
