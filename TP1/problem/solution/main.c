#include <stdlib.h>
#include <stdio.h>

#include "TLista.h"

#define MAX 1000

int read_id(int* i, char* s) {
	int id = 0;
	int tam = 0; // numero de caracteres do id
	for (; s[*i + 1 + tam] != '\0'; tam++) {

		// proximo caractere nao eh numero -> fim do id
		if (s[*i + 1 + tam] > '9' || s[*i + 1 + tam] < '0') break;

		id *= 10;
		id += s[*i + 1 + tam] - '0';
	}

	// pula 'tam' posicoes na string
	*i += tam;
	if (tam == 0) return -1;
	return id;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("ERRO: argumentos insuficientes\n");
		return 1;
	}

	// abre arquivos
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if (in == NULL || out == NULL) {
		printf("ERRO: arquivo de entrada nao encontrado\n");
		return 1;
	}

	char s[MAX];
	while (fscanf(in, " %[^\n]s", s) != EOF) { // le todas as linhas do arquivo
		List* list = new_list();
		for (int i = 0; s[i] != '\0'; i++) {
			int a, b;
			switch (s[i]) {
				case 'A': add(list, read_id(&i, s)); break;
				case 'R':
					    a = read_id(&i, s);
					    i++; // anda uma posicao por causa da virgula
					    b = read_id(&i, s);
					    answ(list, a, b);
					    break;
				case 'D': remove_comment(list, read_id(&i, s)); break;
			}
		}

		// printa lista
		print(list, out);

		fprintf(out, " - ");

		// printa lista ordenada
		sort(list);
		print(list, out);

		fprintf(out, "\n");

		// limpa lista
		clear(list);
	}

	// fecha os arquivos de entrada e saida
	fclose(in);
	fclose(out);

	return 0;
}
