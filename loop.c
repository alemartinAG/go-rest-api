#include "loop.h"
#include <stdio.h>
#include <string.h>

#define SIZE 10000
#define NMAT 5
#define N_PARAM 4
#define JSON_TYPE_1 "\"matrix\""
#define JSON_TYPE_2 "\"values\""

char parsed[NMAT*2][SIZE];
int ** incidence;
int ** inhibition;
int count = 0;

void pass_json(char * json){
	
	strcpy(parsed[count], json);
	count = count+1;
}

void initMatrices(){

	incidence = (int **)malloc(atoi(parsed[2]) * sizeof(int*));
	for(int i = 0; i < rows; i++) incidence[i] = (int *)malloc(atoi(parsed[3]) * sizeof(int));

}

void printParsed(){

	initMatrices();

	for (int i=0; i<atoi(parsed[2]); ++i)
	{
		for(int j=0; j<atoi(parsed[3]); j++){
			printf("%2d", incidence[i][j]);
		}
		printf("\n");
	}

}

int loop(int* matrix, int rows, int columns) {

	int suma = 0;

	printf("Rows: %d\n", rows);
	printf("Columns: %d\n", columns);
	printf("matrix[0][0]: %d\n", matrix[0]);

    
    /*for(int i=0; i<rows; i++){
    	for(int j=0; j<columns; j++){
    		printf("%2d ", matrix[i][j]);
    	}
    	printf("\n");
    }*/

    return suma;
}
