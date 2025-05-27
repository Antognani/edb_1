#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"
#include "fila_cozinha.h"
#include "lista_salao.h"

#define MAX_PRATOS_CARDAPIO 20 //define o número máximo de pratos do cardápio

Prato cardapio[MAX_PRATOS_CARDAPIO];
int numPratosCardapio;
int contadorPedidos = 0; // conta os pedidos feitos

void limparBufferEntrada() { //limpa o buffer de entrada (pra evitar problemas nos scanf)
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarCardapio() { //inicializa o cardápio
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

void exibirCardapio() { //exibe o cardápio
    printf("\n--- Cardapio do Restaurante ---\n");
    printf("ID | Nome do Prato\n");
    printf("---|-------------------------------------------------\n");
        for (int i = 0; i < numPratosCardapio; i++) { //loop para exibir todos os pratos do cardápio até o fim dos index
        printf("%2d | %s\n", cardapio[i].id, cardapio[i].nome); // exibe o id e o nome do prato
    }
    printf("----------------------------------------------------\n");
}

void exibirMenuOpcoes() { //menu de opções do usuário
    printf("\n========= Sistema de Pedidos =========\n");
    printf("1. Adicionar pedido\n");
    printf("2. Remover prato de um pedido\n");
    printf("3. Transferir pedido para a cozinha\n");
    printf("4. Processar pedido\n");
    printf("5. Listar pedidos pendentes do salao\n");
    printf("6. Listar pedidos em processamento na cozinha\n");
    printf("7. Ver cardapio\n");
    printf("0. Sair\n");
    printf("=================================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    NoLista* listaPedidosSalao = NULL; //inicializa a lista de pedidos pendentes do salão
    Fila* filaPedidosCozinha = criarFilaCozinha(); //inicializa a fila de pedidos da cozinha

    inicializarCardapio(); //preenche o cardápio com os pratos

    int opcaoEscolhida; //variável para armazenar a opção escolhida pelo usuário
    do { //repete até entrada 0
        exibirMenuOpcoes(); //exibe o menu de opções
        if (scanf("%d", &opcaoEscolhida) != 1) { //checa se foi digitado algo diferente de número
            printf("Entrada invalida. Digite um numero.\n");
            limparBufferEntrada();
            opcaoEscolhida = -1; //atribui opção inexistente pra evitar conflito
            continue; //retorna loop
        }
        limparBufferEntrada(); //limpeza do buffer de entrada, para garantir

        switch (opcaoEscolhida) {
            case 1: { //ADICIONAR PEDIDO
                Pedido p = criarPedido(cardapio, numPratosCardapio, &contadorPedidos); //cria um novo pedido
                if (p.itensPedido != NULL) { 
                    listaPedidosSalao = adicionarPedidoSalao(listaPedidosSalao, p); //armazena o pedido na lista de pedidos pendentes
                     printf("Pedido ID %d adicionado ao salao.\n", p.idPedido); // confirma adição e informa o id do pedido
                }
                break;
            }
            case 2: { //REMOVER PEDIDO
                //remove o item de um pedido com base no seu id
                if (listaPedidosSalao == NULL) { // verifica se a lista de pedidos está vazia
                    printf("Salao vazio. Nada para remover.\n");
                    break;
                }
                int idItemParaRemover, idPedidoParaModificar; //variáveis para armazenar os ids do item e do pedido a serem removidos
                printf("ID do pedido que deseja modificar: "); 
                if (scanf("%d", &idItemParaRemover) != 1) { //checa se foi digitado algo diferente de número
                    printf("Entrada invalida.\n"); 
                    limparBufferEntrada(); 
                    break; // se não for número, informa e limpa o buffer
                } limparBufferEntrada(); 

                printf("ID do prato a remover: "); 
                if (scanf("%d", &idPedidoParaModificar) != 1) { //checa se foi digitado algo diferente de número
                    printf("Entrada invalida.\n"); 
                    limparBufferEntrada(); 
                    break; // se não for número, informa e limpa o buffer
                } limparBufferEntrada();
                
                //atualiza lista pra refletir a remoção
                listaPedidosSalao = removerPratoPedidoSalao(listaPedidosSalao, idItemParaRemover, idPedidoParaModificar); //passa os atributor informados pra função de remoção
                break;
            }
            case 3: { //PROCESSAR PEDIDO (DA LISTA PRA FILA)
                //transfere o pedido da lista ligada pra fila de processamento
                if (listaPedidosSalao == NULL) { //verifica se a lista de pedidos está vazia
                    printf("Salao vazio. Nenhum pedido para transferir.\n");
                } else { //se não estiver vazia, transfere o pedido do início da lista para a fila de pedidos da cozinha
                    NoLista* noParaTransferir = listaPedidosSalao; //pega o primeiro nó da lista
                    Pedido pedidoTransferido = noParaTransferir->pedidoInfo; // copia as informações do pedido para uma variável 
                    
                    listaPedidosSalao = noParaTransferir->proximoNoLista; // atualiza a lista para remover o nó transferido
                    
                    enfileirarPedidoCozinha(filaPedidosCozinha, pedidoTransferido); // adiciona o pedido na fila de pedidos da cozinha
                    
                    free(noParaTransferir); // libera a memória do nó removido da lista
                    
                    printf("Pedido ID %d transferido do salao para a cozinha.\n", pedidoTransferido.idPedido);
                }
                break;
            }
            case 4: { //PROCESSAR PEDIDO (COZINHA) - tira da fila para preparação
                //first in, first out
                Pedido* pedidoProcessado = desenfileirarPedidoCozinha(filaPedidosCozinha); //remove o pedido do início da fila de pedidos da cozinha
                if (pedidoProcessado != NULL) { //verifica se há pedidos na fila
                    printf("\n--- Processando Pedido ID %d da Cozinha ---\n", pedidoProcessado->idPedido); //informa o id do pedido que está sendo processado
                    ItemPedido* itemAtual = pedidoProcessado->itensPedido; //pega o primeiro item do pedido
                    if(itemAtual == NULL) { //verifica se o pedido está vazio
                        printf("  (Pedido estava vazio ao processar!)\n");
                    }
                    while (itemAtual != NULL) { //roda enquanto houver algum item no pedido
                        printf("  - Preparando: %s (ID: %d)\n", //printa o nome do prato e a id dele
                            itemAtual->pratoInfo.nome, 
                            itemAtual->pratoInfo.id);
                        ItemPedido* proximoItem = itemAtual->proximoItemPedido; //armazena o próximo item antes de liberar o atual
                        free(itemAtual); //libera a memória do item atual
                        itemAtual = proximoItem; //avança para o próximo item
                    }
                    printf("--- Pedido ID %d finalizado! ---\n", pedidoProcessado->idPedido); //
                    free(pedidoProcessado);  //libera a memória do pedido processado
                } else {
                     printf("Cozinha vazia. Nenhum pedido para processar.\n"); 
                }
                break;
            }
            case 5: // Listar pedidos pendentes (salão)
                //exibe os pedidos pendentes na lista ligada do salão
                listarPedidosPendentesSalao(listaPedidosSalao); //
                break;
            case 6: // Listar pedidos em processamento (cozinha)
                //exibes todos os pedidos que estão na lista de processamento
                listarPedidosProcessamentoCozinha(filaPedidosCozinha);
                break;
            case 7:
                exibirCardapio(); //exibe o cardápio
                break;
            case 0:
                printf("Encerrando o sistema...\n"); //encerra
                break;
            default: 
                printf("Opcao invalida. Tente novamente.\n");
        }
        if (opcaoEscolhida != 0) { //se não for a opção de sair, espera o usuário pressionar Enter para continuar
            printf("\nPressione Enter para continuar...");
            getchar(); // espera pelo enter pra limpar a tela antes do próximo menu
        }

    } while (opcaoEscolhida != 0); //repete até o usuário escolher a opção de sair

    //libera memória alocada antes de sair
    liberarListaPedidosSalao(listaPedidosSalao);
    liberarFilaCozinha(filaPedidosCozinha);
    
    printf("Obrigado e volte sempre!\n");
    return 0;
}
