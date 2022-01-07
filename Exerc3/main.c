// #include <stdio.h>
// #include <assert.h>
// #include <time.h> 
// #include <math.h>
// #include <unistd.h>

// //#define CLEAR2CONTINUE
// #include "../include/traces.h" 
// #include "../include/check.h" 

// // C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
// #include "../Headers/elt.h"
// #include "../Headers/avl.h"
// #include "../Headers/list.h"
// #include "../Headers/anagrammes.h"

// #define MAXCHAR 100
#include "../Headers/main.h"

int main(int argc, char ** argv) {
	if(argc < 2){
		printf("Saisissez une entrée avec le nom du programme + dictionaire à utiliser. \n");
		exit(1);
	}

	FILE *fp;
	char mots[50];

	char* fichierArg = argv[1];
	char fichierEntree[MAXCHAR];
	sprintf(fichierEntree, "../Dico_nn/%s", fichierArg);
	fp = fopen (fichierEntree, "r");
	if(fp == NULL){
		printf("Dictionaire pas trouvé. \n");
		exit(1);
	}

	T_abr node = NULL; 
	
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
	
	int nb_anagrammes = nbAnagrams(node);

	puts("|----------- Exercice 3 -----------|");
	printf("Dictionaire recherché : %s \n", argv[1]);
	printf("Nombre de mots du dictionnaire disposant d’anagrammes : %d \n", nb_anagrammes);
	
	T_anagList list = NULL;
	
	puts("Anagrammes (triés par nombre d'éléments décroissant) :");
	puts("");
	getAnagrams(node, &list);
	printAnagrams(list);
	puts("");

	freeAnagrams(list);
	freeAVL(node);
	
	puts("|----------- Programme arrêté -----------|"); 
	system("pwd");

	return 0;
}