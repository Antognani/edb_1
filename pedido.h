#ifndef PEDIDO_H
#define PEDIDO_H

//struct pra um prato do cardápio
typedef struct Prato {
    int id;
    char nome[50];
} Prato;

//struct pra item individual do pedido, sendo que cada itemPedido é uma unidade de um prato no pedido
typedef struct ItemPedido {
    Prato pratoInfo;
    struct ItemPedido* proximoItemPedido;
} ItemPedido;

//struct para um pedido
typedef struct Pedido {
    int idPedido;
    ItemPedido* itensPedido; //lista de pratos
} Pedido;

//nó da lista ligada para o salão
typedef struct NoLista {
    Pedido pedidoInfo;
    struct NoLista* proximoNoLista;
} NoLista;

//nó da fila para a cozinha
typedef struct NoFila {
    Pedido pedidoInfo;
    struct NoFila* proximoNoFila;
} NoFila;

//struct da fila pra cozinha
typedef struct Fila {
    NoFila* inicio;
    NoFila* fim;
    int tamanho; //contador de itens na fila
} Fila;

#endif