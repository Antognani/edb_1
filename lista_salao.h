#ifndef LISTA_SALAO_H
#define LISTA_SALAO_H

#include "pedido.h"

NoLista* adicionarPedidoSalao(NoLista* cabecaLista, Pedido novoPedido);
NoLista* removerPratoPedidoSalao(NoLista* cabecaLista, int idPedidoAlvo, int idPratoRemover);
void listarPedidosPendentesSalao(NoLista* cabecaLista);
void liberarListaPedidosSalao(NoLista* cabecaLista);
Pedido criarPedidoInterativo(Prato cardapio[], int numPratosCardapio, int* proximoIdPedido);

#endif