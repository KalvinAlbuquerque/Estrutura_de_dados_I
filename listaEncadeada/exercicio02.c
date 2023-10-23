/*
    2. Escreva uma função, em C, que receba uma lista simplesmente encadeada, e
    retorne uma lista ordenada (crescente) sem alocar espaços para novos
    elementos da lista. 
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo
{
    int info;
    struct Nodo * prox;

}Nodo;

void limparTela();
void insert(Nodo ** lista, int info);
void listar(Nodo ** lista);
Nodo * insertionSort(Nodo ** lista);
void sortedInsert(Nodo * newNodo, Nodo ** listaOrdenada);

int main()
{
    int opcao;
    int info;
    Nodo * lista = NULL;

    do
    {
        printf("\n1.Inserir elementos");
        printf("\n2.Listar elementos");
        printf("\n3.Ordenar lista em ordem crescente");
        printf("\n0.Sair\n");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {   
                limparTela();
                printf("\nDigite o numero que deseja inserir: ");
                scanf("%d", &info);
                insert(&lista, info);
                break;
            }
            case 2:
            {
                limparTela();
                listar(&lista);
                break;
            }
            case 3:
            {
                limparTela();
                insertionSort(&lista);
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                printf("\nOpcao invalida!");
                break;
            }
        }
    }while(opcao != 0);
    return 0;
}


void insert(Nodo ** lista, int info)
{
    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo *) malloc(sizeof(Nodo));

    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando novo elemento  */
    novoElemento->info = info;
    novoElemento->prox = NULL;

    /* Inserindo novo elemento na lista */

    /* Verificando se a lista está vazia, se estiver , o primeiro elemento será incluído */
    if(*lista == NULL)
    {
        *lista = novoElemento;
    }
    else
    {
        /* Se a lista estiver preenchida, apenas insiro o elemento no final */
        Nodo * atual = *lista;
         
        /* Percorrendo a lista até o último elemento, ou seja, o último elemento aponta para NULL */
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = novoElemento;
    }
    
}

void listar(Nodo ** lista)
{
    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        printf("\nA lista esta vazia!");
        return;
    }

    /* Percorrendo a lista e printando-a */
    Nodo * atual = *lista;
    while(atual != NULL)
    {
        printf("\n%d", atual->info);
        atual = atual->prox;
    }

    printf("\n");
}

void sortedInsert(Nodo * newNodo, Nodo ** listaOrdenada)
{
    /* Caso especial, a lista está vazia ou o newNodo é menor do que o primeiro elemento da lista */
    if(*listaOrdenada == NULL || (*listaOrdenada)->info >= newNodo->info)
    {
        /* New nodo agora será o primeiro elemento da lista ordenada */
        newNodo->prox = *listaOrdenada;

        *listaOrdenada = newNodo;
    }
    else
    {
        /* Iterando a lista até ser o último elemento da lista ou até que o novo elemento encontre algum elemento maior que ele */
        Nodo * atual = *listaOrdenada;
        while(atual->prox != NULL && atual->prox->info < newNodo->info)
        {
            atual = atual->prox;
        }

        /* Uma vez aqui, ou estamos no fim da lista, ou o próximo elemento é maior do que o novo elemento */
        /* Encaixando o novo elemento na frente do atual */
        newNodo->prox = atual->prox;

        /* Fazendo o atual apontar para o novo elemento */
        atual->prox = newNodo;
    }
}

Nodo * insertionSort(Nodo ** lista)
{
    /* Verificando se a lista está vazia */
    if(*lista == NULL || (*lista)->prox == NULL)
    {
        printf("\nA lista esta vazia!");
        return NULL;
    }

    /* Criando nova lista */
    Nodo * listaOrdenada = NULL;

    /* Chamando a função para ordenar a lista */
    Nodo * atual = *lista;
    while(atual != NULL)
    {
        /* Guardando a posição do próximo para não perder a lista */
        Nodo * proximo = atual->prox;

        sortedInsert(atual, &listaOrdenada);

        atual = proximo;

    }
    *lista = listaOrdenada;
    
    return *lista;
}

void limparTela() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}