#ifndef LISTA_SALAO_H
#define LISTA_SALAO_H

#include "pedido.h" //inclusão das estruturas do pedido e da lista

NoLista* adicionarPedidoSalao(NoLista* cabecaLista, Pedido novoPedido); //adiciona um novo pedido à lista de pedidos pendentes do salão
NoLista* removerPratoPedidoSalao(NoLista* cabecaLista, int idPedidoAlvo, int idPratoRemover); //remove um prato de um pedido específico na lista de pedidos pendentes do salão
void listarPedidosPendentesSalao(NoLista* cabecaLista); //lista os pedidos pendentes no salão
void liberarListaPedidosSalao(NoLista* cabecaLista); //libera a memória alocada para a lista de pedidos pendentes do salão
Pedido criarPedido(Prato cardapio[], int numPratosCardapio, int* proximoIdPedido); //cria um novo pedido a partir do cardápio disponível

#endif