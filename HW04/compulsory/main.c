#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int *sieve(int *index_counter)
{
    int size_of_row = 500001;
    int *row_numbers = malloc((size_of_row) * sizeof(int));
    for (int i = 0; i < size_of_row; i++) { // filling of the array
        row_numbers[i] = 2*i+1;
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

void print_number(long long int input, int prime_numbers[],
                  int index_counter) // mela by v budoucnu vypsat cisla  
{
    int same_numbers = 0;
    long long int last_number = 2;

    printf("Prvociselny rozklad cisla %lli je:\n", input);
    long long int rest_of_number = input;

    for (int i = 0; i < index_counter; i++) {         // TODO index_counter
        if (rest_of_number % prime_numbers[i] == 0) { // TODO prime_numbers
            rest_of_number = rest_of_number / prime_numbers[i];
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
            if (rest_of_number == 1) {
                if (same_numbers == 1) {
                    printf("%lli\n", last_number);
                } else {
                    printf("%lli^%i\n", last_number, same_numbers);
                }
                break;
            } else {
                i = -1;
            }
        }
    }
    //konec vypisu
}

/* The main program */
int main(int argc, char *argv[])
{
	int index_counter = 0;
    int *prime_numbers = sieve(&index_counter);
    long long int input = 0; // %lli
    for (;;) {               // infinite loop for scanning numbers
        int input_test = scanf("%lli", &input); // input test
        if (input_test == 0 || input < 0) {     // 0 if char
            fprintf(stderr, "Error: Chybny vstup!\n");
            free(prime_numbers);
            return 100;
        } else if (input_test == -1 || input == 0) { //-1 if EOF
        	free(prime_numbers);
            return 0;
        } else if (input == 1) {
            printf("Prvociselny rozklad cisla 1 je:\n1\n");
            continue;
        }
        print_number(input, prime_numbers, index_counter);
    }
}

