#ifndef TLISTA_H
#define TLISTA_H

typedef struct node node;
typedef struct List List;

struct node {
	node* next; // proxima celula
	List* answ; // respostas
	int id; // valor
};

struct List {
	node* head; // cabeca
	node* tail; // ultima celula
};

List* new_list(); // cria lista vazia

void add(List*, int); // adiciona uma celula no final da lista

int answ(List*, int, int); // responde um comentario

void clear(List*); // apaga uma lista

int remove_comment(List*, int); // apaga um comentario

void print_tab(List*, FILE*, int); // printa lista com tabulacao

void print_line(List*, FILE*, int); // printa lista em uma linha

void print(List*, FILE*); // printa lista

void swap(node*); // troca as duas celulas seguintes a atual

void bouble(List*, int); // bouble sort

void sort(List*); // ordena lista e sublistas

#endif
