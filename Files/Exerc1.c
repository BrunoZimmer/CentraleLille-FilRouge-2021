#include "../Headers/elt.h" // T_elt 
#include "../Headers/Exerc1.h" 
#include "../Headers/avl.h" 

void generatePNG(const T_Arbre l, const char * filename, int indice){
	FILE *file;

	T_Arbre aux = l;
	int i=0;
	// if(fopen(filename, "r")){
    //     // fclose(file);
	// }else{
    //     // fclose(file);
	// 	file = fopen(filename, "w");
	// 	generateHeaderPNG(file);
	// }


    if (aux){
		i=i+1;
        // generatePNG(aux->l, filename, aux->facteur);
		if(aux->l && aux->r){
			//"ID_0003" [label = "{<elt> 30000000  | <next> NULL}|{<> 1 | <next> NULL}"];
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> }", i,toString(aux->data));
			fprintf(file, "|{<> %d | <next>}\"];\n", i,toString(aux->data));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+1);
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+2);
		}else if(aux->l){
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> }", i,toString(aux->data));
			fprintf(file, "|{<> %d | <next> NULL}\"];\n", i,toString(aux->data));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+1);
		}else if(aux->r){
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> NULL}", i,toString(aux->data));
			fprintf(file, "|{<> %d | <next>}\"];\n", i,toString(aux->data));
			fprintf(file, "\"ID_%04d\" : next -> \"ID_%04d\";\n", i,i+2);
		}else{
			fprintf(file, "\"ID_%04d\" [label = \"{<elt> %s  | <next> NULL}", i,toString(aux->data));
			fprintf(file, "|{<> %d | <next> NULL}\"];\n", i,toString(aux->data));
		}
		
		i=i+1;
        generatePNG(aux->r, filename, aux->facteur);
    }


	fputs("}", file);
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