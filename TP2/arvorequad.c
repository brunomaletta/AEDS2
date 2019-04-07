#include "arvorequad.h"
#include <stdlib.h>
#include <stdio.h>

Ponto novo_ponto(int x, int y) {
	Ponto A;
	A.x = x;
	A.y = y;
	return A;
}

Estrela nova_estrela(int peso, Ponto P) {
	Estrela E;
	E.peso = peso;
	E.P = P;
	return E;
}

Lista* nova_lista() {
	Lista* L = (Lista*) malloc(sizeof(Lista));
	L->head = (node*) malloc(sizeof(node));

	L->head->next = NULL;
	L->tail = L->head;

	L->size = 0;

	return L;
}

Quadrante* novo_quadrante(Ponto baixo_esq, Ponto cima_dir) {
	Quadrante* Q = (Quadrante*) malloc(sizeof(Quadrante));

	Q->NE = Q->NW = Q->SE = Q->SW = NULL;

	Q->estrelas = nova_lista();

	Q->cima_dir = cima_dir;
	Q->baixo_esq = baixo_esq;

	Q->centro.x = (cima_dir.x + baixo_esq.x) / 2;
	Q->centro.y = (cima_dir.y + baixo_esq.y) / 2;

	Q->peso = 0;

	return Q;
}

void insere_estrela(Quadrante* Q, Estrela E) {
	Lista* L = Q->estrelas;

	L->tail->next = (node*) malloc(sizeof(node));

	L->tail->next->star = E;
	L->tail->next->next = NULL;

	L->tail = L->tail->next;
	L->size += 1;

	Q->peso += E.peso;
}

void divide_estrelas(Quadrante* Q) {
	// ponteiros para o final das listas de cada quadrante filho
	node* n_NE = Q->NE->estrelas->head;
	node* n_NW = Q->NW->estrelas->head;
	node* n_SE = Q->SE->estrelas->head;
	node* n_SW = Q->SW->estrelas->head;

	// itera pelas estrelas
	for (node* n = Q->estrelas->head->next; n != NULL; n = n->next) {
		int x = n->star.P.x;
		int y = n->star.P.y;

		// coloca a celula atual no final da lista do quadrante filho a que ela pertence
		if (x >= Q->centro.x) {
			if (y >= Q->centro.y) {
				n_NE->next = n; 

				Q->NE->estrelas->tail = n; 	// NE
				Q->NE->estrelas->size += 1;

				Q->NE->peso += n->star.peso;

				n_NE = n_NE->next;
			} else {
				n_SE->next = n;

				Q->SE->estrelas->tail = n; 	// SE
				Q->SE->estrelas->size += 1;

				Q->SE->peso += n->star.peso;

				n_SE = n_SE->next;
			}
		} else {
			if (y >= Q->centro.y) {
				n_NW->next = n;

				Q->NW->estrelas->tail = n; 	// NW
				Q->NW->estrelas->size += 1;

				Q->NW->peso += n->star.peso;

				n_NW = n_NW->next;
			} else {
				n_SW->next = n;

				Q->SW->estrelas->tail = n; 	// SW
				Q->SW->estrelas->size += 1;

				Q->SW->peso += n->star.peso;

				n_SW = n_SW->next;
			}
		}
	}

	// finaliza cada lista
	n_NE->next = n_NW->next = n_SE->next = n_SW->next = NULL;

	// lista do quadrante atual termina vazia
	Q->estrelas->head->next = NULL;
	Q->estrelas->tail = Q->estrelas->head;
}

void particiona(Quadrante* Q) {
	// quadrante nao precisa ser particionado
	if (Q->estrelas->size <= 1) return;
	if (Q->cima_dir.x - Q->baixo_esq.x <= 1 && Q->cima_dir.y - Q->baixo_esq.y <= 1) return;

	// cria quadrantes filhos
	Q->NE = novo_quadrante(Q->centro, Q->cima_dir);
	Q->NW = novo_quadrante(novo_ponto(Q->baixo_esq.x, Q->centro.y), novo_ponto(Q->centro.x, Q->cima_dir.y));
	Q->SE = novo_quadrante(novo_ponto(Q->centro.x, Q->baixo_esq.y), novo_ponto(Q->cima_dir.x, Q->centro.y));
	Q->SW = novo_quadrante(Q->baixo_esq, novo_ponto(Q->centro.x, Q->centro.y));

	// divide estrelas do quadrante atual para os filhos
	divide_estrelas(Q);

	// particiona filhos
	if (Q->NE->estrelas->size > 1) particiona(Q->NE);
	if (Q->NW->estrelas->size > 1) particiona(Q->NW);
	if (Q->SE->estrelas->size > 1) particiona(Q->SE);
	if (Q->SW->estrelas->size > 1) particiona(Q->SW);
}

void printa(Quadrante* Q) {
	// quadrante nao eh uma folha -> printa os filhos primeiro
	if (Q->estrelas->size > 1 &&
			(Q->cima_dir.y - Q->baixo_esq.y > 1 || Q->cima_dir.x - Q->baixo_esq.x > 1)) {
		printa(Q->NE);
		printa(Q->NW);
		printa(Q->SW);
		printa(Q->SE);
	}

	printf("(%d, %d) %d\n", Q->centro.x, Q->centro.y, Q->peso);
}

void libera(Quadrante* Q) {
	// libera lista de estrelas
	for (node* n = Q->estrelas->head; n != NULL;) {
		node* aux = n->next;
		free(n);
		n = aux;
	}
	free(Q->estrelas);

	// libera filhos, se eles estao alocados
	if (Q->NE) libera(Q->NE);
	if (Q->NW) libera(Q->NW);
	if (Q->SE) libera(Q->SE);
	if (Q->SW) libera(Q->SW);

	// libera quadrante
	free(Q);
}
