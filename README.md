# Batalha Naval com Habilidades Especiais

Este projeto implementa um jogo de Batalha Naval em C com funcionalidades avançadas, incluindo posicionamento de navios em diversas orientações e habilidades especiais com diferentes áreas de efeito.

## Características

### Tabuleiro e Navios
- Tabuleiro 10x10
- Navios com tamanho fixo de 3 posições
- Quatro orientações para posicionamento dos navios:
  - Vertical
  - Horizontal
  - Diagonal Descendente
  - Diagonal Ascendente
- Validação de posições para evitar sobreposições e limites do tabuleiro

### Habilidades Especiais
O jogo implementa três tipos de habilidades especiais, cada uma com uma área de efeito distinta:

1. **Cone**
   - Forma de cone expandindo-se de cima para baixo
   - Ponto de origem no topo do cone

2. **Cruz**
   - Forma de cruz com linhas horizontais e verticais
   - Ponto de origem no centro da cruz

3. **Octaedro**
   - Forma de losango (vista frontal de um octaedro)
   - Ponto de origem no centro do losango

## Representação Visual

No tabuleiro, os elementos são representados pelos seguintes valores:
- `0`: Água
- `3`: Navio
- `5`: Área afetada por uma habilidade especial

## Demonstração

O programa demonstra:
1. Posicionamento dos navios em diferentes orientações
2. Visualização das matrizes de cada habilidade especial
3. Aplicação das habilidades em diferentes posições do tabuleiro
4. Exibição do tabuleiro com as áreas afetadas pelas habilidades

## Estrutura do Código

### Principais Constantes
```c
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Tamanho fixo dos navios (3 posicoes)
#define AGUA 0                // Valor para representar agua no tabuleiro
#define NAVIO 3               // Valor para representar navios no tabuleiro
#define HABILIDADE 5          // Valor para representar área afetada por habilidade
#define TAMANHO_HABILIDADE 5  // Tamanho das matrizes de habilidade (5x5)
```

### Enumerações
- `Orientacao`: Define as orientações dos navios (HORIZONTAL, VERTICAL, DIAGONAL_DESCENDENTE, DIAGONAL_ASCENDENTE)
- `TipoHabilidade`: Define os tipos de habilidades (CONE, CRUZ, OCTAEDRO)

### Principais Funções
- `inicializarTabuleiro()`: Inicializa o tabuleiro com água
- `posicaoValida()`: Verifica se uma posição é válida para posicionar um navio
- `posicionarNavio()`: Posiciona um navio no tabuleiro
- `exibirTabuleiro()`: Exibe o tabuleiro no console
- `criarMatrizCone()`: Cria a matriz para a habilidade Cone
- `criarMatrizCruz()`: Cria a matriz para a habilidade Cruz
- `criarMatrizOctaedro()`: Cria a matriz para a habilidade Octaedro
- `exibirMatrizHabilidade()`: Exibe uma matriz de habilidade
- `aplicarHabilidade()`: Aplica uma habilidade ao tabuleiro

## Como Compilar e Executar

1. Certifique-se de ter um compilador C instalado (como GCC)
2. Compile o código:
   ```bash
   gcc batalha_naval.c -o batalha_naval
   ```
3. Execute o programa:
   ```bash
   ./batalha_naval
   ```

## Exemplo de Saída

O programa exibirá:
1. Informações sobre o posicionamento dos navios
2. O tabuleiro inicial com navios
3. Visualização das matrizes de habilidade
4. Três tabuleiros separados, cada um mostrando o efeito de uma habilidade específica

## Possíveis Melhorias Futuras

- Interface gráfica para melhor visualização
- Implementar lógica de jogo completa com jogadores e turnos
- Permitir entrada do usuário para posicionar navios e acionar habilidades
- Adicionar mais tipos de navios com tamanhos diferentes
- Implementar sistema de pontuação e condições de vitória
