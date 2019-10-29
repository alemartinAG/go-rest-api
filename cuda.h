#ifndef _CUDA_H
#define _CUDA_H

#include <stdbool.h>

bool pass_json(char * json);
void printMatrices();

struct PetriMatrix
{
	char * id;
	int rows;
	int columns;
	int** values;
};


#endif
