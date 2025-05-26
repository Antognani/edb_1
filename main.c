#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"
#include "fila_cozinha.h"
#include "lista_salao.h"

#define MAX_PRATOS_CARDAPIO 20

Prato cardapio[MAX_PRATOS_CARDAPIO];
int numPratosCardapio;
int contadorPedidos = 0; // conta os pedidos feitos

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarCardapio() {
    numPratosCardapio = 0; //inicializa o contador de pratos do cardápio
    //entradas
        // cada linha é uma compound literal para criar pratos 
    cardapio[numPratosCardapio++] = (Prato){1, "Sopa de cebola"}; //o contador de pratos do cardápio aumenta após cada adição (index do prato)
    cardapio[numPratosCardapio++] = (Prato){2, "Salada caesar"};
    cardapio[numPratosCardapio++] = (Prato){3, "Brusqueta"};
    cardapio[numPratosCardapio++] = (Prato){4, "Carparcio de carne"};
    cardapio[numPratosCardapio++] = (Prato){5, "Camarao ao alho"};

    //pratos principais
    cardapio[numPratosCardapio++] = (Prato){6, "Lasanha a bolonhesa"};
    cardapio[numPratosCardapio++] = (Prato){7, "File mignon com fritas"};
    cardapio[numPratosCardapio++] = (Prato){8, "Frango grelhado com legumes"};
    cardapio[numPratosCardapio++] = (Prato){9, "Bacalhau a gomes de sa"};
    cardapio[numPratosCardapio++] = (Prato){10, "Risoto de cogumelos"};

    //sobremesas
    cardapio[numPratosCardapio++] = (Prato){11, "Tiramisu"};
    cardapio[numPratosCardapio++] = (Prato){12, "Cheesecake de frutas vermelhas"};
    cardapio[numPratosCardapio++] = (Prato){13, "Mousse de chocolate"};
    cardapio[numPratosCardapio++] = (Prato){14, "Pudim de leite"};
    cardapio[numPratosCardapio++] = (Prato){15, "Sorvete de baunilha com calda de morango"};
}

void exibirCardapio() {
    printf("\n--- Cardapio do Restaurante ---\n");
    printf("ID | Nome do Prato\n");
    printf("---|-------------------------------------------------\n");
        for (int i = 0; i < numPratosCardapio; i++) {
        printf("%2d | %s\n", cardapio[i].id, cardapio[i].nome);
    }
    printf("----------------------------------------------------\n");
}

void exibirMenuOpcoes() {
    printf("\n========= Sistema de Pedidos =========\n");
    printf("1. Adicionar pedido (Salao)\n");
    printf("2. Remover prato de pedido (Salao)\n");
    printf("3. Transferir pedido para cozinha\n");
    printf("4. Processar pedido (Cozinha)\n");
    printf("5. Listar pedidos pendentes (Salao)\n");
    printf("6. Listar pedidos em processamento (Cozinha)\n");
    printf("7. Ver cardapio\n");
    printf("0. Sair\n");
    printf("=================================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    NoLista* listaPedidosSalao = NULL;
    Fila* filaPedidosCozinha = criarFilaCozinha;

    inicializarCardapio();

    int opcaoEscolhida;
    do { //repete até entrada 0
        exibirMenuOpcoes();
        if (scanf("%d", &opcaoEscolhida) != 1) { //checa se foi digitado algo diferente de número
            printf("Entrada invalida. Digite um numero.\n");
            limparBufferEntrada();
            opcaoEscolhida = -1; //atribui opção inexistente pra evitar conflito
            continue; //retorna loop
        }
        limparBufferEntrada(); //limpeza do buffer de entrada, para garantir

        switch (opcaoEscolhida) {
            case 1: { // Adicionar pedido (salão)
                Pedido p = criarPedido(cardapio, numPratosCardapio, &contadorPedidos);
                if (p.itensPedido != NULL) { 
                    listaPedidosSalao = adicionarPedidoSalao(listaPedidosSalao, p); //armazena o pedido na lista de pedidos pendentes
                     printf("Pedido ID %d adicionado ao salao.\n", p.idPedido);
                }
                break;
            }
            case 2: { // Remover Pedido (salão) [cite: 7]
                //remove o item de um pedido com base no seu id
                if (listaPedidosSalao == NULL) {
                    printf("Salao vazio. Nada para remover.\n");
                    break;
                }
                int idItemParaRemover, idPedidoParaModificar;
                printf("ID do Pedido para modificar: ");
                if (scanf("%d", &idItemParaRemover) != 1) {
                    printf("Entrada invalida.\n"); limpar_buffer_entrada_std(); break;
                } limpar_buffer_entrada_std();

                printf("ID do Prato a remover: ");
                if (scanf("%d", &idPedidoParaModificar) != 1) {
                    printf("Entrada invalida.\n"); limpar_buffer_entrada_std(); break;
                } limpar_buffer_entrada_std();
                
                //atualiza lista pra refletir a remoção
                listaPedidosSalao = remover_prato_de_pedido_salao(listaPedidosSalao, idItemParaRemover, idPedidoParaModificar);
                break;
            }
            case 3: { // Processar pedido (Cozinha) - transferir
                //transfere o pedido da lista ligada pra fila de processamento
                if (listaPedidosSalao == NULL) {
                    printf("Salao vazio. Nenhum pedido para transferir.\n");
                } else {
                    //transfere o pedido do início da lista do salão
                    NoLista* noParaTransferir = listaPedidosSalao;
                    Pedido pedidoTransferido = noParaTransferir->pedidoInfo; 
                    
                    listaPedidosSalao = noParaTransferir->proximoNoLista; 
                    
                    enfileirarPedidoCozinha(filaPedidosCozinha, pedidoTransferido); 
                    
                    free(noParaTransferir); 
                    
                    printf("Pedido ID %d transferido do salao para a cozinha.\n", pedidoTransferido.idPedido);
                }
                break;
            }
            case 4: { // Processar pedido (Cozinha) - tira da fila para preparação
                //first in, first out
                Pedido* pedidoProcessado = desenfileirarPedidoCozinha(filaPedidosCozinha);
                if (pedidoProcessado != NULL) {
                    printf("\n--- Processando Pedido ID %d da Cozinha ---\n", pedidoProcessado->idPedido);
                    ItemPedido* itemAtual = pedidoProcessado->itensPedido;
                    if(itemAtual == NULL) {
                        printf("  (Pedido estava vazio ao processar!)\n");
                    }
                    while (itemAtual != NULL) {
                        printf("  - Preparando: %s (ID: %d)\n", 
                            itemAtual->pratoInfo.nome, 
                            itemAtual->pratoInfo.id);
                        ItemPedido* proximoItem = itemAtual->proximoItemPedido;
                        free(itemAtual); 
                        itemAtual = proximoItem;
                    }
                    printf("--- Pedido ID %d finalizado! ---\n", pedidoProcessado->idPedido);
                    free(pedidoProcessado); 
                } else {
                     printf("Cozinha vazia. Nenhum pedido para processar.\n");
                }
                break;
            }
            case 5: // Listar pedidos pendentes (salão)
                //exibe os pedidos pendentes na lista ligada
                listarPedidosPendentesSalao(listaPedidosSalao);
                break;
            case 6: // Listar pedidos em processamento (cozinha)
                //exibes todos os pedidos que estão na lista de processamento
                listarPedidosProcessamentoCozinha(filaPedidosCozinha);
                break;
            case 7:
                exibirCardapio();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        if (opcaoEscolhida != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); // espera pelo enter pra limpar a tela antes do próximo menu
        }

    } while (opcaoEscolhida != 0);

    // Liberar memória alocada antes de sair
    liberarListaPedidosSalao(listaPedidosSalao);
    liberarFilaCozinha(filaPedidosCozinha);
    
    printf("Sistema encerrado. Memoria liberada.\n");
    return 0;
}