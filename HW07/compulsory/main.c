#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lock.h"

#define True 1
#define False 0

char *read_input(void);
void reallocate(char **pointer, int size);
void check_allocation(void *pointer);
void check_input(char *input);
void free_all(char *pointer, int exit_code);

void generate_passwords(char *str_input, int level, char *result);

static int str_size = 0;
static int pss_counter = 0;
static int is_optional = False;

static int is_unloced = False;
/* The main program */
int main(int argc, char *argv[])
{
    const char optional_part_command[] = "-prp-optional";

    char *str_input = read_input();
	check_input(str_input);


	if(argc != 1) {
        for (int i = 0; i < argc; i++) {
            if (strcmp(optional_part_command, *(argv + i)) == 0) {
                is_optional = True;
            }
        }
    }
    str_size = strlen(str_input);

    char *result = (char*)calloc(str_size+1, sizeof(char));

    generate_passwords(str_input, str_size,result);

    free(result);

    if(is_optional && is_unloced == False) {
    	free_all(str_input, 101);
    } else {
    	free_all(str_input, 0);
    }
    
}

void generate_passwords(char *str_input, int level, char *result)
{
	if (level) {
		for (int i = 0; i < str_size; i++) {
			int flag = 0;
			for(int u = str_size - level - 1; u >= 0; u--) {
				if(*(result + u) == *(str_input + i)){
					flag = 1;
					break;
				}
			}
			if(flag == 1) continue;
			*(result + str_size - level) = *(str_input + i);
			generate_passwords(str_input, level-1, result);
		}
	} else {
		if(is_optional) {
			*(result + str_size) = '\0';
			if(unlock(result)) {
				pss_counter++;
				printf("%s - %ix\n", result, pss_counter);
				is_unloced = True;
				free(result);
				free_all(str_input, 0);
			} else {
				pss_counter++;
			}
		} else {
			*(result + str_size) = '\0';
			printf("%s\n", result);
		}		
	}	
}

void check_input(char *input) 
{
	int input_len = strlen(input);
	
	for(int i = 0; i < input_len; i++) {
		char c = *(input + i);
		if(c >= 48 &&  c <= 57){ // numbers
			continue;
		} else if( c >= 65 && c <= 90) { // capitals
			continue;
		} else if( c >= 97 && c <= 122) { // small leters
			continue;
		} else {
			free_all(input, 100);
		}
	}
}

char *read_input(void)
{
    /* reads one line from the input line*/
    char letter = '0';
    int scan_result = scanf("%c", &letter);

    if (scan_result == -1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    int input_allocated = 10;
    char *input = (char *)malloc(input_allocated * sizeof(char));

    check_allocation(input);

    int input_len = -1;
    while (scan_result != -1 && letter != '\n') {
        input_len++;

        if (input_len + 1 >= input_allocated) {
            input_allocated = 2*input_allocated;
            reallocate(&input, input_allocated);
            check_allocation(input);
        }

        *(input + input_len) = letter;
        scan_result = scanf("%c", &letter);
    }

    input_len += 2;
    reallocate(&input, input_len);
    check_allocation(input);

    *(input + input_len - 1) = '\0';
    return input;
}

void check_allocation(void *pointer)
{
    if (pointer == NULL) {
        fprintf(stderr, "Memory error!\n");
        exit(110);
    }
}

void reallocate(char **pointer, int size)
{
    char *temp = (char *)realloc(*pointer, size * sizeof(char));
    if (temp == NULL) {
        fprintf(stderr, "Memory error!\n");
        exit(110);
    }
    *pointer = temp;
}

void free_all(char *pointer, int exit_code) {
	free(pointer);
	if(exit_code != 0){
		if(exit_code == 100) {
			fprintf(stderr, "Error: Chybny vstup!\n");
			exit(exit_code);
		} else if(exit_code == 101) {
			fprintf(stderr, "Error: Heslo nebylo nalezeno!\n");
			exit(exit_code);
		}		
	} else {
		exit(0);
	}
}
