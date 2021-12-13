#include "Headers/main.h"


int main(){
    T_arbNode *arbre;
    int fator,ok;

    arbre = StartTree();

    arbre = InsertAVL(arbre, 35, &ok);
    arbre = InsertAVL(arbre, 2, &ok);
    arbre = InsertAVL(arbre, 71, &ok);
    arbre = InsertAVL(arbre, 6, &ok);
    arbre = InsertAVL(arbre, 49, &ok);
    arbre = InsertAVL(arbre, 73, &ok);
    arbre = InsertAVL(arbre, 28, &ok);
    arbre = InsertAVL(arbre, 44, &ok);
    arbre = InsertAVL(arbre, 50, &ok);

   printf("\nFator da Arvore A\n###########################\n");
   PrintWLevel(arbre, 0);
   printf("###########################\n");
   
   fator = FactorTree(arbre);
   printf("O fator e %d\n", fator);
   printf("###########################\n");

   return 0;

}

