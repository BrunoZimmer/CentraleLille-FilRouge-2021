#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Headers/avl.h"
#include "../Headers/elt.h"
#include "../Headers/Exerc1.h"

#define MAXCHAR 60

int main(){
    T_arbNode *arbre;
    FILE* filePNG;
    int fator,ok, i;
    char filename[MAXCHAR];

    arbre = StartTree();

    for(i=0;i<=5;i++){
        sprintf(filename, "./Output/Image%d.dot", i);
        filePNG = fopen(filename, "w");
        
        generateHeaderPNG(filePNG);
        fclose(filePNG);

        arbre = InsertAVL(arbre, rand()%50, &ok);
        PrintWLevel(arbre, 0);
        generatePNG(arbre, filename, arbre->facteur);
    }

   printf("\nFator da Arvore A\n###########################\n");
   PrintWLevel(arbre, 0);
   printf("###########################\n");
   
   fator = FactorTree(arbre);
   printf("O fator e %d\n", fator);
   printf("###########################\n");

   return 0;

}

