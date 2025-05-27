#include <stdio.h>
#include <stdlib.h>
#include "fila_cozinha.h"

//função que cria fila da cozinha, onde os pedidos serão enfileirados na ordem que chegam no salão
Fila* criarFilaCozinha() { 
    Fila* q = (Fila*) malloc(sizeof(Fila)); //aloca memória para a fila
    if(!q) { //verifica se houve erro na alocação
        perror("Erro ao alocar fila cozinha"); //imprime erro caso falhe ao alocar memória
        exit(EXIT_FAILURE); //encerra o programa
    }
    q->inicio = NULL; //incializa inicio como NULL, já que a fila está vazia
    q->fim = NULL; //inicializa fim como NULL, também indicando que estar vazia
    q->tamanho = 0; //define tamanho como zero, indicando que a fila começça com nenhum pedido
    return q; //retorna ponteiro para a fila criada
}

//função que adciona um pedido vindo do salão na fila da cozinha para preparo, esse pedido vai para o final da lista de processamento
void enfileirarPedidoCozinha(Fila* q, Pedido p) {
    NoFila* novoNo = (NoFila*) malloc(sizeof(NoFila)); // cria novo nó da fila
    if(!novoNo) { //verifica se foi alocado
        perror("Erro ao alocar NoFila"); //imprime erro se falhar na alocação
        exit(EXIT_FAILURE); //encera o programa
    }
    novoNo->pedidoInfo = p; //armazena o pedido no novo nó
    novoNo->proximoNoFila = NULL; //como é último, não aponta pra ninguém

    if (filaCozinhaVazia(q)) { //verifica se a fila tá vazia
        q->inicio = novoNo; //atribui o pedido como o primeiro da fila
        q->fim = novoNo; //atribui o pedido como último, porque ele é o único pedido
    }

    else{
        q->fim->proximoNoFila = novoNo; //atribui ao próximo nó depois do fim o novo pedido
        q->fim = novoNo; //atualiza o fim para a posição que foi atribuida o novo pedido
    }
    q->tamanho++; //atualiza o número total de pedidos na fila
}

//função para remover o primeiro pedido da fila
Pedido* desenfileirarPedidoCozinha(Fila* q) {
    if(filaCozinhaVazia(q)) { //verifica se a fila está vazia
        return NULL; //retorna NULL, pois não havia na para remover
    }
    NoFila* noRemovido = q->inicio; //armazena o nó que está no início

    Pedido* pedidoProcessadoCopia = (Pedido*) malloc(sizeof(Pedido)); //aloca a memória do copiar os dados do pedido
    if(!pedidoProcessadoCopia) { //verifica se alocação ocorreu
        perror("Erro ao alocar copia Pedido processado"); //imprime erro caso alocação falhe
        exit(EXIT_FAILURE); //encerra o programa
    }
    *pedidoProcessadoCopia = noRemovido->pedidoInfo; //copia as informações do pedido, a fim de utilizar mesmo ao liberar a memória do nó

    q->inicio = q->inicio->proximoNoFila; //move o início para o próximo nó
    if(q->inicio == NULL) { //verifica se o novo inicio está vazio, o que significa que fila está vazia
        q->fim = NULL; //se incio estiver vazio, fim também está vazio
    }
    free(noRemovido); //libera memória do nó removido
    q->tamanho--; //atualiza o número total de pedidos na fila

    return pedidoProcessadoCopia; //retorna o pedido que foi removido
}

//função que lista os pedidos que estão em processamento na fila da cozinha, ou seja, estão esperando para serem preparados
void listarPedidosProcessamentoCozinha(Fila* q) {
    printf("\n--- Pedidos em processamento na cozinha ---\n"); 
    if(filaCozinhaVazia(q)) { //verifica se a fila está vazia
        printf("Nenhum pedido na fila da cozinha.\n"); //printa que a fila está vazia
        return; //encerra a função
    }
    NoFila* atual = q->inicio; //atual aponta para o início, onde vai pecorrer pela fila
    int pos = 1; //contador para mostrar posição da fila
    while (atual != NULL) { //while fica ativo enquanto houver pedidos na fila
        printf("\n%dº da Fila - Pedido ID: %d\n", pos++, atual->pedidoInfo.idPedido); //imprime posição do pedido na fila e seu ID
        ItemPedido* itemAtual = atual->pedidoInfo.itensPedido; //ponteiro que pecorre a lista de pratos do pedido
        if (itemAtual == NULL) { //verifica se há pratos no pedido
            printf("Pedido vazio."); //imprime que o pedido está vazio
        }
        while (itemAtual != NULL) { //while fica ativo enquanto houver pratos no pedido
            printf(" - Prato: %s (ID: %d)\n",  //imprime nome do prato e seu ID
                itemAtual->pratoInfo.nome,
                itemAtual->pratoInfo.id
            );
            itemAtual = itemAtual->proximoItemPedido; //percorre para o próximo prato do pedido até o final
        }
        printf("----------------------------------");
        atual = atual->proximoNoFila; //move o ponteiro atual para o próximo pedido da lista
    }
}

//função auxiliar para verificar se fila está vazia
int filaCozinhaVazia(Fila* q) {
    return (q->inicio == NULL);
}

//função para liberar memória da fila
void liberarFilaCozinha(Fila* q) {
    if (!q) return; //verifica se ponteiro q está vazio, se sim, retorna a função
    NoFila* atual = q->inicio; //ponteiro que pecorre a fila começa pelo inicio
    while (atual != NULL) { //while fica ativo enquanto houver nós na fila
        NoFila* proximo = atual->proximoNoFila; //armazena o proxímo nó antes de liberar o atual
        ItemPedido* itemAtual = atual->pedidoInfo.itensPedido; //acessa lista de pratos do pedido atual
        while (itemAtual != NULL) { //whiele fica ativo enquanto houver pratos no pedido
            ItemPedido* proximoItem = itemAtual->proximoItemPedido; //armazena o proxímo prato
            free(itemAtual); //libera memória do prato atual
            itemAtual = proximoItem; //passa para o próximo prato
        }
        free(atual); //libera memória do nó atual
        atual = proximo; //passa pro próximo nó
    }
    free(q); //libera memória da fila
}
