#include <stdio.h>
#include <string.h>
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
#include "../Headers/Exerc2.h"
#include "../Headers/list.h"

#define MAXCHAR 100

int main(int argc, char ** argv) {
	if(argc < 2){
		printf("Saisissez une entrée avec le nom du programme + dictionaire à utiliser. \n");
		exit(1);
	}

	FILE *fp;
	char mots[50];
	double temps;

	char* fichierArg = argv[1];
  char fichierEntree[MAXCHAR];
  sprintf(fichierEntree, "../Dico_nn/%s", fichierArg);
  fp = fopen (fichierEntree, "r");
	if(fp == NULL){
		printf("Dictionaire pas trouvé. \n");
		exit(1);
	}

	T_abr node = NULL; 

	clock_t debut = clock();

	int j, i = 0;
	while(fgets(mots, sizeof(mots), fp)){
		j = 0;
		while(mots[j] != '\n'){
			if(mots[j] == '\0'){
				break;
			}

			j++;
		}

		mots[j] = '\0';
		insertAVL(&node, mots);
		i++;	
	}

	fclose(fp);
	
	clock_t fin = clock();
	temps = (1000.0*(fin - debut)) / CLOCKS_PER_SEC;

	puts("|---------- Exercice 2 ----------|");
	printf("Dictionaire recherché : %s \n", argv[1]);
	printf("Taille des mots dans ce dictionnaire : %d\n", lenWords(node));
	printf("Nombre de mots dans ce dictionnaire : %d\n", nbWords_AVL(node));
	printf("Durée de construction de l'arbre (en millisecondes) : %.3f ms\n", temps);
	printf("Nombre de noeuds : %d\n", nbNodesAVL(node));
	printf("Hauteur de l'abre : %d\n", heightAVL(node));
	int minHeight = (int) log2(nbNodesAVL(node));
	printf("Hauteur minimale de l'arbre : %d\n", minHeight);

	char word[50];

	printf("\n--------------\n");
	printf("Recherche d'un mot dans l'abre : \n");
	printf("Pour arrêter le programme : saisir \"0\" \n");
	while(1){
		printf("Saisissez le mot : ");
		scanf("%s", word);
		if(word[0] == '0'){
			puts("");
			puts("|---------- Programme arrêté ----------|");
			system("pwd"); 
			break;
		}
		print_SearchAVL(node, word);

		printf("\n--------------\n");
		printf("Pour arrêter le programme : saisir \"0\" \n");
	}

	freeAVL(node);
	
	return 0;
}