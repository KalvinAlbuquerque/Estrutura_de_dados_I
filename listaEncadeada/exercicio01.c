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
Nodo * gerarNovaListaImparPrimos(Nodo ** lista);
void inserirElemento(Nodo ** lista, int info);
int removerElemento(Nodo ** lista);
void listarElementos(Nodo ** lista);
int getTamanhoLista(Nodo ** lista);
void retirarElementoPares(Nodo ** lista);
int isPrime(int num);


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

    printf("\n");
}

Nodo * gerarNovaListaImparPrimos(Nodo ** lista)
{
    /* Criando nova lista */
    Nodo * inicioNovaLista = NULL;
    Nodo * inicioListaPrimordial = *lista;
    Nodo * anteriorListaPrimordial = NULL;
    Nodo * atualListaPrimordial = *lista;

    while(atualListaPrimordial != NULL)
    {
        /* Verificando se o número é primo e ímpar */
        if(atualListaPrimordial->info%2 != 0 && isPrime(atualListaPrimordial->info) == 1)
        {
            /* Verificando se o primeiro elemento da lista inicial é ímpar e primo */
            if(anteriorListaPrimordial == NULL)
            {
                /* Fazendo com que o início da lista inicial seja o segundo elemento*/
                inicioListaPrimordial = atualListaPrimordial->prox;

                /* Fazendo com que o elemento ímpar/primo aponte para o início da nova lista */
                atualListaPrimordial->prox = inicioNovaLista;

                /* Realocando o início da nova lista para o atual  */
                inicioNovaLista = atualListaPrimordial;

                /* Fazendo com que o atual retorne para a lista inicial */
                atualListaPrimordial = inicioListaPrimordial;
            }
            else
            {
                /* Caso não seja o primeiro elemento da lista inicial */

                /* Fazendo com que o item anterior aponte para o item subseguinte ao atual */
                anteriorListaPrimordial->prox = atualListaPrimordial->prox;

                /* Fazendo com que o atual aponte para o início da nova lista */
                atualListaPrimordial->prox = inicioNovaLista;

                /* Mudando o inicío da nova lista */
                inicioNovaLista = atualListaPrimordial;

                /* Fazendo com que o atual retorn para a lista inicial do ponto em que parou*/
                atualListaPrimordial = anteriorListaPrimordial->prox;
            }

        }
        else
        {
            /* Se não for um número ímpar ou par, apenas passo para o próximo */
            anteriorListaPrimordial = atualListaPrimordial;
            atualListaPrimordial = atualListaPrimordial->prox;
        }
    }

    listarElementos(&inicioNovaLista);

    return inicioNovaLista;
}

int isPrime(int num)
{
    /* Número menores ou iguais a 1 não são primo */
    if(num <= 1)
    {
        return 0;
    }

    /* 2 ,3, 5 e 7 são primos */
    if(num <= 3 || num == 7 || num == 5)
    {
        return 1;
    }

    /* Se o número for divisível por 2, 3, 5 ou 7 ele não é primo */
    if(num % 2 == 0 || num % 3 == 0 || num % 7 == 0 || num % 5 == 0) 
    {
        return 0;
    }

    return 1;

}

void retirarElementoPares(Nodo ** lista)
{
    Nodo * atual = *lista;
    Nodo * anterior = NULL;

    while(atual != NULL)
    {
        /* Verificando se o número é par */
        if(atual->info %2 == 0)
        {
            /* Verificando se o número está no começo da lista*/
            if(anterior == NULL)
            {
                /* Fazendo com que o início da lista aponte para o próximo elemento */
                *lista = atual->prox;

                /* Dando free no elemento par */
                free(atual);

                /* Fazendo com que o atual aponte para o início da lista novamente */
                atual = *lista;
            }
            else
            {
                /* Caso o elemento par não esteja no início da lista */

                /* Fazendo com que o anterior aponte para o item subseguinte ao atual */
                anterior->prox = atual->prox;

                /* Liberando o elemento par */
                free(atual);

                /* Fazendo com que atual seja o item subseguinte ao anterior */
                atual = anterior->prox;
            }
        }
        else
        {
            /* Se não for par, eu passo para o próximo */
            anterior = atual;
            atual = atual->prox;
        }
    }
}
