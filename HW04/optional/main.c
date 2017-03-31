#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *sieve(int *index_counter);
int get_modulo(char input[], int factor);
char *division_algorithm(char input[], int divisor, unsigned long int *modulo);
void print_number(char input[], int prime_numbers[], int index_counter);

int main(int argc, char *argv[])
{
    int index_counter = 0;
    int *prime_numbers = sieve(&index_counter); // finding prime numbers

    const int length = 1000000; // maximal length of array

    char *input;
    input = (char *)malloc(length * sizeof(char));

    for (;;) { // infinite loop for scanning numbers
    	
        if (scanf("%100s", input) == -1) {
            free(input);
            free(prime_numbers);
            return 100;
        }
        if (*input == '-' || *input < 48 || *input > 57) { // 48 = 0 in ASCII
            fprintf(stderr, "Error: Chybny vstup!\n");
            free(input);
            free(prime_numbers);
            return 100;
        } else if (*input == '0') { //-1 if EOF
            free(input);
            free(prime_numbers);
            return 0;
        }
        print_number(input, prime_numbers, index_counter); // whole algorithm
        // free(input);
        // input = (char *)malloc(length * sizeof(char));
    }
}

void print_number(char input[], int prime_numbers[], int index_counter)
{
    int same_numbers = 0;
    long long int last_number = 1;
    char *rest_of_number;
    rest_of_number = input;
    unsigned long int modulo = 100;
    printf("Prvociselny rozklad cisla %s je:\n", rest_of_number);
    if (strlen(rest_of_number) == 1 && rest_of_number[0] == '1') {
        printf("1\n");
        return;
    }
    for (int i = 0; i < index_counter; i++) {
        // from last index of prime_numbers
        free(division_algorithm(rest_of_number, prime_numbers[i],
                                &modulo)); // ?is modulo 0?
        if (modulo == 0) {
            rest_of_number = division_algorithm(
                rest_of_number, prime_numbers[i],
                &modulo); // real array of new numbers is rest_of_number

            if (prime_numbers[i] == last_number) {
                same_numbers++;
            } else {
                if (same_numbers == 1) {
                    printf("%lli x ", last_number);
                } else if (same_numbers != 0) {
                    printf("%lli^%i x ", last_number, same_numbers);
                }
                last_number = prime_numbers[i];
                same_numbers = 1;
            }
            if (strlen(rest_of_number) == 1 && rest_of_number[0] == '1') {
                if (same_numbers == 1) {
                    printf("%lli\n", last_number);
                } else {
                    printf("%lli^%i\n", last_number, same_numbers);
                }
                break;
            } else {
                i = -1;
            }
        } else {
            continue;
        }
    }
    free(rest_of_number);
}

char *division_algorithm(char input[], int divisor, unsigned long int *modulo)
{
    char *divided_number = (char *)malloc(1000000 * sizeof(char)); // new array
    int string_length = strlen(input);
    int output_arr_index = 0;
    int end_of_calc = 0;
    unsigned long calculation = 1;

    for (int i = 0; i <= string_length; i++) { // unpack whole initial string
        input[i] = input[i] - 48;
    }

    calculation = input[0];
    *modulo = input[0];

    for (int i = 1; i <= string_length;
         i++) { // division algorithm - "as on paper"
        if (divisor <= calculation) {
            divided_number[output_arr_index++] = calculation / divisor;
            calculation = calculation % divisor;
            *modulo = calculation;
            calculation = calculation * 10 + input[i];
            end_of_calc = 1;

        } else {
            *modulo = calculation;
            calculation = calculation * 10 + input[i];
            if (end_of_calc == 1)
                divided_number[output_arr_index++] = 0;
        }
    }

    for (int i = 0; i <= string_length; i++) { // pack it
        input[i] = input[i] + 48;
    }
	
	if (*modulo != 0) {
        free(divided_number);
        return NULL;
    } else {
    	for (int i = 0; i < output_arr_index; i++) { // pack new outgoing string
        	divided_number[i] = divided_number[i] + 48;
    	}
    	divided_number[output_arr_index] = '\0'; // edning of new string
        return divided_number;
    }    
}

int *sieve(int *index_counter) // sieve of erathoset
{
    int size_of_row = 500001;
    int *row_numbers = malloc((size_of_row) * sizeof(int));
    for (int i = 0; i < size_of_row; i++) { // filling of the array
        row_numbers[i] = 2 * i + 1;
    }
    row_numbers[0] = 2;
    row_numbers[1] = 3;
    int temp = sqrt(size_of_row);

    for (int i = 0; i < temp; i++) {
        if (row_numbers[i] == 0) {
            continue;
        } else {
            for (int j = i; j < size_of_row; j += row_numbers[i]) {
                if (row_numbers[j] == 0 || j == i) {
                    continue;
                } else {
                    if (row_numbers[j] % row_numbers[i] == 0) {
                        row_numbers[j] = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < size_of_row; i++) {
        if (row_numbers[i] != 0) {
            (*index_counter)++;
        }
    }

    int *prime_numbers = malloc((*index_counter) * sizeof(int));
    int index_number_prim = 0;
    for (int i = 0; i < size_of_row; i++) {
        if (row_numbers[i] != 0) {
            prime_numbers[index_number_prim] = row_numbers[i];
            index_number_prim++;
        }
    }
    free(row_numbers);
    return prime_numbers;
}
