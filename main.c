#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Item{
    int peso;
    char nomeItem[50];
    struct Item* proximo;
    struct Item* anterior;
} Item;

typedef struct Mochila{
    int pesoMax;
    int pesoAtual;
    Item* inicio;
    Item* fim;
} Mochila;
int calculaPeso(Mochila mAtual) {
    int pesoAtual = 0;
    Item* itemCheck = mAtual.inicio;
    while (itemCheck != NULL){
        pesoAtual += itemCheck->peso;
        itemCheck = itemCheck->proximo;
    }
    return pesoAtual;
}
int verificaEspaco(Item* novo, Mochila* mAtual) {
    int pesoAtual = 0;
    pesoAtual = calculaPeso(*mAtual);
    mAtual->pesoAtual = pesoAtual;
    if (mAtual->pesoMax >= (pesoAtual + novo->peso)) {

      return 0;
    } else {
        printf("Peso %d/%d \n", pesoAtual, mAtual->pesoMax);
        return 1;
    }

}

void criarItem(Item** cabeca, Mochila* mAtual){
    Item* novo = (Item*) malloc(sizeof(Item));

    printf("Digite o nome do item: ");
    scanf("%49s", novo->nomeItem);
    printf("Digite o peso do item: ");
    scanf("%d", &novo->peso);
    if (verificaEspaco(novo, mAtual)) {
        printf("Estourou o peso\n");
        return;
    };
    novo->proximo = NULL;
    novo->anterior = NULL;
    //se não exste um primeiro
    if(*cabeca == NULL){
        *cabeca = novo;
        mAtual->inicio = novo;
        printf("\nItem adicionado.\n");
        return;
    }
    //se é menor que o primeiro
    if(novo->peso < (*cabeca)->peso){
        novo->proximo = *cabeca;
        (*cabeca)->anterior= novo;
        *cabeca = novo;
        printf("\nItem adicionado.\n");
        return;
    }
    Item* atual = *cabeca;
    //rodar até achar um maior que ele, ou o ultimo
    while(novo->peso >= atual->peso && atual->proximo != NULL){
        atual = atual->proximo;
    }

    if(novo->peso >= atual->peso){
        atual->proximo = novo;
        novo->anterior = atual;
        printf("\nItem adicionado.\n");
        return;
    }
    novo->anterior = atual->anterior;
    novo->proximo = atual;
    atual->anterior->proximo = novo;
    atual->anterior = novo;
    printf("\nItem adicionado.\n");
    return;
}



void listarItem(Item* cabeca, Mochila* mAtual){
    Item* atual = cabeca;
    int pesoAtual = 0;
    pesoAtual = calculaPeso(*mAtual);
    while (atual != NULL){
        printf("%s: %d", atual->nomeItem, atual->peso);
        atual = atual->proximo;
        if(atual != NULL){
        printf(" <-> ");
        }
    }
    printf("\nPeso atual da mochila: %d", pesoAtual);
    printf("\n");
}

void excluirItem(Item* cabeca, Mochila* mAtual){
    char nomeExcluir[50];
    listarItem(cabeca, mAtual);
    int condicao = 0;
    Item* atual = cabeca;

    printf("Qual item quer excluir: ");
    scanf("%49s", nomeExcluir);
    int numero = 0;
    while (atual != NULL){
            numero++;
        if(strcmp(atual->nomeItem, nomeExcluir) == 0){
            printf("\nNome: %s  /Peso: %d", atual->nomeItem, atual->peso);
            printf("\nDeseja excluir esse item?");
            scanf("%d", &condicao);

            if(condicao == 1){
                printf("Teste");

                if(atual->anterior != NULL && atual->proximo != NULL){
                    atual->anterior->proximo = atual->proximo;
                    atual->proximo->anterior = atual->anterior;
                } else

                if(atual->anterior == NULL){
                    atual->proximo->anterior = NULL;
                    mAtual->inicio = atual->proximo;

                }else

                if(atual->proximo == NULL){
                    atual->anterior->proximo = NULL;
                    mAtual->fim = atual->anterior;
                }

                free(atual);
                printf("Teste3");
                printf("\nItem excluido.\n");
                return;
            }
        }
        atual = atual->proximo;
    }
    printf("\nNenhum item excluir\n");

    return;
}

Mochila mochila;
Item* Objeto;

int indice = 0;


void main(){
    if(indice == 0){
        mochila.pesoMax = 100;
        mochila.pesoAtual = 0;
        mochila.inicio = NULL;
        mochila.fim = NULL;
    }

    printf("\nAdicionar Item: 1");
    printf("\nExcluir Item: 2");
    printf("\nLista Item: 3");
    printf("\nSair: 0");
    printf("\nDigite a opcao do menu: ");
    scanf("%d", &indice);

    switch(indice){
        case 0:
            break;
        case 1:
            criarItem(&Objeto, &mochila);
            main();
        case 2:
            excluirItem(Objeto, &mochila);
            main();
        case 3:
            listarItem(Objeto, &mochila);
            main();
    }



}
