#include "string.h"
#include <stdio.h>

#include "elt.h" // T_elt 
#include "avl.h" // T_elt 


void generatePNG(const T_Arbre l, const char * filename, int indice);
void generateHeaderPNG(FILE * filePNG);