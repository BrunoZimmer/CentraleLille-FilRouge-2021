#include <stdio.h>
#include <assert.h>
#include <time.h> 
#include <math.h>
#include <unistd.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 
#include "../include/check.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "../Headers/elt.h"
#include "../Headers/avl.h"
#include "../Headers/Exerc1.h"
#include "../Headers/anagrammes.h"

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("Saisissez le nom du programme + Fichier de noms + nombre de lignes à utiliser \n");
    exit(1);
  }
  T_abr arbre  = NULL;
  int nMots = atoi(argv[2]);

  FILE* filePNG, *fileFin;
  int i;
  char commandLine[MAXCHAR];
  char* result;

  char separateur[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
  FILE * prenoms;//ouvrir l'input

  char *mot, ligne[MAXCHAR]; 

  char* fichierArg = argv[1];
  char fichierEntree[MAXCHAR];

  sprintf(fichierEntree, "../Prenoms/%s", fichierArg);
  prenoms = fopen (fichierEntree, "r");

  //Erreur lors de l'ouverture du fichier corrompu
  if (prenoms == NULL){ 
      printf ("Erreur lors de l'ouverture du fichier %s \n", fichierArg);
      return 1;
  }

  for(i=0; i<=nMots; i++){
      printf("Mot %d \n", i);
      mot= strtok (ligne, separateur);// Tous les caractères définis auparavant comme séparateur
      result = fgets(mot, 50, prenoms);


      insertAVL(&arbre, mot);

//Ici manque une fonction de delay, parce que la prochaine ligne de command marche pas
//parce que le document .dot n'est pas prêt pour faire la passage à PNG

      createDotAVL(arbre, "displayAVL");

      
  }
  
  // sprintf(commandLine, "zip -r ./Output/PNGImages.zip ./img/png/*.png");
  // system(commandLine);

  system("pwd");

  return 0;

}