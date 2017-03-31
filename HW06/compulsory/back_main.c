#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0

char *read_input(int *len);
int check_input(char *input, int input_len);
char *get_result(char *cipher, char *tapped_text, int size);

void pack_unpack(char *input, int len, char p_u);
void print_result(char *result, char *cipher, char *tapped_text);
void free_all(char *cipher, char *tapped_text, int exit_code);
void check_allocation(void *pointer);

void optional_part(void);
void mandatory_part(void);

int main(int argc, char *argv[])
{
    const char optional_part_command[] = "-prp-optional";

    if (argc == 1 || strcmp(optional_part_command, *(argv + 1)) != 0) {
        mandatory_part();
    } else {
        optional_part();
    }
}

void mandatory_part(void)
{
    int cipher_len = 0;
    char *cipher = read_input(&cipher_len);
    int tapped_text_len = 0;
    char *tapped_text = read_input(&tapped_text_len);

    /* ascii check - if it's successful return value is 0 */
    int check_result = check_input(cipher, cipher_len);
    if (check_result != 0) {
        free_all(cipher, tapped_text, check_result);
    }
    check_result = check_input(tapped_text, cipher_len);
    if (check_result != 0) {
        free_all(cipher, tapped_text, check_result);
    }

    if (cipher_len != tapped_text_len)
        free_all(cipher, tapped_text, 101);

    char *result = get_result(cipher, tapped_text, cipher_len);

    print_result(result, cipher, tapped_text);
}

void optional_part(void)
{
    // TODO here
	exit(100);
    int cipher_len = 0;
    char *cipher = read_input(&cipher_len);
    int tapped_text_len = 0;
    char *tapped_text = read_input(&tapped_text_len);

    int check_result = check_input(cipher, cipher_len);
    if (check_result != 0) {
        free_all(cipher, tapped_text, check_result);
    }
    check_result = check_input(tapped_text, cipher_len);
    if (check_result != 0) {
        free_all(cipher, tapped_text, check_result);
    }

    int result_size = 10;
    char *result = (char *)malloc(result_size * sizeof(char));

    print_result(result, cipher, tapped_text);
}

char *read_input(int *len)
{
    /* reads one line from the input line*/
    char letter = '0';
    int scan_result = scanf("%c", &letter);

    if (scan_result == -1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    int input_allocated = 500;
    char *input = (char *)malloc(input_allocated * sizeof(char));

    check_allocation(input);

    int input_len = -1;
    while (scan_result != -1 && letter != '\n') { //TODO - check allocation -> timeouts
        input_len++;

        if (input_len + 1 >= input_allocated) {
            input_allocated = 2*input_allocated;
            input = (char *)realloc(input, input_allocated * sizeof(char));
            check_allocation(input);
        }

        *(input + input_len) = letter;
        scan_result = scanf("%c", &letter);
    }

    input_len += 2;
    input = (char *)realloc(input, input_len * sizeof(char));
    check_allocation(input);

    *(input + input_len - 1) = '\0';
    *len = input_len;
    return input;
}

int check_input(char *input, int input_len)
{
    /* ASCII check - success -> return value 0, otherwise 100*/
    *(input + input_len - 1) = 'a';
    for (int i = 0; i < input_len; i++) {
        if (*(input + i) < 65 || *(input + i) > 122) {
            return 100;
        } else if (*(input + i) > 90 && *(input + i) < 97) {
            return 100;
        } else {
            continue;
        }
    }
    *(input + input_len - 1) = '\0'; // end of the string
    return 0;
}

char *get_result(char *cipher, char *tapped_text, int size)
{
    /* let's get wannted result of cipher */
    char *result = (char *)malloc(size * sizeof(char));
    size -= 1;

    pack_unpack(cipher, size, 'u');
    pack_unpack(tapped_text, size, 'u');


    for(int i = 0; i< size;i++) {

    	*(result + i) = *(cipher + i);
    	//printf("%i ", *(result + i));
    }
    //printf("\n");
    
    int final_distance = 0;
    int index = 1;
    for(int i = 1; i < 52; i++) {
    	int distance = 0;
    	for(int j = 0; j < size; j++) {
    		*(result + j) = (*(result + j) + 1)%52;
    		
    		//printf("%2i - %2i\n", *(result + j), *(tapped_text + j));

    		if(*(result + j) == *(tapped_text + j)) {
    			distance++;
    		}
    	}
    	//printf("\ndistance %i\n\n", distance);
    	if(distance == 0) continue;
    	if(final_distance < distance) {
    		final_distance = distance;
    		//printf("index = %i, distance = %i\n",index, final_distance);
    		index = i;
    	}
    }

    for(int i = 0; i < size; i++){
    	*(result + i) = (*(cipher + i) + index)%52;
    }

    //printf("index = %i, distance = %i\n",index, final_distance);
    //exit(10);
    pack_unpack(result, size, 'p');
    *(result + size) = '\0';

    return result;
}

void pack_unpack(char *input, int len, char p_u)
{
    if (p_u == 'u' || p_u == 'U') {

        for (int i = 0; i < len; i++) {
            if (*(input + i) < 91) {
                *(input + i) -= 65;
            } else {
                *(input + i) -= 71;
            }
        }

    } else {
        for (int i = 0; i < len; i++) {
            if (*(input + i) < 26) {
                *(input + i) += 65;
            } else {
                *(input + i) += 71;
            }
        }
    }
}

void free_all(char *cipher, char *tapped_text, int exit_code)
{
    /* end of the programme */

    free(cipher);
    free(tapped_text);

    if (exit_code == 100) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    } else if (exit_code == 101) {
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        exit(101);
    } else if (exit_code == 0) {
        exit(0);
    }
}

void print_result(char *result, char *cipher, char *tapped_text)
{
    /* it will print result and end the program*/
    printf("%s\n", result);
    free(result);
    free_all(cipher, tapped_text, 0);
}

void check_allocation(void *pointer) {
	if(pointer == NULL) {
		fprintf(stderr, "Memory error.\n");
    	exit(110);
	}
}
