#include "../Headers/elt.h" // T_elt 
#include "../Headers/Exerc1.h" 
#include "../Headers/avl.h" 
#include <assert.h>
#include <sys/stat.h>

char* outputPath = ".";

void imprimir_simples(T_abrNode* a){//////////////////////////////////
    if (a == NULL){
        return;
    }

    printf("%s ", a->mots->data);
    imprimir_simples(a->l);
    imprimir_simples(a->r);

}

static void genDotAVL(const T_abrNode* root, FILE* basename)
{
	fprintf(basename, "\t\"%s\"",toString(root->mots->data)); 
	fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> | <d>}}\"];\n",toString(root->mots->data),root->facteur);
	if (root->r == NULL && root->l == NULL)
	{
		fprintf(basename, "\t\"%s\"", toString(root->mots->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> NULL | <d> NULL}}\"];\n", toString(root->mots->data),root->facteur);
	}
	else if (root->r == NULL)
	{
		fprintf(basename, "\t\"%s\"", toString(root->mots->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> | <d> NULL}}\"];\n", toString(root->mots->data),root->facteur);
	}
	else if (root->l == NULL)
	{
		fprintf(basename, "\t\"%s\"",toString(root->mots->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> NULL | <d> }}\"];\n", toString(root->mots->data),root->facteur);
	}

	if (root->l)
	{
		fprintf(basename, "\t\"%s\"",toString(root->mots->data));
		fprintf(basename, ":g -> \"%s\";\n", toString(root->l->mots->data));
		genDotAVL(root->l, basename);
	}

	if (root->r)
	{
		fprintf(basename, "\t\"%s\"",toString(root->mots->data));
		fprintf(basename,":d -> \"%s\";\n", toString(root->r->mots->data));
		genDotAVL(root->r, basename);
	}
}

void createDotAVL(const T_abrNode* root, const char* basename)
{
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }
	
	sprintf(DOSSIER_DOT, "%s/img/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/img/png/",outputPath);
	
	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	
	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);
	
	fp = fopen(fnameDot, "w");
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);
		
    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -T png  %s -o %s", fnameDot, fnamePng);
    printf("dot -T png  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}