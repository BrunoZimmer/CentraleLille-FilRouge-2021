#include <stdio.h> // sprintf
#include <string.h> // strdup

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

#include "../Headers/elt.h"

	/////////////////////////////////////////////////////////////////////////
	// 
	// Type T_elt
	// char * toString(T_elt) :
	// 	Renvoie une chaîne de caractère représentant un T_elt pour l’afficher
	// T_elt genElt(void) :
	// 	Génère un nouveau T_elt différent du précédent 
	// 	(utiliser une variable statique)
	/////////////////////////////////////////////////////////////////////////

#ifdef ELT_CHAR
// T_elt est un char... 
char * toString(T_elt e) {
	// Il faut transformer un char en chaine... 
	static char buffer[2]; 
	buffer[0] = e; 
	buffer[1] = '\0';
	return buffer; 
	// Si on allouait de la mémoire pour buffer, il faudrait penser à la libérer... 
	// => Risque de fuite de mémoire... 
	// On ne peut pas non plus allouer un tableau static sur la pile ! 
	// => On utilise un buffer déclaré comme variable statique !
	// Dans ce cas, deux appels à toString renverraient la même adresse...
}

T_elt genElt(void) {
	static int indice = 0; 
	// on va égrainer les caractères alphabétiques de 'a' à 'z'
	// de manière circulaire pour ne pas déborder... 
	return 'a' + (indice++%26); 
}

T_elt eltdup(T_elt e) {
	// rien à faire : le T_elt ne contient pas d'adresses mémoire 
	return e; 
} 

int eltcmp(T_elt e1, T_elt e2) {
	// on renvoie la différence de code ascii 
	return e1 - e2; 
}

int compElt(T_elt e1, T_elt e2) {
  return e1 - e2;
}
#endif

#ifdef ELT_INT
// T_elt est un int... 
char * toString(T_elt e) {
	// Il faut transformer un int en chaine... 
	static char buffer[11]; // nbr max de chiffres nécessaires ? 
	// 2^31 vaut 2147483648...

	sprintf(buffer, "%d",e); 
	return buffer; 
	// cf. remarques précédentes
}

T_elt eltdup(T_elt e) {
	// rien à faire : le T_elt ne contient pas d'adresses mémoire 
	return e; 
} 
T_elt genElt(void) {
	static int indice = 0; 
	return indice++; 
}

int compElt(T_elt e1, T_elt e2) {
	// on renvoie la différence de valeur
  return e1 - e2;
}

int eltcmp(T_elt e1, T_elt e2) {
	// on renvoie la différence de valeur
	return e1 - e2; 
}

#endif

#ifdef ELT_STRING
// T_elt est un char * ...
char * toString(T_elt e) {
	return e; // c'est déjà une chaine ! 
}

T_elt genElt(void) {
	static int indice = 0; 
	// produire une chaine aléatoire... 
	// On va écrire elt_<numéro>
	char buffer[15]; // elt_+<11 chiffres>
	sprintf(buffer, "elt_%d",indice++); 
	return strdup(buffer); 
} 

int compElt(T_elt e1, T_elt e2) {
  while (*e1 != '\0' && (*e1 == *e2)) {
    e1++; 
    e2++;
  }
  return (e1==e2) ? 0 : (*(char *)e1 - *(char *)e2);
}

T_elt eltdup(T_elt e) {
	// on renvoie une chaine dupliquée
	return strdup(e); 
} 

T_elt eltSig(T_elt e) {

	T_elt sig = NULL;
	sig = strdup(e);
	char temp;

   	int i, j;
   	int n = strlen(sig);
	//Bubble sort
	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
        	if (sig[i] > sig[j]) {
        		temp = sig[i];
        		sig[i] = sig[j];
            	sig[j] = temp;
        	}
      	}
   	}
	
	return sig;
}

int eltcmp(T_elt e1, T_elt e2) {
	// on renvoie la différence de code ascii 
	return strcmp(e1,e2); 
}
#endif

#ifdef ELT_STRUCT
// T_elt est une structure plus complexe
char * toString(T_elt e) {
	// on affiche la première case du tableau
	// On pourrait boucler pour afficher les entiers dans le tableau 
	 
	static char buffer[11]; // nbr max de chiffres nécessaires ? 
	// 2^31 vaut 2147483648...
	sprintf(buffer, "%d",e.t[0]); 
	return buffer;

	// => On utilise un buffer déclaré comme variable statique !
	// Dans ce cas, deux appels à toString renverraient la même adresse...
	// Il ne faut pas les utiliser dans le cadre du même appel à la fonction printf
}

T_elt genElt(void) {
	T_elt aux; 
	static int indice = 0; 
	// On produit un tableau ne contenant qu'une seule case avec une valeur toujours différente 
	aux.size = 1;
	aux.t = (int *) malloc(sizeof(int)); 
	aux.t[0] = indice++;
	return aux;  
} 

/*
	typedef struct {
		int * t; 	// un tableau 
		int size; 	// la taille de ce tableau   	
	} T_elt; 
*/

T_elt eltdup(T_elt e) {
	// On duplique le tableau avec memcpy 
	T_elt aux;
	aux.size = e.size; 
	aux.t =   (int *) malloc(e.size * sizeof(int)); // t est un tableau d'entiers...
	memcpy(aux.t, e.t, e.size * sizeof(int));
	return aux; 
} 

int eltcmp(T_elt e1, T_elt e2) {
	// On renvoie la différence entre les premières cases de chaque tableau 
	// Il faudrait continuer avec les cases suivantes en cas d'égalité... 
 	return e1.t[0] - e2.t[0]; 
}
#endif

