#include <stdio.h>
#include <stdlib.h>

/*
 Definindo struct node. Ela irá conter uma info 
 e um ponteiro para a próxima struct
 */
 
 typedef struct Node
 {
    int info;
    struct Node * prox;

 }Node;

 void push(int info, Node ** topo);
 int pop(Node ** topo);
void listar(Node ** topo);


 /* 
 Sobre ponteiro de ponteiros. O ponteiro é uma VARIÁVEL que armazena um endereço de memória.
 Quando criamos um ponteiro de um tipo qualquer, tipo um int, estamos armazenando o endereço
 de memória daquele inteiro. Daí, quando passamos esse ponteiro por parâmetro em uma função, 
 estamos criando uma nova variável local na função que irá receber aquele endereço, ir na 
 memória, acessar aquele endereço e manipular o conteúdo daquele endereço em específico. 
 Entretanto, não podemos alterar o endereço guardado pelo ponteiro. Isto é, não podemos 
 manipular o ponteiro, se o fizemos na função, quando retornarmos para o main, ele não irá ter
 sido modificado, pois são ponteiros distintos, apenas o conteúdo(endereço) foi pasado do main
 para a funçaõ em questão, houve a criação de um novo ponteiro do tipo int para poder armazenar
 o conteúdo do ponteiro inicial, que foi criado no main. É uma cópia, ou seja, o ponteiro está
 sendo passado por valor enquanto o inteiro está sendo passado por referência. A mesma lógica
 se aplica a todas as variáveis, desde que sejam variáveis, não importa se são ponteiros ou não,
 desde de que sejam variáveis essa será a lógica da passagem por parâmetro. Qunado estamos passando
 a variável em questão, estamos passando apenas uma cópia dessa variável, isto é, indo na memória, 
 criando uma variável com um endereço novo e transferindo o conteúdo da primeira variável para a 
 nova, isso chama-se passagem de parâmetro por valor. 
 
 Por outro lado, quando passamos o endereço de memória daquela variável, anida precisamos criar uma
 variável para armazenar esse endereço - que são os ponteiros - em ambas as funções, mas as modificações
 que realizamos são especificamente no endereço de memória armazenado, então, se utilizarmos o caso do 
 ponteiro de int. Fui na memória, criei um espaço para um inteiro e preenchi com um número qualquer. Depois
 criei outra variável em outro endereço e o preenchi com o endereço de memória da variável inteira. Quando 
 passei esse ponteiro criado para uma outra função, outro endereço de memória foi alocado e preenchido com 
 uma cópia do conteúdo do primeiro ponteiro. Veja que passei o ponteiro por valor, mas o inteiro foi por 
 referência - não criei uma cópia do inteiro. Portanto, quando for modificar o inteiro, estarei acessando
 seu endereço de memória e modificando-o. Entretanto, não consigo modificar o ponteiro, pois ele está no main,
 por exemplo, enquanto eu estou trabalhando em outra função, embora o conteúdo seja o mesmo, são ponteiros, isto
 é, variáveis distintas.
 
 Dito isto, como que modificamos o conteúdo de um ponteiro? Criando uma variável que guarde o endereço do ponteiro,
 para isso serve o ponteiro de ponteiro (dois asteriscos ** ). 
 
 Exemplo:
 int a;
 int b;
 int * ptrB;
 int * ptrA = &a;
 int ** ponteiroDePonteiro = &ptrA;
 
 Para manipular o ponteiro de ponteiro faço o seguinte:

 ponteiroDePonteiro = &ptrB //Após ter sido declarado, é claro.
 
 Na linha acima, modifiquei o endereço do ponteiro que o ponteiro de ponteiro armazena. Ou seja, modifiquei seu conteúdo,
 antes ele armazenava o endereço do ponteiro ptrA, agora ele armazena o endereço de memória do ponteiro ptrB.
 
 *ponteiroDePonteiro = &a
 
 Na linha acima, derreferenciei o ponteiro de ponteiro, acessei o endereço de memória do ponteiro ptrA e substitui o conteúdo dele.
 Antes o ponteiro ptrB era nulo, agora ele aponta para a variável a.
 
 **ponteiroDePonteiro = 10
 
 Na linha acima, eu derreferenciei o ponteiroDePonteiro, isto é, acessei o endereço de memória que ele apontava (que era ptrB), depois
 de entrar nesse endereço, eu acessei o endereço para onde o ponteito ptrB aponta (variável a), derreferenciei, isto é, acessei o endereço
 de memória de a e mudei seu conteúdo para 10. */

int main()
{
   Node * topo = NULL;
   int info = 0;


   int opcao;
   do
   {
      
      printf("\n\n1.Empilhar");
      printf("\n2.Desempilhar");
      printf("\n3.Listar elementos");
      printf("\n0.Sair do programa");
      printf("\nDigite sua opcao: ");
      scanf("%d", &opcao);
      
      switch(opcao)
      {
         case 1:
         {
            printf("\nDigite o valor do elemento: ");
            scanf("%d", &info);
            push(info,&topo);
            break;
         }
         case 2:
         {
            pop(&topo);
            break;
         }
         case 3:
         {
            listar(&topo);
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
 void push(int info, Node ** topo)
 {
   Node * novoElemento = (Node*)malloc(sizeof(Node));
   novoElemento->info = info;
   novoElemento->prox = NULL;
   
   /* Caso não haja memória livre */
   if(novoElemento == NULL)
   {
      printf("\nNao ha memoria livre para ser alocada");
      return;
   }
   else if(topo == NULL)
   {
      printf("\nAQUI");
      /* O ponteiro de ponteiro armazena o endereço de memória do novo elemento(que é um ponteiro) */
      *topo = novoElemento;
   }
   else
   {
      /* topo -> novoElemento1
         novoElemento2 -> *topo(novoElemento1)
         topo -> novoElemento2  */

         novoElemento->prox = *topo;
         *topo = novoElemento;
   }

   printf("\nElemento empilhado com sucesso!\nO valor do novo topo eh: %d", (*topo)->info);

 }

 int pop(Node ** topo)
 {    
      int info;
      Node * aux = NULL;

      if(*topo == NULL)
      {
         printf("\nA pilha esta vazia!");
         return -1;  
      }

      /*
      Estou acessando o ponteiro de ponteiro, derreferenciando ele, isto é, acessando o endereço de memória do ponteiro
      que ele armazena e armazenando esse endereço em uma variável auxiliar(que também é um ponteiro)
      Depois estou fazendo topo apontar para o próximo elemento da pilha e dando um free no antigo topo
      */
      if(*topo != NULL)
      {
         aux = *topo;

         info = (*topo)->info;

         *topo = aux->prox;

         free(aux);
      }

      /* DICA! O compilador dá prioridade ao ->, então se quiser derreferenciar o topo para poder acessar os atributos (info || prox) 
      coloque entre parênteses para o compilador dá prioridade para a operação de derreferenciar */

      printf("\nItem desempilhado com sucesso. O valor desempilhado foi: %d.", info);

      return info;
 }

 void listar(Node ** topo)
 {
   Node * aux = *topo;
   int count = 0;

   if(aux == NULL)
   {
      printf("\nA pilha esta vazia!");
      return;
   }

   while(aux != NULL)
   {
      printf("\nO item %d da pilha possui o valor: %d", count, aux->info);
      count++;
      aux = aux->prox;
   }
 }

 