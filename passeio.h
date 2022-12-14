#ifndef PASSEIO_H
#define PASSEIO_H

#define M 7
#define N 6

void print_tabuleiro(int tabuleiro[N][M]);

int jogada_valida(int x, int y, int tabuleiro[N][M]);

int passeio_cavalo_seq(int tabuleiro[N][M], int x, int y, int jogada);

int passeio_cavalo_par(int tabuleiro[N][M], int x, int y, int jogada);



#endif 