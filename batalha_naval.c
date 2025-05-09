#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Tamanho fixo dos navios (3 posições)
#define AGUA 0                // Valor para representar água no tabuleiro
#define NAVIO 3               // Valor para representar navios no tabuleiro

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Preenche todo o tabuleiro com água (valor 0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se é possível posicionar um navio na posição especificada
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                  int linhaInicial, int colunaInicial, 
                  bool ehVertical) {
    
    // Verifica se o navio está dentro dos limites do tabuleiro
    if (ehVertical) {
        // Para navios verticais, verifica se todas as posições estão dentro do tabuleiro
        if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
            colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
            return false;
        }
        
        // Verifica se há sobreposição com outro navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicial + i][colunaInicial] == NAVIO) {
                return false;  // Sobreposição detectada
            }
        }
    } else {
        // Para navios horizontais, verifica se todas as posições estão dentro do tabuleiro
        if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
            colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;
        }
        
        // Verifica se há sobreposição com outro navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicial][colunaInicial + i] == NAVIO) {
                return false;  // Sobreposição detectada
            }
        }
    }
    
    // Se chegou até aqui, a posição é válida
    return true;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linhaInicial, int colunaInicial, 
                    bool ehVertical) {
    
    // Cria um vetor para representar o navio (todas as posições com valor 3)
    int navio[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        navio[i] = NAVIO;
    }
    
    // Posiciona o navio no tabuleiro conforme a orientação
    if (ehVertical) {
        // Navio vertical - ocupa posições na mesma coluna
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicial + i][colunaInicial] = navio[i];
        }
    } else {
        // Navio horizontal - ocupa posições na mesma linha
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicial][colunaInicial + i] = navio[i];
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  "); // Espaço para alinhar com os números das colunas
    
    // Exibe os números das colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    // Exibe o tabuleiro com os números das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Número da linha
        
        // Exibe os valores do tabuleiro para esta linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declara e inicializa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // Coordenadas iniciais para os navios
    int linha1 = 2, coluna1 = 3;  // Coordenadas para o navio vertical
    int linha2 = 7, coluna2 = 1;  // Coordenadas para o navio horizontal
    
    // Orientação dos navios (true = vertical, false = horizontal)
    bool navio1Vertical = true;   // Primeiro navio na vertical
    bool navio2Vertical = false;  // Segundo navio na horizontal
    
    // Valida e posiciona o primeiro navio (vertical)
    if (posicaoValida(tabuleiro, linha1, coluna1, navio1Vertical)) {
        posicionarNavio(tabuleiro, linha1, coluna1, navio1Vertical);
        printf("Navio 1 posicionado com sucesso na posição (%d,%d) - Vertical\n", linha1, coluna1);
    } else {
        printf("Erro: Posição inválida para o Navio 1\n");
    }
    
    // Valida e posiciona o segundo navio (horizontal)
    if (posicaoValida(tabuleiro, linha2, coluna2, navio2Vertical)) {
        posicionarNavio(tabuleiro, linha2, coluna2, navio2Vertical);
        printf("Navio 2 posicionado com sucesso na posição (%d,%d) - Horizontal\n", linha2, coluna2);
    } else {
        printf("Erro: Posição inválida para o Navio 2\n");
    }
    
    // Exibe o tabuleiro com os navios posicionados
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("0 = Água, 3 = Navio\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}