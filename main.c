#include "Headers/main.h"


int main(){
    T_abrNode *arbre;
    int fator,ok;

    arbre = StartTree();

    arbre = insertAVL(&arbre, 35);
    arbre = insertAVL(&arbre, 2);
    arbre = insertAVL(&arbre, 71);
    arbre = insertAVL(&arbre, 6);
    arbre = insertAVL(&arbre, 49);
    arbre = insertAVL(&arbre, 73);
    arbre = insertAVL(&arbre, 28);
    arbre = insertAVL(&arbre, 44);
    arbre = insertAVL(&arbre, 50);

   printf("\nFator da Arvore A\n###########################\n");
   PrintWLevel(arbre, 0);
   printf("###########################\n");
   
   fator = FactorTree(arbre);
   printf("O fator e %d\n", fator);
   printf("###########################\n");

   return 0;

}
