#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Tamanho fixo dos navios (3 posicoes)
#define AGUA 0                // Valor para representar agua no tabuleiro
#define NAVIO 3               // Valor para representar navios no tabuleiro

// Enumeracao para os tipos de orientacao dos navios
typedef enum {
    HORIZONTAL = 0,
    VERTICAL = 1,
    DIAGONAL_DESCENDENTE = 2,  // Diagonal principal (i,i)
    DIAGONAL_ASCENDENTE = 3    // Diagonal invertida (i,9-i)
} Orientacao;

// Funcao para inicializar o tabuleiro com agua
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Preenche todo o tabuleiro com agua (valor 0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Funcao para verificar se eh possivel posicionar um navio na posicao especificada
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                  int linhaInicial, int colunaInicial, 
                  Orientacao orientacao) {
    
    // Verifica se o navio esta dentro dos limites do tabuleiro e se nao ha sobreposicao
    switch (orientacao) {
        case VERTICAL:
            // Para navios verticais, verifica se todas as posicoes estao dentro do tabuleiro
            if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
                return false;
            }
            
            // Verifica se ha sobreposicao com outro navio
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial + i][colunaInicial] == NAVIO) {
                    return false;  // Sobreposicao detectada
                }
            }
            break;
            
        case HORIZONTAL:
            // Para navios horizontais, verifica se todas as posicoes estao dentro do tabuleiro
            if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
                colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return false;
            }
            
            // Verifica se ha sobreposicao com outro navio
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial][colunaInicial + i] == NAVIO) {
                    return false;  // Sobreposicao detectada
                }
            }
            break;
            
        case DIAGONAL_DESCENDENTE:
            // Para navios na diagonal descendente, verifica limites do tabuleiro
            // A diagonal descendente aumenta tanto linha quanto coluna
            if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
                colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return false;
            }
            
            // Verifica sobreposicao
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial + i][colunaInicial + i] == NAVIO) {
                    return false;
                }
            }
            break;
            
        case DIAGONAL_ASCENDENTE:
            // Para navios na diagonal ascendente, verifica limites do tabuleiro
            // A diagonal ascendente aumenta linha mas diminui coluna
            if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
                colunaInicial - (TAMANHO_NAVIO - 1) < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
                return false;
            }
            
            // Verifica sobreposicao
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial + i][colunaInicial - i] == NAVIO) {
                    return false;
                }
            }
            break;
    }
    
    // Se chegou ate aqui, a posicao eh valida
    return true;
}

// Funcao para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linhaInicial, int colunaInicial, 
                    Orientacao orientacao) {
    
    // Posiciona o navio no tabuleiro conforme a orientacao
    switch (orientacao) {
        case VERTICAL:
            // Navio vertical - ocupa posicoes na mesma coluna
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial] = NAVIO;
            }
            break;
            
        case HORIZONTAL:
            // Navio horizontal - ocupa posicoes na mesma linha
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial][colunaInicial + i] = NAVIO;
            }
            break;
            
        case DIAGONAL_DESCENDENTE:
            // Navio na diagonal descendente
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
            }
            break;
            
        case DIAGONAL_ASCENDENTE:
            // Navio na diagonal ascendente
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
            }
            break;
    }
}

// Funcao para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  "); // Espaco para alinhar com os numeros das colunas
    
    // Exibe os numeros das colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    // Exibe o tabuleiro com os numeros das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Numero da linha
        
        // Exibe os valores do tabuleiro para esta linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Funcao para converter a orientacao em texto para exibicao
const char* obterTextoOrientacao(Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            return "Horizontal";
        case VERTICAL:
            return "Vertical";
        case DIAGONAL_DESCENDENTE:
            return "Diagonal Descendente";
        case DIAGONAL_ASCENDENTE:
            return "Diagonal Ascendente";
        default:
            return "Desconhecida";
    }
}

int main() {
    // Declara e inicializa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // Coordenadas e orientacoes para os quatro navios
    struct {
        int linha;
        int coluna;
        Orientacao orientacao;
    } navios[4] = {
        {2, 3, VERTICAL},              // Navio 1 (vertical)
        {7, 1, HORIZONTAL},            // Navio 2 (horizontal)
        {0, 6, DIAGONAL_DESCENDENTE},  // Navio 3 (diagonal descendente)
        {4, 5, DIAGONAL_ASCENDENTE}    // Navio 4 (diagonal ascendente)
    };
    
    // Tenta posicionar cada navio
    for (int i = 0; i < 4; i++) {
        if (posicaoValida(tabuleiro, navios[i].linha, navios[i].coluna, navios[i].orientacao)) {
            posicionarNavio(tabuleiro, navios[i].linha, navios[i].coluna, navios[i].orientacao);
            printf("Navio %d posicionado com sucesso na posicao (%d,%d) - %s\n", 
                   i+1, navios[i].linha, navios[i].coluna, 
                   obterTextoOrientacao(navios[i].orientacao));
        } else {
            printf("Erro: Posicao invalida para o Navio %d na posicao (%d,%d) - %s\n", 
                   i+1, navios[i].linha, navios[i].coluna, 
                   obterTextoOrientacao(navios[i].orientacao));
        }
    }
    
    // Exibe o tabuleiro com os navios posicionados
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("0 = Agua, 3 = Navio\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}