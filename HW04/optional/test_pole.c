#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


/*int get_modulo(char input[], int divisor) 
{
	int string_length = strlen(input);
	
	for(int i=0;i<=string_length;i++){
         input[i] = input[i] - 48;
    }
	
	unsigned long int rest_of_number = input[0];
	unsigned long int temp = 1;
	
    for(int i=1;i<=string_length;i++){
         if(divisor<=temp){
             temp = temp % divisor;
             rest_of_number = temp;
             temp =temp*10 + input[i];

         }
         else{
             rest_of_number = temp;
             temp =temp*10 + input[i];
         }
    }
    
    for(int i=0;i<=string_length;i++){
         input[i] = input[i] + 48;
    }
    
    return rest_of_number;
}
*/
int get_modulo(char a[],unsigned long b){
//http://www.cquestions.com/2010/08/division-of-large-numbers-in-c.html
    static char c[100000000];
    int la;
    int i,k=0,flag=0;
    unsigned long temp=1,reminder;
    la=strlen(a);

    for(i=0;i<=la;i++){
         a[i] = a[i] - 48;
    }

    temp = a[0];
    reminder = a[0];
    for(i=1;i<=la;i++){
         if(b<=temp){
             c[k++] = temp/b;
             temp = temp % b;
             reminder = temp;
             temp =temp*10 + a[i];
             flag=1;

         }
         else{
             reminder = temp;
             temp =temp*10 + a[i];
             if(flag==1)
                 c[k++] = 0;
         }
    }

    for(i=0;i<k;i++){
         c[i]=c[i]+48;
    }
    c[i]= '\0';
    //printf("size %lu\n", sizeof(c));

    //printf("Reminder of division:  %lu  ",reminder);
    return reminder;
 }
char *division_algorithm(char input[], int divisor)
{
	int string_length = strlen(input);	
    for (int i = 0; i <= string_length; i++) {
        input[i] = input[i] - 48;
    }	
    
    char *divided_number = (char *)malloc((string_length+1) * sizeof(char));
    int output_arr_index = 0;
    int flag = 0;
    unsigned long int temp = input[0];
    unsigned long int rest_of_number = input[0];

    for (int i = 1; i <= string_length; i++) {
        if (divisor <= temp) {
            divided_number[output_arr_index++] = temp / divisor;
            temp = temp % divisor;
            rest_of_number = temp;
            temp = temp * 10 + input[i];
            flag = 1;

        } else {
            rest_of_number = temp;
            temp = temp * 10 + input[i];
            if (flag == 1)
                divided_number[output_arr_index++] = 0;
        }
    }
    
    for (int i = 0; i < output_arr_index; i++) {
        divided_number[i] = divided_number[i] + 48;
    }
    divided_number[output_arr_index] = '\0';
    
    divided_number = (char *) realloc(divided_number, (output_arr_index)*sizeof(char));
 	return divided_number;   
}
 
void print(char input[]) {
	int iter = 2;
	char *c = input;
	printf("%s\n", input);
	char *te;
	int mod;
	while(strlen(c) != 0) {
		if(strlen(c) == 1 && c[0] == '1') {
			printf("last -  %s\n",c);
			break;
		}
		else {
			mod = get_modulo(c, iter);
			if(mod == -48) {
				te = division_algorithm(c,iter);
    			printf("%i -  %s\n",iter,te);
    			c = te;
    			iter = 2;
    			continue;
			}
			else {
				iter++;
			}
			
		} 		
   	}
}


int main(int argc, char *argv[])
{	
	char *cislo = (char *)malloc(100000000 * sizeof(char));    
    //char cislo[100000000];
    scanf("%s",cislo);
    //int delitel;
    //scanf("druhe - %i", &delitel);
	//printf("treti - %i\n", get_modulo(cislo, delitel));
	print(cislo);
    
    return 0;
	
}

