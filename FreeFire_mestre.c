
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Struct para cada item do inventário
typedef struct {
    char nome[30];
    char tipo[20];  
    int prioridade;
} Componente;

// Arrays e contadores globais
Componente torreComponentes[20];
int totalComponentes = 0;
int contadorBubble = 0;
int contadorInsertion = 0;
int contadorSelection = 0;
int contadorBinaria = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Entrada segura de strings
void obterString(char *str, int tam) {
    fgets(str, tam, stdin);
    // Remove quebra de linha se presente
    size_t comprimento = strlen(str);
    if (comprimento > 0 && str[comprimento-1] == '\n') {
        str[comprimento-1] = '\0';
    }
}

// Funcao para cadastrar novos componentes
void adicionarComponente() {
    if (totalComponentes >= 20) {
        printf("\nCapacidade maxima atingida! Nao eh possivel adicionar mais componentes.\n");
        return;
    }

    printf("\n=== NOVO COMPONENTE ===\n");
    printf("Cadastrando componente %d de 20\n", totalComponentes + 1);

    printf("Digite o nome do componente: ");
    obterString(torreComponentes[totalComponentes].nome, 30);

    printf("Informe o tipo (controle/suporte/propulsao): ");
    obterString(torreComponentes[totalComponentes].tipo, 20);

    printf("Defina a prioridade (escala de 1 a 10): ");
    scanf("%d", &torreComponentes[totalComponentes].prioridade);
    limparBuffer();

    // Validacao simples da prioridade
    if (torreComponentes[totalComponentes].prioridade < 1 ||
        torreComponentes[totalComponentes].prioridade > 10) {
        printf("Valor fora do intervalo! Ajustando para prioridade media (5).\n");
        torreComponentes[totalComponentes].prioridade = 5;
    }

    totalComponentes++;
    printf("Componente adicionado com sucesso!\n");
}

// Exibir lista de componentes
void listarComponentes(Componente lista[], int quantidade) {
    printf("\n=== COMPONENTES CADASTRADOS ===\n");

    if (quantidade == 0) {
        printf("Lista vazia - nenhum componente foi cadastrado ainda.\n");
        return;
    }

    printf("Total de componentes: %d/20\n", quantidade);
    printf("-----------------------------------------------\n");
    printf("%-3s %-20s %-12s %-10s\n", "ID", "Nome", "Tipo", "Prioridade");
    printf("-----------------------------------------------\n");

    int i;
    for (i = 0; i < quantidade; i++) {
        printf("%-3d %-20s %-12s %-10d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
    printf("-----------------------------------------------\n");
}

// Ordenacao por bolha - critério: nome
void ordenarBolhaNome(Componente lista[], int tamanho) {
    contadorBubble = 0;
    int i, j;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            contadorBubble++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                // Efetua a troca
                Componente aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

// Ordenacao por insercao - critério: tipo
void ordenarInsercaoTipo(Componente lista[], int tamanho) {
    contadorInsertion = 0;
    int i, j;

    for (i = 1; i < tamanho; i++) {
        Componente elemento = lista[i];
        j = i - 1;

        while (j >= 0) {
            contadorInsertion++;
            if (strcmp(lista[j].tipo, elemento.tipo) <= 0) {
                break;
            }
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = elemento;
    }
}

// Ordenacao por selecao - critério: prioridade (decrescente)
void ordenarSelecaoPrioridade(Componente lista[], int tamanho) {
    contadorSelection = 0;
    int i, j;

    for (i = 0; i < tamanho - 1; i++) {
        int posicaoMaior = i;

        for (j = i + 1; j < tamanho; j++) {
            contadorSelection++;
            if (lista[j].prioridade > lista[posicaoMaior].prioridade) {
                posicaoMaior = j;
            }
        }

        if (posicaoMaior != i) {
            Componente aux = lista[i];
            lista[i] = lista[posicaoMaior];
            lista[posicaoMaior] = aux;
        }
    }
}

// ========== BUSCA BINARIA ==========

int localizarComponente(Componente lista[], int tamanho, char nomeDesejado[]) {
    contadorBinaria = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        contadorBinaria++;

        int comparacao = strcmp(lista[meio].nome, nomeDesejado);

        if (comparacao == 0) {
            return meio; // Encontrado
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1; // Nao encontrado
}

// ========== MEDICAO DE DESEMPENHO ==========

double calcularTempoExecucao(void (*funcaoOrdenacao)(Componente[], int), Componente lista[], int tamanho) {
    clock_t tempoInicial = clock();
    funcaoOrdenacao(lista, tamanho);
    clock_t tempoFinal = clock();

    return ((double)(tempoFinal - tempoInicial)) / CLOCKS_PER_SEC;
}

// ========== OPERACOES DE MENU ==========

void executarOrdenacao() {
    if (totalComponentes == 0) {
        printf("\nNao ha componentes para ordenar! Cadastre alguns primeiro.\n");
        return;
    }

    int escolha;
    printf("\n=== ALGORITMOS DE ORDENACAO ===\n");
    printf("1 - Ordenacao por Bolha (nome)\n");
    printf("2 - Ordenacao por Insercao (tipo)\n");
    printf("3 - Ordenacao por Selecao (prioridade)\n");
    printf("4 - Retornar ao menu\n");
    printf("Selecione uma opcao: ");

    scanf("%d", &escolha);
    limparBuffer();

    // Cria uma copia dos dados originais
    Componente copia[20];
    int idx;
    for (idx = 0; idx < totalComponentes; idx++) {
        copia[idx] = torreComponentes[idx];
    }

    double duracao;

    switch (escolha) {
        case 1:
            printf("\n--- Executando Ordenacao por Bolha ---\n");
            duracao = calcularTempoExecucao(ordenarBolhaNome, copia, totalComponentes);
            printf("Processo finalizado!\n");
            printf("Total de comparacoes: %d\n", contadorBubble);
            printf("Tempo gasto: %.6f segundos\n", duracao);
            listarComponentes(copia, totalComponentes);

            // Atualiza array principal para permitir busca posterior
            for (idx = 0; idx < totalComponentes; idx++) {
                torreComponentes[idx] = copia[idx];
            }
            break;

        case 2:
            printf("\n--- Executando Ordenacao por Insercao ---\n");
            duracao = calcularTempoExecucao(ordenarInsercaoTipo, copia, totalComponentes);
            printf("Processo finalizado!\n");
            printf("Total de comparacoes: %d\n", contadorInsertion);
            printf("Tempo gasto: %.6f segundos\n", duracao);
            listarComponentes(copia, totalComponentes);
            break;

        case 3:
            printf("\n--- Executando Ordenacao por Selecao ---\n");
            duracao = calcularTempoExecucao(ordenarSelecaoPrioridade, copia, totalComponentes);
            printf("Processo finalizado!\n");
            printf("Total de comparacoes: %d\n", contadorSelection);
            printf("Tempo gasto: %.6f segundos\n", duracao);
            listarComponentes(copia, totalComponentes);
            break;

        case 4:
            printf("Retornando...\n");
            break;

        default:
            printf("Opcao inexistente!\n");
    }
}

void procurarComponenteEspecifico() {
    if (totalComponentes == 0) {
        printf("\nLista vazia!\n");
        return;
    }

    char nomeChave[30];
    printf("\n=== LOCALIZACAO DE COMPONENTE ===\n");
    printf("OBSERVACAO: Para busca binaria funcionar corretamente,\n");
    printf("os dados devem estar ordenados por nome (opcao 1 do menu anterior).\n");
    printf("Digite o nome do componente: ");
    obterString(nomeChave, 30);

    clock_t inicio = clock();
    int resultado = localizarComponente(torreComponentes, totalComponentes, nomeChave);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (resultado != -1) {
        printf("\n*** COMPONENTE LOCALIZADO! ***\n");
        printf("Nome: %s\n", torreComponentes[resultado].nome);
        printf("Tipo: %s\n", torreComponentes[resultado].tipo);
        printf("Prioridade: %d\n", torreComponentes[resultado].prioridade);
        printf("Posicao na lista: %d\n", resultado + 1);
        printf("Comparacoes necessarias: %d\n", contadorBinaria);
        printf("Tempo de busca: %.6f segundos\n", tempo);
        printf("\nComponente encontrado com sucesso!\n");
    } else {
        printf("\nComponente '%s' nao foi encontrado.\n", nomeChave);
        printf("Comparacoes realizadas: %d\n", contadorBinaria);
        printf("Tempo de busca: %.6f segundos\n", tempo);
        printf("Verifique o nome digitado e se os dados estao ordenados adequadamente.\n");
    }
}

void construirTorreCompleta() {
    printf("\n=== CONSTRUCAO DA TORRE ===\n");

    if (totalComponentes == 0) {
        printf("Sem componentes disponiveis para construcao!\n");
        return;
    }

    printf("Iniciando processo de montagem...\n");
    listarComponentes(torreComponentes, totalComponentes);

    printf("\n--- Diagnostico do Sistema ---\n");
    printf("Componentes disponiveis: %d/20\n", totalComponentes);

    // Verifica disponibilidade de cada tipo essencial
    int possuiControle = 0, possuiSuporte = 0, possuiPropulsao = 0;
    int i;

    for (i = 0; i < totalComponentes; i++) {
        if (strcmp(torreComponentes[i].tipo, "controle") == 0) possuiControle = 1;
        else if (strcmp(torreComponentes[i].tipo, "suporte") == 0) possuiSuporte = 1;
        else if (strcmp(torreComponentes[i].tipo, "propulsao") == 0) possuiPropulsao = 1;
    }

    printf("Modulo de controle: %s\n", possuiControle ? "DISPONIVEL" : "AUSENTE");
    printf("Modulo de suporte: %s\n", possuiSuporte ? "DISPONIVEL" : "AUSENTE");
    printf("Modulo de propulsao: %s\n", possuiPropulsao ? "DISPONIVEL" : "AUSENTE");

    if (possuiControle && possuiSuporte && possuiPropulsao) {
        printf("\n*** TORRE CONSTRUIDA COM SUCESSO! ***\n");
        printf("Todos os modulos essenciais estao operacionais!\n");
        printf("Sistema pronto para operacao!\n");
    } else {
        printf("\nALERTA: Construcao incompleta. Componentes essenciais estao faltando.\n");
        printf("Adicione componentes dos tipos ausentes para finalizar.\n");
    }
}

void exibirEstatisticas() {
    printf("\n=== ESTATISTICAS DE DESEMPENHO ===\n");

    printf("Quantidade de componentes: %d/20\n\n", totalComponentes);

    printf("--- Historico de Execucoes ---\n");
    printf("Ordenacao por Bolha: %d comparacoes\n", contadorBubble);
    printf("Ordenacao por Insercao: %d comparacoes\n", contadorInsertion);
    printf("Ordenacao por Selecao: %d comparacoes\n", contadorSelection);
    printf("Busca Binaria: %d comparacoes\n\n", contadorBinaria);

    printf("--- Informacoes dos Algoritmos ---\n");
    printf("ORDENACAO POR BOLHA:\n");
    printf("  • Complexidade temporal: O(n²)\n");
    printf("  • Facil implementacao\n");
    printf("  • Inadequado para grandes conjuntos\n");
    printf("  • Muitas operacoes de troca\n\n");

    printf("ORDENACAO POR INSERCAO:\n");
    printf("  • Complexidade temporal: O(n²)\n");
    printf("  • Bom desempenho em arrays pequenos\n");
    printf "  • Eficiente com dados pre-ordenados\n");
    printf("  • Algoritmo estavel\n\n");

    printf("ORDENACAO POR SELECAO:\n");
    printf("  • Complexidade temporal: O(n²)\n");
    printf("  • Numero reduzido de trocas\n");
    printf("  • Comportamento previsivel\n");
    printf("  • Nao preserva ordem relativa\n\n");

    printf("BUSCA BINARIA:\n");
    printf("  • Complexidade temporal: O(log n)\n");
    printf("  • Alta eficiencia\n");
    printf("  • Necessita dados pre-ordenados\n");
    printf("  • Estrategia divisao e conquista\n");
}

// ========== PROGRAMA PRINCIPAL ==========

int main() {
    int opcaoMenu;

    printf("=================================================\n");
    printf("     GERENCIADOR DE TORRE DE RESGATE v2.0       \n");
    printf("=================================================\n");
    printf("Sistema para construcao e gerenciamento de torres\n");
    printf("Monte sua estrutura com os componentes corretos!\n");

    do {
        printf("\n=======================================\n");
        printf("           MENU DE OPCOES\n");
        printf("=======================================\n");
        printf("1. Adicionar componente\n");
        printf("2. Visualizar componentes\n");
        printf("3. Executar ordenacao\n");
        printf("4. Localizar componente\n");
        printf("5. Construir torre\n");
        printf("6. Ver estatisticas\n");
        printf("7. Encerrar programa\n");
        printf("=======================================\n");
        printf("Digite sua opcao: ");

        scanf("%d", &opcaoMenu);
        limparBuffer();

        switch (opcaoMenu) {
            case 1:
                adicionarComponente();
                break;
            case 2:
                listarComponentes(torreComponentes, totalComponentes);
                break;
            case 3:
                executarOrdenacao();
                break;
            case 4:
                procurarComponenteEspecifico();
                break;
            case 5:
                construirTorreCompleta();
                break;
            case 6:
                exibirEstatisticas();
                break;
            case 7:
                printf("\nPrograma finalizado. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcaoMenu != 7);

    return 0;
}