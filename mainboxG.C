#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILA 3
#define MAX_PILHA 3

typedef struct
{
    int tamanho;
    char status[15];
} Caixa;

typedef struct
{
    Caixa *caixas[MAX_PILHA];
    int topo;
} Pilha;

typedef struct
{
    Caixa *caixas[MAX_FILA];
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
    return (fila->fim + 1) % MAX_FILA == fila->inicio;
}

int estaVaziaFila(Fila *fila)
{
    return fila->inicio == -1;
}

int estaCheiaPilha(Pilha *pilha)
{
    return pilha->topo == MAX_PILHA - 1;
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
                fila->fim = (fila->fim + 1) % MAX_FILA;

                fila->caixas[fila->fim] = novaCaixa;

                strcpy(novaCaixa->status, "aguardando");
                printf("Caixa de tamanho %d enfileirada.\n", novaCaixa->tamanho);
                return;
            }
        }

        // Cadastrar caixa de tamanho 1 ou 2
        if (estaVaziaFila(fila))
        {
            fila->inicio = 0;
        }
        fila->fim = (fila->fim + 1) % MAX_FILA;

        fila->caixas[fila->fim] = novaCaixa;

        strcpy(novaCaixa->status, "aguardando");
        printf("Caixa de tamanho %d enfileirada.\n", novaCaixa->tamanho);
    }
    else
    {
        printf("Fila cheia. Nao e possivel enfileirar mais caixas.\n");
    }
}

void empilhar(Fila *fila, Pilha *pilha1, Pilha *pilha2)
{
    // Verificar se há caixas na fila para empilhar
    if (!estaVaziaFila(fila))
    {
        // Encontrar a maior caixa na fila
        int indiceMaiorCaixa = fila->inicio;
        int maiorTamanho = fila->caixas[indiceMaiorCaixa]->tamanho;

        for (int i = (fila->inicio + 1) % MAX_FILA; i != (fila->fim + 1) % MAX_FILA; i = (i + 1) % MAX_FILA)
        {
            if (fila->caixas[i]->tamanho > maiorTamanho)
            {
                maiorTamanho = fila->caixas[i]->tamanho;
                indiceMaiorCaixa = i;
            }
        }

        // Retirar a maior caixa da fila
        Caixa *caixaParaEmpilhar = fila->caixas[indiceMaiorCaixa];
        fila->caixas[indiceMaiorCaixa] = NULL; // Liberar o espaço na fila
        fila->inicio = (fila->inicio + 1) % MAX_FILA;

        // Empilhar a caixa na pilha correspondente
        if (maiorTamanho == 3)
        {
            if (!estaCheiaPilha(pilha1))
            {
                pilha1->topo++;
                pilha1->caixas[pilha1->topo] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 1.\n", caixaParaEmpilhar->tamanho);
            }
            else if (!estaCheiaPilha(pilha2))
            {
                pilha2->topo++;
                pilha2->caixas[pilha2->topo] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 2.\n", caixaParaEmpilhar->tamanho);
            }
            else
            {
                // Pilhas cheias, reenfileirar a caixa
                fila->fim = (fila->fim + 1) % MAX_FILA;
                fila->caixas[fila->fim] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "aguardando");
                printf("Caixa de tamanho %d reenfileirada.\n", caixaParaEmpilhar->tamanho);
            }
        }
        else
        {
            // Caixa de tamanho 1 ou 2
            if (!estaCheiaPilha(pilha1))
            {
                pilha1->topo++;
                pilha1->caixas[pilha1->topo] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 1.\n", caixaParaEmpilhar->tamanho);
            }
            else if (!estaCheiaPilha(pilha2))
            {
                pilha2->topo++;
                pilha2->caixas[pilha2->topo] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "EMPILHADA");
                printf("Caixa de tamanho %d empilhada na Pilha 2.\n", caixaParaEmpilhar->tamanho);
            }
            else
            {
                // Pilhas cheias, reenfileirar a caixa
                fila->fim = (fila->fim + 1) % MAX_FILA;
                fila->caixas[fila->fim] = caixaParaEmpilhar;
                strcpy(caixaParaEmpilhar->status, "aguardando");
                printf("Caixa de tamanho %d reenfileirada.\n", caixaParaEmpilhar->tamanho);
            }
        }
    }
    else
    {
        printf("Fila vazia. Nao ha caixas para empilhar.\n");
    }
}


void desempilhar(Pilha *pilha)
{
    if (!estaVaziaPilha(pilha))
    {
        Caixa *caixaDesempilhada = pilha->caixas[pilha->topo];
        pilha->topo--;

        printf("Caixa de tamanho %d desempilhada.\n", caixaDesempilhada->tamanho);

        free(caixaDesempilhada); // Liberar espaço de memória da caixa desempilhada
    }
    else
    {
        printf("Pilha vazia. Nao e possivel desempilhar.\n");
    }
}

void desempilharAmbasPilhas(Pilha *pilha1, Pilha *pilha2)
{
    printf("Desempilhando ambas as pilhas...\n");

    while (!estaVaziaPilha(pilha1))
    {
        desempilhar(pilha1);
    }

    while (!estaVaziaPilha(pilha2))
    {
        desempilhar(pilha2);
    }
}

void exibir(Fila *fila, Pilha *pilha1, Pilha *pilha2)
{
    // Exibir caixas enfileiradas
    printf(">>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>Caixas enfileiradas:\n");

    if (!estaVaziaFila(fila))
    {
        int i = fila->inicio;
        do
        {
            printf("caixa tamanho: %d %s\n", fila->caixas[i]->tamanho, fila->caixas[i]->status);
            i = (i + 1) % MAX_FILA;
        } while (i != (fila->fim + 1) % MAX_FILA);
    }
    printf("\n");

    // Exibir pilha1
    printf(">>>>Pilha 1:\n");
    for (int i = 0; i <= pilha1->topo; i++)
    {
        printf("caixa tamanho: %d %s\n", pilha1->caixas[i]->tamanho, pilha1->caixas[i]->status);
    }
    printf("\n");

    // Exibir pilha2
    printf(">>>>Pilha 2:\n");
    for (int i = 0; i <= pilha2->topo; i++)
    {
        printf("caixa tamanho: %d %s\n", pilha2->caixas[i]->tamanho, pilha2->caixas[i]->status);
    }
    printf("\n");
}

void exibirMenu()
{
    printf("\nMenu:\n");
    printf("1. Cadastar\n");
    printf("2. Empilhar\n");
    printf("3. Desempilhar\n");
    printf("4. Exibir\n");
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
        {
            enfileirar(&fila, &pilha1, &pilha2);
            break;
        }
        case 2:
            empilhar(&fila, &pilha1, &pilha2);
            break;
        case 3:
            desempilharAmbasPilhas(&pilha1, &pilha2);
            break;
        case 4:
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
