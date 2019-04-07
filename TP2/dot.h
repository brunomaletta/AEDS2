#ifndef DOT_H
#define DOT_H

#include "arvorequad.h"
#include <stdio.h>
#include <string.h>

void imprimeArvoreQuadruplaEmArquivoDot(Quadrante* raiz, const char* nome_arquivo);
void imprimeQuadranteRecursivamente(Quadrante* Q, int nodeIndex, FILE* fout);

void imprimeArvoreQuadruplaEmArquivoDot(Quadrante* raiz, const char* nome_arquivo) {
		FILE* fout = fopen(nome_arquivo, "w");
		fprintf(fout, "digraph {\n");
		imprimeQuadranteRecursivamente(raiz, 0, fout);
		fprintf(fout, "\n}\n");
		fclose(fout);
}

void imprimeQuadranteRecursivamente(Quadrante* Q, int nodeIndex, FILE* fout) {
	if (Q == NULL) return;
	fprintf(fout, "\"%d\"[shape=rect, label=\"Q%d \\n(%d, %d)\"]\n", nodeIndex, nodeIndex, Q->centro.x, Q->centro.y);
	if (Q->NE) fprintf(fout, "\"%d\" -> \"%d\"\n", nodeIndex, 4*nodeIndex + 1);
	if (Q->NW) fprintf(fout, "\"%d\" -> \"%d\"\n", nodeIndex, 4*nodeIndex + 2);
	if (Q->SW) fprintf(fout, "\"%d\" -> \"%d\"\n", nodeIndex, 4*nodeIndex + 3);
	if (Q->SE) fprintf(fout, "\"%d\" -> \"%d\"\n", nodeIndex, 4*nodeIndex + 4);
	imprimeQuadranteRecursivamente(Q->NE, 4*nodeIndex + 1, fout);
	imprimeQuadranteRecursivamente(Q->NW, 4*nodeIndex + 2, fout);
	imprimeQuadranteRecursivamente(Q->SW, 4*nodeIndex + 3, fout);
	imprimeQuadranteRecursivamente(Q->SE, 4*nodeIndex + 4, fout);
}

#endif
