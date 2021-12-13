#ifndef _ELT_H_
	#define _ELT_H_ // prévient les includes multiples

	/////////////////////////////////////////////////////////////////////////
	// CHOISIR ICI CE QUE REPRESENTE LE TYPE T_elt 
	//#define ELT_CHAR		// un caractère ?
	#define ELT_INT		// un entier (choix par défaut) ?
	//#define ELT_STRING	// une chaîne de caractères ?
	/////////////////////////////////////////////////////////////////////////

	//https://stackoverflow.com/questions/2998864/how-to-add-a-or-condition-in-ifdef

	#if ! defined(ELT_CHAR) && ! defined(ELT_INT) && ! defined(ELT_STRING)
	#define ELT_INT
	#endif

	#ifdef ELT_CHAR
	typedef char T_elt;
	#endif

	#ifdef ELT_INT
	typedef int T_elt; 
	#endif

	#ifdef ELT_STRING
	typedef char * T_elt; 
	#endif

	// valable pour tous les types de T_elt 
	char * toString(T_elt e); 
	T_elt genElt(void); 
  int compElt(T_elt e1, T_elt e2);
#endif 

