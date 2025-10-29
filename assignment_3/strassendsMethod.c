#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocate_matrix(int n);
void free_matrix(int** matrix, int n);
void initialize_matrix(int** matrix, int n);
void add(int** C, int** A, int** B, int n);
void subtract(int** C, int** A, int** B, int n);
void strassen_multiply(int** C, int** A, int** B, int n);

int main() {

    int sizes[] = {32, 64, 128, 256};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Algorithm,Size,Time\n");

    printf("\n--- Strassen's Matrix Multiplication Performance ---\n");
    printf("+-----------+---------------------+-------------------+\n");
    printf("| Matrix Size (N x N) | Execution Time (seconds) |\n");
    printf("+-----------+---------------------+-------------------+\n");

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        int** A = allocate_matrix(N);
        int** B = allocate_matrix(N);
        int** C = allocate_matrix(N);

        initialize_matrix(A, N);
        initialize_matrix(B, N);

        clock_t start = clock();

        strassen_multiply(C, A, B, N);

        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


        printf("|  %-4d x %-12d | %-24.6f |\n", N, N, time_spent);
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

void strassen_multiply(int** C, int** A, int** B, int n) {
    // Base case for the recursion
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Dynamically allocate all sub-matrices and temporary matrices
    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);
    int** C11 = allocate_matrix(k); int** C12 = allocate_matrix(k);
    int** C21 = allocate_matrix(k); int** C22 = allocate_matrix(k);

    int** M1 = allocate_matrix(k); int** M2 = allocate_matrix(k);

    int** P = allocate_matrix(k); int** Q = allocate_matrix(k);
    int** R = allocate_matrix(k); int** S = allocate_matrix(k);
    int** T = allocate_matrix(k); int** U = allocate_matrix(k);
    int** V = allocate_matrix(k);

    // Divide A and B into sub-matrices (Partitioning)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j]; A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j]; B22[i][j] = B[i + k][j + k];
        }
    }

    // --- Strassen's 7 recursive calls ---
    // P = (A11+A22)*(B11+B22)
    add(M1, A11, A22, k); add(M2, B11, B22, k); strassen_multiply(P, M1, M2, k);
    // Q = (A21+A22)*B11
    add(M1, A21, A22, k); strassen_multiply(Q, M1, B11, k);
    // R = A11*(B12-B22)
    subtract(M1, B12, B22, k); strassen_multiply(R, A11, M1, k);
    // S = A22*(B21-B11)
    subtract(M1, B21, B11, k); strassen_multiply(S, A22, M1, k);
    // T = (A11+A12)*B22
    add(M1, A11, A12, k); strassen_multiply(T, M1, B22, k);
    // U = (A21-A11)*(B11+B12)
    subtract(M1, A21, A11, k); add(M2, B11, B12, k); strassen_multiply(U, M1, M2, k);
    // V = (A12-A22)*(B21+B22)
    subtract(M1, A12, A22, k); add(M2, B21, B22, k); strassen_multiply(V, M1, M2, k);

    // --- Combine results to form C sub-matrices ---
    // C11 = P+S-T+V
    add(M1, P, V, k); subtract(M2, S, T, k); add(C11, M1, M2, k);
    // C12 = R+T
    add(C12, R, T, k);
    // C21 = Q+S
    add(C21, Q, S, k);
    // C22 = P+R-Q+U
    add(M1, P, U, k); subtract(M2, R, Q, k); add(C22, M1, M2, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k); free_matrix(M2, k);
    free_matrix(P, k); free_matrix(Q, k); free_matrix(R, k); free_matrix(S, k);
    free_matrix(T, k); free_matrix(U, k); free_matrix(V, k);
}

int** allocate_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initialize_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i + j; 
        }
    }
}

void add(int** C, int** A, int** B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int** C, int** A, int** B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}