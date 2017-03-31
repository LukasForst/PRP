#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  // TODO - insert your code here
  	int num_one;
	int num_two;
	scanf("%i", &num_one);
	scanf("%i", &num_two);
	if(num_one>10000 || num_one<-10000 || num_two>10000 || num_two<-10000)
	{
		printf("Vstup je mimo interval!\n");
		return 0;
	}
	printf("Desitkova soustava: %i %i\n", num_one, num_two);
	printf("Sestnactkova soustava: %x %x\n", num_one, num_two);
	printf("Soucet: %i + %i = %i\n", num_one, num_two, num_one+num_two);
	printf("Rozdil: %i - %i = %i\n", num_one, num_two, num_one-num_two);
	printf("Soucin: %i * %i = %i\n", num_one, num_two, num_one*num_two);
	if(num_two == 0)
	{
		printf("Nedefinovany vysledek!\n");
	}
	else
	{
		printf("Podil: %i / %i = %i\n", num_one, num_two, num_one/num_two);
	}
	float avg = (num_one+num_two)/2.0;
	printf("Prumer: %.1f\n", avg);
	return 0;
  return 0;
}

