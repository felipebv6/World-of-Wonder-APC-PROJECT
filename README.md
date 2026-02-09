Words of Wonder - Terminal Game 

Este é um jogo de palavras cruzadas desenvolvido inteiramente em C como projeto final para a disciplina de Algoritmos e Programação de Computadores (APC) no curso de Ciência da Computação. O objetivo é desafiar o jogador a encontrar palavras ocultas a partir de um conjunto de letras embaralhadas.

- O Jogo

O Words of Wonder apresenta uma interface via terminal onde o jogador:

Visualiza uma matriz de letras embaralhadas.

Deve adivinhar quais palavras podem ser formadas com aquelas letras.

Ganha pontos por acertos (+100) e perde por erros ou palavras repetidas (-10).

Possui um sistema de Ranking persistente para competir com outros jogadores.

- Funcionalidades

Sistema de Fases: As palavras e letras são carregadas dinamicamente de um arquivo de texto (entrada.txt).

Ranking Binário: As pontuações são salvas em um arquivo binário (ranking.bin), garantindo que os dados não se percam ao fechar o programa.

Ordenação de Dados: Utiliza o algoritmo Bubble Sort para exibir os melhores jogadores no topo do ranking.

Multiplataforma: Macros de pré-processamento para garantir que o comando de "limpar tela" funcione tanto em Windows quanto em Linux.

- Importância para o Aprendizado (APC)

Desenvolver este projeto foi fundamental para consolidar conceitos abstratos vistos em sala de aula através da prática direta:

Manipulação de Arquivos: Pratiquei a leitura de arquivos de texto com fscanf para as fases e a escrita/leitura de arquivos binários com fwrite e fread para o sistema de ranking.

Structs e Tipos de Dados: O uso de typedef struct foi essencial para organizar as informações do jogador, das fases e das palavras encontradas em blocos lógicos.

Lógica de Vetores e Matrizes: A exibição visual das letras exigiu uma manipulação precisa de matrizes bidimensionais e strings (vetores de char).

Algoritmos de Ordenação: Implementar o Bubble Sort manualmente para o ranking ajudou a entender como a ordenação funciona "por baixo do capô" na computação.

- Como Executar

Certifique-se de ter um compilador C (como o GCC) instalado.

Clone o repositório.

Certifique-se de que o arquivo entrada.txt esteja no mesmo diretório.

Compile o código.
gcc PROJETOAPC.C -o wow_game

Execute o programa.
./wow_game
