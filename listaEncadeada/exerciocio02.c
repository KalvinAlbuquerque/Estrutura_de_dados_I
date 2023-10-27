#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo
{
    int info;
    struct Nodo * prox;
}Nodo;

void insert(Nodo ** lista, int info);
void listar(Nodo * proxElemento);
void limparTela();
Nodo * ordernarLista(Nodo * newNodo, Nodo ** novaLista);

int main()
{
    Nodo * lista = NULL;
    int opcao;
    int info;

    do
    {
        printf("\n1.Inserir elemento");
        printf("\n2.Listar");
        printf("\n0.Sair");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                limparTela();
                printf("\nDigite o numero: ");
                scanf("%d", &info);
                insert(&lista, info);
                break;
            }
            case 2:
            {
                limparTela();
                listar(lista);
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                printf("\nOpcao Invalida!");
                break;
            }
        }
    }while(opcao != 0);

    return 0;
}

void insert(Nodo ** lista, int info)
{
    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo *)malloc(sizeof(Nodo));

    /* Verificando se há espaço disponível na memória */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando novo elemento */
    novoElemento->info = info;
    novoElemento->prox = NULL;

    /* Adicionando novo elemento na fila */
    if(*lista == NULL)
    {
        /* Se a lista estiver vazia, ela vira o novo elemento */
        *lista = novoElemento;
    }
    else
    {
        /* Caso esteja preenchida, irei iterar até o último elemento e fazê-lo apontar para
        o novo elemento */

        Nodo * atual = *lista;
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = novoElemento;
    }
}

void listar(Nodo * proxElemento)
{
    if(proxElemento == NULL)
    {
        return;
    }

    printf("\n%d", proxElemento->info);
    listar(proxElemento->prox);
}

Nodo * ordernarLista(Nodo * newNodo, Nodo ** novaLista)
{
    Nodo * atual = *novaLista;

    /* Verificando se a nova lista está vazia, ou se o primeiro elemento da nova lista
    é maior que o novo elemento*/
    if(novaLista == NULL || (*novaLista)->info > newNodo->info)
    {
        newNodo->prox = novaLista;

        novaLista = newNodo;
    }
    else
    {
        /* Vou percorrer toda a lista e vou parar quando encontrar uma
        
         */
    }


    while(atual != NULL)
    {   
        Nodo * atualLista2 = listaOrdenada;

        while(atualLista2 != NULL && atual->info >= atualLista2->info)
        {
            anterior = atualLista2;
            atualLista2 = atualLista2->prox;
        }


        atualListaOrdenada->prox = atual;
        atualListaOrdenada = atualListaOrdenada->prox;
        atual = atual->prox;
    }

    *lista = listaOrdenada;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}