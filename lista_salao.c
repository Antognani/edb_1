#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_salao.h"

NoLista* adicionar_pedido_salao(NoLista* cabecaLista, Pedido novoPedido) {
    NoLista* novoNo = (NoLista*) malloc(sizeof(NoLista));
    if (!novoNo) {
        perror("Erro ao alocar memoria para novo pedido no salao");
        return cabecaLista;
    }
    novoNo -> pedidoData = novoPedido;
    novoNo -> proximoNoLista = cabecaLista;
    printf("Pedido ID %d adicionado ao salao.\n", novoPedido.idPedido);
    return novoNo;
}

NoLista* remover_prato_de_pedido_salao(NoLista* cabecaLista, int idPedidoAlvo, int idPratoRemover) {
    if (cabecaLista == NULL) {
        printf("Salao vazio. Nada para modificar.\n");
        return NULL;
    }

    NoLista* atualPedido = cabecaLista;
    NoLista* anteriorPedido = NULL;

    while (atualPedido != NULL && atualPedido->pedidoData.idPedido != idPedidoAlvo) {
        anteriorPedido = atualPedido;
        atualPedido = atualPedido->proximoLista;
    }

    if (atualPedido == NULL) {
        printf("Pedido com ID %d nao encontrado no salao.\n", idPedidoAlvo);
        return cabecaLista;
    }

    ItemPedido* itemRemover = atualPedido->pedidoData.itensPedido;
    ItemPedido* anteriorItem = NULL;

    while (itemRemover != NULL && itemRemover->pratoInfo.id != idPratoRemover) {
        anteriorItem = itemRemover;
        itemRemover = itemRemover->proximoItemPedido;
    }

    if (itemRemover == NULL) {
        printf("Prato com ID %d nao encontrado no Pedido ID %d.\n", idPratoRemover, idPedidoAlvo);
        return cabecaLista;
    }

    if (anteriorItem == NULL) { 
        atualPedido->pedidoData.itensPedido = itemRemover->proximoItemPedido;
    } else { 
        anteriorItem->proximoItempedido = itemRemover->proximoItemPedido;
    }
    printf("Prato '%s' (ID: %d) removido do Pedido ID %d.\n", itemRemover->pratoInfo.nome, itemRemover->pratoInfo.id, idPedidoAlvo);
    free(itemRemover); 

    if (atualPedido->pedidoData.itensPedido == NULL) {
        printf("Pedido ID %d ficou vazio e foi removido do salao.\n", idPedidoAlvo);
        if (anteriorPedido == NULL) { 
            cabecaLista = atualPedido->proximoLista;
        } else { 
            anteriorPedido->proximoLista = atualPedido->proximoLista;
        }
        free(atualPedido); 
    }
    return cabecaLista;
}

void listarPedidosPendentesSalao(NoLista* cabecaLista) {
    printf("\n--- Pedidos Pendentes no Salao ---\n");
    if (cabecaLista == NULL) {
        printf("Nenhum pedido pendente no salao.\n");
        return;
    }
    NoLista* atual = cabecaLista;
    int contador = 1;
    while (atual != NULL) {
        printf("\nPedido #%d (ID Global: %d)\n", contador++, atual->pedidoData.idPedido);
        ItemPedido* itemAtual = atual->pedidoData.itensPedido;
        if (itemAtual == NULL) {
            printf("  (Este pedido esta vazio!)\n");
        }
        while (itemAtual != NULL) {
            printf("  - Prato: %s (ID: %d), Quantidade: %d\n",
                   itemAtual->pratoInfo.nome,
                   itemAtual->pratoInfo.id,
                   itemAtual->quantidade);
            itemAtual = itemAtual->proximoItemPedido;
        }
        printf("----------------------------------");
        atual = atual->proximoLista;
    }
}

void liberar_lista_pedidos_salao(NoLista* cabecaLista) {
    NoLista* atual = cabecaLista;
    while (atual != NULL) {
        NoLista* proximo = atual->proximoLista;
        ItemPedido* itemAtual = atual->pedidoData.itensPedido;
        while (itemAtual != NULL) {
            ItemPedido* proximoItem = itemAtual->proximoItemPedido;
            free(itemAtual);
            itemAtual = proximoItem;
        }
        free(atual);
        atual = proximo;
    }
}

Pedido criar_pedido_interativo(Prato cardapio[], int numPratosCardapio, int* proximoIdPedido) {
    Pedido novoPedido;
    novoPedido.idPedido = (*proximoIdPedido)++;
    novoPedido.itensPedido = NULL; 

    printf("\n--- Criando Novo Pedido (ID Global: %d) ---\n", novoPedido.idPedido);
    int idPratoEscolhido;
    int quantidadeEscolhida;

    do {
        printf("\nCardapio Disponivel (para Pedido %d):\n", novoPedido.idPedido);
        for (int i = 0; i < numPratosCardapio; i++) {
            printf("  %d. %s\n", cardapio[i].id, cardapio[i].nome);
        }
        printf("Digite o ID do prato a adicionar (ou 0 para finalizar este pedido): ");
        if (scanf("%d", &idPratoEscolhido) != 1) {
             printf("Entrada invalida. Tente um numero.\n");
             int c; while((c = getchar()) != '\n' && c != EOF); 
             continue;
        }
        if (idPratoEscolhido == 0) break; 

        Prato* pratoSelecionado = NULL;
        for (int i = 0; i < numPratosCardapio; i++) {
            if (cardapio[i].id == idPratoEscolhido) {
                pratoSelecionado = &cardapio[i];
                break;
            }
        }

        if (pratoSelecionado) {
            printf("Digite a quantidade para '%s': ", pratoSelecionado->nome);
            if (scanf("%d", &quantidadeEscolhida) != 1 || quantidadeEscolhida <= 0) {
                printf("Quantidade invalida (deve ser > 0).\n");
                int c; while((c = getchar()) != '\n' && c != EOF); 
                continue;
            }

            ItemPedido* novoItem = (ItemPedido*) malloc(sizeof(ItemPedido));
            if (!novoItem) {
                perror("Erro ao alocar item do pedido");
                continue; 
            }
            novoItem->pratoInfo = *pratoSelecionado; 
            novoItem->quantidade = quantidadeEscolhida;
            novoItem->proximoItemPedido = novoPedido.itensPedido; 
            novoPedido.itensPedido = novoItem;
            printf("'%s' (x%d) adicionado ao pedido.\n", pratoSelecionado->nome, quantidadeEscolhida);
        } else {
            printf("ID de prato invalido.\n");
        }
    } while (1);

    if (novoPedido.itensPedido == NULL) {
        printf("Nenhum item adicionado. Pedido ID %d efetivamente cancelado.\n", novoPedido.idPedido);
        (*proximoIdPedido)--; 
    } else {
        printf("Pedido ID %d finalizado.\n", novoPedido.idPedido);
    }
    return novoPedido;
}