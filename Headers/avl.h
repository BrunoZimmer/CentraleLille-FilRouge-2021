#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h> 

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"

#include "elt.h"
#include "list.h"

#ifndef _AVL_H_
#define _AVL_H_
#define MAXCHAR 100

typedef struct abrNode{
	T_list mots;
	T_elt signature;
	int facteur;
	struct abrNode *l;
	struct abrNode *r;
} T_abrNode, *T_abr;

extern char * outputPath;

int	insertAVL (T_abrNode ** node, T_elt e);
void printAVL(T_abr node, int indent); 
int heightAVL(T_abr);
int nbNodesAVL(T_abr);
T_abrNode * searchAVL_rec(T_abr node, T_elt e);
T_abrNode * searchAVL_it(T_abr node, T_elt e);
void print_SearchAVL(T_abr root, char *mot);
void freeAVL(T_abr root); 

int profondeurNode(T_abr, T_elt);
int lenWords(T_abr node);
int nbWords_AVL(T_abr root);
int thereIsWord(T_abrNode *node, T_elt mot);
int nbAnagrams(T_abr node);

#endif 


