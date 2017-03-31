#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#define MAX 10000

char * division(char [],unsigned long);
int main(){
    char a[MAX];
    unsigned long b;
    char *c;
    printf("Enter the divdend : ");
    scanf("%s",a);
    printf("Enter the divisor : ");
    scanf("%lu",&b);
    c = division(a,b);
    printf("\nQuotient of the division : ");
    printf("%s\n",c);
    return 0;
}

char * division(char a[],unsigned long b){
//http://www.cquestions.com/2010/08/division-of-large-numbers-in-c.html
    static char c[MAX];
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
    printf("size %lu\n", sizeof(c));

    printf("Reminder of division:  %lu  ",reminder);
    return c;
 }
