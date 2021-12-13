// struct TNodoA
// {
//     int facteur;
//     int fator;
//     struct TNodoA *l;
//     struct TNodoA *r;
// };
// typedef struct TNodoA T_Arbre;
#include "elt.h" // T_elt
#include "string.h" 

#ifndef _LIST_H_
#define _LIST_H_
#define LINELENGTH 60

typedef struct T_arbNode {
	T_elt data;
	int facteur;
	struct T_arbNode *l;
	struct T_arbNode *r;
} T_arbNode, * T_Arbre;

//Inicializa a arvore
T_arbNode* StartTree(void);
//insere um novo nó na arvore
T_arbNode* InsertTree(T_arbNode *node, T_elt data);

T_arbNode* Case1(T_arbNode *a, int *ok);

T_arbNode* Case2(T_arbNode *a, int *ok);

void checkAVL(T_arbNode *a);

T_arbNode* InsertAVL(T_arbNode *node, T_elt data, int *ok);
//printa os elementos da arvore no caminhamento pre fixado a luerda
void PrintPreOrder(T_arbNode *node);

void PrintPostOrder(T_arbNode *node);

void PrintInOrder(T_arbNode *node);
//print pre fixado a luerda só que com "=" mostrando o nivel do nó
void PrintWLevel(T_arbNode *node, int nivel);
//conta quantidade de elementos na arvore
int NodeCounter(T_arbNode *node, int nivel);
//retorna a altura do nodo A
int Height (T_arbNode *a);
//retorna o fator do nodo A
int FindFactor(T_arbNode *a);
//retorna o fator da arvore
int FactorTree(T_arbNode *a);
//retorna 1 se a lista estiver equilibrada e se não estiver retorna 0
int Balanced(T_arbNode *a);

T_arbNode* QueryABP(T_arbNode* a, T_elt data);

T_arbNode* IntersectionTree(T_arbNode *a, T_arbNode *a2);

void Intersect (T_arbNode* a, T_arbNode *b,  T_arbNode **c);

int Compare (T_arbNode *a, T_arbNode *b);

//##################ROTACOES AVL####################
T_arbNode* RightRotation(T_arbNode* a);

T_arbNode* LeftRotation(T_arbNode *a);

T_arbNode* DoubleLeftRotation (T_arbNode *a);

T_arbNode* DoubleRightRotation (T_arbNode* a);

int xxx(T_arbNode *a);

void PrintIntervalo(T_arbNode *node, T_elt small, T_elt big);

void NodePosition(T_arbNode *node, int n, int k);

void FactorizesTree(T_arbNode **a);


#endif 