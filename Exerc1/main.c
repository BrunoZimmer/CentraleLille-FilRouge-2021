#include "../Headers/main.h"

#define MAXCHAR 60

int main(){
    T_arbNode *arbre;
    FILE* filePNG, *fileFin;
    int fator,ok, i;
    char filename[MAXCHAR];

    arbre = StartTree();

    for(i=0;i<=5;i++){
        sprintf(filename, "./Output/Image%d.dot", i);
        filePNG = fopen(filename, "w");
        
        generateHeaderPNG(filePNG);
        fclose(filePNG);

        arbre = InsertAVL(arbre, rand()%50, &ok);
        PrintWLevel(arbre, 0);NL();NL();
        generatePNG(arbre, filename, 1);
        fputs("\n\n}", filePNG);
        // fclose(filePNG);
    }
    

    printf("\nFator da Arvore A\n###########################\n");
    PrintWLevel(arbre, 0);
    printf("###########################\n");

    fator = FactorTree(arbre);
    printf("O fator e %d\n", fator);
    printf("###########################\n");

    return 0;

}

