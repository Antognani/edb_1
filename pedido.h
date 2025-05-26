#ifndef PEDIDO_H
#define PEDIDO_H

//struct pra um prato do cardápio
typedef struct Prato {
    int id;
    char nome[50];
} Prato;

//struct pra item individual do pedido, sendo que cada itemPedido é uma unidade de um prato no pedido
typedef struct ItemPedido {
    Prato pratoInfo; //informações do prato
    int quantidade; //quantidade do prato no pedido
    struct ItemPedido* proximoItemPedido; //ponteiro para o próximo item do pedido
} ItemPedido; //lista ligada de pratos no pedido

//struct para um pedido
typedef struct Pedido { //representa um pedido feito por um cliente
    int idPedido; //identificador único do pedido
    ItemPedido* itensPedido; //lista de pratos do pedido
} Pedido; //lista ligada de itensPedido

//nó da lista ligada para o salão
typedef struct NoLista { //representa um nó na lista ligada de pedidos pendentes do salão
    Pedido pedidoInfo; //informações do pedido
    struct NoLista* proximoNoLista; //ponteiro para o próximo nó na lista
} NoLista; //lista ligada de pedidos pendentes no salão

//nó da fila para a cozinha
typedef struct NoFila { //representa um nó na fila de pedidos da cozinha
    Pedido pedidoInfo; //informações do pedido
    struct NoFila* proximoNoFila; //ponteiro para o próximo nó na fila
} NoFila; //fila de pedidos da cozinha

//struct da fila pra cozinha
typedef struct Fila { //representa a fila de pedidos da cozinha
    NoFila* inicio; //ponteiro para o início da fila
    NoFila* fim; //ponteiro para o fim da fila
    int tamanho; //contador de itens na fila
} Fila;

#endif