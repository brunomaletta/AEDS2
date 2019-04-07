#include <stdio.h>
#include <stdlib.h>

#include "TLista.h"

List* new_list() {
	List* ret = (List*) malloc(sizeof(List));
	ret->head = (node*) malloc(sizeof(node));
	ret->tail = ret->head;
	ret->head->next = NULL;
	return ret;
}

void add(List* L, int id) {
	node* n = L->tail; // n: ultima celula da lista

	n->next = (node*) malloc(sizeof(node));
	n->next->id = id;
	n->next->answ = new_list();
	n->next->next = NULL;

	L->tail = n->next;
}

int answ(List* L, int id1, int id2) {
	for (node* n = L->head->next; n != NULL; n = n->next) { // itera pela lista
		if (n->id == id1) {
			add(n->answ, id2); // achou -> adiciona
			return 1;
		}
		if (answ(n->answ, id1, id2)) return 1; // tenta responder recursivamente
	}
	return 0; // nao achou -> retorna 0
}

void clear(List* L) {
	for (node* n = L->head->next; n != NULL; ) { // itera pela lista
		node* tmp = n->next;
		clear(n->answ); // apaga respostas recursivamente
		free(n);
		n = tmp;
	}
	free(L->head);
	free(L);
}

int remove_comment(List* L, int id) {
	node* prev = L->head;
	for (node* n = L->head->next; n != NULL; prev = n, n = n->next) { // itera pela lista

		// achou
		if (n->id == id) {
			if (n == L->tail) L->tail = prev; // apaga ultimo

	 		prev->next = n->next;
			clear(n->answ); 		// apaga respostas
			free(n); 			// apaga comentario
			return 1;
		}

		// tenta apagar recursivamente
		if (remove_comment(n->answ, id)) return 1;
	}
	return 0; // nao achou -> retorna 0
}

void print_tab(List* L, FILE* f, int tab) { // printa lista com tabulacao
	for (node* n = L->head->next; n != NULL; n = n->next) {
		for (int j = 0; j < tab; j++) fprintf(f, "---");
		fprintf(f, "%d\n", n->id);
		print_tab(n->answ, f, tab + 1); // printa sublistas
	}
}

void print_line(List* L, FILE* f, int first) { // printa lista em uma linha
	for (node* n = L->head->next; n != NULL; n = n->next) {
		if (first) {
			fprintf(f, "%d", n->id);
			first = 0;
		} else fprintf(f, " %d", n->id);
		print_line(n->answ, f, 0); // printa sublistas
	}
}

void print(List* L, FILE* f) {
	print_line(L, f, 1);
}

void swap(node* prev) { // troca prev->next e prev->next->next
	node* k  = prev->next->next;
	prev->next->next = prev->next->next->next;
	k->next = prev->next;
	prev->next = k;
}

void bouble(List* L, int size) { // bouble sort
	if (size <= 1) return;

	int changed = 0;

	node* n = L->head;
	for (int i = 0; i < size - 1; i++, n = n->next) { // itera pela lista ate size
		if (n->next->id > n->next->next->id) {
			swap(n);
			changed = 1;
		}
	}

	// ordena ate size - 1
	if (changed) bouble(L, size - 1);
}

void sort(List* L) {

	// descobre tamanho
	int size = 0;
	for (node* n = L->head->next; n != NULL; n = n->next) size++;

	// ordena lista
	bouble(L, size);

	// ajusta 'tail'
	for (node* n = L->head; n != NULL; n = n->next) L->tail = n;

	// ordena sublistas
	for (node* n = L->head->next; n != NULL; n = n->next) sort(n->answ);
}
