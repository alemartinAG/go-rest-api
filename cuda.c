#include "cuda.h"
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

bool pass_json(char * strJson){

	cJSON *root = cJSON_Parse(strJson);

	cJSON *item_iterator = root ? root->child : 0;
	cJSON *vector_iterator = NULL;
	cJSON *int_iterator = NULL;

	int count = 0;

	/* Obtains the objects */
	while (item_iterator)
	{
		char *name = cJSON_GetObjectItem(item_iterator, "matrix")->valuestring;

		cJSON *values = cJSON_GetObjectItem(item_iterator, "values");

		int rows = cJSON_GetObjectItem(item_iterator, "rows")->valueint;
		int columns = cJSON_GetObjectItem(item_iterator, "columns")->valueint;

		/* Creates the structure an allocate 
			memory for it */
		struct PetriMatrix matrix;

		matrix.id = malloc(strlen(name)*sizeof(char));
		strcpy(matrix.id, name);

		matrix.rows = rows;
		matrix.columns = columns;

		matrix.values = (int **)malloc(rows * sizeof(int *)); 
    	for (int k=0; k<rows; k++) 
        	matrix.values[k] = (int *)malloc(columns * sizeof(int));


		matrixIndex[count] = matrix;


		/* Obtains the int matrix */
		vector_iterator = values ? values->child : 0;

		int r = 0;

		while(vector_iterator){

			int_iterator = vector_iterator ? vector_iterator->child : 0;

			int c = 0;

			while(int_iterator){

				matrix.values[r][c] = int_iterator->valueint;

				c++;
				int_iterator = int_iterator->next;

			}

			r++;
			vector_iterator = vector_iterator->next;
		}

		printf("%s[%d][%d] - DONE!\n", name, rows, columns);

		item_iterator = item_iterator->next;

		count++;
	}

	cJSON_Delete(item_iterator);
	cJSON_Delete(vector_iterator);
	cJSON_Delete(int_iterator);

	return true;
	
}

void printMatrices(){

	for(int k=0; k<N_MATR; k++){

		printf("\n\n%s\n", matrixIndex[k].id);

		for(int i=0; i<matrixIndex[k].rows; i++){
			for (int j=0; j<matrixIndex[k].columns; j++){
				printf("%2d ", matrixIndex[k].values[i][j]);
			}
			printf("\n");
		}
	}

}
