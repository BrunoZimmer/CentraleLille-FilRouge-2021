#include "../Headers/elt.h" // T_elt 
#include "../Headers/Exerc1.h" 
#include "../Headers/avl.h" 

void generatePNG(const T_Arbre l, const char * filename, const int value){
	FILE *file;

	T_Arbre aux = l;
	int i=value;
	// if(fopen(filename, "r")){
    //     // fclose(file);
	// }else{
    //     // fclose(file);
	// 	file = fopen(filename, "w");
	// 	generateHeaderPNG(file);
	// }
	file = fopen(filename, "a");


    if (aux){
	// for(i=1;aux;i++, aux = aux->r){
		// i=i+1;
		if(aux->l)
        	generatePNG(aux->l, filename, i+1);
		if(aux->l && aux->r){
			//"ID_0003" [label = "{<elt> 30000000  | <next> NULL}|{<> 1 | <next> NULL}"];
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> }", i,toString(aux->data));
			fprintf(file, "|{<facteur> %s | <next>}\"];\n", toString(aux->facteur));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+1);
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+2);
		}else if(aux->l){
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> }", i,toString(aux->data));
			fprintf(file, "|{<facteur> %s | <next> NULL}\"];\n", toString(aux->facteur));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+1);
		}else if(aux->r){
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> NULL}", i,toString(aux->data));
			fprintf(file, "|{<facteur> %s | <next>}\"];\n", toString(aux->facteur));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+2);
		}else{
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> NULL}", i,toString(aux->data));
			fprintf(file, "|{<facteur> %s | <next> NULL}\"];\n", toString(aux->facteur));
		}
		
		// i=i+1;
		if(aux->r)
        	generatePNG(aux->r, filename, i+2);
    }

	// fclose(file);
}

void generateHeaderPNG(FILE * filePNG)
{
	char ch, sourceFile[MAXCHAR];
	FILE *source;

	strcpy(sourceFile, "../Headers/header.dot");
	
    
	source = fopen(sourceFile, "r");
	while( ( ch = fgetc(source) ) != EOF )
		fputc(ch, filePNG);

	//printf("Header copied successfully.\n");

	fclose(source);
}