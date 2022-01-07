#include "avl.h"
#include "list.h"
#include "../include/check.h"

typedef struct anagNode {
	T_list mots_anag;
	struct anagNode* next;
}T_anagNode, *T_anagList;

static T_anagNode* newNodeAnag(T_list e);
T_anagList sortAddNodeAnag(T_list e, T_anagList l);
void getAnagrams(T_abr root, T_anagList* l);
void printAnagrams(T_anagList anagramsList);
void freeAnagrams(T_anagList l);