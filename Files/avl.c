#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h> 

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"

#include "../Headers/elt.h"
#include "../Headers/avl.h"
#include "../Headers/list.h"


int maximum2(int x, int y){
	if(x>=y) return x;
	else return y;
}

int minimum2(int x, int y){
	if(x<=y) return x;
	else return y;
}

int maximum3(int x, int y, int z){
	if(x>=y) return maximum2(x, z);
	else return maximum2(y, z);
}

int minimum3(int x, int y, int z){
	if(x<=y) return minimum2(x, z);
	else return minimum2(y, z);
}

static T_abr newNodeAVL(T_elt e); 
static T_abrNode * rotateLeftAVL (T_abrNode * node); 
static T_abrNode * rotateRightAVL (T_abrNode * node);
static T_abrNode * balanceAVL(T_abrNode * node);


static T_abr newNodeAVL(T_elt e){
	T_abrNode* pAux; 
	pAux = (T_abrNode *) malloc(sizeof (T_abrNode));

	if(pAux == NULL){
		printf("ERREUR : malloc");
		exit(1);
	}

	pAux->mots = addNode(e, pAux->mots); 
	pAux->signature = eltSig(e);
	pAux->l = NULL; 
	pAux->r = NULL;
	pAux->facteur = 0;

	return pAux;
}

int	insertAVL (T_abrNode ** pnode, T_elt e){
	// Cas si l'arbre est vide
	if (!(*pnode)){
		(*pnode) = newNodeAVL(e);
		return 1;
	}

	// Cas si l'arbre n'est pas vide 
	int deltaH;
	T_elt sig_e = eltSig(e);

	// Comparaison entre l'élément ajouté et la racine 
	if (eltcmp(sig_e, (*pnode)->signature) < 0){
		deltaH = insertAVL(&(*pnode)->l, e); 
		(*pnode)->facteur += deltaH;
	}
	else if(eltcmp(sig_e, (*pnode)->signature) > 0){
		deltaH = insertAVL(&(*pnode)->r, e); 
		(*pnode)->facteur -= deltaH;
	}
	else if(eltcmp(sig_e, (*pnode)->signature) == 0){
	// Insertion dans la list de mots
		if(!inList_ite(e, (*pnode)->mots)){
			(*pnode)->mots = addNode(e, (*pnode)->mots);
		}
		return 0;
	}

	if(deltaH == 0){
		return 0;
	}
	else{
		(*pnode) = balanceAVL(*pnode);
	}

	return (*pnode)->facteur != 0;
}


static T_abrNode * rotateLeftAVL (T_abrNode * node) {
	T_abrNode *aux = node->r;

	int f22 = heightAVL(node->l) - heightAVL(aux);
	int f11 = heightAVL(aux->l) - heightAVL(aux->r);
	
	node->r = aux->l;
	aux->l = node;

	int f2 = f22 + 1 - minimum2(0,f11);
	int f1 = f11 + 1 + maximum2(0,f2);
	
	aux->facteur = f1;
	node->facteur = f2;

	return aux; 
}

static T_abrNode * rotateRightAVL (T_abrNode * node) {
	T_abrNode *aux = node->l;

	int f1 = heightAVL(aux) - heightAVL(node->r);
	int f2 = heightAVL(aux->l) - heightAVL(aux->r);

	node->l = aux->r;
	aux->r = node;

	int f11 = f1 - 1 - maximum2(0,f2);
	int f22 = f2 - 1 + minimum2(0,f11);

	node->facteur = f11;
	aux->facteur = f22;

	return aux; 
}

static T_abrNode * balanceAVL(T_abrNode * node) {
	if(node->facteur == 2){
		if( node->l->facteur == -1){
			// leftRightCase
			node->l = rotateLeftAVL(node->l);
			return rotateRightAVL(node);
		}
		else{
			// leftLeftCase
			return rotateRightAVL(node);
		}
	}

	if(node->facteur == -2){
		if( node->r->facteur == 1){
			// rightLeftCase
			node->r = rotateRightAVL(node->r);
			return rotateLeftAVL(node);
		}
		else{
			// rightRightCase
			return rotateLeftAVL(node);
		}
	}

	return node;

}

int lenWords(T_abr node){
	if(!node){
	return 0;
	}

	int len = maximum3(strlen(node->signature), lenWords(node->l), lenWords(node->r));

	return len;
}

int profondeurNode(T_abr node, T_elt e){
	int profondeur = -1;

	// Si l'arbre est vide
	if(node == NULL){
		return profondeur;
	}
	
	// Si e = racine
	if(eltcmp(e, node->signature) == 0){
		profondeur++;
		return profondeur;
	}

	int profondeur_l = profondeurNode(node->l, e);
	if (profondeur_l > -1){
		profondeur_l++;
		return profondeur_l;
	}

	int profondeur_r = profondeurNode(node->r, e);
	if (profondeur_r > -1){
		profondeur_r++;
		return profondeur_r;
	}
	return profondeur;
}

int nbWords_AVL(T_abr node){
	if (!node){
		return 0;
	}
	
	int nombre = getSize_ite(node->mots) + nbWords_AVL(node->l) + nbWords_AVL(node->r);

	return nombre;
}

int thereIsWord(T_abrNode *node, T_elt mot){
	return inList_ite(mot, node->mots);
}

void print_SearchAVL(T_abr node, T_elt word){
	double time_spent;

	T_elt sig = eltSig(word);
	printf("Mot recherché : %s Signature : %s \n", word, sig);
	clock_t begin = clock();
	T_abrNode *search = searchAVL_rec(node, sig);
	clock_t end = clock();
	

	if(search == NULL || !thereIsWord(search, word)){
		printf("Mot %s pas trouvé !\n", word);
		return;
	}
	
	printf("Liste des mots avec la même signature : \n");
	showList(search->mots);
	puts("");

	printf("La profondeur du noeud pour ce mot : %d \n", profondeurNode(node, sig));

	time_spent = 1000.0*(end-begin)/CLOCKS_PER_SEC;

	printf("Temp nécessaire pour trouver ce mot (en millisecondes) : %.3f ms \n", time_spent);
}

// IDEM pour ABR 

void printAVL(T_abr root, int indent) {
	int i; 
	// ordre de la récurrence : hauteur de l'arbre 
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre 

	// pas de cas de base... 
	if (root!=NULL) {
		// afficher le sous-arbre droit avec indentation+1
		printAVL(root->r, indent+1);
		// afficher le noeud racine 
		for(i=0;i<indent;i++) printf("\t");
		printf("%s\n", toString(root->signature));
		// afficher le sous-arbre gauche avec indentation+1
		printAVL(root->l, indent+1);
	}
}

int heightAVL(T_abr root){
	// hauteur d'un arbre 
	int l,r; 
	if (root == NULL) return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1 + ((l >= r) ? l : r); 
}

int nbNodesAVL(T_abr root){
	// nb de noeuds d'un arbre (y compris les feuilles) 
	if (root == NULL) 
		return 0;
	
	return 1 + nbNodesAVL(root->l) + nbNodesAVL(root->r);
}

T_abrNode * searchAVL_rec(T_abr root, T_elt e){
	// recherche récursive

	// ordre de récurrence : hauteur de l'arbre 	
	int test; 

	// base 
	if (root== NULL) return NULL; 
	else {
		test = eltcmp(e, root->signature); 
		if (test == 0) return root; // trouvé ! 
		else if (test <= 0) return searchAVL_rec(root->l,e);
		else return searchAVL_rec(root->r,e);
	}
}

T_abrNode * searchAVL_it(T_abr root, T_elt e){
	// recherche itérative
	int test;
	while(root!=NULL) {	
		test = eltcmp(e, root->signature);
		if (test ==0) return root;
		else if  (test <= 0) root = root->l; 
		else root = root->r; 
	}

	// Cas si l'élement n'est pas trouvé
	return NULL;  
}

void freeAVL(T_abr node){

	if(node == NULL) return;

	freeAVL(node->l);
	freeAVL(node->r);

	freeList(node->mots);
	free(node);
}

int nbAnagrams(T_abr node){
	int nb_anagrammes, nb_mots;

	// Vérifie si l'arbre est vide (pas d'anagrammes)
	if(!node){
		nb_anagrammes = 0;
		return nb_anagrammes;
	}

	nb_mots = getSize_ite(node->mots); 

	if(nb_mots > 1){
		nb_anagrammes = nb_mots;
	}
	else{
		nb_anagrammes = 0;
	}

	// Total d'anagrammes après avoir fait défiler la liste
	return nb_anagrammes + nbAnagrams(node->l) + nbAnagrams(node->r);
}