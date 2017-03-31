#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int * newMatrix(int row, int column){
    return (int *)calloc(row * column,sizeof(int));
}

void delMatrix(int *matrix){
    free(matrix);
}

bool readMatrix (int *matrix, int row, int column){
    for (int i=0;i<row;++i){
        for (int j=0; j<column; ++j){
            if (scanf("%i\n", &matrix[i * column +j])!=1){
				return false;
            }   
        }
    }
    return true;
}

void printMatrix(int *matrix, int row, int column){
    for (int i=0;i<row; ++i){
        for (int j=0; j<column; ++j){
            if (j==0){
            	printf("%i", matrix[i * column +j]) ;
            } else{
            	printf(" %i", matrix[i * column +j]) ;
           	}
        } 
        printf("\n");       
    }
    
}

void addMatrix (int *matrix, int row, int column){
	int addnumber;
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < column; ++j){
			int a = scanf("%i\n", &addnumber);
			if(a == -1) {
				exit(100);
			}
			matrix[i * column +j]+=addnumber;
		}
	}

}

void minusMatrix (int *matrix, int row, int column){
	int addnumber;
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < column; ++j){
			int a = scanf("%i\n", &addnumber);
			if(a == -1) {
				exit(100);
			}
			matrix[i * column +j]-=addnumber;
		}
	}

}

void multilication (int *pommatrix,int *fmatrix,int *matrix,int frow, int fcolumn,int row,int column){
	for (int i = 0; i < frow; ++i){
		for (int j = 0; j < column; ++j){
			for (int k = 0; k < row; ++k){
 				pommatrix[i * column +j] += matrix[i * fcolumn +k]*fmatrix[k * column +j];
			}
		}
	}

}

bool check (int row, int column,int frow,int fcolumn){
	if (row==frow && column==fcolumn){
		return true;
	}else{
		return false;
	}
}

int main (int argc, char **argv){

	int row,frow,column,fcolumn;
	int *matrix=NULL;
	int *fmatrix=NULL;
	int *pommatrix=NULL;
	int i=0;
	char operation[2];

	while (scanf("%i %i", &row, &column)==2){
		if (i==0){
			frow=row;
			fcolumn=column;
			++i;
			matrix=newMatrix(row, column);
			if (readMatrix(matrix,row,column)==false){
				delMatrix(matrix);
				fprintf(stderr,"Error: Chybny vstup!\n");
				return 100;
			}
			int a = scanf("%s",operation);
			if(a == -1) {
				exit(100);
			}
		}else{
			switch (operation[0])
				{
					case '+':
					    if (check(row,column,frow,fcolumn)==true){
					    	addMatrix(matrix,row,column);
					    	printf("%i %i\n",row,column);
							printMatrix(matrix,row,column);
							delMatrix(matrix);
							return 0;
						}else{
							fprintf(stderr,"Error: Chybny vstup!\n");
							delMatrix(matrix);
							return 100;
						}
						break;
					case '-':
						if (check(row,column,frow,fcolumn)==true){
							minusMatrix(matrix,row,column);
							printf("%i %i\n",row,column);
							printMatrix(matrix,row,column);
							delMatrix(matrix);
							return 0;
						}else{
							fprintf(stderr,"Error: Chybny vstup!\n");
							delMatrix(matrix);
							return 100;
						}
						break;
					case '*':
						if (row==fcolumn){
							fmatrix=newMatrix(row, column);
							if(readMatrix(fmatrix,row,column)==false){
								delMatrix(fmatrix);
								delMatrix(matrix);
								fprintf(stderr,"Error: Chybny vstup!\n");
								return 100;
							}else{
								pommatrix=newMatrix(frow,column);
								multilication(pommatrix,fmatrix,matrix,frow,fcolumn,row,column);
								delMatrix(matrix);
								delMatrix(fmatrix);
								printf("%i %i\n",frow,column);
								printMatrix(pommatrix,frow,column);
								delMatrix(pommatrix);
								return 0;
							}
						}else{
							fprintf(stderr,"Error: Chybny vstup!\n");
							delMatrix(matrix);
							return 100;
						}
						break;
					default:
						fprintf(stderr,"Error: Chybny vstup!\n");
						delMatrix(matrix);
						return 100; 
						break;    	
		    	}
		    	//scanf("%s",operation);
		}
	}
	fprintf(stderr,"Error: Chybny vstup!\n");
	delMatrix(matrix);
	return 100;
}