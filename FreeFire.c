
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Struct para cada item do inventário
typedef struct {
    char nome[30];      
    char tipo[20];      
    int quantidade;     
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;         
    struct No* proximo; 
} No;

// Variáveis globais
Item inventarioArray[10];  
int totalItens = 0; 

No* listaInventario = NULL; 

int contadorBuscaSeq = 0;
int contadorBuscaBin = 0;

// ========== UTILITÁRIOS ==========

void limpaBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// ========== OPERAÇÕES COM ARRAY ==========

void adicionarNoArray() {
    if (totalItens >= 10) {
        printf("\nInventário cheio! Remova algum item primeiro.\n");
        return;
    }

    printf("\n=== Adicionando item no array ===\n");
    
    printf("Nome do item: ");
    scanf("%s", inventarioArray[totalItens].nome);
    
    printf("Tipo (arma/municao/cura/ferramenta): ");
    scanf("%s", inventarioArray[totalItens].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &inventarioArray[totalItens].quantidade);

    totalItens++;
    printf("Item adicionado!\n");
}

void removerDoArray() {
    if (totalItens == 0) {
        printf("\nInventário vazio!\n");
        return;
    }

    char nomeItem[30];
    int achou = 0;
    int pos = -1;

    printf("\n=== Removendo item do array ===\n");
    printf("Nome do item para remover: ");
    scanf("%s", nomeItem);

    // Procura o item
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventarioArray[i].nome, nomeItem) == 0) {
            achou = 1;
            pos = i;
            break;
        }
    }

    if (achou) {
        // Desloca os elementos
        for (int i = pos; i < totalItens - 1; i++) {
            inventarioArray[i] = inventarioArray[i + 1];
        }
        totalItens--;
        printf("Item '%s' removido!\n", nomeItem);
    } else {
        printf("Item '%s' nao encontrado.\n", nomeItem);
    }
}

void mostrarArray() {
    printf("\n=== Inventário (Array) ===\n");
    
    if (totalItens == 0) {
        printf("Nenhum item no inventário.\n");
        return;
    }

    printf("Total: %d/10 itens\n", totalItens);
    printf("------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%d) %s [%s] x%d\n",
               i + 1, inventarioArray[i].nome, inventarioArray[i].tipo, inventarioArray[i].quantidade);
    }
}

void buscaLinearArray() {
    if (totalItens == 0) {
        printf("\nArray vazio!\n");
        return;
    }

    char itemProcurado[30];
    int achou = 0;
    contadorBuscaSeq = 0;

    printf("\n=== Busca Linear ===\n");
    printf("Item a procurar: ");
    scanf("%s", itemProcurado);

    clock_t inicio = clock();
    
    for (int i = 0; i < totalItens; i++) {
        contadorBuscaSeq++;
        if (strcmp(inventarioArray[i].nome, itemProcurado) == 0) {
            clock_t fim = clock();
            double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            printf("\nEncontrado!\n");
            printf("Item: %s\n", inventarioArray[i].nome);
            printf("Tipo: %s\n", inventarioArray[i].tipo);
            printf("Qtd: %d\n", inventarioArray[i].quantidade);
            printf("Posição: %d\n", i + 1);
            printf("Comparações: %d\n", contadorBuscaSeq);
            printf("Tempo: %.6f seg\n", duracao);
            achou = 1;
            break;
        }
    }

    if (!achou) {
        clock_t fim = clock();
        double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Item '%s' não foi encontrado.\n", itemProcurado);
        printf("Comparações: %d\n", contadorBuscaSeq);
        printf("Tempo: %.6f seg\n", duracao);
    }
}

void ordenarArray() {
    if (totalItens <= 1) {
        printf("\nPoucos itens para ordenar.\n");
        return;
    }

    printf("\n=== Ordenando por nome ===\n");
    
    clock_t inicio = clock();
    
    // Bubble sort simples
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(inventarioArray[j].nome, inventarioArray[j + 1].nome) > 0) {
                Item temp = inventarioArray[j];
                inventarioArray[j] = inventarioArray[j + 1];
                inventarioArray[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Array ordenado!\n");
    printf("Tempo: %.6f seg\n", duracao);
}

void buscaBinariaArray() {
    if (totalItens == 0) {
        printf("\nArray vazio!\n");
        return;
    }

    char itemProcurado[30];
    contadorBuscaBin = 0;

    printf("\n=== Busca Binária ===\n");
    printf("IMPORTANTE: Array precisa estar ordenado!\n");
    printf("Item a procurar: ");
    scanf("%s", itemProcurado);

    clock_t inicio = clock();
    
    int esq = 0;
    int dir = totalItens - 1;
    int achou = 0;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        contadorBuscaBin++;
        
        int comp = strcmp(inventarioArray[meio].nome, itemProcurado);
        
        if (comp == 0) {
            clock_t fim = clock();
            double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            printf("\nEncontrado com busca binária!\n");
            printf("Item: %s\n", inventarioArray[meio].nome);
            printf("Tipo: %s\n", inventarioArray[meio].tipo);
            printf("Qtd: %d\n", inventarioArray[meio].quantidade);
            printf("Posição: %d\n", meio + 1);
            printf("Comparações: %d\n", contadorBuscaBin);
            printf("Tempo: %.6f seg\n", duracao);
            achou = 1;
            break;
        } else if (comp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    
    if (!achou) {
        clock_t fim = clock();
        double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Item '%s' não encontrado.\n", itemProcurado);
        printf("Comparações: %d\n", contadorBuscaBin);
        printf("Tempo: %.6f seg\n", duracao);
    }
}

// ========== OPERAÇÕES COM LISTA ==========

int contaItensLista() {
    int contador = 0;
    No* atual = listaInventario;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void adicionarNaLista() {
    if (contaItensLista() >= 10) {
        printf("\nLista cheia!\n");
        return;
    }

    No* novoItem = (No*)malloc(sizeof(No));
    if (novoItem == NULL) {
        printf("\nErro de memória!\n");
        return;
    }

    printf("\n=== Adicionando item na lista ===\n");
    
    printf("Nome do item: ");
    scanf("%s", novoItem->dados.nome);
    
    printf("Tipo: ");
    scanf("%s", novoItem->dados.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoItem->dados.quantidade);

    // Adiciona no início
    novoItem->proximo = listaInventario;
    listaInventario = novoItem;

    printf("Item adicionado na lista!\n");
}

void removerDaLista() {
    if (listaInventario == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nomeItem[30];
    printf("\n=== Removendo da lista ===\n");
    printf("Nome do item: ");
    scanf("%s", nomeItem);

    No* atual = listaInventario;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeItem) == 0) {
            if (anterior == NULL) {
                listaInventario = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            printf("Item '%s' removido da lista!\n", nomeItem);
            return;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item '%s' não encontrado na lista.\n", nomeItem);
}

void mostrarLista() {
    printf("\n=== Inventário (Lista) ===\n");
    
    if (listaInventario == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    int qtd = contaItensLista();
    printf("Total: %d/10 itens\n", qtd);
    printf("------------------------\n");
    
    No* atual = listaInventario;
    int pos = 1;
    
    while (atual != NULL) {
        printf("%d) %s [%s] x%d\n",
               pos, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        pos++;
    }
}

void procurarNaLista() {
    if (listaInventario == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char itemProcurado[30];
    int comparacoes = 0;

    printf("\n=== Busca na Lista ===\n");
    printf("Item: ");
    scanf("%s", itemProcurado);

    clock_t inicio = clock();
    
    No* atual = listaInventario;
    int pos = 1;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, itemProcurado) == 0) {
            clock_t fim = clock();
            double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            printf("\nEncontrado na lista!\n");
            printf("Item: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Qtd: %d\n", atual->dados.quantidade);
            printf("Posição: %d\n", pos);
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f seg\n", duracao);
            return;
        }
        
        atual = atual->proximo;
        pos++;
    }

    clock_t fim = clock();
    double duracao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Item '%s' não encontrado na lista.\n", itemProcurado);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo: %.6f seg\n", duracao);
}

// ========== MENUS ==========

void menuArray() {
    int opcao;
    do {
        printf("\n>>> MENU ARRAY <<<\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca linear\n");
        printf("5 - Ordenar\n");
        printf("6 - Busca binária\n");
        printf("7 - Voltar\n");
        printf("Opção: ");
        
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1: adicionarNoArray(); break;
            case 2: removerDoArray(); break;
            case 3: mostrarArray(); break;
            case 4: buscaLinearArray(); break;
            case 5: ordenarArray(); break;
            case 6: buscaBinariaArray(); break;
            case 7: printf("Voltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 7);
}

void menuLista() {
    int opcao;
    do {
        printf("\n>>> MENU LISTA <<<\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("5 - Voltar\n");
        printf("Opção: ");
        
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1: adicionarNaLista(); break;
            case 2: removerDaLista(); break;
            case 3: mostrarLista(); break;
            case 4: procurarNaLista(); break;
            case 5: printf("Voltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 5);
}

void analisarPerformance() {
    printf("\n=== ANÁLISE DE PERFORMANCE ===\n");
    printf("Array: %d/10 itens\n", totalItens);
    printf("Lista: %d/10 itens\n", contaItensLista());
    printf("\nÚltimas buscas:\n");
    printf("- Busca linear: %d comparações\n", contadorBuscaSeq);
    printf("- Busca binária: %d comparações\n", contadorBuscaBin);
    
    printf("\n--- Comparação das estruturas ---\n");
    printf("ARRAY:\n");
    printf("  • Acesso direto rápido\n");
    printf("  • Busca binária após ordenação\n");
    printf("  • Melhor uso da cache\n");
    printf("  • Inserção/remoção no meio é lenta\n");
    printf("  • Tamanho fixo\n");
    
    printf("\nLISTA ENCADEADA:\n");
    printf("  • Inserção/remoção no início é rápida\n");
    printf("  • Tamanho flexível\n");
    printf("  • Sem desperdício de memória\n");
    printf("  • Acesso sequencial apenas\n");
    printf("  • Busca binária impraticável\n");
    printf("  • Overhead dos ponteiros\n");
}

void liberaMemoria() {
    No* atual = listaInventario;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    listaInventario = NULL;
}

int main() {
    int escolha;

    printf("Sistema de Inventário\n");
    printf("Comparação: Array vs Lista Encadeada\n");

    do {
        printf("\n===================================\n");
        printf("    INVENTÁRIO - COMPARAÇÃO\n");
        printf("===================================\n");
        printf("1. Trabalhar com Array\n");
        printf("2. Trabalhar com Lista Encadeada\n");
        printf("3. Analisar Performance\n");
        printf("4. Sair\n");
        printf("===================================\n");
        printf("Sua escolha: ");
        
        scanf("%d", &escolha);
        limpaBuffer();

        switch (escolha) {
            case 1: menuArray(); break;
            case 2: menuLista(); break;
            case 3: analisarPerformance(); break;
            case 4: 
                printf("\nLimpando memória...\n");
                liberaMemoria();
                printf("Até mais!\n");
                break;
            default: printf("Opção inválida!\n");
        }

    } while (escolha != 4);

    return 0;
}