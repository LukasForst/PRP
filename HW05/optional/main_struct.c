#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_MATRIX 100

void count(char math_symbol, int *result, int *a, int rows, int columns);
int multiply(int *result, int *a, int *b, int a_rows, int a_columns, int b_rows,
             int b_columns);
void free_all(int **matrix, int matrix_counter);
typedef struct 
{
    int * matrix;
    int rows;
    int columns;
} Matrix;

int main(int argc, char *argv[])
{
    int size_of_matrix[NUMBER_OF_MATRIX][2]; // 0 = rows, 1 = columns
    char math_symbol[NUMBER_OF_MATRIX];
    int matrix_counter = -1;

    int result_matrix_size[2] = {0, 0}; // 0 = rows, 1 = columns

    int **matrix;
    matrix = (int **)calloc(NUMBER_OF_MATRIX, sizeof(int *));

    int scaned_number;
    char scaned_symbol;

    math_symbol[0] = '+';
    int max_rows = 0;
    int max_columns = 0;
    /* -------------------------------------------------------------- */
    // scanning input
    for (;;) {
        int rows, columns;
        matrix_counter++;

        if (scanf("%i", &rows) != 1 || scanf("%i", &columns) != 1) {
            free_all(matrix, matrix_counter);
        }
        size_of_matrix[matrix_counter][0] = rows;
        size_of_matrix[matrix_counter][1] = columns;
		
		max_rows = (rows > max_rows) ? rows : max_rows;
		max_columns = (columns > max_columns) ? columns : max_columns;
        *(matrix + matrix_counter) =
            (int *)calloc(rows * columns, sizeof(int));

        for (int i = 0; i < rows * columns; i++) {
            if (scanf(" %i", &scaned_number) != 1) {
                free_all(matrix, matrix_counter);
            }
            *(*(matrix + matrix_counter) + i) = scaned_number;
        }

        if (scanf(" %c", &scaned_symbol) != -1) {
            math_symbol[matrix_counter + 1] = scaned_symbol;

        } else {
            break;
        }
    }
    
    for (int i = 0; i <= matrix_counter; i++) {
        *(matrix + i) = (int*) realloc(*(matrix + i),(max_rows*max_columns+2)*sizeof(int));
    }
    
    /* ------------------------------------------------------------ */
    // test of matrix whether I can count with them
    // initial test - get some first daat
    int number_of_multiply = 0;
    int number_of_pls_min = 0;

    for (int i = 1; i <= matrix_counter; i++) {
        if (math_symbol[i] == '*') {
            number_of_multiply++;
        } else {
            number_of_pls_min++;
        }
    }

    if (number_of_multiply == 0) {
        result_matrix_size[0] = size_of_matrix[0][0];
        result_matrix_size[1] = size_of_matrix[0][1];
    } else if (number_of_pls_min != 0) {
        for (int i = 1; i <= matrix_counter; i++) {
            if (math_symbol[i - 1] != '*' && math_symbol[i] != '*') {
                result_matrix_size[0] = size_of_matrix[i - 1][0];
                result_matrix_size[1] = size_of_matrix[i - 1][1];
                break;
            } else if (i == matrix_counter && math_symbol[i] != '*') {
                result_matrix_size[0] = size_of_matrix[i][0];
                result_matrix_size[1] = size_of_matrix[i][1];
                break;
            }
        }
    } else {
        for (int i = 1; i <= matrix_counter; i++) {
            if (size_of_matrix[i - 1][1] == size_of_matrix[i][0]) {
                int mult_count = 1;
                int temp_size[2] = {size_of_matrix[i - 1][0],
                                    size_of_matrix[i][1]};
                while (i + mult_count <= matrix_counter &&
                       math_symbol[i + mult_count] == '*') {

                    if (temp_size[1] == size_of_matrix[i + mult_count][0]) {
                        temp_size[1] = size_of_matrix[i + mult_count][1];
                        mult_count++;
                        continue;
                    } else {
                        free_all(matrix, matrix_counter);
                    }
                }
                result_matrix_size[0] = temp_size[0];
                result_matrix_size[1] = temp_size[1];
                break;
            } else {
                free_all(matrix, matrix_counter);
            }
        }
    }

    /* -------------------------------------------------------------- */
    if (result_matrix_size[0] == 0 || result_matrix_size[1] == 0) {
        free_all(matrix, matrix_counter);
    }

    /* -------------------------------------------------------------- */
    // priorintí algoritmus

    int *nula;
    nula = (int *)calloc(result_matrix_size[0] * result_matrix_size[1],
                         sizeof(int));

    //int *a, *b, *c;

    Matrix a,b,c;
    a.matrix = *(matrix);
    a.rows = size_of_matrix[0][0];
    a.columns = size_of_matrix[0][1];
    
    b.matrix = *(matrix + 1);
    b.rows = size_of_matrix[1][0];
    b.columns = size_of_matrix[1][1];

    char symbol1, symbol2;
    if (2 > matrix_counter) {
        c.matrix = nula;
        symbol2 = '+';
        c.rows = result_matrix_size[0];
        c.columns = result_matrix_size[1];
    } else {
        c.matrix = *(matrix + 2);
        c.rows = size_of_matrix[2][0];
        c.columns = size_of_matrix[2][1];
        symbol2 = *(math_symbol + 2);
    }

    symbol1 = *(math_symbol + 1);

    for (int i = 0; i <= matrix_counter; i++) {
        if (symbol1 != '*') { // case with *
            if (symbol2 != '*') {
                if (a.rows != b.rows || a.columns != b.columns) {
                    fprintf(stderr, "ERROR 1\n");
                    free(nula);
                    free_all(matrix, matrix_counter);
                }
                count(symbol1, a.matrix, b.matrix, a.rows, a.columns);
                b.matrix = c.matrix;
                b.rows = c.rows;
                b.columns = c.columns;
                if (i + 3 > matrix_counter) {
                    c.rows = result_matrix_size[0];
                    c.columns = result_matrix_size[1];
                    c.matrix = nula;
                    symbol1 = symbol2;
                    symbol2 = '+';
                    continue;
                } else {
                    c.matrix = *(matrix + i + 3);
                    c.rows = size_of_matrix[i + 3][0];
                    c.columns = size_of_matrix[i + 3][1];
                    symbol1 = symbol2;
                    symbol2 = math_symbol[i + 3];
                    continue;
                }

            } else {
                if (b.columns != c.rows) {
                    fprintf(stderr, "ERROR 2\n");
                    free(nula);
                    free_all(matrix, matrix_counter);
                }
                multiply(b.matrix, b.matrix, c.matrix, b.rows, b.columns, c.rows, c.columns);
                b.columns = c.columns;
                if (i + 3 > matrix_counter) {
                    c.rows = result_matrix_size[0];
                    c.columns = result_matrix_size[1];
                    c.matrix = nula;
                    symbol2 = '+';
                    continue;
                } else {
                    c.matrix = *(matrix + i + 3);
                    c.rows = size_of_matrix[i + 3][0];
                    c.columns = size_of_matrix[i + 3][1];
                    symbol2 = math_symbol[i + 3];
                    continue;
                }
            }
        } else {
            if (a.columns != b.rows) {
                fprintf(stderr, "ERROR 3\n");
                free(nula);
                free_all(matrix, matrix_counter);
            }
            multiply(a.matrix, a.matrix, b.matrix, a.rows, a.columns, b.rows, b.columns);
            a.columns = b.columns;
            b.matrix = c.matrix;
            b.rows = c.rows;
            b.columns = c.columns;
            if (i + 3 > matrix_counter) {
                c.rows = result_matrix_size[0];
                c.columns = result_matrix_size[1];
                c.matrix = nula;
                symbol1 = symbol2;
                symbol2 = '+';
                continue;
            } else {
                c.matrix = *(matrix + i + 3);
                c.rows = size_of_matrix[i + 3][0];
                c.columns = size_of_matrix[i + 3][1];
                symbol1 = symbol2;
                symbol2 = math_symbol[i + 3];
                continue;
            }
        }
    }
    /* ------------------------------------------------------------ */
    // result matrix print
    printf("%i %i\n", a.rows, a.columns);
    for (int row = 0; row < a.rows; row++) {
        for (int column = 0; column < a.columns; column++) {
            if (column == 0) {
                printf("%i", *(a.matrix + row * a.columns + column));
            } else {
                printf(" %i", *(a.matrix + row * a.columns + column));
            }
        }
        printf("\n");
    }

    // free every matrix in matrix
    for (int i = 0; i <= matrix_counter; i++) {
        free(*(matrix + i));
    }
    free(nula);
    free(matrix);
    return 0;
}

void free_all(int **matrix, int matrix_counter)
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    for (int i = 0; i <= matrix_counter; i++) {
        free(*(matrix + i));
    }
    free(matrix);
    exit(100);
}

void count(char math_symbol, int *result, int *a, int rows, int columns)
{
    int *semi_result = (int *)calloc(columns * rows, sizeof(int));
    if (math_symbol == '+') {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                *(semi_result + (row * columns + column)) =
                    *(result + (row * columns + column)) +
                    *(a + (row * columns + column));
            }
        }
    } else if (math_symbol == '-') {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                *(semi_result + (row * columns + column)) =
                    *(result + (row * columns + column)) -
                    *(a + (row * columns + column));
            }
        }
    }
    for (int i = 0; i < rows * columns; i++) { // deep copy
        *(result + i) = *(semi_result + i);
    }
    free(semi_result);
}

int multiply(int *result, int *a, int *b, int a_rows, int a_columns, int b_rows,
             int b_columns)
{ // classic multiplying of matrix - as we've learnt
    int final_rows = a_rows;
    int final_columns = b_columns;
    if (a_columns != b_rows) {
        return 1;
    }
    int *semi_result;
    semi_result = (int *)calloc(final_rows * final_columns, sizeof(int));
    for (int row = 0; row < final_rows; row++) {
        for (int column = 0; column < final_columns; column++) {
            for (int second_index = 0; second_index < a_columns;
                 second_index++) {
                *(semi_result + (row * final_columns + column)) +=
                    (*(a + (row * a_columns + second_index)) *
                     (*(b + (second_index * b_columns + column))));
            }
        }
    }
    for (int i = 0; i < final_rows * final_columns; i++) { // deep copy
        *(result + i) = *(semi_result + i);
    }
    free(semi_result);
    return 0;
}