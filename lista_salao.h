#ifndef LISTA_SALAO_H
#define LISTA_SALAO_H

#include "pedido.h"

NoLista* adicionar_pedido_salao(NoLista* cabeca_lista, Pedido novo_pedido);
NoLista* remover_prato_de_pedido_salao(NoLista* cabeca_lista, int id_pedido_alvo, int id_prato_remover);
void listar_pedidos_pendentes_salao(NoLista* cabeca_lista);
void liberar_lista_pedidos_salao(NoLista* cabeca_lista);
Pedido criar_pedido_interativo(Prato cardapio[], int num_pratos_cardapio, int* proximo_id_pedido);

#endif