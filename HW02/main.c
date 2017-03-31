#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{  
  int input = 0;
  int loaded = 0;
  int plus = 0;
  int minus = 0;
  int even = 0;
  int odd = 0;
  int max = -10000;
  int min = 10000;
  int sum = 0;
  int number = 0;
  
  while(scanf("%d", &input) > 0)
  { 
  	if(input>10000 || input<-10000)
	{
		printf("\nError: Vstup je mimo interval!\n");
		return 100;
	}
	else
	{
		if(loaded == 0)
  		{
  			printf("%d", input); //vypsani posledniho cisla
  		}
  		else
  		{
  			printf(", %d", input);
  		}
	}
	
	loaded ++;//pocet cisel dohromady
	
	if(input>0) //kladne nebo zaporne, nula se nepocita
	{
		plus++;
	}
	else if(input<0)
	{
		minus++;
	}
	
	if(input%2 == 0)
	{
		even++;
	}
	else
	{
		odd++;
	}
	
	if(input < min) //prirazeni minima
	{
		min = input;
	}
	if(input > max) //prirazeni maxima
	{
		max = input;
	}
	
	sum += input;
	number++;
	
	

  }
  
  printf("\n"); //odradkovani
  
  float plus_perc = (float)plus/loaded; //procenta kladna
  float minus_perc = (float)minus/loaded; //procenta zaporna
  float even_perc = (float)even/loaded; //procenta sudych
  float odd_perc = (float)odd/loaded; //procenta liche
  float avg = (float)sum/number; //prumer
  
  plus_perc *= 100;
  minus_perc *= 100;
  even_perc *= 100;
  odd_perc *=100;
  
  printf("Pocet cisel: %i\n", number);
  printf("Pocet kladnych: %i\n", plus);
  printf("Pocet zapornych: %i\n", minus);
  printf("Procento kladnych: %.2f\n", plus_perc);
  printf("Procento zapornych: %.2f\n", minus_perc);
  printf("Pocet sudych: %i\n", even);
  printf("Pocet lichych: %i\n", odd);
  printf("Procento sudych: %.2f\n", even_perc);
  printf("Procento lichych: %.2f\n", odd_perc);
  printf("Prumer: %.2f\n", avg);
  printf("Maximum: %i\n", max);
  printf("Minimum: %i\n", min);
  
  
  return 0;
}

