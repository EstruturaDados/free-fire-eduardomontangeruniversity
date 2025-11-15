#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item para representar cada item do inventário
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item no inventário
} Item;

// Variáveis globais
Item mochila[10];       // Vetor para armazenar até 10 itens
int totalItens = 0;     // Contador de itens atualmente na mochila

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inserir um novo item na mochila
void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= 10) {
        printf("\n MOCHILA CHEIA! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- CADASTRAR NOVO ITEM ---\n");

    // Lê o nome do item
    printf("Digite o nome do item: ");
    scanf("%s", mochila[totalItens].nome);

    // Lê o tipo do item
    printf("Digite o tipo do item (arma/munição/cura/ferramenta): ");
    scanf("%s", mochila[totalItens].tipo);

    // Lê a quantidade do item
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    // Incrementa o contador de itens
    totalItens++;

    printf("Item cadastrado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("\nMOCHILA VAZIA! Não há itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    int encontrado = 0;
    int posicao = -1;

    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeRemover);

    // Busca o item na mochila
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            posicao = i;
            break;
        }
    }

    // Se o item foi encontrado, remove-o
    if (encontrado) {
        // Move todos os itens após a posição encontrada uma posição para trás
        for (int i = posicao; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("Item '%s' removido com sucesso!\n", nomeRemover);
    } else {
        printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n--- INVENTÁRIO DA MOCHILA ---\n");

    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("Mochila vazia. Colete alguns itens!\n");
        return;
    }

    printf("Total de itens: %d/10\n", totalItens);
    printf("----------------------------------------\n");

    // Lista todos os itens
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------\n");
}

// Função para buscar um item específico na mochila
void buscarItem() {
    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("\n⚠MOCHILA VAZIA! Não há itens para buscar.\n");
        return;
    }

    char nomeBuscar[30];
    int encontrado = 0;

    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item a ser buscado: ");
    scanf("%s", nomeBuscar);

    // Busca sequencial pelo nome do item
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n🔍 ITEM ENCONTRADO!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Posição na mochila: %d\n", i + 1);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' não encontrado na mochila.\n", nomeBuscar);
    }
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n=======================================\n");
    printf("🎮 SISTEMA DE INVENTÁRIO - MOCHILA LOOT\n");
    printf("=======================================\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item\n");
    printf("5. Sair do jogo\n");
    printf("=======================================\n");
    printf("Escolha uma opção (1-5): ");
}

// Função principal do programa
int main() {
    int opcao;

    printf("BEM-VINDO AO SISTEMA DE INVENTÁRIO!\n");
    printf("Organize a mochila e sobreviva!\n");

    // Loop principal do menu
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer após scanf

        // Executa a ação baseada na opção escolhida
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nObrigado!\n");
                break;
            default:
                printf("\nOpção inválida! Escolha um número de 1 a 5.\n");
        }

        // Lista os itens após cada operação (exceto ao sair)
        if (opcao != 5 && opcao >= 1 && opcao <= 4) {
            listarItens();
        }

    } while (opcao != 5);

    return 0;
}