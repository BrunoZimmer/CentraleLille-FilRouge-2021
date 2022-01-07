#include "string.h"
#include <stdio.h>

#include "elt.h" // T_elt 
#include "avl.h" // T_elt 


void imprimir_simples(T_abrNode * a);

static void genDotAVL(const T_abrNode* root, FILE* basename);

void createDotAVL(const T_abrNode* root, const char* basename);