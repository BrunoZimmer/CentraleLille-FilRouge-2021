#include <stdio.h>
#include <stdlib.h>
#include "../include/traces.h" 
#include "../Headers/anagrammes.h"

static T_anagNode* newNodeAnag(T_list e) {
	// Créer un nouveau node dans l'abre pour la liste e
	// Cas où les mots dans e n'ont pas encore d'anagrammes

	static T_anagNode* node;
	node = malloc(sizeof(T_anagNode));
	// Vérifie le bon fonctionnement de malloc()
	if(node == NULL){
		printf("Erreur : malloc");
		exit(1);
	} 
	
	// Remplissage du nouveau node
	node->mots_anag = e; 
	node->next = NULL;

	return node;
}

T_anagList sortAddNodeAnag(T_list e, T_anagList list){
	// Vérifie si la liste est vide
  if(list){
		T_anagList p_next;
		T_anagList aux = list;

		// Chercher un node qui contient un nombre d'anagrammes moins grand que dans e
    while( aux->next && ( getSize_ite(e) > getSize_ite(aux->next->mots_anag) ) ){
      aux = aux->next;
    }

		// Positionnement de e
    p_next = aux->next;
		aux->next = newNodeAnag(e);
		aux->next->next = p_next;

		return list;
	}
  else{
		// Si la liste est vide, il faut créer un nouveau node
		return newNodeAnag(e);
	}
}

void getAnagrams(T_abr node, T_anagList* plist){
  // Vérifie si le node est vide
	if(!node){
		return;
	}

	// S'il y a plus qu'un mot dans le node de l'arbre (donc il y a un anagramme), le programme récupère la liste 
  if(getSize_ite(node->mots) >= 2){
    *plist = sortAddNodeAnag(node->mots, *plist);
  }
  
	// Faire défiler dans l'arbre
  getAnagrams(node->l, plist);
  getAnagrams(node->r, plist);
}

void printAnagrams(T_anagList list){
	// Vérifie si la liste est vide
  if(!list){
		return;
	}

	// Faire défiler dans la liste chainée d'anagrammes
  printAnagrams(list->next);
	// Print de chaque list d'anagrammes
  showList(list->mots_anag);
	puts("");
}

void freeAnagrams(T_anagList list){
	// Vérifie si la liste est déjà vide
  if(!list){
		return;
	}

	// Faire défiler dans la liste d'anagrammes
  freeAnagrams(list->next);

  free(list);
	list = NULL; // Bonne pratique
}