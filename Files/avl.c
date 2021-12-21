#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Headers/avl.h"

T_arbNode* StartTree(void){
    return NULL;
}

T_arbNode* InsertTree(T_arbNode *node, T_elt data){
    if (!node){
        node = (T_arbNode*) malloc(sizeof(T_arbNode));
        node->data = data;
        node->facteur = 0;
        node->l = NULL;
        node->r = NULL;
    }
    else if (data < node->data){
        node->l = InsertTree(node->l,data);
    }
    else{
        node->r = InsertTree(node->r,data);
    }
    return node;
}

T_arbNode* InsertAVL(T_arbNode *node, T_elt data, int *ok){

    if (!node){
        node = (T_arbNode*) malloc(sizeof(T_arbNode));
        node->data = data;
        //FAIRE LA FONCTION POUR AVOIR CE CODE ICI
        //node->data2 = SIGNATURE(data);

        node->facteur = 0;
        node->l = NULL;
        node->r = NULL;

        *ok = 1;
    }
//else if(data < node->data2){LE CORRECT *************************************************************
    else if(data < node->data){
        node->facteur = FindFactor(node);
        node->l = InsertAVL(node->l, data, ok);
        if(*ok){
            switch (node->facteur) {
                case -1: node->facteur = 0; *ok = 0; break;
                case 0: node->facteur = 1; break;
                case 1: node=Case1(node,ok); break;
            }
        }
    }else{
        node->facteur = FindFactor(node);
        node->r = InsertAVL(node->r, data, ok);
        if(*ok){
            switch (node->facteur) {
                case 1: node->facteur = 0; *ok = 0; break;
                case 0: node->facteur = -1; break;
                case -1: node=Case2(node,ok); break;
            }
        }
    }
    return node;
};

T_arbNode* Case1 (T_arbNode *a, int *ok){
    T_arbNode *aux;
    aux = a->l;
    if (aux->facteur == 1)
        a = RightRotation(a);
    else
        a = DoubleRightRotation(a);
    a->facteur = 0;
    *ok = 0;
    return a;
}

T_arbNode* Case2 (T_arbNode *a, int *ok){
    T_arbNode *aux;
    aux = a->r;
    if (aux->facteur == -1)
        a = LeftRotation(a);
    else
        a = DoubleLeftRotation(a);
    a->facteur = 0;
    *ok = 0;
    return a;
}

void FactorizesTree(T_arbNode **a){
        printf("FATORIZA\nnode=%d\nfacteur=%d\n\n", (*a)->data, (*a)->facteur+1);
    if(a){
        (*a)->facteur = FindFactor(a);
        printf("FATORIZA");

        (*a)->l = FactorTree((*a)->l);
        (*a)->r = FactorTree((*a)->r);
    }
}

void checkAVL(T_arbNode *a){
    if(a){
//        printf("VERIFICA\nnode = %d\nfacteur = %d\n\n", a->data, a->facteur);
        if (abs(a->facteur) >= 2){
            if(a->facteur == -2){
                if(a->r->facteur == 1)
                    a = DoubleLeftRotation(a);
                if(a->r->facteur == -1)
                    a = LeftRotation(a);
            }
            if(a->facteur == 2){
                if(a->l->facteur == -1)
                    a = DoubleRightRotation(a);
                if(a->l->facteur == 1)
                    a = RightRotation(a);

            }
        }
        checkAVL(a->l);
        checkAVL(a->r);
    }
}

void PrintWLevel(T_arbNode *node, int nivel){
    int i;
    if (node){
        nivel+=1;
        for(i = nivel; i>0; i--)
            printf("=");

        printf("%d\n",node->data);
        PrintWLevel(node->l, nivel);
        PrintWLevel(node->r, nivel);
    }
};

int NodeCounter(T_arbNode *node, int nivel){
    int a, b;
    if(nivel == 0){
        a = 0;
        b = 0;
    }

    if (node){
        if(node->l)
            a += NodeCounter(node->l, nivel);
        if(node->r)
            b += NodeCounter(node->r, nivel);
    }

    return a+b+1;
};

int Height (T_arbNode *a){
    int Alt_l, Alt_r;

    if (!a)
        return 0;

    Alt_l = Height (a->l);
    Alt_r = Height (a->r);

    if(Alt_r > Alt_l)
        return Alt_r +1;
    else
        return Alt_l +1;

};

int FindFactor(T_arbNode *a){
    return (Height(a->l) - Height(a->r));
};

int FactorTree(T_arbNode *a){
    int facteurR, facteurL, facteur;

    if (a)
    {
        facteurL = FactorTree(a->l);
        facteurR = FactorTree(a->r);

        facteur = FindFactor(a);
        a->facteur = facteur;
//        printf("node=%d\nfacteur=%d\n\n", a->data, a->facteur);

        if(abs(facteurL) > abs(facteur) && abs(facteurL) > abs(facteurR))
            return facteurL;
        else{
            if(abs(facteurR)>abs(facteur))
                return facteurR;
            else
                return facteur;
        }
    }
    else
        return 0;
};

int Balanced(T_arbNode *a){
    int alt_l, alt_r;
    if (a!=NULL)
    {
        alt_l = Height(a->l);
        alt_r = Height(a->r);
        return ( (alt_l - alt_r <2) && (alt_r - alt_l <2) &&
                 (Balanced (a->l)) && (Balanced (a->r)) );
    }
    else
        return 1;
};

void PrintPreOrder(T_arbNode *node){
    if (node){
        printf("%d ",node->data);
        PrintPreOrder(node->l);
        PrintPreOrder(node->r);
    }
};

void PrintPostOrder(T_arbNode *node){
    if (node){
        PrintPostOrder(node->l);
        PrintPostOrder(node->r);
        printf("%d ",node->data);
    }
};

void PrintInOrder(T_arbNode *node){
    if (node){
        PrintInOrder(node->l);
        printf("%d ",node->data);
        PrintInOrder(node->r);
    }

}

void PrintInterval(T_arbNode *node, T_elt small, T_elt big){
  if (node){//Se o node existe verifica a função
    //fazer caminhamento central a luerda para printar números em sequencia, print entre a recursão pra reita e a pra            luerda faz com que seja esse caminhamento

    PrintInterval(node->l, small, big);

    if (node->data >= small && node->data <= big)//Se o valor do node ta entre os limites, [small, big], printa
      printf("%d ",node->data);

    PrintInterval(node->r, small, big);
  }
};

T_arbNode* IntersectionTree(T_arbNode *a, T_arbNode *a2){
    T_arbNode *a3;

    a3 = StartTree();

    if (a && a2){
        printf("1 = %d\n2 = %d\n\n", a->data, a2->data);//printa as datas só para ver em que estado está

        if (a->data == a2->data){//quando encontra duas datas iguais
            a3 = InsertTree(a3, a->data);//insere na arvore nova
            printf("##########data = %d\n\n", a->data);//printa o item inserido
            return a3;
        }
        //colocando a condicao antes da recursividade e a primeira recursividade é pra luerda eu tenho um pré fixado luerda

        //eu percorro toda a arvore 'a' com caminhamento pre fixado a luerda
        a3 = IntersectionTree(a->l, a2);
        a3 = IntersectionTree(a->r, a2);
        //Depois de percorrer a arvore 'a' eu percorro a arvore 1 com o mesmo caminhamento
        //Toda vez q eu andar um elemnto na  arvore 'a2' eu vou percorrer toda a arvore 'a'
        a3 = IntersectionTree(a, a2->l);
        a3 = IntersectionTree(a, a2->r);

        //retorno o a3 pra deixar ele salvo
        return a3;
    }else {
        return 0;//retorno 0 quando chegar no fim da arvore
    }
}

T_arbNode* QueryABP(T_arbNode* a, T_elt data){

    while (a!=NULL){
        if (a->data == data )
            return a; //achou então retorna o ponteiro para o node
        else if (a->data > data)
            a = a->l;
        else
            a = a->r;
    }
    return NULL; //se não achou
}

void Intersect(T_arbNode* a, T_arbNode* b,  T_arbNode **c){
        if (a && b){
          if ( QueryABP(b,a->data) )
             *c = InsertTree(*c,a->data);
          Intersect(a->l, b, c);
          Intersect(a->r, b, c);
        }

}

int Compare(T_arbNode *a, T_arbNode *b){
//    if(!a && !b)
//        return 1;
//    if(a && b)
//        return (
//                Compare(a->r, b->r) &&
//                Compare(a->l, b->l) &&
//                (a->data == b->data)
//                );
//
//    return 0;
    int comp=1;

    if(!a && !b)
        return 1;
    if(a && b){
        comp = Compare(a->r, b->r);
        comp = Compare(a->l, b->l);

        if (a->data != b->data || comp == 0){
            return 0;
        }
        else
            return 1;
    }
    return 0;
}

T_arbNode* RightRotation(T_arbNode* a){
    T_arbNode *aux;

    aux = a->l;
    a->l = aux->r;
    aux->r = a;
    //Trocar o facteur de a para 0 pq agr ele ficou equilibrado.
    a = aux;
    return a;
}

T_arbNode* LeftRotation(T_arbNode *a){
    T_arbNode *aux;

    aux = a->r;
    a->r = aux->l;
    aux->l = a;
    //Trocar o facteur de a para 0 pq agr ele ficou equilibrado.
    a = aux;
    return a;
}

T_arbNode* DoubleLeftRotation (T_arbNode *a){
    T_arbNode *aux1, *aux2;

    aux1 = a->r;
    aux2 = aux1->l;
    aux1->l = aux2->r;
    aux2->r = aux1;
    a->r = aux2->l;
    aux2->l = a;

    a = aux2;
    return a;
}

T_arbNode* DoubleRightRotation (T_arbNode* a){
//TESTE
    a->l = LeftRotation(a->l);
    a = RightRotation(a);

//    a->l = LeftRotation(a->l);
//    a = RightRotation(a);

    return a;
}

int xxx(T_arbNode *a){
  if (a!= NULL)
  {
     if (!a->l && !a->r)
        return 1;
     return xxx(a->l) + xxx(a->r);
  }
   return 0;
}

void NodePosition(T_arbNode *node, int n, int k){
    //  if (node){
//
//    if(!node->r && !node->l && n>0){
//        n = n*-1;
//    }
//
//    if(n>0){
//        printf("data ANTES = %d\n",node->data);
//        NodePosition(node->r, n);
//    }
//    if(n>=0){
//        printf("data DEPOIS = %d\n",node->data);
//        NodePosition(node->r, n+1);
//        NodePosition(node->l, n+1);
//
//        printf("n = %d\n",n);
//        if (n == -1)
//          printf("RESPOSTA%d\n",node->data);
//    }
//
//  }
    if(node){
        NodePosition(node->r, n-1, k+1);
        printf("n = %d\n",n);
        printf("k = %d\n",k);
        printf("data = %d\n\n",node->data);
        if(n+k == 1)
            printf("RESPOSTA = %d\n\n",node->data);
        NodePosition(node->l, n+4, k-4);

    }

};

int imprime_nesino(T_arbNode *a, int n){
    if(a!=NULL){
        n = imprime_nesino(a->r, n);
        printf("pos = %d\n",n);
        printf("data = %d\n\n",a->data);
        n--;
        if(n==0)
            printf("%d", a->data);
        else if (n>0){
            printf("pos = %d\n",n);
            printf("data = %d\n\n",a->data);
            n = imprime_nesino(a->l, n);
        }
    }
    return n;
}

char* ConsulterAVL(T_arbNode *a, char* cle, int *comp){
    while (a!=NULL){

        *comp+=1;
        //percorre a arvore até encontrar o nodo
        //if (strcmp(a->data2,cle)==0){ LE CORRECT *************************************************************
        if (strcmp(a->data,cle)==0){
            *comp+=1;//conta uma operação toda vez que avança um nodo ou quando encontra o requerido
            return a->data;
        }
        else {
            *comp+=1;
        //if (strcmp(a->data2,cle)==0){ LE CORRECT *************************************************************
            if (strcmp(a->data,cle)>0)
                a = a->l;

            else
                a = a->r;
        }
    }
    return cle;
}