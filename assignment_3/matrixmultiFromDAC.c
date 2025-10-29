#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocate_matrix(int N);
void free_matrix(int** matrix, int N);
void initialize_matrix(int** matrix, int N);

void matrix_add(int** C, int** A, int** B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void dnc_multiply(int** C, int** A, int** B, int N) {

    if (N == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int n2 = N / 2;

    int** A11 = allocate_matrix(n2); int** A12 = allocate_matrix(n2);
    int** A21 = allocate_matrix(n2); int** A22 = allocate_matrix(n2);
    int** B11 = allocate_matrix(n2); int** B12 = allocate_matrix(n2);
    int** B21 = allocate_matrix(n2); int** B22 = allocate_matrix(n2);
    
    int** P1 = allocate_matrix(n2); int** P2 = allocate_matrix(n2);
    int** P3 = allocate_matrix(n2); int** P4 = allocate_matrix(n2);
    int** P5 = allocate_matrix(n2); int** P6 = allocate_matrix(n2);
    int** P7 = allocate_matrix(n2); int** P8 = allocate_matrix(n2);

    int** C11 = allocate_matrix(n2); int** C12 = allocate_matrix(n2);
    int** C21 = allocate_matrix(n2); int** C22 = allocate_matrix(n2);

    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n2];
            A21[i][j] = A[i + n2][j];
            A22[i][j] =A[i + n2][j + n2];

            B11[i][j] =B[i][j];
            B12[i][j] = B[i][j + n2];
            B21[i][j]= B[i + n2][j];
            B22[i][j] = B[i + n2][j + n2];
        }
    }

    dnc_multiply(P1, A11, B11, n2);
    dnc_multiply(P2, A12, B21, n2);
    dnc_multiply(P3,A11, B12, n2);
    dnc_multiply(P4, A12,B22, n2);
    dnc_multiply(P5, A21, B11,n2);
    dnc_multiply(P6, A22,B21, n2);
    dnc_multiply(P7, A21, B12, n2);
    dnc_multiply(P8, A22, B22, n2);

    matrix_add(C11, P1, P2, n2);
    matrix_add(C12, P3, P4, n2);
    matrix_add(C21, P5, P6, n2);
    matrix_add(C22, P7, P8, n2);

    for (int i = 0; i <n2; i++) {
        for (int j = 0;j < n2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n2] = C12[i][j];
            C[i + n2][j] =C21[i][j];
            C[i + n2][j+ n2] = C22[i][j];
        }
    }

    free_matrix(A11, n2); free_matrix(A12, n2); free_matrix(A21, n2); free_matrix(A22, n2);
    free_matrix(B11, n2); free_matrix(B12, n2); free_matrix(B21, n2); free_matrix(B22, n2);
    free_matrix(P1, n2); free_matrix(P2, n2); free_matrix(P3, n2); free_matrix(P4, n2);
    free_matrix(P5, n2); free_matrix(P6, n2); free_matrix(P7, n2); free_matrix(P8, n2);
    free_matrix(C11, n2); free_matrix(C12, n2); free_matrix(C21, n2); free_matrix(C22, n2);
}

int main() {
    
    int sizes[] = {64, 128, 256, 512};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "Algorithm,Size,Time\n");
    printf("+-----------+---------------------+--------------------+\n");
    printf("| Matrix Size (N x N) | Execution Time (seconds) |\n");
    printf("+-----------+---------------------+--------------------+\n");

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        int** A = allocate_matrix(N);
        int** B = allocate_matrix(N);
        int** C = allocate_matrix(N);

        initialize_matrix(A, N);
        initialize_matrix(B, N);

        clock_t start = clock();
        dnc_multiply(C, A, B, N);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("| %-4d x %-12d | %-24.6f |\n", N, N, time_spent);
        fprintf(file, "%d,%.6f\n", N, time_spent);

        free_matrix(A, N);
        free_matrix(B, N);
        free_matrix(C, N);
    }
    printf("+---------------------+-------------------------+\n");

    fclose(file);
    printf("\nPerformance data saved to results.txt\n\n");
    return 0;
}


int** allocate_matrix(int N) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initialize_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = i + j;
        }
    }
}