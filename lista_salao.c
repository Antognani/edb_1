#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_salao.h"

// função que adiciona um novo pedido a lista do salão
NoLista* adicionarPedidoSalao(NoLista* cabecaLista, Pedido novoPedido) {
    NoLista* novoNo = (NoLista*) malloc(sizeof(NoLista)); //aloca memória para novo nó
    if (!novoNo) { //verifica se há falha na alocação
        perror("Erro ao alocar memoria para novo pedido no salao"); //imprime erro caso alocação falhe
        return cabecaLista; //retorna lista sem modificação
    }
    novoNo -> pedidoInfo = novoPedido; // armazena os dados do pedido no novo nó
    novoNo -> proximoNoLista = cabecaLista; //insere o nó no início da lista
    printf("Pedido com ID %d adicionado a lista.\n", novoPedido.idPedido); //imprime que o pedido foi adicionado
    return novoNo; //retorna novo nó como cabeça da lista
}

//função que remove um prato específico de um pedido na lista do salão
NoLista* removerPratoPedidoSalao(NoLista* cabecaLista, int idPedidoAlvo, int idPratoRemover) {
    if (cabecaLista == NULL) { //verifica se a lista está vazia
        printf("Lista vazia. Não tem nada para modificar.\n"); //imprime que a lista está vazia
        return NULL; //retorna NULL, pois a lista está vazia
    }

    NoLista* atualNoPedido = cabecaLista; //ponteiro para percorrer os pedidos da lista
    NoLista* anteriorNoPedido = NULL; //ponteiro para nó anterior, usado para remover

    while (atualNoPedido != NULL && atualNoPedido->pedidoInfo.idPedido != idPedidoAlvo) { //while fica ativo enquanto houver pedidos na lista e id atual não for igual o id que está sendo procurado
        anteriorNoPedido = atualNoPedido; //atualiza nó anterior
        atualNoPedido = atualNoPedido->proximoNoLista; //passa para o próximo nó
    }

    if (atualNoPedido == NULL) { // verifica se não encontrou o pedido
        printf("Pedido com ID %d nao encontrado na lista.\n", idPedidoAlvo); //imprime que o pedido não está na lista
        return cabecaLista; //retorna lista sem modificações
    }

    ItemPedido* itemRemover = atualNoPedido->pedidoInfo.itensPedido; //ponteiro para pecorrer itens do pedido
    ItemPedido* anteriorItem = NULL; //ponteiro para item anterior, para remoção

    while (itemRemover != NULL && itemRemover->pratoInfo.id != idPratoRemover) { //while fica ativo enquanto houver itens no pedido e o id do pedido for diferente do id do item procurado
        anteriorItem = itemRemover; //atualiza item anterior
        itemRemover = itemRemover->proximoItemPedido; //passa para o próximo item
    }

    if (itemRemover == NULL) { //verifica se não encontrou o item
        printf("Prato com ID %d nao encontrado no pedido com ID %d.\n", idPratoRemover, idPedidoAlvo); //imprime que o item não está no pedido
        return cabecaLista; //retorna lista sem modificações
    }

    if (anteriorItem == NULL) { //verifica se o prato procurado é o primeiro da lista
        atualNoPedido->pedidoInfo.itensPedido = itemRemover->proximoItemPedido; //atualiza o inicio da lista de itens
    } else { 
        anteriorItem->proximoItemPedido = itemRemover->proximoItemPedido; //atualiza o ponteiro do item anterior 
    }
    printf("Prato '%s' (ID: %d) removido do pedido ID %d.\n", itemRemover->pratoInfo.nome, itemRemover->pratoInfo.id, idPedidoAlvo); //imprime que o prato foi removido
    free(itemRemover); //libera memória do prato removido

    if (atualNoPedido->pedidoInfo.itensPedido == NULL) { //verifica se o pedido ficou vazio após remoção
        printf("Pedido ID %d ficou vazio e foi removido do salao.\n", idPedidoAlvo); //imprime que o pedido está vazio
        if (anteriorNoPedido == NULL) { //verifica se o inicio da lista está vazio
            cabecaLista = atualNoPedido->proximoNoLista; //atualiza o inicio da lista para o próximo nó
        } else { 
            anteriorNoPedido->proximoNoLista = atualNoPedido->proximoNoLista; //atualiza o ponteiro do nó anterior
        }
        free(atualNoPedido); //libera memória do nó do pedido removido
    }
    return cabecaLista; //retorna lita atualizada
}

//função que lista todos os pedidos pendentes no salão
void listarPedidosPendentesSalao(NoLista* cabecaLista) {
    printf("\n--- Pedidos Pendentes no Salao ---\n");
    if (cabecaLista == NULL) { //verifica se há pedidos na lista
        printf("Nenhum pedido pendente no salao.\n"); //imprime que não há pedidos
        return; //encera a função
    }
    NoLista* atual = cabecaLista; //ponteiro para pecorrer a lista
    int contador = 1; //contador para exibir número do pedido
    while (atual != NULL) { //while fica ativo enquanto houver pedidos na lista
        printf("\nPedido #%d (ID Global: %d)\n", contador++, atual->pedidoInfo.idPedido); //imprime número e id do pedido
        ItemPedido* itemAtual = atual->pedidoInfo.itensPedido; //ponteiro para pecorrer itens do pedido
        if (itemAtual == NULL) { //verifica se o pedido está vazio
            printf("  (Este pedido esta vazio!)\n"); //imprime que pedido está vazio
        }
        while (itemAtual != NULL) { //while fica ativo enquanto houver itens no pedido
            printf("  - Prato: %s (ID: %d), Quantidade: %d\n", //imprime nome do prato, seu id e quantidade
                   itemAtual->pratoInfo.nome,
                   itemAtual->pratoInfo.id,
                   itemAtual->quantidade);
            itemAtual = itemAtual->proximoItemPedido; //passa para o próximo item
        }
        printf("----------------------------------");
        atual = atual->proximoNoLista; //avança para o próximo pedido
    }
}

//função para liberar memória da lista de pedidos do salão
void liberarListaPedidosSalao(NoLista* cabecaLista) {
    NoLista* atual = cabecaLista; //ponteiro para pecorrer lista
    while (atual != NULL) { //while fica ativo enquanto houver nós na lista
        NoLista* proximo = atual->proximoNoLista; //guarda próximo pedido antes de liberar o atual
        ItemPedido* itemAtual = atual->pedidoInfo.itensPedido; //ponteiro para liberar itens do pedido
        while (itemAtual != NULL) { //while fica ativo enquanto houver itens no pedido
            ItemPedido* proximoItem = itemAtual->proximoItemPedido; //guardar o próximo prato antes de liberar o atual
            free(itemAtual); //libera prato atual
            itemAtual = proximoItem; //passa pro próximo prato
        }
        free(atual); //libera pedido atual
        atual = proximo; //passa pro próximo pedido
    }
}


//função para criar pedidos
Pedido criarPedido(Prato cardapio[], int numPratosCardapio, int* proximoIdPedido) {
    Pedido novoPedido; //define variável para novo pedido
    novoPedido.idPedido = (*proximoIdPedido)++; //atribui ID único e incrementa contador global para não repetir IDs
    novoPedido.itensPedido = NULL; //inciializa a lista de itens vazia

    printf("\n--- Criando novo pedido (ID: %d) ---\n", novoPedido.idPedido); //imprime início de criação de pedido
    int idPratoEscolhido; //variável para id do prato
    int quantidadeEscolhida; //variável para quantidade de pratos

    do { //realiza implementação até que uma condição seja satisfeita
        printf("\nCardapio disponivel (para pedido %d):\n", novoPedido.idPedido); //imprime cabeçalho para escolha do pedido
        for (int i = 0; i < numPratosCardapio; i++) {
            printf("  %d. %s\n", cardapio[i].id, cardapio[i].nome); //imprime cardápio
        }
        printf("Digite o ID do prato a adicionar (ou 0 para finalizar este pedido): "); //imprime solicitação do ID do prato a adicionar ou que se encerre o pedido
        if (scanf("%d", &idPratoEscolhido) != 1) { //verifica entradainválida
             printf("Entrada invalida. Tente um numero.\n"); //imprime que entrada é inválida
             int c; while((c = getchar()) != '\n' && c != EOF); //limpa buffer do teclado
             continue; //repete a solicitação
        }
        if (idPratoEscolhido == 0) break; //caso a entrada seja 0, encerra a o pedido

        Prato* pratoSelecionado = NULL; //ponteiro para prato selecionado
        for (int i = 0; i < numPratosCardapio; i++) { //busca prato no cardápio
            if (cardapio[i].id == idPratoEscolhido) { //verifica se o id do prato é igual ao id do prato escolhido
                pratoSelecionado = &cardapio[i]; //define o prato escolhido
                break; //encerra caso tenha encontrado o prato
            }
        }

        if (pratoSelecionado) { //verifica se o prato foi selecionado
            printf("Digite a quantidade para '%s': ", pratoSelecionado->nome); //solicita a quantidade 
            if (scanf("%d", &quantidadeEscolhida) != 1 || quantidadeEscolhida <= 0) { //verifica quantidade
                printf("Quantidade invalida (deve ser > 0).\n"); //imprime que quantidade é inválida
                int c; while((c = getchar()) != '\n' && c != EOF); //limpa buffer do teclado
                continue; //repete a solicitação
            }

            ItemPedido* novoItem = (ItemPedido*) malloc(sizeof(ItemPedido)); //aloca memória para o novo item do prato
            if (!novoItem) { //verifica se a alocação falhou
                perror("Erro ao alocar item do pedido"); //imprime erro caso a alocação falhe
                continue; //tenta adicionar outro prato
            }
            novoItem->pratoInfo = *pratoSelecionado; //armazena informações do prato escolhido
            novoItem->quantidade = quantidadeEscolhida; //armazena a quantidade
            novoItem->proximoItemPedido = novoPedido.itensPedido; //insere item no início da lista
            novoPedido.itensPedido = novoItem; //
            printf("'%s' (x%d) adicionado ao pedido.\n", pratoSelecionado->nome, quantidadeEscolhida);
        } else { //se prato for inválido
            printf("ID de prato invalido.\n"); //imprime erro
        }
    } while (1); //condição de satisfação para o "do", repete até o usuário encerrar o pedido

    if (novoPedido.itensPedido == NULL) { //verifica se o pedido está vazio
        printf("Nenhum item adicionado. Pedido ID %d cancelado com scesso!\n", novoPedido.idPedido); //imprime que o pedido está vazio
        (*proximoIdPedido)--;  //reverto incremento do ID, pois o pedido não foi realizado
    } else {
        printf("Pedido ID %d finalizado.\n", novoPedido.idPedido); //informa finalização do pedido
    }
    return novoPedido; //retorna o pedido
}