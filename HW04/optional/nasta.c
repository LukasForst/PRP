#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * deleni(char[],long long int);
char * nuly_pryc(char[]);
long long int zustatek;

int main(int argc, char *argv[])
{
	char *num;
	char *num_pomoc;
	char *num_pomoc2;
	char *ulozit;
	char value[100];
	int d = 78498; /* Pocet prvocisel do 10^6*/
	int *p_d;
	p_d = &d;
	int mocnina = 0;
	int ret;
	int suma_num = 0;

	/* Sito */

	unsigned int limit = 1000000;
	unsigned int n = limit;
	int *cisla = malloc(sizeof(int) * n);

	for (int i = 1; i < n; i++) {
		cisla[i] = 1;
	}	
	for (int m = 2; m < n; m++) {
		for (int j = m*2; j < n; j += m) {
			cisla[j] = 0;
		}
	}

	int *prvocisla = malloc(sizeof(int) * *p_d);

	for (int i = 2, k = 0; i < n; i++, k++) {
		if (cisla[i] == 1) {
			prvocisla[k] = i;
		} else {
			k -= 1;
		}
	}

	free(cisla);

	/* Nacteni vstupu */

	while (scanf("%s", value) == 1) {

		ret = strncmp(value, "0", 1);
		if (ret == 0) {
			free(prvocisla);
			return 0;
		} else {
			int i = 0;
			while (value[i]) {
				if (value[i] < 48 || value[i] > 57) {		
					fprintf(stderr,"Error: Chybny vstup!\n");
					free(prvocisla);
					return 100;
				} else if (value[i] == 0) {
					free(prvocisla);			
					return 0;
				} else {
					i += 1;
				}
			}

			/* Rozklad */

			printf("Prvociselny rozklad cisla %s je:\n",value);

			ret = strncmp(value, "1", 100);

			if (ret == 0) {
				printf("%s\n", value);
			} else {
				num = value;
				num_pomoc = num;

				suma_num = 0;
				ret = 0;

				for (unsigned int i = 0; i < *p_d; i++) {

					if (suma_num == 1) {
						break;
					}

					num_pomoc = num;
					num = deleni(num, prvocisla[i]);

					if (zustatek == 0) {
						while (zustatek == 0) {
							mocnina += 1;

							num = nuly_pryc(num);
							num_pomoc2 = num;
							num = deleni(num, prvocisla[i]);

							suma_num = 0;
							for (int j = 0; j < strlen(num); j++) {
								suma_num += num[j]-48;
							}	
							if (suma_num == 0) {
								break;
							}
						}
						suma_num = 0;
						int len_num = strlen(num_pomoc2);
						for (int j = 0; j < len_num; j++) {
							suma_num += num[j]-48;
						}
						if (suma_num == 0) {
							if (mocnina == 1) {
								printf("%i\n", prvocisla[i]);
							} else {
								printf("%i^%i\n", prvocisla[i], mocnina);
							}
						} else {
							if (mocnina == 1) {
								printf("%i x ", prvocisla[i]);
							} else {
								printf("%i^%i x ", prvocisla[i], mocnina);
							}
						}

						mocnina = 0;
						ulozit = num_pomoc2;
						num = num_pomoc2;

					} else {
						num = ulozit;
					}
					suma_num = 0;
					int len_num = strlen(num_pomoc2);
					for (int j = 0; j < len_num; j++) {
						suma_num += num[j]-48;
					}
				}
			}

		}
	}	
}

char * nuly_pryc(char num[])
{
	int delka = strlen(num);
	int k = 0;
	int i = 0;
	int pomoc = 0;
	static char nove_cislo[100];

	for (i = 0; i <= delka; i++) {
		if (num[i] == 48 && pomoc == 0) {
			continue;
		} else if (num[i] == 48 && pomoc == 1) {
			nove_cislo[k++] = num[i];
		} else {
			nove_cislo[k++] = num[i];
			pomoc = 1;
		}
	}

	nove_cislo[k] = '\0';

	return nove_cislo;
}


char * deleni(char value[], long long int delitel)
{

	static char podil[100];
	long long int temp = 0;
	int i = 0;
	int j = 0;

	value = nuly_pryc(value);

	while (value[i]) {
		temp = temp*10 + (value[i] - 48);
		if (temp < delitel) {
			podil[j++] = 48;
		} else {
			podil[j++] = (temp / delitel) + 48;
			temp = temp % delitel;
		}
		i += 1;
	}
	
	podil[j] = '\0';
	zustatek = temp;
	return podil;
}
