/* 
    5. Considere uma lista simplesmente encadeada que armazene números em
    ordem crescente. Escreva uma função, em C, que receba esta lista, e remova o
    nó antecessor e o sucessor a um determinado nó contendo um elemento X
    (inteiro).
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo
{
    int info;
    struct Nodo * prox;
}Nodo;

void insert(Nodo ** lista, int info);
void listar(Nodo ** lista);
void ordernarLista(Nodo ** lista, Nodo * novoElemento);
void remover_Antecessor_Sucessor(Nodo ** lista, int info);

int main()
{
    int opcao, info, elemento;
    Nodo * lista = NULL;

    do
    {
        printf("\n1.Inserir elemento");
        printf("\n2.Listar");
        printf("\n3.Remover o sucessor e o antecessor de um elemento");
        printf("\n0.Sair");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                system("clear");
                printf("\nDigite o numero do elemento: ");
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
                system("clear");
                printf("\nDigite o elemento desejado: ");
                scanf("%d", &elemento);
                remover_Antecessor_Sucessor(&lista, elemento);
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

void insert(Nodo ** lista, int info)
{
    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo*) malloc(sizeof(Nodo));

    /* Verificando se há espaço na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria");
        return ;
    }

    /* Setando  novo elemento*/
    novoElemento->info = info;
    novoElemento->prox = NULL;

    /* Incluindo novo elemento na lista */
    ordernarLista(lista, novoElemento);
}

void listar(Nodo ** lista)
{
    system("clear");

    /* Verificando se a lista está vazia */
    if(*lista == NULL)
    {
        printf("\nA lista esta vazia!");
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

void ordernarLista(Nodo ** lista, Nodo * novoElemento)
{
    /* Se a lista estiver nula ou o novo elemento for menor do que o primeiro elemento da lista */
    if(*lista == NULL || (*lista)->info > novoElemento->info)
    {
        novoElemento->prox = *lista;

        *lista = novoElemento;
    }
    else
    {
        Nodo * atual = *lista;
        /* Vou iterar a lista até encontrar o último elemento ou um elemento maior do que o novo elemento */
        while(atual->prox != NULL && atual->prox->info < novoElemento->info)
        {
            atual = atual->prox;
        }
        /* Uma vez aqui, estou no final da lista ou antes de um elemento maior ao novo elemento */
        
        novoElemento->prox = atual->prox;

        atual->prox = novoElemento;
    }
}

void remover_Antecessor_Sucessor(Nodo ** lista, int info)
{
    /* Verificar a lista está vazia */
    if(*lista == NULL || (*lista)->prox == NULL)
    {
        printf("\nA lista esta vazia!");
        return;
    }

    /* Percorrendo a lista até encontrar o elemento informado */
    Nodo * atual = *lista;
    Nodo * anterior = NULL;
    Nodo * anterior_do_anterior = NULL;
    while(atual->prox != NULL && atual->info != info)
    {
        anterior_do_anterior = anterior;
        anterior = atual;
        atual = atual->prox;
    }

    /* Verificando se saiu do while por não existir o elemento desejado na lista */
    if(atual->info != info)
    {
        printf("\nO elemento nao existe!");
        return;
    }
    else
    {
        /* Verificando se o elemento desejado é o primeiro da fila */
        if(anterior == NULL)
        {
            /* Guardando o sucessor */
            Nodo * aux = atual->prox;

            /* Fazendo o atual apontar para o elemento seguinte ao sucessor */
            atual->prox = atual->prox->prox;

            /* Liberando sucessor */
            free(aux);
        } 
        else
        {
            /* Removendo o anterior */

            /* Verificando se o anterior_do_anterior é nulo */
            if(anterior_do_anterior == NULL)
            {
                *lista = anterior->prox;

                free(anterior);
            }
            else
            {
                /* Caso anterior_do_anterior não seja nulo */
                
                /* Fazendo com que o anterior do anterior aponte para o atual */
                anterior_do_anterior->prox = atual;

                /* Liberando o anterior ao atual */
                free(anterior);
            }

            /* Verificando se o sucessor não é nulo. Pois se for, não há o que remover */
            if(atual->prox != NULL)
            {
                /* Armazenando o sucessor */
                Nodo * aux = atual->prox;

                /* Fazendo com que o atual aponte pare o elemento seguinte ao sucessor */
                atual->prox = atual->prox->prox;

                /* Liberando o sucessor */
                free(aux);
            }
        }
    }
}