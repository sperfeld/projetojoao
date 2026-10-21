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
    getchar();
    fgets(novo->nomeItem, 50, stdin);
    novo->nomeItem[strcspn(novo->nomeItem, "\n")] = '\0';
    printf("Digite o peso do item: ");
    scanf("%d", &novo->peso);
    if (verificaEspaco(novo, mAtual)) {
        printf("Estourou o peso\n");
        free(novo);
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
        
        mAtual->inicio = novo; // <--- ADICIONE ESTA LINHA AQUI
        
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
        mAtual->fim = novo;
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
    int numeroItem = 1;
    Item* atual = cabeca;
    int pesoAtual = 0;
    pesoAtual = calculaPeso(*mAtual);
    printf("\nItens na mochila:\n\n");
    while (atual != NULL){
        printf("%d - %s - %d\n",numeroItem, atual->nomeItem, atual->peso);
        atual = atual->proximo;
        if(atual != NULL){
            
        }
        numeroItem++;
    }
    printf("\nPeso atual da mochila: %d", pesoAtual);
    printf("\n");
}

void excluirItem(Item** cabeca, Mochila* mAtual) {
    char nomeExcluir[50];
  
    if (*cabeca == NULL) {
        printf("\nA mochila ja esta vazia.\n");
        return;
    }

    listarItem(*cabeca, mAtual);
    int condicao = 0;
    Item* atual = *cabeca;

    printf("Qual item quer excluir: ");
    getchar();
    fgets(nomeExcluir, 50, stdin);
    nomeExcluir[strcspn(nomeExcluir, "\n")] = '\0';

    while (atual != NULL) {
        if (strcmp(atual->nomeItem, nomeExcluir) == 0) {
            printf("\nNome:%s/Peso: %d", atual->nomeItem, atual->peso);
            printf("\nDeseja excluir esse item?\n1 - Sim\n2 - Não");
             printf("\nDigite a opcao do menu: ");
            scanf("%d", &condicao);

            if (condicao == 1) {
                if (atual->anterior == NULL && atual->proximo == NULL) {
                    *cabeca = NULL;
                    mAtual->inicio = NULL;
                    mAtual->fim = NULL;
                } 
                else if (atual->anterior == NULL) {
                    atual->proximo->anterior = NULL;
                    *cabeca = atual->proximo;
                    mAtual->inicio = atual->proximo;
                } 
                else if (atual->proximo == NULL) {
                    atual->anterior->proximo = NULL;
                    mAtual->fim = atual->anterior;
                } 
                else {
                    atual->anterior->proximo = atual->proximo;
                    atual->proximo->anterior = atual->anterior;
                }

                free(atual);
                printf("\nItem excluido e peso removido.\n");
                return;
            }
        }
        atual = atual->proximo;
    }
    
    printf("\nNenhum item foi excluido.\n");
}
Mochila mochila;
Item* Objeto;

int indice = 0;


void main(){
    
    mochila.pesoMax = 100;
    mochila.pesoAtual = 0;
    mochila.inicio = NULL;
    mochila.fim = NULL;

    do{
        printf("\n0 - Fechar programa.");
        printf("\n1 - Adicionar Item.");
        printf("\n2 - Excluir Item.");
        printf("\n3 - Lista Item.");
        printf("\nDigite a opcao do menu: ");
        scanf("%d", &indice);
    
        switch(indice){
            case 0:
                printf("\nO programa foi encerrado.\n");
                
                break;
            case 1:
                criarItem(&Objeto, &mochila);
            
                 break;
            case 2:
                excluirItem(&Objeto, &mochila);
             
                 break;
            case 3:
                listarItem(Objeto, &mochila);
            
                 break;
            default:
                printf("\nOpção não encontrada\n");
                break;
        }
    }while(indice!=0);



}