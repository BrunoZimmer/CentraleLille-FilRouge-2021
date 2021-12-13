#include "data.h"
//gcc main.c data.h avl.c -o main
//.\main lemas_en_shuf.txt TheGodfather-MarioPuzo-Chapter1.txt SaidaTeste.txt

int main(int argc, char **argv) {

    char* arquivoEntrada = argv[2];
    char* arquivoSaida = argv[3];
    char* arquivoDicionario = argv[1];
//    char* arquivoEntrada = "c:\\Users\\Bruno\\Desktop\\Estudos\\EstruturaDados\\ProjetoFinal\\ArquivosTeste\\TheGodfather-MarioPuzo-Chapter1.txt";
//    char* arquivoSaida = "c:\\Users\\Bruno\\Desktop\\Estudos\\EstruturaDados\\ProjetoFinal\\ArquivosTeste\\saida.txt";
//    char* arquivoDicionario = "c:\\Users\\Bruno\\Desktop\\Estudos\\EstruturaDados\\ProjetoFinal\\ArquivosTeste\\lemas_en_shuf.txt";

    char *palavra, *chave, linha[MAXCHAR], *lema; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};

    int contador, comp;

    int ok;

    clock_t comeco, fimArvore, fim; //para contar o tempo decorrido

    FILE * dicionario;//abrir o input
    FILE * entrada;//abrir o input
    FILE * saida;//Abrir o output

    pNodoA *arvoreAVL;//Raiz da arvore AVL


    setlocale(LC_ALL,"");//Permitir print de acentos corretamente


//############################## ARIR ARQUIVO DE LEMAS AVL ########################################################
    comeco = clock();//Contagem de tempo mexendo no arquivo

    dicionario = fopen (arquivoDicionario, "r");
    if (dicionario == NULL){//Erro ao abrir arquivo corrompido
        printf ("Erro ao abrir o arquivo %s", arquivoDicionario);
        return 1;
    }
    arvoreAVL = InicializaArvoreAVL();//Inicia arvore AVL
    contador = 0;//inicia contador de tempo só pra visualizar


//############################# CRIAR DICIONARIO AVL #######################################################
    while (fgets(linha,MAXCHAR,dicionario)){//Percorre por paragrafos
        palavra= strtok (linha, separador);// Todos caracteres definidos antes como separador
        chave= palavra;
        palavra= strtok(NULL, separador);
        arvoreAVL = InsereAVL(arvoreAVL, palavra, chave, &ok);
        if(abs(clock()%CLOCKS_PER_SEC) < 50){//ficar contando enquanto carrega a arvore
            contador ++;
            system("cls");
            printf("Carregando o dicionario em AVL: %d\n", contador);
        }
    }
    system("cls");
    printf("Carregamento concluído");

    fimArvore = clock();

//############################### ARQUIVO DE SAIDA AVL###########################################################
    entrada = fopen (arquivoEntrada, "r");//Abre arquivo de entrada
    saida = fopen(arquivoSaida, "w");//Cria o arquivo de saida PARA POR OS LEMAS

    comp = 0;
    while (fgets(linha,MAXCHAR,entrada)){//Percorre por paragrafos
        palavra = strtok (linha, separador);

        while (palavra != NULL){
            lema = ConsultaAVL(arvoreAVL, strlwr(palavra), &comp);//Verifica se a palavra do texto tem lema
            fprintf(saida,"%s ", strlwr(lema));//salva a palavra no arquivo de saida
            palavra = strtok (NULL, separador);
        }
        fprintf(saida,"\n");//Separador de paragrafos
    }

    printf("\nArquivo %s usando a AVL gerado com sucesso.\n",arquivoSaida);
    printf("\nForam feitas %d acoes de pesquisa na AVL.\n",comp);

    fim = clock(); // finaliza contagem do tempo
    float milisecondsTot = (float)(fim - comeco) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
    float milisecondsArv = (float)(fimArvore - comeco) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
    float milisecondsLema = (float)(fim - fimArvore) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
    printf("Demandou um tempo total de %.2f ms\n",milisecondsTot);
    printf("Demandou um tempo para criacao da arvore de %.2f ms\n",milisecondsArv);
    printf("Demandou um tempo para lematizar de %.2f ms\n",milisecondsLema);

    fclose (entrada); //fecha os arquivos
    fclose (saida);

    return 0;
}