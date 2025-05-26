#ifndef LISTA_SALAO_H
#define LISTA_SALAO_H

#include "pedido.h"

NoLista* adicionar_pedido_salao(NoLista* cabecaLista, Pedido novoPedido);
NoLista* remover_prato_de_pedido_salao(NoLista* cabecaLista, int idPedidoAlvo, int idPratoRemover);
void listar_pedidos_pendentes_salao(NoLista* cabecaLista);
void liberar_lista_pedidos_salao(NoLista* cabecaLista);
Pedido criar_pedido_interativo(Prato cardapio[], int numPratosCardapio, int* proximoIdPedido);

#endif