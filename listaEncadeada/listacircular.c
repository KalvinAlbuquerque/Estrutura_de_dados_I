#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    char * info;
    struct Nodo * next;
    struct Nodo * prev;
}Nodo;

void insert(Nodo ** start, Nodo ** end, char * info, Nodo ** atual);
char * criarPalavra();
void listar(Nodo ** start, Nodo ** end, Nodo ** selecionado);
void printarMenu();
void editarPalavra(Nodo ** selecinado);
void removerPalavra(Nodo ** end, Nodo ** start, Nodo ** selecionado);

int main()
{
    Nodo * start = NULL;
    Nodo * end = NULL;
    Nodo * selecionado = NULL;
    char opcao;
    char * palavra = NULL;
    
    int loop = 1;
    while(loop == 1)
    {
        if(start == NULL)
        {
            system("clear");

            printf("\nNao ha elementos na lista!\n");

            palavra = criarPalavra();

            insert(&start, &end, palavra, NULL);

            selecionado = start;   
        }
        else
        {
            listar(&start, &end, &selecionado);
            printarMenu();
            scanf("%c", &opcao);

            switch(opcao)
            {
                case 'E':
                case 'e':
                {
                    editarPalavra(&selecionado);
                    break;
                }
                case 'd':
                case 'D':
                {
                    removerPalavra(&end, &start, &selecionado);
                    break;
                }
                case 's':
                case 'S':
                {   
                    //system("clear");
                    palavra = criarPalavra();
                    insert(&start, &end, palavra, &selecionado);
                    break;
                }
                case '<':
                {
                    selecionado = selecionado->prev;
                    break;
                }
                case '>':
                {
                    selecionado = selecionado->next;
                    break;
                }
                case 'x':
                case 'X':
                {
                    loop = 0;
                    break;  
                }
                default:
                {
                    printf("\nOpcao invalida!");
                    break;
                }
            }
            
        }
    }

    return 0;
}

void insert(Nodo ** start, Nodo ** end, char * info, Nodo ** atual)
{
    /* Criando novo elemento */
    Nodo * novoElemento = (Nodo*)malloc(sizeof(Nodo));

    /* Verificando se há memória disponível */
    if(novoElemento == NULL)
    {
        printf("\nNao ha espaco na memoria!");
        return;
    }

    /* Setando novo elemento */
    novoElemento->info = info;
    novoElemento->next = NULL;
    novoElemento->prev = NULL;

    /* Verificando se é o primeiro elemento da lista */
    if(*start == NULL)
    {
        *start = novoElemento;

        *end = novoElemento;

        (*end)->next = *start;
    }
    else
    {
        /* Caso não seja  */
        /* Verificando se o elemento selecionado é o último */
        
        novoElemento->next = (*atual)->next;

        (*atual)->next = novoElemento;

        novoElemento->prev = (*atual);

        novoElemento->next->prev = novoElemento; 
        
        if(*atual == *end)
        {
            *end = novoElemento;
        }

    }
}

char * criarPalavra()
{
    char array[100];

    printf("\nDigite a palavra: ");

    scanf("%s", array);

    char * palavra = (char *)malloc((strlen(array)) * sizeof(char));

    if (palavra == NULL) 
    {
        printf("\nErro na alocacao de memoria.");

        return NULL;
    }

    strcpy(palavra, array);

    return palavra;
}

void listar(Nodo ** start, Nodo ** end, Nodo ** selecionado)
{
    system("clear");

    /* Verificando se a lista está vazia */
    if(*start == NULL)
    {
        printf("\nNao ha palavras ainda!");
        return;
    }

    printf("\n\n\t");

    Nodo * atual = *start;
    /* Verificando se só há uma palavra na lista */
    if(*start == *end)
    {
        printf("->%s", (*start)->info);
    }
    else
    {
        while(atual->next != *start)
        {
            /* Verificando se é o selecionado */
            if(atual == *selecionado)
            {
                printf("->");
            }

            printf("%s\t", atual->info);
            
            atual = atual->next;
        }

        if(atual == *selecionado)
        {
            printf("->");
        }
        printf("%s\t", atual->info);
    }
}

void printarMenu()
{
    printf("\n");
    printf("\nE: Editar palavra atual");
    printf("\nD: Inserir (depois da palavra atual)");
    printf("\nS: Eliminar palavra atual");
    printf("\n<: Palavra anterior");
    printf("\n>: Palavra posterior");
    printf("\nX: Sair");
    printf("\nDigite sua opcao: ");   
}

void editarPalavra(Nodo ** selecinado)
{
    system("clear");
    printf("\nDigite a nova palavra: ");

    char array[100];

    scanf("%s", array);

    (*selecinado)->info = (char*)realloc((*selecinado)->info, strlen(array));

    strcpy((*selecinado)->info, array);
}

void removerPalavra(Nodo ** end, Nodo ** start, Nodo ** selecionado)
{

    Nodo * aux = *selecionado;
    /* Verificando se só há um elemento na lista */
    if(*selecionado == *start && *selecionado == *end)
    {
        free((*selecionado)->info);
        
        free((*selecionado));

        *start = NULL;

        *end  = NULL;
    }
    else if(*selecionado == *start)
    {
        /* Verificando se é o primeiro da lista */
        *start = (*start)->next;

        (*start)->prev = *end;

        (*end)->next = *start;

        (*selecionado) = *start;

        free(aux->info);
        free(aux);
    }
    else if(*selecionado == *end)
    {
        /* Se o selecionado for o último da fila */
        *end = (*end)->prev;

        (*end)->next = *start;

        (*start)->prev = *end;

        (*selecionado) = *end;

        free(aux->info);
        free(aux);
    }
    else
    {
        /* Se o selecionado estiver no meio entre duas palavras */

        (*selecionado)->prev->next = (*selecionado)->next;

        (*selecionado)->next->prev = (*selecionado)->prev;

        (*selecionado) = (*selecionado)->next;

        free(aux->info);

        free(aux);
    }
}