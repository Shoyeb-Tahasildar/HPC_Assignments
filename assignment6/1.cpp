#include <stdio.h>
#include <omp.h>
#include<time.h>

void prefix_sum(int* arr, int n) {

    int i, sum = 0;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        #pragma omp critical
        {
            sum += arr[i];
            arr[i] = sum;
        }
    }
}

int main() {
  double start=omp_get_wtime();
    int n = 10;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    prefix_sum(arr, n);

    printf("Prefix Sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    double end=omp_get_wtime();

    printf("Execution time: %f", end-start);

    return 0;
}

