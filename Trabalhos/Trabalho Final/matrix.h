#include <stdio.h>
#include <stdlib.h>

struct matrix {
    struct matrix* right;
    struct matrix* below;
    int line;
    int column;
    float info;
};

typedef struct matrix Matrix;

Matrix* matrix_create(void);
float matrix_getelem(Matrix* m, int x, int y);
void matrix_setelem(Matrix* m, int x, int y, float elem);
void matrix_print(Matrix* m);
void matrix_destroy(Matrix* m);
Matrix* matrix_add(Matrix* m, Matrix* n);
Matrix* matrix_transpose(Matrix* m);

Matrix* matrix_create(void) {
    Matrix* head = (Matrix*)malloc(sizeof(Matrix));
    if (head == NULL) {
        perror("Erro na alocação de memória");
        exit(EXIT_FAILURE);
    }
    
    head->right = head;
    head->below = head;
    head->line = -1; // Cabeça da linha
    head->column = -1; // Cabeça da coluna
    head->info = 0.0; // Valor padrão para a célula cabeça

    int numRows, numCols;

    printf("Digite o número de linhas e colunas da matriz: ");
    scanf("%d %d", &numRows, &numCols);


    printf("Digite os elementos da matriz A:\n");
    for (int l = 1; l <= numRows; l++) {
        for (int k = 1; k <= numCols; k++) {
            float elem;
            int i, j;
            scanf("%d %d %f", &i, &j, &elem);
            matrix_setelem(head, i, j, elem);
        }
    }
    return head;
}

float matrix_getelem(Matrix* m, int x, int y) {
    Matrix* row_head = m->below;
    while (row_head != m) {
        if (row_head->line == x) {
            Matrix* current = row_head->right;
            while (current != row_head) {
                if (current->column == y) {
                    return current->info;
                }
                current = current->right;
            }
            break;
        }
        row_head = row_head->below;
    }
    return 0.0; // Valor padrão para elementos não encontrados
}

void matrix_setelem(Matrix* m, int x, int y, float elem) {
    Matrix* row_head = m->below;
    Matrix* prev_row = m;
    while (row_head != m && row_head->line < x) {
        prev_row = row_head;
        row_head = row_head->below;
    }
    
    if (row_head->line != x) {
        // A linha x ainda não existe, precisamos criá-la
        Matrix* new_row = (Matrix*)malloc(sizeof(Matrix));
        if (new_row == NULL) {
            perror("Erro na alocação de memória");
            exit(EXIT_FAILURE);
        }
        new_row->line = x;
        new_row->column = -1; // Cabeça da coluna
        new_row->info = 0.0;
        new_row->right = new_row;
        
        // Inserir nova linha
        prev_row->below = new_row;
        new_row->below = row_head;
        row_head = new_row;
    }
    
    Matrix* current = row_head->right;
    Matrix* prev = row_head;
    
    while (current != row_head && current->column < y) {
        prev = current;
        current = current->right;
    }
    
    if (current->column == y) {
        // O elemento (x, y) já existe, atualize-o
        current->info = elem;
    } else {
        // O elemento (x, y) não existe, crie-o
        Matrix* new_elem = (Matrix*)malloc(sizeof(Matrix));
        if (new_elem == NULL) {
            perror("Erro na alocação de memória");
            exit(EXIT_FAILURE);
        }
        new_elem->line = x;
        new_elem->column = y;
        new_elem->info = elem;
        
        // Inserir novo elemento
        prev->right = new_elem;
        new_elem->right = current;
    }
}

void matrix_print(Matrix* m) {
    int maxLine = -1, maxColumn = -1;

    // Encontre o número máximo de linhas e colunas com base nos elementos existentes
    Matrix* row_head = m->below;
    while (row_head != m) {
        Matrix* current = row_head->right;
        while (current != row_head) {
            if (current->line > maxLine) {
                maxLine = current->line;
            }
            if (current->column > maxColumn) {
                maxColumn = current->column;
            }
            current = current->right;
        }
        row_head = row_head->below;
    }

    // Imprima a matriz preenchendo com zero onde não há valores
    for (int i = 1; i <= maxLine; i++) {
        for (int j = 1; j <= maxColumn; j++) {
            float elem = matrix_getelem(m, i, j);
            printf("%.2f\t", elem);
        }
        printf("\n");
    }
}

void matrix_destroy(Matrix* m) {
    Matrix* row_head = m->below;
    while (row_head != m) {
        Matrix* current = row_head->right;
        while (current != row_head) {
            Matrix* temp = current;
            current = current->right;
            free(temp); // Liberar cada célula da matriz
        }
        Matrix* temp = row_head;
        row_head = row_head->below;
        free(temp); // Liberar a cabeça da linha
    }
    free(m); // Liberar a cabeça da matriz
}
Matrix* matrix_add(Matrix* m, Matrix* n) {
    // Check if the matrices have compatible dimensions
    if (m->line != n->line || m->column != n->column) {
        fprintf(stderr, "Matrices have incompatible dimensions for addition.\n");
        return NULL;
    }

    // Create a new matrix to store the result
    Matrix* result = matrix_create();

    // Iterate through rows and columns to perform element-wise addition
    Matrix* row_head_m = m->below;
    while (row_head_m != m) {
        Matrix* current_m = row_head_m->right;
        while (current_m != row_head_m) {
            float elem_m = current_m->info;
            float elem_n = matrix_getelem(n, current_m->line, current_m->column);
            float sum = elem_m + elem_n;
            matrix_setelem(result, current_m->line, current_m->column, sum);
            current_m = current_m->right;
        }
        row_head_m = row_head_m->below;
    }

    return result;
}


Matrix* matrix_transpose(Matrix* m) {
    // Crie uma nova matriz para armazenar a matriz transposta
    Matrix* transpose = matrix_create();

    // Itere pelos elementos da matriz original e insira-os na matriz transposta
    Matrix* row_head = m->below;
    while (row_head != m) {
        Matrix* current = row_head->right;
        while (current != row_head) {
            float elem = current->info;
            int row = current->column;  // Troque a linha pela coluna
            int column = current->line; // Troque a coluna pela linha
            matrix_setelem(transpose, row, column, elem);
            current = current->right;
        }
        row_head = row_head->below;
    }

    return transpose;
}

