#include "exercicio01.c"

void limparTela();

int main()
{

    int opcao;
    int info;
    Nodo * lista = NULL;

    do
    {
        printf("\n1.Inserir elemento");
        printf("\n2.Remover elemento");
        printf("\n3.Listar elementos");
        printf("\n4.Gerar Nova lista com elementos impares e primos");
        printf("\n0.Sair");
        printf("\n\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {
                limparTela();
                printf("\n\nDigite a info do elemento: ");
                scanf("%d", &info);
                inserirElemento(&lista, info);
                break;
            }
            case 2:
            {
                limparTela();
                removerElemento(&lista);
                break;
            }
            case 3:
            {
                limparTela();
                listarElementos(&lista);
                break;
            }
            case 4:
            {
                limparTela();
                gerarNovaListaImparPrimos(&lista);
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                printf("\n\nOpcao invalida!");
                break;
            }
        }

    }while(opcao != 0);

    return 0;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}