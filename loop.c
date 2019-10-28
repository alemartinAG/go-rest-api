#include "loop.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>

#define N_PARAM 4
#define N_MATR	5
#define JSON_TYPE_1 "\"matrix\""
#define JSON_TYPE_2 "\"values\""
#define JSON_TYPE_3 "\"rows\""
#define JSON_TYPE_4 "\"columns\""



struct PetriMatrix matrixIndex[N_MATR];

void pass_json(char * strJson){

	cJSON *root = cJSON_Parse(strJson);

	cJSON *item_iterator = root ? root->child : 0;
	cJSON *vector_iterator = NULL;
	cJSON *int_iterator = NULL;

	int count = 0;


	while (item_iterator)
	{
		char *name = cJSON_GetObjectItem(item_iterator, "matrix")->valuestring;

		cJSON *values = cJSON_GetObjectItem(item_iterator, "values");

		int rows = cJSON_GetObjectItem(item_iterator, "rows")->valueint;
		int columns = cJSON_GetObjectItem(item_iterator, "columns")->valueint;

		//int matrix[rows][columns];

		struct PetriMatrix matrix;

		matrix.id = malloc(strlen(name)*sizeof(char));

		strcpy(matrix.id, name);
		matrix.rows = rows;
		matrix.columns = columns;

		printf("%s...\n", name);

		//matrix.values = malloc(rows * columns * sizeof(int));
		matrix.values = (int **)malloc(rows * sizeof(int *)); 
    	for (int k=0; k<rows; k++) 
        	matrix.values[k] = (int *)malloc(columns * sizeof(int));

		matrixIndex[count] = matrix;

		vector_iterator = values ? values->child : 0;

		int i = 0;

		while(vector_iterator){

			int_iterator = vector_iterator ? vector_iterator->child : 0;

			int j = 0;

			while(int_iterator){

				//printf("%2d", int_iterator->valueint);
				matrix.values[i][j] = int_iterator->valueint;

				j++;
				int_iterator = int_iterator->next;

			}

			//printf("\n");
			i++;
			vector_iterator = vector_iterator->next;
		}

		printf("%s[%d][%d] - DONE!\n", name, rows, columns);

		item_iterator = item_iterator->next;

		count++;
	}

	cJSON_Delete(item_iterator);
	cJSON_Delete(vector_iterator);
	cJSON_Delete(int_iterator);
	
}

void printMatrices(){

	for(int k=0; k<N_MATR; k++){

		printf("\n\n%s\n", matrixIndex[k].id);

		for(int i=0; i<matrixIndex[k].rows; i++){
			for (int j=0; j<matrixIndex[k].columns; j++){
				printf("%2d", matrixIndex[k].values[i][j]);
			}
			printf("\n");
		}
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
