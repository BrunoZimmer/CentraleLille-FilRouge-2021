#include "../Headers/main.h"

#define MAXCHAR 100

int main(){
    T_arbNode *arbre;
    FILE* filePNG, *fileFin;
    int fator,ok, i;
    char filename[MAXCHAR];
    const char commandLine[MAXCHAR];

    char separateur[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    FILE * prenoms;//ouvrir l'input

    char *mot, *cle, ligne[MAXCHAR], *lema; 

    // char* fichierArg = argv[1];
    char* fichierArg = "Dico_01.txt";
    char* fichierEntree[MAXCHAR];

    sprintf(fichierEntree, "../Prenoms/%s", fichierArg);
    prenoms = fopen (fichierEntree, "r");

    if (prenoms == NULL){//Erreur lors de l'ouverture du fichier corrompu
        printf ("Erreur lors de l'ouverture du fichier %s", fichierArg);
        return 1;
    }
    arbre = StartTree();

    for(i=1;i<=10 || fgets(ligne,MAXCHAR,prenoms);i++){

        mot= strtok (ligne, separateur);// Tous les caractères définis auparavant comme séparateur

        sprintf(filename, "./Image%d.dot", i);
        filePNG = fopen(filename, "w");
        
        generateHeaderPNG(filePNG);
        fclose(filePNG);

        arbre = InsertAVL(arbre, mot, &ok);
        PrintWLevel(arbre, 0);NL();NL();
        generatePNG(arbre, filename, 1);
        fputs("\n}", filePNG);

//Ici manque une fonction de delay, parce que la prochaine ligne de command marche pas
//parce que le document .dot n'est pas prêt pour faire la passage à PNG
        sprintf(commandLine, "dot ./Output/Image%d.dot -T png -o ./Output/PNGImage.png", i);
        system(commandLine);
        sprintf(commandLine, "rm ./Output/Image%d.dot", i); //ÇA MARCHE (?????)
        system(commandLine);
        
    }
    
    sprintf(commandLine, "zip -r ./Output/PNGImages.zip ./Output/*.png", i);
    system(commandLine);
    

    printf("\nFator da Arvore A\n###########################\n");
    PrintWLevel(arbre, 0);
    printf("###########################\n");

    fator = FactorTree(arbre);
    printf("O fator e %d\n", fator);
    printf("###########################\n");

    system("pwd");

    return 0;

}

