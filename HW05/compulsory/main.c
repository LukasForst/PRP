#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_MATRIX 100

void count(char math_symbol, int *result, int *a, int *b, int rows,
           int columns);
int multiply(int *result, int *a, int *b, int a_rows, int a_columns, int b_rows,
             int b_columns);

int main(int argc, char *argv[])
{
    int size_of_matrix[NUMBER_OF_MATRIX][2]; // 0 = rows, 1 = columns
    char math_symbol[NUMBER_OF_MATRIX];
    int matrix_counter = -1;

    int *result_matrix;
    int result_matrix_size[2]; // 0 = rows, 1 = columns

    int **matrix;
    matrix = (int **)calloc(NUMBER_OF_MATRIX, sizeof(int *));

    int scaned_number;
    char scaned_symbol;

    math_symbol[0] = '+';
    /* -------------------------------------------------------------- */
    // scanning input
    for (;;) {
        int rows, columns;
        matrix_counter++;
        if (scanf("%i", &rows) != 1 || scanf("%i", &columns) != 1) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            for (int i = 0; i < matrix_counter; i++) {
                free(*(matrix + i));
            }
            free(matrix);
            return 100;
        }

        size_of_matrix[matrix_counter][0] = rows;
        size_of_matrix[matrix_counter][1] = columns;

        *(matrix + matrix_counter) = (int *)calloc(rows * columns, sizeof(int));

        for (int i = 0; i < rows * columns; i++) {
            if (scanf("%i", &scaned_number) != 1) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                for (int i = 0; i <= matrix_counter; i++) {
                    free(*(matrix + i));
                }
                free(matrix);
                return 100;
            }
            *(*(matrix + matrix_counter) + i) = scaned_number;
        }

        if (scanf(" %c", &scaned_symbol) != -1) {
            math_symbol[matrix_counter + 1] = scaned_symbol;

        } else {
            break;
        }
    }
    /* ------------------------------------------------------------ */

    /* ------------------------------------------------------------ */
    // test of matrix whether I can count with them
    // initial test - get some first daat
    if (math_symbol[1] == '*') {
        if (size_of_matrix[0][1] == size_of_matrix[1][0]) {
            result_matrix_size[0] = size_of_matrix[0][0];
            result_matrix_size[1] = size_of_matrix[1][1];
        } else {
            fprintf(stderr, "Error: Chybny vstup!\n");
            for (int i = 0; i <= matrix_counter; i++) {
                free(*(matrix + i));
            }
            free(matrix);
            return 100;
        }
    } else {
        if (size_of_matrix[0][0] == size_of_matrix[1][0] &&
            size_of_matrix[0][1] == size_of_matrix[1][1]) {
            result_matrix_size[0] = size_of_matrix[0][0];
            result_matrix_size[1] = size_of_matrix[0][1];
        } else {
            fprintf(stderr, "Error: Chybny vstup!\n");
            for (int i = 0; i <= matrix_counter; i++) {
                free(*(matrix + i));
            }
            free(matrix);
            return 100;
        }
    }
    /* -------------------------------------------------------------- */
    // final complete test of whole matrix array
    for (int i = 1; i < matrix_counter; i++) {
        if (math_symbol[i] == '*') {
            if (size_of_matrix[i - 1][1] == size_of_matrix[i][0] &&
                result_matrix_size[0] == size_of_matrix[i - 1][0] &&
                result_matrix_size[1] == size_of_matrix[i][1]) {
                continue;
            } else {
                fprintf(stderr, "Error: Chybny vstup!\n");
                for (int i = 0; i <= matrix_counter; i++) {
                    free(*(matrix + i));
                }
                free(matrix);
                return 100;
            }
        } else {
            if (i != NUMBER_OF_MATRIX - 1 &&
                math_symbol[i + 1] != '*') { // case + +
                if (result_matrix_size[0] == size_of_matrix[i][0] &&
                    result_matrix_size[1] == size_of_matrix[i][1]) {
                    continue;
                } else {
                    fprintf(stderr, "Error: Chybny vstup!\n");
                    for (int i = 0; i <= matrix_counter; i++) {
                        free(*(matrix + i));
                    }
                    free(matrix);
                    return 100;
                }
            }
        }
    }
    /* -------------------------------------------------------------- */

    result_matrix = (int *)calloc(result_matrix_size[0] * result_matrix_size[1],
                                  sizeof(int));
    /* ------------------------------------------------------------ */
    if (math_symbol[1] == '*') {
        int multiply_result = 0;
        multiply_result = multiply(result_matrix, *(matrix + 0), *(matrix + 1),
                                   size_of_matrix[0][0], size_of_matrix[0][1],
                                   size_of_matrix[1][0], size_of_matrix[1][1]);
        if (multiply_result == 1) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            for (int i = 0; i <= matrix_counter; i++) {
                free(*(matrix + i));
            }
            free(matrix);
            free(result_matrix);
            return 100;
        }
    } else {
        count(math_symbol[1], result_matrix, *(matrix + 0), *(matrix + 1),
              size_of_matrix[0][0], size_of_matrix[0][1]);
    }
    /* ------------------------------------------------------------ */
    // TODO - test

    // result matrix print
    printf("%i %i\n", result_matrix_size[0], result_matrix_size[1]);
    for (int row = 0; row < result_matrix_size[0]; row++) {
        for (int column = 0; column < result_matrix_size[1]; column++) {
        	if(column == 0) {
        		printf("%i",
                   *(result_matrix + row * result_matrix_size[1] + column));
        	} else {
            printf(" %i",
                   *(result_matrix + row * result_matrix_size[1] + column));
            }
        }
        printf("\n");
    }

    // free every matrix in matrix
    for (int i = 0; i <= matrix_counter; i++) {
        free(*(matrix + i));
    }
    free(result_matrix);
    free(matrix);
}

void count(char math_symbol, int *result, int *a, int *b, int rows, int columns)
{
    if (math_symbol == '+') {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                *(result + (row * columns + column)) =
                    *(a + (row * columns + column)) +
                    *(b + (row * columns + column));
            }
        }
    } else if (math_symbol == '-') {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                *(result + (row * columns + column)) =
                    *(a + (row * columns + column)) -
                    *(b + (row * columns + column));
            }
        }
    }
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
