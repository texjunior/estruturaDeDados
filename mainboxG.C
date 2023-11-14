#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct
{
    int tamanho;
    char status[15];
} Caixa;

typedef struct
{
    Caixa *caixas[MAX];
    int topo;
} Pilha;

typedef struct
{
    Caixa *caixas[MAX];
    int inicio;
    int fim;
} Fila;

void inicializarPilha(Pilha *pilha)
{
    pilha->topo = -1;
}

void inicializarFila(Fila *fila)
{
    fila->inicio = -1;
    fila->fim = -1;
}

int estaCheiaFila(Fila *fila)
{
    return fila->fim == MAX - 1;
}

int estaVaziaFila(Fila *fila)
{
    return fila->inicio == -1;
}

int estaCheiaPilha(Pilha *pilha)
{
    return pilha->topo == MAX - 1;
}

int estaVaziaPilha(Pilha *pilha)
{
    return pilha->topo == -1;
}

void enfileirar(Fila *fila, Pilha *pilha1, Pilha *pilha2)
{
    if (!estaCheiaFila(fila))
    {
        int tamanho;
        printf("Informe o tamanho da caixa (1, 2 ou 3): ");
        scanf("%d", &tamanho);

        if (tamanho < 1 || tamanho > 3)
        {
            printf("Tamanho inválido. Informe um valor entre 1 e 3.\n");
            return;
        }

        Caixa *novaCaixa = (Caixa *)malloc(sizeof(Caixa));
        novaCaixa->tamanho = tamanho;

        if (tamanho == 3)
        {
            if (estaVaziaPilha(pilha1))
            {
                pilha1->topo++;
                pilha1->caixas[pilha1->topo] = novaCaixa;
                strcpy(novaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 1.\n", novaCaixa->tamanho);
                return;
            }
            else if (estaVaziaPilha(pilha2))
            {
                pilha2->topo++;
                pilha2->caixas[pilha2->topo] = novaCaixa;
                strcpy(novaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 2.\n", novaCaixa->tamanho);
                return;
            }
            else
            {
                // Não há pilha vazia, enfileirar a caixa de tamanho 3
                if (estaVaziaFila(fila))
                {
                    fila->inicio = 0;
                }
                fila->fim = (fila->fim + 1) % MAX;

                fila->caixas[fila->fim] = novaCaixa;

                strcpy(novaCaixa->status, "AGUARDANDO");
                printf("Caixa de tamanho %d enfileirada.\n", novaCaixa->tamanho);
                return;
            }
        }
        // Cadastrar caixa de tamanho 1 ou 2
        if (estaVaziaFila(fila))
        {
            fila->inicio = 0;
        }
        fila->fim = (fila->fim + 1) % MAX;

        fila->caixas[fila->fim] = novaCaixa;

        strcpy(novaCaixa->status, "AGUARDANDO");
        printf("Caixa de tamanho %d enfileirada.\n", novaCaixa->tamanho);
        novaCaixa = NULL;
    }

    else
    {
        printf("Fila cheia. Nao e possivel enfileirar mais caixas.\n");
    }
}

void empilhar(Fila *fila, Pilha *pilha1, Pilha *pilha2)
{
    if (pilha1->topo < MAX || pilha2->topo < MAX)
    {

        int i;
        for (i = 0; i < MAX; i++)
        {
            Caixa *proximaCaixa = fila->caixas[i];

            // Verificar se a pilha 1 esta cheia ou se a proxima caixa tem tamanho menor ou igual ao topo da pilha
            if (pilha1->topo < 0)
            {
                pilha1->topo++;
                pilha1->caixas[pilha1->topo] = proximaCaixa;
                strcpy(proximaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 1.\n", proximaCaixa->tamanho);
                free(fila->caixas[i]);
                fila->caixas[i] = NULL;
                fila->fim = fila->fim - 1;
            }
            else if (pilha2->topo < 0)
            {
                pilha2->topo++;
                pilha2->caixas[pilha2->topo] = proximaCaixa;
                strcpy(proximaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 2.\n", proximaCaixa->tamanho);
                free(fila->caixas[i]);
                fila->caixas[i] = NULL;
                fila->fim = fila->fim - 1;
            }
            else if (!estaCheiaPilha(pilha1) && proximaCaixa->tamanho <= pilha1->caixas[pilha1->topo]->tamanho)
            {
                pilha1->topo++;
                pilha1->caixas[pilha1->topo] = proximaCaixa;
                strcpy(proximaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 1.\n", proximaCaixa->tamanho);
                free(fila->caixas[i]);
                fila->caixas[i] = NULL;
                fila->fim = fila->fim - 1;
            }
            else if (!estaCheiaPilha(pilha2) && proximaCaixa->tamanho <= pilha2->caixas[pilha2->topo]->tamanho)
            {
                pilha2->topo++;
                pilha2->caixas[pilha2->topo] = proximaCaixa;
                strcpy(proximaCaixa->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 2.\n", proximaCaixa->tamanho);
                free(fila->caixas[i]);
                fila->caixas[i] = NULL;
                fila->fim = fila->fim - 1;
            }
        }
    }
    else
    {
        printf("nao foi possivel empilhar outra caixa.\n");
    }
}

void desempilhar(Pilha *pilha)
{
    while (pilha->topo > -1 && pilha->caixas[pilha->topo] != NULL)
    {
        printf("Caixa de tamanho %d desempilhada.\n", pilha->caixas[pilha->topo]->tamanho);
        pilha->caixas[pilha->topo] = NULL;
        free(pilha->caixas[pilha->topo]);
        pilha->topo--;
    }
    printf("Pilha vazia. Nao e possivel desempilhar caixas.\n");
}

void exibir(Fila *fila, Pilha *pilha1, Pilha *pilha2)
{
    // Exibir caixas enfileiradas
    printf(">>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>Caixas enfileiradas:\n");

    if (!estaVaziaFila(fila))
    {

        int i;
        for (i = 0; i <= fila->fim; i++)
        {
            if (fila->caixas[i] != NULL)
            {
                printf("caixa tamanho: %d %s\n", fila->caixas[i]->tamanho, fila->caixas[i]->status);
            }
        }
    }
    printf("\n");

    // Exibir pilha1
    printf(">>>>Pilha 1:\n");
    int i;
    for (i = 0; i <= pilha1->topo; i++)
    {
        printf("caixa tamanho: %d %s\n", pilha1->caixas[i]->tamanho, pilha1->caixas[i]->status);
    }
    printf("\n");

    // Exibir pilha2
    printf(">>>>Pilha 2:\n");

    for (i = 0; i <= pilha2->topo; i++)
    {
        printf("caixa tamanho: %d %s\n", pilha2->caixas[i]->tamanho, pilha2->caixas[i]->status);
    }
    printf("\n");
}

void exibirMenu()
{
    printf("\n>>>>>>Menu:\n");
    printf("1. Cadastar\n");
    printf("2. Empilhar\n");
    printf("3. Desempilhar Pilha 1\n");
    printf("4. Desempilhar Pilha 2\n");
    printf("5. Exibir\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Fila fila;
    Pilha pilha1, pilha2;
    inicializarFila(&fila);
    inicializarPilha(&pilha1);
    inicializarPilha(&pilha2);

    int escolha;
    do
    {
        exibirMenu();
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            enfileirar(&fila, &pilha1, &pilha2);
            break;
        case 2:
            empilhar(&fila, &pilha1, &pilha2);
            break;
        case 3:
            desempilhar(&pilha1);
            break;
        case 4:
            desempilhar(&pilha2);
            break;
        case 5:
            exibir(&fila, &pilha1, &pilha2);
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);
    return 0;
}
