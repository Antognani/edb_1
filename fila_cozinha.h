#ifndef FILA_COZINHA_H
#define FILA_COZINHA_H

#include "pedido.h"

Fila* criarFilaCozinha();
void enfileirarPedidoCozinha(Fila* q, Pedido p);
Pedido* desenfileirarPedidoCozinha(Fila* q);
void listarPedidosProcessamentoCozinha(Fila* q);
int filaCozinhaVazia(Fila* q);
void liberarFilaCozinha(Fila* q);

#endif