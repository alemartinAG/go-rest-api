#include <stdio.h>
#include <string.h>
#include "cJSON.c"

int main(){

	//char *strJson = "[{\"matrix\":\"Incidence\",\"values\":\"[-1, 0, 1, 0, 0, 0][1, -1, 0, 0, 0, 0][0, 1, -1, 0, 0, 0][0, 0, 0, -1, 0, 1][0, 0, 0, 1, -1, 0][0, 0, 0, 0, 1, -1][-1, 1, 0, -1, 1, 0]\",\"rows\":\"7\",\"columns\":\"6\"},{\"matrix\":\"Inhibition\",\"values\":\"[0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0][0, 0, 0, 0, 0, 0]\",\"rows\":\"7\",\"columns\":\"6\"}]";
	char *strJson = "[{\"matrix\":\"Incidence\",\"values\":[[-1, 0, 1, 0, 0, 0],[1, -1, 0, 0, 0, 0],[0, 1, -1, 0, 0, 0],[0, 0, 0, -1, 0, 1],[0, 0, 0, 1, -1, 0],[0, 0, 0, 0, 1, -1],[-1, 1, 0, -1, 1, 0]],\"rows\":\"7\",\"columns\":\"6\"},{\"matrix\":\"Inhibition\",\"values\":[[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0]],\"rows\":\"7\",\"columns\":\"6\"}]";
	cJSON *root = cJSON_Parse(strJson);

	cJSON *item = root ? root->child : 0;
	cJSON *vector_iterator = NULL;
	cJSON *int_iterator = NULL;

	printf("Array Size: %d\n", cJSON_GetArraySize(item));


	while (item)
	{
		char *matrix = cJSON_GetObjectItem(item, "matrix")->valuestring;

		cJSON *values = cJSON_GetObjectItem(item, "values");

		char *rows = cJSON_GetObjectItem(item, "rows")->valuestring;
		char *columns = cJSON_GetObjectItem(item, "columns")->valuestring;

		printf("%s: \nRows: %s\nColumns: %s\nValues:\n", matrix, rows, columns);


		vector_iterator = values ? values->child : 0;

		while(vector_iterator){

			int_iterator = vector_iterator ? vector_iterator->child : 0;

			while(int_iterator){

				printf("%2d", int_iterator->valueint);

				int_iterator = int_iterator->next;

			}

			printf("\n");

			vector_iterator = vector_iterator->next;
		}

		printf("\n");

		item=item->next;
	}

	cJSON_Delete(item);

	return 1;
}