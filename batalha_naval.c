#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Tamanho fixo dos navios (3 posicoes)
#define AGUA 0                // Valor para representar agua no tabuleiro
#define NAVIO 3               // Valor para representar navios no tabuleiro
#define HABILIDADE 5          // Valor para representar área afetada por habilidade

// Constantes para as matrizes de habilidades
#define TAMANHO_HABILIDADE 5  // Tamanho das matrizes de habilidade (5x5)

// Enumeracao para os tipos de orientacao dos navios
typedef enum {
    HORIZONTAL = 0,
    VERTICAL = 1,
    DIAGONAL_DESCENDENTE = 2,  // Diagonal principal (i,i)
    DIAGONAL_ASCENDENTE = 3    // Diagonal invertida (i,9-i)
} Orientacao;

// Enumeracao para os tipos de habilidades
typedef enum {
    CONE = 0,
    CRUZ = 1,
    OCTAEDRO = 2
} TipoHabilidade;

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

// Funcao para converter o tipo de habilidade em texto para exibicao
const char* obterTextoHabilidade(TipoHabilidade tipoHabilidade) {
    switch (tipoHabilidade) {
        case CONE:
            return "Cone";
        case CRUZ:
            return "Cruz";
        case OCTAEDRO:
            return "Octaedro";
        default:
            return "Desconhecida";
    }
}

// Função para criar a matriz de habilidade do tipo Cone
void criarMatrizCone(int matrizHabilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializa matriz com zeros
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matrizHabilidade[i][j] = 0;
        }
    }
    
    // Define o formato de cone (apontando para baixo, expandindo)
    // O ponto de origem está no topo e a área se expande para baixo
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        // A largura do cone aumenta em cada linha
        int larguraCone = 2 * i + 1;
        int inicioColuna = (TAMANHO_HABILIDADE - larguraCone) / 2;
        
        // Preenche a linha atual do cone
        for (int j = 0; j < larguraCone && j + inicioColuna < TAMANHO_HABILIDADE; j++) {
            matrizHabilidade[i][inicioColuna + j] = 1;
        }
    }
}

// Função para criar a matriz de habilidade do tipo Cruz
void criarMatrizCruz(int matrizHabilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializa matriz com zeros
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matrizHabilidade[i][j] = 0;
        }
    }
    
    // Define o meio da matriz
    int meio = TAMANHO_HABILIDADE / 2;
    
    // Preenche a linha horizontal da cruz
    for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
        matrizHabilidade[meio][j] = 1;
    }
    
    // Preenche a linha vertical da cruz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        matrizHabilidade[i][meio] = 1;
    }
}

// Função para criar a matriz de habilidade do tipo Octaedro (losango)
void criarMatrizOctaedro(int matrizHabilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializa matriz com zeros
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matrizHabilidade[i][j] = 0;
        }
    }
    
    // Define o meio da matriz
    int meio = TAMANHO_HABILIDADE / 2;
    
    // Preenche o formato de losango
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        // Calcula a distância da linha atual ao centro
        int distancia = (i > meio) ? i - meio : meio - i;
        
        // Define quantas células serão preenchidas nesta linha
        int larguraLosango = TAMANHO_HABILIDADE - 2 * distancia;
        
        // Se a largura for positiva, preenche as células
        if (larguraLosango > 0) {
            int inicioColuna = distancia;
            for (int j = 0; j < larguraLosango; j++) {
                matrizHabilidade[i][inicioColuna + j] = 1;
            }
        }
    }
}

// Função para exibir uma matriz de habilidade (para depuração)
void exibirMatrizHabilidade(int matrizHabilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    printf("\nMatriz de Habilidade:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", matrizHabilidade[i][j]);
        }
        printf("\n");
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int matrizHabilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                      int linhaOrigem, int colunaOrigem) {
    
    // Determina o ponto de origem (centro) na matriz de habilidade
    int centroHabilidade = TAMANHO_HABILIDADE / 2;
    
    // Cria um tabuleiro temporário para armazenar os resultados
    int tabuleiroTemp[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Copia o tabuleiro original para o temporário
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroTemp[i][j] = tabuleiro[i][j];
        }
    }
    
    // Aplica a habilidade ao tabuleiro
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a posição correspondente no tabuleiro
            int linhaTabuleiro = linhaOrigem + (i - centroHabilidade);
            int colunaTabuleiro = colunaOrigem + (j - centroHabilidade);
            
            // Verifica se a posição está dentro dos limites do tabuleiro
            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {
                
                // Se a célula da matriz de habilidade for 1, marca a posição no tabuleiro
                if (matrizHabilidade[i][j] == 1) {
                    // Apenas marca se a posição for água ou navio, mantendo o navio visível
                    if (tabuleiroTemp[linhaTabuleiro][colunaTabuleiro] == AGUA) {
                        tabuleiroTemp[linhaTabuleiro][colunaTabuleiro] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    // Copia o tabuleiro temporário de volta para o original
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = tabuleiroTemp[i][j];
        }
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
    
    // Exibe o tabuleiro inicial com os navios posicionados
    printf("\nTabuleiro de Batalha Naval (Inicial):\n");
    printf("0 = Agua, 3 = Navio\n");
    exibirTabuleiro(tabuleiro);
    
    // Cria as matrizes para as habilidades
    int matrizCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Inicializa as matrizes de habilidade
    criarMatrizCone(matrizCone);
    criarMatrizCruz(matrizCruz);
    criarMatrizOctaedro(matrizOctaedro);
    
    // Exibe as matrizes de habilidade para verificação
    printf("\n--- Matrizes de Habilidade ---\n");
    
    printf("\nHabilidade: Cone");
    exibirMatrizHabilidade(matrizCone);
    
    printf("\nHabilidade: Cruz");
    exibirMatrizHabilidade(matrizCruz);
    
    printf("\nHabilidade: Octaedro");
    exibirMatrizHabilidade(matrizOctaedro);
    
    // Define as coordenadas de origem para cada habilidade
    struct {
        int linha;
        int coluna;
        TipoHabilidade tipo;
    } habilidades[3] = {
        {2, 7, CONE},      // Habilidade Cone
        {5, 5, CRUZ},      // Habilidade Cruz
        {8, 8, OCTAEDRO}   // Habilidade Octaedro
    };
    
    // Cria tabuleiros separados para cada habilidade
    int tabuleiroCone[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiroCruz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiroOctaedro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Copia o tabuleiro original para cada tabuleiro de habilidade
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroCone[i][j] = tabuleiro[i][j];
            tabuleiroCruz[i][j] = tabuleiro[i][j];
            tabuleiroOctaedro[i][j] = tabuleiro[i][j];
        }
    }
    
    // Aplica cada habilidade em seu respectivo tabuleiro
    printf("\n--- Aplicando Habilidades ---\n");
    
    // Aplica a habilidade Cone
    aplicarHabilidade(tabuleiroCone, matrizCone, habilidades[0].linha, habilidades[0].coluna);
    printf("\nTabuleiro com Habilidade Cone na posicao (%d,%d):\n", 
           habilidades[0].linha, habilidades[0].coluna);
    printf("0 = Agua, 3 = Navio, 5 = Area da Habilidade\n");
    exibirTabuleiro(tabuleiroCone);
    
    // Aplica a habilidade Cruz
    aplicarHabilidade(tabuleiroCruz, matrizCruz, habilidades[1].linha, habilidades[1].coluna);
    printf("\nTabuleiro com Habilidade Cruz na posicao (%d,%d):\n", 
           habilidades[1].linha, habilidades[1].coluna);
    printf("0 = Agua, 3 = Navio, 5 = Area da Habilidade\n");
    exibirTabuleiro(tabuleiroCruz);
    
    // Aplica a habilidade Octaedro
    aplicarHabilidade(tabuleiroOctaedro, matrizOctaedro, habilidades[2].linha, habilidades[2].coluna);
    printf("\nTabuleiro com Habilidade Octaedro na posicao (%d,%d):\n", 
           habilidades[2].linha, habilidades[2].coluna);
    printf("0 = Agua, 3 = Navio, 5 = Area da Habilidade\n");
    exibirTabuleiro(tabuleiroOctaedro);
    
    return 0;
}