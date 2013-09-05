#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

struct matriz {
    int linha;
    int coluna;
    int plano;
    float*** valor;
}matriz;

// Cria a matriz[x][y][z]
Matriz* cria_matriz (int linha, int coluna, int plano){
    int i=0, j=0, k=0;
    Matriz* mat = (Matriz*)malloc(sizeof(Matriz));
    mat->linha = linha;
    mat->coluna = coluna;
    mat->plano = plano;
    mat->valor = (float***)malloc(plano*sizeof(float**));
    for (j=0; j<plano; j++){
        mat->valor[j] = (float**)malloc(linha*sizeof(float*));
        for (i=0; i<linha; i++){
            mat->valor[j][i] = (float*)malloc(coluna*sizeof(float));
        }
    }
    return mat;
}

// preenche a matriz com os elementos lidos do arquivo de entrada
void preenche_matriz(FILE* fd, Matriz* mat){
	int z=0, x=0, y=0;
	for (z = 0; z < mat->plano; z++){
		for (x = 0; x < mat->linha; x++){
			for (y = 0; y < mat->coluna; y++){
				float v=0;
				fscanf(fd, "%f", &v);
				atribui(mat, x, y, z, v);
			}
		}
	}
}

// Retorna o valor de um elemento, dado seu indice
float acessa_elemento (Matriz* mat, int x, int y, int z){
    if (x<0 || x>mat->linha || y<0 || y>mat->coluna || z<0 || z>mat->plano){
        printf("Indice do elemento eh invalido!\n");
        exit(1);
    }
    return (mat->valor[z][x][y]);
}

// Atribuir um valor a um elemento da matriz, dado seu indice
void atribui(Matriz* mat, int x, int y, int z, float v) {
    mat->valor[z][x][y] = v;
}

// Salva a matriz resultante no arquivo de saída
void grava_matriz(FILE *fd, Matriz* mat){
    int linha=0, coluna=0, plano=0;
    for (plano=0; plano<mat->plano; plano++){
        for (linha=0; linha<mat->linha; linha++){
            for (coluna=0; coluna<mat->coluna; coluna++){
                fprintf(fd, "%g ", mat->valor[plano][linha][coluna]);
            }
            fprintf(fd, "\n");
        }
    }
    fprintf(fd, "\n");
}

// Libera a memória depois de realizadas as operações
void libera_matriz (Matriz* mat) {
     int i=0, j=0;
     for (j=0; j<mat->plano; j++){
        for(i=0; i<mat->linha; i++) {
                free(mat->valor[j][i]);
        }
        free(mat->valor[j]);
     }
     free(mat->valor);
     free(mat);
}

// Soma as matrizes
Matriz* soma_matrizes(Matriz* A, Matriz* B){
int linha=0, coluna=0, plano=0, x=0, y=0, z=0;
float aux;
Matriz *C; 
    linha=A->linha;
    coluna=A->coluna;
    plano=A->plano;
        C=cria_matriz(linha, coluna, plano);
        for (z=0; z<plano; z++){
            for(x=0; x<linha; x++){
               for(y=0; y<coluna; y++){
                  aux=(acessa_elemento(A, x, y, z)) + (acessa_elemento(B, x, y, z));
                  atribui(C, x, y, z, aux);
               }
            }
        }
return (C);
}

// Subtrai as matrizes
Matriz* subtrai_matrizes(Matriz* A, Matriz* B){
int linha=0, coluna=0, plano=0, x=0, y=0, z=0;
float aux;
Matriz *C; 
    linha=A->linha;
    coluna=A->coluna;
    plano=A->plano;
        C=cria_matriz(linha, coluna, plano);
        for (z=0; z<plano; z++){
            for(x=0; x<linha; x++){
               for(y=0; y<coluna; y++){
                  aux=(acessa_elemento(A, x, y, z)) - (acessa_elemento(B, x, y, z));
                  atribui(C, x, y, z, aux);
               }
            }
        }
return (C);
}
