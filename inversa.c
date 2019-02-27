/*	this program calculate the inverse of an NxN matrix from file, first it calculate the determinant
	then if det !=0 it calculate the inverse of a matrix else it finish the execution
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 100

double pow(double base, double exp) {
   /* function that calculate the power of number*/
    int i;
    double res=1;
    for(i=0; i<exp; i++) {
        res *= base;
    }
    return res;
}

float det(float **m, int n) {
	/* 	function that calculate the determinant of a matrix 
		using the Laplace algorithm
		float **m pointer to the matrix
		int n  dimension of a matrix 
	*/
   
    float determinante = 0;
    float **sub_m;
    int row,i,j;
	/*determiant of a 1x1 matrix*/
    if(n == 1) {
        determinante = m[0][0];
    } else if(n == 2) {
		/*determinant of a 2x2 matrix*/
        determinante = m[1][1]*m[0][0]-m[0][1]*m[1][0];
    } else {
		/*determinant of a matrix upper 2x2 dimension*/
        for(row = 0; row<n; row++) {
			/*	create a submatrix that will be used in input
				in det() function
			*/
            sub_m=(float **)malloc(sizeof(float *)*n);
            for(i=0; i<n; i++){
                sub_m[i]=(float *)malloc(sizeof(float)*n);
			}
            for(i=0; i<n-1; i++) {
                for(j=0; j<n-1; j++) {
                    int sub_row = (i < row ? i : i+1);
					/*	apply the algorithm for the first column*/
                    int sub_col = j+1;
                    sub_m[i][j] = m[sub_row][sub_col];
                }
            }
            if(row%2 == 0) {
                determinante +=m[row][0]*det(sub_m,n-1);
            } else {
                determinante -=m[row][0]*det(sub_m,n-1);
            }
        }
    }
    return determinante;
}

void trasposta(float c[MAX_DIM][MAX_DIM],float d[MAX_DIM][MAX_DIM],int n,float det) {
    /* 	this function create the traspose of a matrix then divide it by determinant
		float c[MAX_DIM][MAX_DIM] matrix that contains the cofactors
		float d[MAX_DIM][MAX_DIM] matrix that will contain the inverse matrix
		int n dimension
		float det determinant					
	*/
	int i,j;
	printf("\n");
    for(i=0; i<n; i++) {
		printf(" [");
        for(j=0; j<n; j++) {
            d[i][j]=c[j][i]/det;
            printf("  %.4f\t ",d[i][j]);
        }
        printf("]\n");
    }

}

void cofattore(float **m,float d[MAX_DIM][MAX_DIM],int n,float det2) {
    /*	function thet calculate the cofactors of a matrix
		float **m pointer to the matrix
		float d[MAX_DIM][MAX_DIM] temporary matrix
		int n dimension
		float det2 determinant
	*/
	float c[MAX_DIM][MAX_DIM];
    float **b;
    int l,h,r,k,i,j;
	
    b=(float **)malloc(sizeof(float *)*n);
    for(j=0; j<n; j++) {
        b[j]=(float *)malloc(sizeof(float)*n);
    }

    for (h=0; h<n; h++) {
        for (l=0; l<n; l++) {
            r=0;
            k=0;
            for (i=0; i<n; i++)
                for (j=0; j<n; j++)
                    if (i != h && j != l) {
                        b[r][k]=m[i][j];
                        if (k<(n-2))
                            k++;
                        else {
                            k=0;
                            r++;
                        }
                    }
			
            c[h][l] = pow(-1,(h+l))*det(b,(n-1));
        }
    }
	
    trasposta(c,d,n,det2);
}

void inversa(float **m,float d[MAX_DIM][MAX_DIM],int n,float det) {
   /*	function that calculate theinverse of a matrix 
	   	float **m pointer to the matrix
	   	float d[MAX_DIM][MAX_DIM] temporary matrix
	   	int n dimension
	   	float det determinant
	*/
    if(det == 0) {
        printf("\n MATRICE NON INVERTIBILE\n");
    } else if(n == 1) { 
        printf("\n MATRICE INVERSA\n");
		printf("  %f\n",1/det);
    } else {
		printf("\n MATRICE INVERSA");
   
		cofattore(m,d,n,det);
    }
}

int main() {
    float **matrix,d[MAX_DIM][MAX_DIM],determinante;           
    int i, j,dimensione,righe,colonne;  			
    FILE *InputFile;                				
    char inputtxt[ 100 ];           			 	   
    
    printf("Inserisci il file di input: ");
    scanf("%s",inputtxt);

    
    if( ( InputFile = fopen( inputtxt, "r") ) == NULL) {  
        printf(" ATTENZIONE! impossibile aprire il file, per favore inserire il file.txt nella stessa directory del file.c oppure scrivere correttamente il nome ");
    } else {
        printf("\n **********  Calcolo Matrice Inversa  ********** \n");
        fscanf( InputFile,"%d", &righe );
        printf("\n DIMENSIONE DELLA MATRICE: %d\n",righe);  
		
        printf(" MATRICE DI INPUT\n");
		colonne = dimensione =  righe;
        

        matrix = ( float** )malloc( righe * sizeof( float* ) );
        for( i = 0; i < righe; i++ ) { 
			printf(" [" );
		    matrix[i]=(float*)malloc(colonne * sizeof(float));
            for( j=0; j<colonne; j++ ) {    
                fscanf( InputFile, "%f", &( matrix[i][j] ) );
                printf("  %.4f\t", matrix[i][j]);  
            }
            printf("]\n");
        }
    }

    printf("\n");
    determinante=det(matrix,dimensione);
    printf(" DETERMINANTE: %.4f\n", determinante);
   
	inversa(matrix,d,dimensione,determinante);
	free(matrix);
	printf("\n ***************  Fine Programma  *************** \n");
    return 0;
}
