#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0

// Macro for getting minimal value from three values
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

char *read_input(int *len);
int check_input(char *input, int input_len);
char *get_result(char *cipher, char *tapped_text, int size);

void pack_unpack(char *input, int len, char p_u);
void print_result(char *result, char *cipher, char *tapped_text);
void free_all(char *cipher, char *tapped_text, int exit_code);
void check_allocation(void *pointer);
void reallocate(char **pointer, int size);

int levenshtein(char *s1, int s1len, char *s2m, int s2len);

void optional_part(void);
void mandatory_part(void);

static int is_optional = False;

static int tapped_size = 0;

int main(int argc, char *argv[])
{
    const char optional_part_command[] = "-prp-optional";

    if (argc == 1) {
        mandatory_part();
    } else {
        for (int i = 0; i < argc; i++) {
            if (strcmp(optional_part_command, *(argv + i)) == 0) {
                is_optional = True;
                optional_part();
            }
        }
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

    tapped_size = tapped_text_len;

    char *result = get_result(cipher, tapped_text, cipher_len);

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
    while (scan_result != -1 &&
           letter != '\n') { // TODO - check allocation -> timeouts
        input_len++;

        if (input_len + 1 >= input_allocated) {
            input_allocated = 2 * input_allocated;
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

    int final_levensthein = 9999;
    int final_levensthein_index = 0;

    for (int i = 0; i < size; i++) {
        *(result + i) = *(cipher + i);
    }

    int final_distance = 0;
    int index = 0;
    for (int i = 1; i < 53; i++) {
        int distance = 0;
        int leven = 0;
        for (int j = 0; j < size; j++) {
            *(result + j) = (*(result + j) + 1) % 52;

            if (*(result + j) == *(tapped_text + j)) {
                distance++;
            }
        }

        if (is_optional == True) {
            leven = levenshtein(result, size, tapped_text, tapped_size);
            if (leven < final_levensthein) {
                final_levensthein = leven;
                final_levensthein_index = i;
            }
        }

        if (final_distance < distance) {
            final_distance = distance;
            index = i;
        }
    }

    for (int i = 0; i < size; i++) {
        if (is_optional) {
            *(result + i) = (*(cipher + i) + final_levensthein_index) % 52;
        } else {
            *(result + i) = (*(cipher + i) + index) % 52;
        }
    }

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

void check_allocation(void *pointer)
{
    if (pointer == NULL) {
        fprintf(stderr, "Memory error.\n");
        exit(110);
    }
}

void reallocate(char **pointer, int size)
{
    char *temp = (char *)realloc(*pointer, size * sizeof(char));
    if (temp == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(110);
    }
    *pointer = temp;
}

/* Source of Levensthein distance according to the ISO:
 * Algorithm Implementation/Strings/Levenshtein distance [online]. 16 September
 * 2016, at 08:05th ed. https://en.wikibooks.org, [cited 16 Dec 1]. Available from:
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.
 */

/* Necessary changes were made for succesfull implementation in my program.*/


int levenshtein(char *s1, int s1len, char *s2, int s2len)
{
    unsigned int x, y, lastdiag, olddiag;
    unsigned int column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1,
                             lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return (column[s1len]);
}

/* End of the reference */
