# 🛳️ Batalha Naval em C

Este projeto implementa a lógica básica do jogo Batalha Naval usando a linguagem C. O foco principal está no posicionamento de navios em um tabuleiro 10x10 e na visualização desse tabuleiro no console.

## 📋 Funcionalidades

- Inicialização do tabuleiro com água (valor 0)
- Verificação de posições válidas para navios (sem ultrapassar limites ou sobreposição)
- Posicionamento de navios vertical e horizontalmente
- Impressão do tabuleiro no terminal

## 🧠 Regras do Modelo Atual

- O tabuleiro tem tamanho fixo de 10x10.
- Cada navio ocupa 3 posições.
- A água é representada por `0` e os navios por `3`.

## 🔧 Como compilar

Certifique-se de ter um compilador C instalado, como o `gcc`.

```bash
gcc batalha_naval.c -o batalha_naval
