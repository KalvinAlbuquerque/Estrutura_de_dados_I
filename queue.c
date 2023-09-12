#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int info;
    struct Node * next;
}Node;

void push(int info, Node ** end, Node ** begin);
void listar(Node ** begin);
int pop(Node ** begin, Node ** end);
int isEmpty(Node ** end);


int main()
{
   Node * begin = NULL;
   Node * end = NULL;
   int info = 0;


   int opcao;
   do
   {
      
      printf("\n\n1.Push");
      printf("\n2.Pop");
      printf("\n3.Listar");
      printf("\n0.Sair do programa");
      printf("\nDigite sua opcao: ");
      scanf("%d", &opcao);
      
      switch(opcao)
      {
         case 1:
         {
            printf("\nDigite o valor do elemento: ");
            scanf("%d", &info);
            push(info,&end, &begin);
            break;
         }
         case 2:
         {
            if(isEmpty(&end) == 1)
            {
                pop(&begin, &end);
            }
            break;
         }
         case 3:
         {
            if(isEmpty(&end) == 1)
            {
                listar(&begin);
            }

            break;
         }
         case 0:
         {
            return 0;
         }
      }

   }while(opcao != 0);

   return 0;
}


void push(int info, Node ** end, Node ** begin)
{
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->info = info;
    newNode->next = NULL;

    if(newNode == NULL)
    {
        printf("\nMemoria insuficiente");
        return;
    }

    /* Se o começo da fila estiver nulo, quer dizer que a fila está vazia */
    if(*end == NULL)
    {
        *begin = *end = newNode;
    }
    else
    {
        (*end)->next = newNode;
        *end = newNode;
    }

    printf("\nElemento adicionado com sucesso!");
}

void listar(Node ** begin)
{
    Node * aux = *begin;
    int count = 0;

    while(aux != NULL)
    {
        printf("\nO elemento %d possui o valor: %d", count, aux->info);
        count++;
        aux = aux->next;
    }
}

int isEmpty(Node ** end)
{
    if(*end == NULL)
    {
        printf("\nA fila esta vazia!");
        return -1;
    }
    else
    {
        return 1;
    }
}

int pop(Node ** begin, Node ** end)
{

    if (*begin == NULL)
    {
        printf("\nA fila esta vazia!");
        return -1;
    }

        Node * aux = *begin;
        int info = (*begin)->info;

        *begin = (*begin)->next;
        free(aux);

    if(*begin != NULL)
    {

        printf("\nO elemento de valor %d foi removido com sucesso. O inicio da fila agora possui o valor %d:", info, (*begin)->info);
        
        return info;
    }
    else
    {
        printf("\nA fila foi completamante esvaziada");
        *end = NULL;
        return -1;
    }

}


