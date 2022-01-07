#pragma once

#include "elt.h" // T_elt 
//#define DEBUG 
#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;

T_node * addNode (T_elt e, T_node * n);
void showList(T_list l);
void freeList(T_list l);
T_elt getFirstElt(T_list l);
T_list removeFirstNode(T_list l);

unsigned int getSize_ite(const T_list l);
unsigned int getSize_rec(const T_list l, int taille);
T_list tailAddNode_ite(T_elt e, T_list l);
T_list tailAddNode_rec(T_elt e, T_list l);
T_list sortAddNode_ite(T_elt e, T_list l);
T_list sortAddNode_rec(T_elt e, T_list l);
int inList_ite(T_elt e, const T_list l);
int inList_rec(T_elt e, const T_list l);
T_list removeDuplicates_ite(T_list l);
T_list removeDuplicates_rec(T_list l);


#endif 


