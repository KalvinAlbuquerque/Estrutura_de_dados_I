#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#include "stack.c"


#define TAM 100

void empilharOperaçao(Node ** stack1, Node ** stack2, char * operacao);
void printarOperacao(Node ** stack1, Node ** stack2);

int main()
{   
    Node * stack1 = NULL;
    Node * stack2 = NULL;
    char operacao[TAM];
    
    /* Solicitando que o usuário digite a operação */
    printf("\nDigite a operacao: ");
    fgets(operacao, TAM, stdin);
    
    /* Empilhando a operação */
    empilharOperaçao(&stack1, &stack2, operacao);

    listar(&stack1);
    listar(&stack2);

    printarOperacao(&stack1, &stack2);

    return 0;
}

void empilharOperaçao(Node ** stack1, Node ** stack2, char * operacao)
{
    for(int i = 0 ; i < TAM ; i++)
    {
        if(operacao[i] == '\0')
        {
            return;
        }
        else
        {
            if((operacao[i] == '*') || (operacao[i] == '/') || (operacao[i] == '(')  || (operacao[i] == ')') )
            {
                push(operacao[i], stack2);
            }
            else
            {
                push(operacao[i], stack1);
            }            
        }
    }

}

void printarOperacao(Node ** stack1, Node ** stack2)
{
    Node * atualStack1 = *stack1;
    Node * atualStack2 = *stack2;

    /* Primeiro caso: a pilha 1 não está vazia(não nula) e os dois primeiros elementos são dígitos, logo quer dizer que houve uma operação de maior precedência */
    if(atualStack1 == NULL)
    {
        printf("\nNao ha nada na pilha");
        return;
    }
    else
    {
        atualStack1 = atualStack1->prox;
        printf("\n");
        while(atualStack1 != NULL)
        {
            /* Se forem dois dígitos seguidos na pilha um, quer dizer que há um operador de maior precedência na pilha dois */
            if((atualStack1->prox != NULL) && isdigit(atualStack1->info) && isdigit(atualStack1->prox->info))
            {
                printf("%c %c",atualStack1->info, atualStack2->info);
                
                atualStack1 = atualStack1->prox;

                printf("%c", atualStack1->info);
            }
            else
            {
                /* Caso seja um dígito seguido de operando, basta printá-los */
                printf("%c", atualStack1->info);

            }
            atualStack1 = atualStack1->prox;
        }
    }
}   

