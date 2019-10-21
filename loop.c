#include "loop.h"
#include <stdio.h>

int loop(int cantidad) {

	int suma = 0;
    
    for(int i=0; i<cantidad; i++){
		suma += i;
    }

    return suma;
}
