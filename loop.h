#ifndef _LOOP_H
#define _LOOP_H


void pass_json(char * json);
void printMatrices();

struct PetriMatrix
{
	char * id;
	int rows;
	int columns;
	int** values;
};


#endif
