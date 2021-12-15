#include "../Headers/main.h"

#define MAXCHAR 100

int main(){
    T_arbNode *arbre;
    FILE* filePNG, *fileFin;
    int fator,ok, i;
    char filename[MAXCHAR];
    const char commandLine[MAXCHAR];

    arbre = StartTree();

    for(i=0;i<=5;i++){
        sprintf(filename, "./Output/Image%d.dot", i);
        filePNG = fopen(filename, "w");
        
        generateHeaderPNG(filePNG);
        fclose(filePNG);

        arbre = InsertAVL(arbre, rand()%50, &ok);
        PrintWLevel(arbre, 0);NL();NL();
        generatePNG(arbre, filename, 1);
        fputs("\n}", filePNG);

        // sprintf(commandLine, "dot ./Output/Image%d.dot -T png -o ./Output/PNGImage%d.png", i,i);
        // sprintf(commandLine, "rm ./Output/Image%d.dot", i); ÇA MARCHE (?????)
        // system(commandLine);
        
    }
    // sprintf(commandLine, "zip -r ./Output/PNGImages.zip ./Output/*.png", i);
    // system(commandLine);
    

    printf("\nFator da Arvore A\n###########################\n");
    PrintWLevel(arbre, 0);
    printf("###########################\n");

    fator = FactorTree(arbre);
    printf("O fator e %d\n", fator);
    printf("###########################\n");

    system("pwd");

    return 0;

}

