#include <stdio.h>
#include <string.h>

// Estrutura para representar dimensões (Altura, Largura, Comprimento)
typedef struct {
    int a, l, c;
} Dimensoes;

// Estrutura para representar uma caixa
typedef struct {
    char nome[20];
    Dimensoes original;
    Dimensoes atual;
} Caixa;

// Estrutura para representar um item do pedido
typedef struct {
    char nome[50];
    Dimensoes dim;
    int empacotado; // 0 para não, 1 para sim
} Item;

// Função para tentar encaixar um item em uma caixa considerando rotações
// Retorna 1 se couber e atualiza as dimensões restantes nos 3 eixos
int tenta_encaixar(Dimensoes item, Dimensoes *caixa) {
    int dim_item[3] = {item.a, item.l, item.c};
    
    // Tenta todas as 6 rotações possíveis do item
    int rotacoes[6][3] = {
        {0, 1, 2}, {0, 2, 1},
        {1, 0, 2}, {1, 2, 0},
        {2, 0, 1}, {2, 1, 0}
    };

    for (int i = 0; i < 6; i++) {
        int ia = dim_item[rotacoes[i][0]];
        int il = dim_item[rotacoes[i][1]];
        int ic = dim_item[rotacoes[i][2]];

        // Verifica se o item rotacionado cabe nas dimensões atuais da caixa
        if (ia <= caixa->a && il <= caixa->l && ic <= caixa->c) {
            // Ocupação 3D: subtrai as dimensões do item da caixa
            caixa->a -= ia;
            caixa->l -= il;
            caixa->c -= ic;
            
            if (caixa->a < 0) caixa->a = 0;
            if (caixa->l < 0) caixa->l = 0;
            if (caixa->c < 0) caixa->c = 0;
            
            return 1; // Item coube
        }
    }
    return 0; // Item não coube
}

// Função para verificar se um item cabe em uma caixa vazia (qualquer rotação)
int cabe_em_caixa_vazia(Dimensoes item, Dimensoes caixa_vazia) {
    int dim_item[3] = {item.a, item.l, item.c};
    int rotacoes[6][3] = {
        {0, 1, 2}, {0, 2, 1},
        {1, 0, 2}, {1, 2, 0},
        {2, 0, 1}, {2, 1, 0}
    };

    for (int i = 0; i < 6; i++) {
        if (dim_item[rotacoes[i][0]] <= caixa_vazia.a && 
            dim_item[rotacoes[i][1]] <= caixa_vazia.l && 
            dim_item[rotacoes[i][2]] <= caixa_vazia.c) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Definição das 3 opções de caixas
    Caixa opcoes[3] = {
        {"Caixa 1", {30, 40, 80}, {30, 40, 80}},
        {"Caixa 2", {80, 50, 40}, {80, 50, 40}},
        {"Caixa 3", {50, 80, 60}, {50, 80, 60}}
    };

    printf("--- SISTEMA DE EMPACOTAMENTO OTIMIZADO ---\n");
    printf("Caixas Disponiveis:\n");
    for(int i=0; i<3; i++) {
        printf("%s: %dx%dx%d\n", opcoes[i].nome, opcoes[i].original.a, opcoes[i].original.l, opcoes[i].original.c);
    }

    // Loop externo para Pedidos
    for (int novo_pedido = 1; novo_pedido != 0; ) {
        printf("\n>>> Iniciando Novo Pedido <<<\n");
        
        Item itens_pedido[100];
        int total_itens = 0;

        // Loop interno para Itens do Pedido
        for (int novo_item = 1; novo_item != 0; ) {
            printf("\nNome do produto: ");
            scanf(" %[^\n]", itens_pedido[total_itens].nome);
            
            printf("Dimensoes (Altura Largura Comprimento): ");
            scanf("%d %d %d", &itens_pedido[total_itens].dim.a, &itens_pedido[total_itens].dim.l, &itens_pedido[total_itens].dim.c);
            itens_pedido[total_itens].empacotado = 0;

            // Validação inicial: o item cabe em pelo menos uma das caixas vazias?
            int cabe_em_alguma = 0;
            for(int c=0; c<3; c++) {
                if(cabe_em_caixa_vazia(itens_pedido[total_itens].dim, opcoes[c].original)) {
                    cabe_em_alguma = 1;
                    break;
                }
            }

            if (!cabe_em_alguma) {
                printf("ERRO: O item '%s' nao cabe em nenhuma das caixas disponiveis!\n", itens_pedido[total_itens].nome);
            } else {
                total_itens++;
            }

            printf("Deseja inserir mais algum item? (1-Sim / 0-Nao): ");
            scanf("%d", &novo_item);
            if (total_itens >= 100) break;
        }

        if (total_itens > 0) {
            printf("\n--- Processando Empacotamento Otimizado ---\n");
            
            int caixas_usadas = 0;
            int itens_restantes = total_itens;
            int tipo_caixa = 2; // Usando Caixa 3 como padrão para transbordo

            // Enquanto houver itens não empacotados
            while (itens_restantes > 0) {
                caixas_usadas++;
                Caixa caixa_atual = opcoes[tipo_caixa];
                printf("\n>>> Abrindo Caixa %d (%s) <<<\n", caixas_usadas, caixa_atual.nome);

                // Percorre todos os itens para tentar preencher o máximo desta caixa
                for (int i = 0; i < total_itens; i++) {
                    if (itens_pedido[i].empacotado == 0) {
                        if (tenta_encaixar(itens_pedido[i].dim, &caixa_atual.atual)) {
                            itens_pedido[i].empacotado = 1;
                            itens_restantes--;
                            printf("Item '%s' empacotado na Caixa %d. Espaco restante: A:%d L:%d C:%d\n", 
                                    itens_pedido[i].nome, caixas_usadas, caixa_atual.atual.a, caixa_atual.atual.l, caixa_atual.atual.c);
                        }
                    }
                }
                printf("Caixa %d finalizada.\n", caixas_usadas);
            }

            printf("\nRESULTADO FINAL DO PEDIDO:\n");
            printf("Total de itens: %d\n", total_itens);
            printf("Total de caixas utilizadas: %d\n", caixas_usadas);
        }

        printf("\nDeseja realizar um novo pedido? (1-Sim / 0-Nao): ");
        scanf("%d", &novo_pedido);
    }

    printf("\nSistema encerrado.\n");
    return 0;
}
