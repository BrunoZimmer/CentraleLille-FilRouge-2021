#include "../Headers/main.h"


int main(){
    T_arbNode *arbre;
    FILE *filePNG;
    int fator,ok, i;
    char filename[12];



    arbre = StartTree();
    for(i=0;i<=10;i++){
        sprintf(filename, "./Output/Image%d.dot", i);

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

