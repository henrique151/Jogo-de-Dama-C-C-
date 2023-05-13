#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

// Enumeração para as cores das peças
enum {EMPTY, RED, BLACK};

// Estrutura para representar uma peça
typedef struct {
    int color;
    int is_king;
} Piece;

// Matriz para representar o tabuleiro
Piece board[BOARD_SIZE][BOARD_SIZE];

// Função para inicializar o tabuleiro com as peças nas posições corretas
void init_board() {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if ((i + j) % 2 == 0) {
                if (i < 3) {
                    board[i][j].color = BLACK;
                    board[i][j].is_king = 0;
                } else if (i > 4) {
                    board[i][j].color = RED;
                    board[i][j].is_king = 0;
                } else {
                    board[i][j].color = EMPTY;
                    board[i][j].is_king = 0;
                }
            } else {
                board[i][j].color = EMPTY;
                board[i][j].is_king = 0;
            }
        }
    }
}

// Função para exibir o tabuleiro na tela
void print_board() {
    int i, j;

    printf("  ");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].color == EMPTY) {
                printf(". ");
            } else if (board[i][j].color == RED) {
                if (board[i][j].is_king) {
                    printf("R ");
                } else {
                    printf("r ");
                }
            } else if (board[i][j].color == BLACK) {
                if (board[i][j].is_king) {
                    printf("B ");
                } else {
                    printf("b ");
                }
            }
        }
        printf("%d\n", i);
    }

    printf("  ");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

// Função para verificar se um movimento é válido
int is_valid_move(int x1, int y1, int x2, int y2, int turn) {
    // Verifique se as coordenadas estão dentro dos limites do tabuleiro
    if (x1 < 0 || x1 >= BOARD_SIZE || y1 < 0 || y1 >= BOARD_SIZE ||
        x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
        return 0;
    }

    // Verifique se a peça na posição de origem pertence ao jogador atual
    if (board[x1][y1].color != turn) {
return 0;
}

// Verifique se a posição de destino está vazia
if (board[x2][y2].color != EMPTY) {
    return 0;
}

// Verifique se o movimento é diagonal
if (abs(x2 - x1) != abs(y2 - y1)) {
    return 0;
}

// Verifique se o movimento é válido para a peça
if (!board[x1][y1].is_king && ((turn == RED && y2 < y1) || (turn == BLACK && y2 > y1))) {
    return 0;
}

// Verifique se o movimento é uma captura
if (abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
    int x_mid = (x1 + x2) / 2;
    int y_mid = (y1 + y2) / 2;
    if (board[x_mid][y_mid].color == EMPTY || board[x_mid][y_mid].color == turn) {
        return 0;
    }
}

return 1;
}

// Função para fazer um movimento
void make_move(int x1, int y1, int x2, int y2, int turn) {
// Faça o movimento
board[x2][y2] = board[x1][y1];
board[x1][y1].color = EMPTY;
// Verifique se a peça se tornou um rei
if ((turn == RED && x2 == 0) || (turn == BLACK && x2 == BOARD_SIZE - 1)) {
    board[x2][y2].is_king = 1;
}

// Se o movimento foi uma captura, remova a peça capturada
if (abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
    int x_mid = (x1 + x2) / 2;
    int y_mid = (y1 + y2) / 2;
    board[x_mid][y_mid].color = EMPTY;
    }
}

// Função para verificar se o jogo acabou
int is_game_over(int turn) {
int i, j;
int red_pieces = 0, black_pieces = 0;

// Contar as peças restantes de cada jogador
for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j].color == RED) {
            red_pieces++;
        } else if (board[i][j].color == BLACK) {
            black_pieces++;
        }
    }
}

// Verificar se um dos jogadores não tem mais peças
if (red_pieces == 0 || black_pieces == 0) {
    return 1;
}

// Verificar se um dos jogadores não tem mais movimentos
for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j].color == turn) {
            if (board[i][j].is_king) {
                 if (is_valid_move(i, j, i+1, j+1, turn) || is_valid_move(i, j, i+1, j-1, turn) ||
                    is_valid_move(i, j, i-1, j+1, turn) || is_valid_move(i, j, i-1, j-1, turn)) {
return 0;
}
} else {
if (turn == RED && (is_valid_move(i, j, i+1, j+1, turn) || is_valid_move(i, j, i+1, j-1, turn))) {
return 0;
} else if (turn == BLACK && (is_valid_move(i, j, i-1, j+1, turn) || is_valid_move(i, j, i-1, j-1, turn))) {
return 0;
}
}
}
}
}
return 1;

}

// Função principal do jogo
int main() {
int turn = RED;
int game_over = 0;
int x1, y1, x2, y2;

// Inicialize o tabuleiro
init_board();

while (!game_over) {
    // Imprima o tabuleiro
    print_board();

    // Obtenha o movimento do jogador atual
    printf("%s's turn\n", turn == RED ? "Red" : "Black");
    printf("Enter move: ");
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    // Verifique se o movimento é válido
    if (!is_valid_move(x1, y1, x2, y2, turn)) {
        printf("Invalid move\n");
        continue;
    }

    // Faça o movimento
    make_move(x1, y1, x2, y2, turn);

    // Troque o turno
    turn = (turn == RED ? BLACK : RED);

    // Verifique se o jogo acabou
    game_over = is_game_over(turn);
}

// Imprima o tabuleiro final e a mensagem de vitória
print_board();
printf("%s wins!\n", turn == RED ? "Black" : "Red");

return 0;
}
