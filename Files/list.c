#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"

#include "../Headers/elt.h" // T_elt 
#include "../Headers/list.h" // prototypes 

/*
typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;
*/

static T_node * newNode(T_elt e) {
	// Créer une nouvelle cellule contenant l'élément e

	T_node * pNode; 
	CHECK_IF(pNode = malloc(sizeof(T_node)), NULL, "malloc allocateNode"); 
	pNode->data = e; 
	pNode->pNext = NULL;

	return pNode;
}

T_node * addNode (T_elt e, T_node * n) {
	// Créer une maille (node), la remplir 
	// et l'accrocher en tête d'une liste existante (ou vide)
	// Renvoyer la nouvelle tête

	T_node * pNode; 
	pNode = newNode(eltdup(e)); 
	pNode->pNext = n; 
	return pNode;
}

void showList(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en itératif 

	if (l==NULL) {
		printf("Liste Vide !\n");
		return;
	}

	while(l != NULL) {
		printf("%s ", toString(l->data));
		l = l->pNext; 
	}
}

void freeList(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l
	// A faire en itératif 

	T_node * pAux; 
	// Il faut un pointeur auxiliaire : 
	// on ne doit libérer qu'après avoir enregistré quelque part
	// l'adresse de la maille suivante

	assert(l != NULL); 

	while(l != NULL) {
		#ifdef DEBUG
		printf("Freeing %s\n", toString(l->data));
		#endif
		
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
}

T_elt getFirstElt(T_list l) {
	// Renvoyer l'élément contenu dans la cellule de tête de la liste

	assert(l != NULL); 

	return l->data; 
}

T_list removeFirstNode(T_list l) {
	// Supprimer la tête de la liste 
	// Renvoyer la nouvelle liste privée de sa première cellule

	assert(l!= NULL);	
	T_node * p =l->pNext; 
	free(l); 
	return p; 
}

// A produire en version récursive (+ tard dans le sujet)

void showList_rec(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		printf("%s ", toString(l->data));
		showList_rec(l->pNext); 
	}
}

void showList_inv_rec(T_list l) {
	// Afficher la liste en commençant par sa queue 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		showList_inv_rec(l->pNext); 
		printf("%s ", toString(l->data));	
	}
}

void freeList_rec(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en récursif

	if (l == NULL) {
		return;
	} else {
		freeList_rec(l->pNext);
		//printf("Libération de %s\n",toString(l->data));
		free(l); 
	}
}

//////////////////////////////

//getSize iterative
unsigned int getSize_ite(const T_list l){
	int taille = 0;

	T_list aux = l;
	while(aux != NULL){
		taille++;
		aux = aux->pNext;
	}

	return taille;
}

//getSize recursive
unsigned int getSize_rec(const T_list l, int taille){
	static int t = 1;

	T_list aux = l;
	if(aux->pNext != NULL){
		getSize_rec(aux->pNext, t++);
	}

	return t;
}

/*static T_node * newNode(T_elt e) {
	T_node * pNode = malloc(sizeof(T_node)); 
	pNode->data = e; 
	pNode->pNext = NULL;
	return pNode;
}*/


//tailAddNode iterative
T_list tailAddNode_ite(T_elt e, T_list l){
	if(l == NULL){
		return newNode(e);
	}

	T_list aux = l;
	// la boucle va jusqu'a la fin de la liste pour l'élément au bout (il faut verifier si le prochain pointeur point vers NULL pour ne pas avoir d'erreur de segmantation fault lors de l'appel de newNode(e))
	while(aux->pNext != NULL){
		aux = aux->pNext;
	}

	aux->pNext = newNode(e);

	return l;
}

//tailAddNode recursive
T_list tailAddNode_rec(T_elt e, T_list l){
	if(l == NULL){
		return newNode(e);
	}

	T_list aux = l;
	// la recursion va jusqu'a la fin de la liste pour l'élément au bout
	if(aux != NULL){
		tailAddNode_rec(e, aux->pNext);
	}

	// vérifie si la fonction est dans la fin de la liste (pour ne pas ajouter des nodes à chque recursion)
	if(aux->pNext == NULL){
		aux->pNext = newNode(e);
	}
	
	//printf("%d", aux->data);

	return l;
}


//sortAddNode iterative
T_list sortAddNode_ite(T_elt e, T_list l){
	if(l == NULL){
		return newNode(e);
	}

	T_list aux = l;
	T_list next = l->pNext;
	while(aux->pNext != NULL){
		if(e < next->data){
			aux->pNext = newNode(e);
			aux->pNext->pNext = next;
			//printf("%d", next->data);
			break;
		}
		if(next->pNext == NULL){
			next->pNext = newNode(e);
			break;
		}

		aux = aux->pNext;
		next = aux->pNext;
	}

	return l;
}

//sortAddNode recursive
T_list sortAddNode_rec(T_elt e, T_list l){
	if(l == NULL){
		return newNode(e);
	}

	T_list aux = l;
	T_list next = l->pNext;
	if(e < next->data){
		aux->pNext = newNode(e);
		aux->pNext->pNext = next;
		//printf("%d", next->data);
	}
	else if(next->pNext == NULL){
		next->pNext = newNode(e);
	}
	else{
		if(aux != NULL){
			sortAddNode_rec(e, aux->pNext);
		}
	}

	return l;
}


//inList iterative
int inList_ite(T_elt e, const T_list l){
	T_list aux = l;
	while(aux != NULL){
		if(eltcmp(e, aux->data) == 0){
			return 1;
		}

		aux = aux->pNext;
	}
	
	return 0;
}

//inList recursive
int inList_rec(T_elt e, const T_list l){
	T_list aux = l;

	if(aux != NULL){
		//printf("%d", aux->data);
		return (eltcmp(e, aux->data) == 0) || inList_rec(e, aux->pNext);
	}
	
	return 0;
}


//removeDuplicates iterative
T_list removeDuplicates_ite(T_list l){
	T_list unique = NULL;

	T_list aux = l;
	while(aux != NULL){
		if(inList_ite(aux->data, unique) == 0){
			unique = tailAddNode_ite(aux->data, unique);
		}
		else{
			printf("Removed: %s \n", aux->data);
		}
		aux = aux->pNext;
	}

	freeList(l);

	return unique;
}

//removeDuplicates recursive
T_list removeDuplicates_rec(T_list l){
	static T_list unique = NULL;

	if(l != NULL){
		if(inList_ite(l->data, unique) == 0){
			unique = tailAddNode_ite(l->data, unique);
			//printf("%d  ", l->data);
		}
		else{
			printf("Removed: %s \n", l->data);
		}
		removeDuplicates_rec(l->pNext);
	}

	return unique;
}