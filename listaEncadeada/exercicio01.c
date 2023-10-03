/* Escreva funções, em C, que recebam uma lista simplesmente encadeada ordenada, e realizem as seguintes operações:
a. retirar todos os elementos ímpares que são primos, e, gerar uma outra lista contendo apenas os elementos retirados
da lista inicial, em ordem decrescente;
b. retirar todos os elementos pares da lista inicial. */

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int info;
    struct Nodo * prox;
}Nodo;

/* Funçoes referentes à lista */
void inserirElemento(Nodo ** lista, int info);
int removerElemento(Nodo ** lista);
void listarElementos(Nodo ** lista);
int getTamanhoLista(Nodo ** lista);

void inserirElemento(Nodo ** lista, int info)
{
    /* Alocando espaço na memória para novo elemento */
    Nodo * novoElemento = (Nodo * ) malloc(sizeof(Nodo));
    
    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha memoria disponível!");
        return;
    }
    /* Setando atributos do novo elemento*/
    novoElemento->prox = NULL;
    novoElemento->info = info;

    /*Verificando se a lista está vazia*/
    if(*lista == NULL)
    {
        /* Se a lista estiver vazia, então o primeiro elemento será o novoElemento criado */
        printf("\nCriando primeiro elemento da lista");
        *lista = novoElemento;
    }
    else
    {
        /* Caso  a lista estiver preenchida, o novo elemento da lista entrará no final da lista*/
        /* Iterando a lista e certificando que estou no final dela, ou seja, o final da lista está apontando para NULL */
        Nodo * finalDaLista = *lista;
        while(finalDaLista->prox != NULL)
        {
            printf("\nInfo: %d", finalDaLista->info);
            finalDaLista = finalDaLista->prox; 
        }

        /* Uma vez aqui, tenho certeza que a variável "finalDaLista" armazena o endereço do último elemento da lista */
        finalDaLista->prox = novoElemento;
        printf("\nAgora o último elemento da lista eh: %d", finalDaLista->prox->info);
    }
}


int removerElemento(Nodo ** lista)
{
    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        printf("\nA lista esta vazia\n");
        return -1;
    }
    else
    {
        Nodo * aux = *lista;
        int info = (*lista)->info;
        /* Fazendo com que o inicio da lista seja o segundo elemento */
        *lista = (*lista)->prox;

        /* Removendo o antigo primeiro item da lista */
        free(aux);

        printf("\nO elemento de info %d foi removido\n", info);
        return info;
    }

}

void listarElementos(Nodo ** lista)
{
    Nodo * aux = *lista;
    
    /* Verificando se a lista está vazia */
    if(aux == NULL)
    {
        printf("\nA lista esta vazia\n");
        return;
    }
    else
    {
        while(aux != NULL)
        {
            printf("\n%d", aux->info);
            aux = aux->prox;
        }
    }
}
