
#ifndef LISTA_H
#define LISTA_H

#define TAM_MAX 50000 /*estimativa do tamanho máximo da lista*/
#define inicial 0
#define ERRO -32000
#define ORDENADA 1 // 0 = lista não ordenada, 1 = lista ordenada

typedef struct lista_ LISTA;
LISTA *lista_criar(void);
bool lista_remover(LISTA *lista, int chave);
bool lista_inserir(LISTA *lista, int chave);
void lista_apagar(LISTA **lista);
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);

#endif