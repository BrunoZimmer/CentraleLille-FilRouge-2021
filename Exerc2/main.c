#include "../Headers/main.h"
//gcc main.c data.h avl.c -o main
//.\main lemas_en_shuf.txt TheGodfather-MarioPuzo-Chapter1.txt sortieTeste.txt

int main(int argc, char **argv) {

    // char* fichierEntree = argv[2];
    // char* fichierSortie = argv[3];
    // char* fichierArg = argv[1];
    char* fichierArg = "../Dico_nn/Dico_01.txt";
//    char* fichierSortie = "./Output/Test.txt";
//    char* fichierDictionnaire = "../Dico_nn/Dico_03.txt";
    char* fichierEntree[MAXCHAR];

    sprintf(fichierEntree, "../Dico_nn/%s", fichierArg);

    char *mot, *cle, ligne[MAXCHAR], *lema; // lignes a lire par le programme
    char separateur[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};

    int compteur, comp, compteurMots=0, compteurNodes=0, hauter=0;

    int ok;

    clock_t debut, finArbre, fin; //Pour compter le temps

    FILE * dictionnaire;//ouvrir l'input
    FILE * entree;//ouvrir l'input
    FILE * sortie;//ouvrir l'output

    T_arbNode *arbreAVL ;//Racine de l'arbre AVL


    // setlocale(LC_ALL,"");//Autoriser correctement les caractères d'accentuation


//############################## OUVRIER LE FICHIER DE LEMA ########################################################
    debut = clock();//Compter le temps de déplacement du fichier

    dictionnaire = fopen (fichierEntree, "r");
    if (dictionnaire == NULL){//Erreur lors de l'ouverture du fichier corrompu
        printf ("Erreur lors de l'ouverture du fichier %s", fichierArg);
        return 1;
    }
    arbreAVL = StartTree();//Demarrer l'arbre AVL
    compteur = 0;//Demarrer compteur de temp que pour visualizer


//############################# CREER dictionnaire AVL #######################################################
    while (fgets(ligne,MAXCHAR,dictionnaire)){//Parchemins par paragraphes
        compteurMots = compteurMots+1;
        mot= strtok (ligne, separateur);// Tous les caractères définis auparavant comme séparateur
        printf("La taille de %s est de %d", mot, length(mot));

        //FAIRE LA FONCTION POUR FAIRE LA SIGNATURE DE LA MOT - ORDENER EN ORDER ALPHABETIC
        cle= mot;


        mot= strtok(NULL, separateur);
        arbreAVL = InsertAVL(arbreAVL, cle, &ok);
        if(abs(clock()%CLOCKS_PER_SEC) < 50){//continuer à compter tout en portant l'arbre
            compteur ++;
            system("cls");
            printf("Chargement du dictionnaire dans AVL: %d\n", compteur);
        }
    }
    system("cls");
    printf("Chargement conclu");

    finArbre = clock();

//############################### fichier de sortie AVL###########################################################
    comp = 0;
    while (fgets(ligne,MAXCHAR,entree)){//Parchemins par paragraphes
        mot = strtok (ligne, separateur);

        while (mot != NULL){
            lema = ConsulterAVL(arbreAVL, mot, &comp);//Vérifiez si le texte a une lema
            fprintf(sortie,"%s ", strlen(lema));//enregistrer mot dans le fichier de sortie
            mot = strtok (NULL, separateur);
        }
        fprintf(sortie,"\n");//separateur de paragraphes
    }

    // printf("\nFichier %s utilisant AVL généré avec succès.\n",fichierSortie);
    printf("\n%d actions de recherche ont été effectuées dans AVL.\n",comp);

    fin = clock(); // fin du compte du temp
    float milisecondsTot = (float)(fin - debut) / CLOCKS_PER_SEC * 1000; //calcul de temps écoule
    float milisecondsArb = (float)(finArbre - debut) / CLOCKS_PER_SEC * 1000; // calcul de temps écoule
    float milisecondsLema = (float)(fin - finArbre) / CLOCKS_PER_SEC * 1000; // calcul de temps écoule
    printf("Cela a pris un temps total de %.2f ms\n",milisecondsTot);
    printf("Il a fallu du temps pour créer l'arbre %.2f ms\n",milisecondsArb);
    printf("A mis du temps à provenir de %.2f ms\n",milisecondsLema);
    printf("Il y a %d mots sur le dictionnaire\n",compteurMots);

    compteurNodes = NodeCounter(arbreAVL, 0);
    printf("Il y a %d nodes sur le dictionnaire\n",compteurNodes);

    hauter = Height(arbreAVL);
    printf("Il y a une hauter de %d\n",hauter);

    fclose (entree); //fermer les fichiers
    fclose (sortie);

    return 0;
}