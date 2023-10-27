#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo2
{
    int info;
    struct Nodo2 * prox;
    struct Nodo2* ant;
}Nodo2;


void listar(Nodo2 ** inicio);
Nodo2 * identificarSequencia(Nodo2 ** inicio);
void insertionSort(Nodo2 ** inicio);
void ordernarCrescente(Nodo2 ** listaOrdenada, Nodo2 * novoElemento);
void insert(Nodo2 ** inicio, int info);

int main()
{
    int opcao, info;
    Nodo2 * lista = NULL;

    do
    {
        printf("\n1.Insert");
        printf("\n2.Listar");
        printf("\n3.Ordernar Lista");
        printf("\n4.Identificar sequencia");
        printf("\n0.Sair");
        printf("\nDigite sua opcao: ");
        scanf("%d",&opcao);

        switch(opcao)
        {
            case 1:
            {
                system("clear");
                printf("\nDigite o valor: ");
                scanf("%d", &info);
                insert(&lista, info);
                break;
            }
            case 2:
            {
                listar(&lista);
                break;
            }
            case 3:
            {
                insertionSort(&lista);
                break;
            }
            case 4:
            {
                Nodo2 * aux = identificarSequencia(&lista);
                printf("\nElemento anterior: %d", aux->ant->info);
                printf("\nComeço da sequencia: %d", aux->info);
                printf("\nElemento posterior: %d", aux->prox->info);
                getchar();
                getchar();
                break;
            }
            case 0:
            {
                break;
            }
            default:
            {
                printf("\nOpcao invalida!!");
                break;
            }
        }
    }while(opcao != 0);
    return 0;
}


void insertionSort(Nodo2 ** inicio)
{
    /* Verificar se a lista está vazia */
    if(*inicio == NULL || (*inicio)->prox == NULL)
    {
        printf("\nA lista esta vazia!");
        return;
    }

    Nodo2* sequencia =identificarSequencia(inicio);
    if(sequencia != NULL)
    {
        int soma = sequencia->info;

        Nodo2* next = sequencia->prox;

        while(next != NULL && next->info == sequencia->info) 
        {
            soma += next->info;

            Nodo2* temp = next;

            next = next->prox;

            free(temp);
        }

        sequencia->info = soma;

        sequencia->prox = next;

        if(next != NULL) 
        {
            next->ant = sequencia;
        }

    }
    
    Nodo2 * listaOrdenada = NULL;
    while(*inicio != NULL)
    {
        Nodo2 * atual = *inicio;

        *inicio = (*inicio)->prox;

        ordernarCrescente(&listaOrdenada, atual);
    }

    *inicio = listaOrdenada;
}


Nodo2 * identificarSequencia(Nodo2 ** inicio)
{
    Nodo2 * atual = *inicio;
    
    /* Verificando se a lista está vazia */
    if(*inicio == NULL || (*inicio)->prox == NULL)
    {
        printf("\nA lista esta vazia!");
        return NULL;
    }

    while(atual->prox != NULL)
    {
        if(atual->info == atual->prox->info)
        {
            break;
        }

        atual = atual->prox;
    }

    return atual;
}


void listar(Nodo2 ** inicio)
{
    /* Verificando se a lista está vazia */
    system("clear");
    if(*inicio == NULL)
    {
        printf("\nA lista esta vazia!");
        return;
    }

    printf("\n");

    Nodo2 * atual = *inicio;
    while(atual != NULL)
    {
        printf("\n%d", atual->info);
        atual = atual->prox;
    }

    printf("\n");
}

void ordernarCrescente(Nodo2 ** listaOrdenada, Nodo2 * novoElemento)
{

    /* Caso a lista esteja vazia ou o novo elemento for menor que o primeiro elemento da lista */
    if(*listaOrdenada == NULL)
    {
        *listaOrdenada = novoElemento;
        novoElemento->ant = NULL;
        novoElemento->prox = NULL;
    }
    else if((*listaOrdenada)->info > novoElemento->info)
    {
        novoElemento->prox = *listaOrdenada;

        novoElemento->ant = NULL;

        (*listaOrdenada)->ant = novoElemento;

        *listaOrdenada = novoElemento;
    }
    else
    {
        Nodo2 * atual = *listaOrdenada;
        while(atual->prox != NULL && novoElemento->info > atual->prox->info )
        {
            atual= atual->prox;     
        }   

        novoElemento->prox = atual->prox;

        novoElemento->ant = atual;

        atual->prox = novoElemento;

        if(novoElemento->prox != NULL)
        {
            novoElemento->prox->ant = novoElemento;
        }

    }
}

void insert(Nodo2 ** inicio, int info)
{
    Nodo2 * novoElemento = (Nodo2*)malloc(sizeof(Nodo2));

    novoElemento->info = info;

    novoElemento->info = info;

    novoElemento->prox = NULL;

    if(*inicio == NULL)
    {
        *inicio = novoElemento;
    }
    else
    {
        Nodo2 * atual = *inicio;
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = novoElemento;

        novoElemento->ant = atual;
    }
}

