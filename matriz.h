#ifndef MATRIZ_H
#define	MATRIZ_H

    typedef struct matriz Matriz;
    
    Matriz* cria_matriz (int linha, int coluna, int plano);
    float acessa_elemento (Matriz* mat, int x, int y, int z);
    void atribui(Matriz* mat, int x, int y, int z, float v);
    void libera_matriz (Matriz* mat);
    Matriz* soma_matrizes(Matriz* A, Matriz* B);
    Matriz* subtrai_matrizes(Matriz* A, Matriz* B);
    void grava_matriz(FILE* fd, Matriz* mat);
    void preenche_matriz(FILE* fd, Matriz* mat);

#endif	/* MATRIZ_H */

