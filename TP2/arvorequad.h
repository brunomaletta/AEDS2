#ifndef ARVOREQUAD_H
#define ARVOREQUAD_H

typedef struct {
	int x;
	int y;
} Ponto;

typedef struct {
	Ponto P;
	int peso;
} Estrela;

typedef struct node {
	struct node* next;
	Estrela star; // cada celula da lista possui uma estrela
} node;

typedef struct {
	node* head;
	node* tail;
	int size;
} Lista;

typedef struct Quadrante {
	struct Quadrante* NE;
	struct Quadrante* NW;
	struct Quadrante* SE;
	struct Quadrante* SW;

	Lista* estrelas; // lista de estrelas

	Ponto cima_dir; // quina superior direita do quadrante
	Ponto baixo_esq; // quina inferior esquerda do quadrante

	Ponto centro; // centro do quadrante

	int peso; // peso total do quadrante
} Quadrante;


Ponto novo_ponto(int, int); // cria ponto com coordenadas predefinidas

Estrela nova_estrela(int, Ponto); // cria estrela com peso e ponto

Lista* nova_lista(); // cria lista vazia

Quadrante* novo_quadrante(Ponto, Ponto); // cria quadrante de limites predefinidos

void insere_estrela(Quadrante*, Estrela); // insere estrela no quadrante

void divide_estrelas(Quadrante*); // divide estrelas entre os filhos

void particiona(Quadrante*); // particiona recursivamente o quadrante

void printa(Quadrante* Q); // printa quadrante recursivamente

void libera(Quadrante* Q); // libera quadrante recursivamente

#endif
