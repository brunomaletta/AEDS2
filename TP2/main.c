#include <stdio.h>
#include <stdlib.h>

#include "arvorequad.h"
#include "dot.h"

int main() {
	int L, N; scanf("%d %d", &L, &N);

	// cria quadrante principal -> de (0, 0) a (L, L)
	Quadrante* Q = novo_quadrante(novo_ponto(0, 0), novo_ponto(L, L));

	// recebe e insere estrelas
	for (int i = 0; i < N; i++) {
		int x, y, p; scanf("%d %d %d", &x, &y, &p);

		if (x < 0 || y < 0 || x >= L || y >= L) continue; // estrela invalida

		insere_estrela(Q, nova_estrela(p, novo_ponto(x, y)));
	}

	particiona(Q);

	printa(Q);

	imprimeArvoreQuadruplaEmArquivoDot(Q, "meuarquivo.dot");

	libera(Q);

	return 0;
}
