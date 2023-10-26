/*  
    9. Escreva um programa, em C, para inserir, retirar e consultar uma lista
    duplamente encadeada ordenada em forma decrescente. Após cada operação,
    o programa deve informar a quantidade de nós, da direita para a esquerda e da
    esquerda para a direita. (implemente um menu de opções).
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo
{
    int info;
    struct Nodo * prox;
    struct Nodo * prev;

}Nodo;

/* Função para inserir um elemento no começo da lista */
void push(Nodo ** lista, int info);
void inserirDepois(Nodo * anterior, int info);
void inserirAntes(Nodo* sucessor, int info, Nodo ** lista);
void listar(Nodo ** lista);
Nodo * buscarElemento(Nodo ** lista, int info);
void append(Nodo ** lista, int info);
int solicitarValor();
void ordenarDescrescente(Nodo ** listaOrdenada, Nodo * novoElemento);
void insertionSort(Nodo ** lista);

int main()
{
    int opcao, info;
    Nodo * lista = NULL;  
    do
    {
        printf("\n1.Push");
        printf("\n2.Inserir elemento antes");
        printf("\n3.Inserir elemento depois");
        printf("\n4.Listar");
        printf("\n5.Append");
        printf("\n6.Ordernar lista em ordem decrescente");
        printf("\n9.Limpar tela");
        printf("\n0.Sair");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                push(&lista, solicitarValor());
                break;
            }
            case 2:
            {
                /* Solicitando valor que deseja buscar */
                printf("\nDigite antes de qual elemento deseja inserir outro: ");
                scanf("%d", &info);
                Nodo * sucessor = buscarElemento(&lista, info);

                if(sucessor)
                {
                    inserirAntes(sucessor, solicitarValor(), &lista);
                }

                break;
            }
            case 3:
            {
                /* Solicitando valor que deseja buscar */
                printf("\nDigite depois de qual elemento deseja interir outro: ");
                scanf("%d", &info);
                Nodo * anterior = buscarElemento(&lista, info);

                if(anterior)
                {
                    inserirDepois(anterior, solicitarValor());
                }
                break;
            }
            case 4:
            {
                listar(&lista);
                break;
            }
            case 5:
            {
                append(&lista, solicitarValor());
                break;
            }
            case 6:
            {
                insertionSort(&lista);
                break;
            }
            case 9:
            {
                system("clear");
                break;
            }
            case 0:
            {
                break;
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
void push(Nodo ** lista, int info)
{
    /*Criando novo elemento */
    Nodo * novoElemento = (Nodo*)malloc(sizeof(Nodo));
    
    /* Verificando se há memória disponível */
    if(novoElemento == NULL)
    {
        printf("\nNao ha memoria disponivel!");
        return;
    }

    /* Setando info do novo elemento */
    novoElemento->info = info;
    novoElemento->prev = NULL;
    novoElemento->prox = NULL;

    /* Verificando se a lista esta vazia, ou seja, se é o primeiro elemento da lista */
    if(*lista == NULL)
    {
        *lista = novoElemento;
    }
    else
    {
        /* Caso a lista não esteja vazia */
        /* Fazendo o novo elemento  apontar para o inicio da lista */
        novoElemento->prox = *lista;
        *lista = novoElemento;
    }
}

void inserirDepois(Nodo * anterior, int info)
{
    /* Verificando se o prev_node é nulo */
    if(anterior ==  NULL)
    {
        printf("\nO nodo nao pode ser nulo!");
        return;
    }

    /* Criando novo Nodo */
    Nodo * novoElemento = (Nodo*)malloc(sizeof(Nodo));

    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando informações do novo elemento */
    novoElemento->info = info;

    /* Fazendo com que o novo elemento fique entre o anterior e o atual */
    novoElemento->prox = anterior->prox;

    novoElemento->prev = anterior;

    /* Fazendo o anterior apontar para o novo elemento */
    anterior->prox = novoElemento;


    /* Verificando se o atual é nulo */
    /* Se for nulo, não tenho como mudar o prev dele */
    if(novoElemento->prox != NULL)
    {
        /* Fazendo o atual apontar o prov para o novo elemento caso o atual não seja nulo*/
        novoElemento->prox->prev = novoElemento;
    }
    
}

void inserirAntes(Nodo * sucessor, int info, Nodo ** lista)
{
    /* Verificando se o sucessor é nulo*/
    if(sucessor == NULL)
    {
        printf("\nO elemento não pode ser nulo");
        return;
    }

    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo*)malloc(sizeof(Nodo));

    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando informações do novo elemento */
    novoElemento->info = info;

    /* Fazendo o novo elemento apontar o prev para o atual */
    novoElemento->prev = sucessor->prev;

    /* Fazendo novo elemento apontar para o sucessor */
    novoElemento->prox = sucessor;

    /* Fazendo sucessor prev apontar para novo elemento */
    sucessor->prev = novoElemento;

    /* Verificando se o anterior ao novo elemento é nulo */
    /* Ou seja, se ele é o primeiro da fila. Se for, não posso acessar, pois ele é nulo */
    if(novoElemento->prev != NULL)
    {
        novoElemento->prev->prox = novoElemento;

    }
    else
    {
        /* Se for nulo, eu faço a lista começar pelo novo elemento */
        *lista = novoElemento;
    }

}

Nodo * buscarElemento(Nodo ** lista, int info)
{
    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        printf("\nA lista esta vazia!");
        return NULL;
    }

    Nodo * atual = *lista;
    while(atual->info != info && atual->prox != NULL)
    {
        atual = atual->prox;
    }

    if(atual->info != info)
    {
        printf("\nO elemento nao existe");
        return NULL;
    }
    else
    {
        printf("\nElemento encontrado com sucesso!");
        return atual;
    }
}

int solicitarValor()
{
    int info;
    system("clear");
    printf("\nDigite o valor que deseja inserir: ");
    scanf("%d", &info);

    return info;
}

void listar(Nodo ** lista)
{
    system("clear");

    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        printf("\nA lista esta vazia!!");
        return;
    }
    
    Nodo * atual = *lista;
    while(atual != NULL)
    {
        printf("\n%d", atual->info);
        atual = atual->prox;
    }

    printf("\n");
}

void append(Nodo ** lista, int info)
{
    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo *)malloc(sizeof(Nodo));

    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando novo elemento */
    novoElemento->info = info;
    novoElemento->prev = NULL;
    novoElemento->prox = NULL;

    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        *lista = novoElemento;

    }
    else
    {
        /* Iterando a lista até o último elemento */
        Nodo * atual = *lista;

        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }

        /* Fazendo atual apontar para novo elemento */
        atual->prox = novoElemento;

        /* Fazendo com que novo elemento prev aponte para o último da lista */
        novoElemento->prev = atual;
    }
    
}

void ordenarDescrescente(Nodo ** listaOrdenada, Nodo * novoElemento)
{

    /* Caso a lista esteja vazia ou o novo elemento for menor que o primeiro elemento da lista */
    if(*listaOrdenada == NULL)
    {
        *listaOrdenada = novoElemento;
        novoElemento->prev = NULL;
        novoElemento->prox = NULL;
    }
    else if((*listaOrdenada)->info < novoElemento->info)
    {
        novoElemento->prox = *listaOrdenada;

        novoElemento->prev = NULL;

        (*listaOrdenada)->prev = novoElemento;

        *listaOrdenada = novoElemento;
    }
    else
    {
        Nodo * atual = *listaOrdenada;
        while(atual->prox != NULL && novoElemento->info < atual->prox->info )
        {
            atual= atual->prox;     
        }   

        novoElemento->prox = atual->prox;

        novoElemento->prev = atual;

        atual->prox = novoElemento;

        if(novoElemento->prox != NULL)
        {
            novoElemento->prox->prev = novoElemento;
        }

    }

}

void insertionSort(Nodo ** lista)
{
    /* Verificando se a lista está vazia  */
    if(*lista == NULL || (*lista)->prox == NULL)
    {
        printf("\nA lista esta vazia!");
        return;
    }

    /* Criando lista ordenada temporaria */
    Nodo * listaOrdenada = NULL;

    while(*lista != NULL)
    {
        Nodo * atual = *lista;

        (*lista) = (*lista)->prox;

        ordenarDescrescente(&listaOrdenada, atual);

    }

    *lista = listaOrdenada;

}