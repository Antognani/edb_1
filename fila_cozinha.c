#include <stdio.h>
#include <stdlib.h>
#include "fila_cozinha.h"

Fila* criarFilaCozinha() {
    Fila* q = (Fila*) malloc(sizeof(Fila));
    if(!q) {
        perror("Erro ao alocar Fila Cozinha");
        exit(EXIT_FAILURE);
    }
    q->inicio = NULL;
    q->fim = NULL;
    q->tamanho = 0;
    return q;
}

void enfileirarPedidoCozinha(Fila* q, Pedido p) {
    NoFila* novoNo = (NoFila*) malloc(sizeof(NoFila));
    if(!novoNo) {
        perror("Erro ao alocar NoFila");
        exit(EXIT_FAILURE);
    }
    novoNo->pedidoData = p;
    novoNo->proximoNoFila = NULL;

    if (filaCozinhaVazia(q)) {
        q->inicio = novoNo;
        q->fim = novoNo;
    }

    else{
        q->fim->proximoNoFila = novoNo;
        q->fim = novoNo;
    }
    q->tamanho++;
}

Pedido* desenfileirarPedidoCozinha(Fila* q) {
    if(filaCozinhaVazia(q)) {
        return NULL;
    }
    NoFila* noRemovido = q->inicio;

    Pedido* pedidoProcessadoCopia = (Pedido*) malloc(sizeof(Pedido));
    if(!pedidoProcessadoCopia) {
        perror("Erro ao alocar copia Pedido processado");
        exit(EXIT_FAILURE);
    }
    *pedidoProcessadoCopia = noRemovido->pedidoData;

    q->inicio = q->inicio->proximoNoFila;
    if(q->inicio == NULL) {
        q->fim = NULL;
    }
    free(noRemovido);
    q->tamanho--;

    return pedidoProcessadoCopia;
}

void listarPedidosProcessamentoCozinha(Fila* q) {
    printf("\n--- Pedidos em Processamento na Cozinha ---\n");
    if(filaCozinhaVazia(q)) {
        printf("Nenhum pedido na fila da cozinha.\n");
        return;
    }
    NoFila* atual = q->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("\n%dº da Fila - Pedido ID: %d\n", pos++, atual->pedidoData.idPedido);
        ItemPedido* itemAtual = atual->pedidoData.itensPedido;
        if (itemAtual == NULL) {
            printf("Pedido vazio.");
        }
        while (itemAtual != NULL) {
            printf(" - Prato: %s (ID: %d), Quantidade: %d\n", 
                itemAtual->pratoInfo.nome,
                itemAtual->pratoInfo.id,
                itemAtual->quantidade);
            itemAtual = itemAtual->proximoItemPedido;
        }
        printf("----------------------------------");
        atual = atual->proximoNoFila
    }
}

int filaCozinhaVazia(Fila* q) {
    return (q->inicio == NULL);
}

void liberarFilaCozinha(Fila* q) {
    if (!q) return;
    NoFila* atual = q->inicio;
    while (atual != NULL) {
        NoFila* proximo = atual->proximoNoFila;
        ItemPedido* itemAtual = atual->pedidoData.itensPedido;
        while (itemAtual != NULL) {
            ItemPedido* proximoItem = itemAtual->proximoItemPedido;
            free(itemAtual);
            itemAtual = proximoItem;
        }
        free(atual);
        atual = proximo;
    }
    free(q);
}