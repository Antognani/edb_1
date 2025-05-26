#ifndef FILA_COZINHA_H
#define FILA_COZINHA_H

#include "pedido.h" //inclusão das estruturas do pedido e da fila

Fila* criarFilaCozinha();  //cria a fila de pedidos da cozinha
void enfileirarPedidoCozinha(Fila* q, Pedido p); //adiciona um pedido à fila de pedidos da cozinha
Pedido* desenfileirarPedidoCozinha(Fila* q); //remove o pedido do início da fila de pedidos da cozinha
void listarPedidosProcessamentoCozinha(Fila* q); //lista os pedidos que estão em processamento na cozinha
int filaCozinhaVazia(Fila* q); //verifica se a fila de pedidos da cozinha está vazia
void liberarFilaCozinha(Fila* q); //libera a memória alocada para a fila de pedidos da cozinha

#endif