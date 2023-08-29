#include <stdio.h>
#include "matrix.h"

int main( void ) {
    Matrix *A = matrix_create();
    printf("Matriz A:\n");
    matrix_print(A);

    Matrix *B = matrix_create();
    printf("Matriz B:\n");
    matrix_print(B);

    Matrix *C = matrix_add(A, B);
    printf("Matriz C (soma de A e B):\n");
    matrix_print(C);
    matrix_destroy(C);

    // C = matrix_multiply(A, B);
    // printf("Matriz C (resultado da multiplicação):\n");
    // matrix_print(C);
    // matrix_destroy(C);

    C = matrix_transpose(A);
    printf("Matriz C (transposta de A):\n");
    matrix_print(C);
    matrix_destroy(C);

    matrix_destroy(A);
    matrix_destroy(B);
    return 0;
}

