#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(int argc, char *argv[]) {

    // Verificando se os arquivos foram passados como parametros
    if (argc<3){
       printf("Forneca os arquivos de entrada e saida de dados!\n");
       exit(1);
    }

    int instancias = 0, i = 0, indice=0, linha = 0, coluna = 0, plano = 0;
    FILE *input, *output;
    Matriz *A, *B, *C;
    char operador[1];

    // Arquivo de entrada.
    input = fopen(argv[1], "r");
        
    if (input == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    // Arquivo de saída
    output = fopen(argv[2], "w");

    // Pegando o número de instancias
    fscanf(input, "%d", &instancias);

    if (feof(input)){
	printf("Arquivo de entrada vazio!\n");
	fclose(output);
	fclose(input);
	exit(1);
    }

    indice = instancias;

    // Para cada instancia, realiza as operações de soma/subtração
    for (i = 0; i < indice; i++) {
        
        fscanf(input, "%d %d %d", &plano, &linha, &coluna);

        A = cria_matriz(linha, coluna, plano);
        
	//Preenche a matriz com os elementos do arquivo
	preenche_matriz(input, A);

        // Verificando o primeiro operador
        fscanf(input, "%s", &operador[0]);

        // Enquanto o operador for diferente de =, lê as matrizes e o próximo operador
        while (operador[0] != '=') {
            if (operador[0] == '+') {
                B = cria_matriz(linha, coluna, plano);
                preenche_matriz(input, B);
                C = soma_matrizes(A, B);
                libera_matriz(A);
                A = C;
            }
            if (operador[0] == '-') {
                B = cria_matriz(linha, coluna, plano);
                preenche_matriz(input, B);
                C = subtrai_matrizes(A, B);
                libera_matriz(A);
                A = C;
            }
            
            // Lê o próximo operador
            fscanf(input, "%s", &operador[0]);
        }
        
        // Grava matriz resultante no arquivo de saída
        grava_matriz(output, A);        
    }
    
    // Libera memória utilizada pelas matrizes A e C
    libera_matriz(C);
    
    // Libera memória utilizada pela matriz B
    libera_matriz(B);
    
    fclose(input);
    fclose(output);

    return (EXIT_SUCCESS);
}


