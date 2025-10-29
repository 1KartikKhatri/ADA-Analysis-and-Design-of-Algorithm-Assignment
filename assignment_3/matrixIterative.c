#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int**allocate_matrix(int N) {
    int** matrix = (int**)malloc(N* sizeof(int*));
    for (int i= 0; i< N;i++) {
        matrix[i] = (int*)malloc(N *sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix,int N) {
    for (int i= 0; i<N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initialize_matrix(int** matrix,int N) {
    for (int i= 0; i <N; i++) {
        for (int j= 0; j< N;j++) {
            matrix[i][j] =i+j; 
        }
    }
}

int main() {
    int sizes[] = {100, 250, 500, 1000, 1500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results.txt","w"); 
    if (file ==NULL) {
        printf("Error opening file!\n");
        return 1; 
    }

    fprintf(file,"Size,Time\n");

    printf("+---------------------+--------------------------+\n");
    printf("| Matrix Size (N x N) | Execution Time (seconds) |\n");
    printf("+---------------------+--------------------------+\n");

    for (int s=0; s <num_sizes;s++) {
        int N = sizes[s];

        int** A = allocate_matrix(N);
        int**B = allocate_matrix(N);
        int** C = allocate_matrix(N);
        initialize_matrix(A, N);
        initialize_matrix(B,N);

        clock_t start = clock();
        for (int i =0; i< N; i++) {
            for (int j= 0; j <N; j++) {
                C[i][j]=0;
                for (int k = 0; k<N; k++) {
                    C[i][j]+= A[i][k]*B[k][j];
                }
            }
        }
        clock_t end = clock();

        double time_spent = (double)(end-start)/CLOCKS_PER_SEC;

        printf("| %-4d x %-12d | %-24.6f |\n", N, N, time_spent);

        fprintf(file, "%d,%.6f\n", N, time_spent);

        free_matrix(A, N);
        free_matrix(B, N);
        free_matrix(C, N);
    }
    printf("+---------------------+--------------------------+\n");
    fclose(file);
    printf("\nPerformance data successfully saved to results.txt\n\n");
    return 0;
}