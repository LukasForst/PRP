#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  // TODO - insert your code here
  int height, width;
  
  if(scanf("%i", &width) == 0)
  {
  	fprintf(stderr, "Error: Chybny vstup!\n");
  	return 100;
  }
  
  if(scanf("%i", &height) == 0) //chybny vstup
  {
  	fprintf(stderr, "Error: Chybny vstup!\n");
  	return 100;
  }  
  
  if(width < 3 || width > 69 || height < 3 || height > 69) // chybny interval
  {
  	fprintf(stderr, "Error: Vstup mimo interval!\n");
  	return 101;
  }
  
  if(width%2 == 0) // liche nebo sude cislo
  {
  	fprintf(stderr, "Error: Sirka neni liche cislo!\n");
  	return 102;
  }
  
  //TODO strecha
  
  int temp =  width/2;
  for(int i = 0; i < temp; i++)
  {
  	for(int j = 0 ; j < width; j++)
  		{
  			if(j == (temp-i) || j == (temp+i))
  			{
  				if(j == (temp+i))
  				{
  					printf("X");
  					break;
  				}
  				printf("X");
  			}
  			else
  			{
				printf(" ");
  			}
  		}
  		printf("\n");
  }

  
  for(int i = 0; i < height; i++) //domecek
  {
  	for(int j = 0; j < width; j++)
  		if(i == 0 || i == (height-1) || j == 0 || j == (width-1))
  		{
  			printf("X");
  		}
  		else
  		{
  			printf(" ");
  		}
  	printf("\n");
  }
  
  return 0;
}

