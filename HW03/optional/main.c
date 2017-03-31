#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
    // TODO - insert your code here
    int height, width, fence;
    int print_fence = 0;

    if (scanf("%i", &width) == 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return 100;
    }

    if (scanf("%i", &height) == 0) // chybny vstup
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return 100;
    }

    if (width < 3 || width > 69 || height < 3 || height > 69) // chybny interval
    {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return 101;
    }

    if (width % 2 == 0) // liche nebo sude cislo
    {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return 102;
    }

    if (width == height) // volitelny, nacteni dalsiho cisla
    {
        int fence_state = scanf("%i", &fence);
        if (fence_state == 0) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return 100;
        }
        if (fence >= height || fence <= 0) {
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            return 103;
        } else {
            print_fence = 1;
        }
    }
    // strecha
    int temp = width / 2;
    for (int i = 0; i < temp; i++) {
        for (int j = 0; j < width; j++) {
            if (j == (temp - i) || j == (temp + i)) {
                if (j == (temp + i)) {
                    printf("X");
                    break;
                }
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < height; i++) // domecek
    {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1)) {
                printf("X");
            } else // volitekna uhola
            {
                if (print_fence == 1) {
                    if (i % 2 == 1) {
                        if (j % 2 == 1) {
                            printf("o");
                        } else {
                            printf("*");
                        }
                    } else {
                        if (j % 2 == 1) {
                            printf("*");
                        } else {
                            printf("o");
                        }
                    }
                } else {
                    printf(" ");
                }
            }
        }

        if (print_fence == 0 || i < (height - fence)) {
            printf("\n");
        } else // TODO plot
        {
            int temp2 = height - fence;
            for (int z = 0; z < fence; z++) {
                if ((i == height - 1 || i == temp2) && fence % 2 == 0) {
                    if (z % 2 == 0) {
                        printf("-");
                    } else {
                        printf("|");
                    }
                } else if (fence % 2 == 0) {
                    if (z % 2 == 0) {
                        printf(" ");
                    } else {
                        printf("|");
                    }
                } else if (fence % 2 == 1 && (i == height - 1 || i == temp2)) {
                    if (z % 2 == 0) {
                        printf("|");
                    } else {
                        printf("-");
                    }
                } else if (fence % 2 == 1) {
                    if (z % 2 == 1) {
                        printf(" ");
                    } else {
                        printf("|");
                    }
                }
            }
            printf("\n");
        }
    }

    return 0;
}

