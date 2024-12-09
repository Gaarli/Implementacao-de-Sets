#ifndef AVL_H
#define AVL_H
#define max(a, b) ((a > b) ? a : b)

#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct avl AVL;

AVL *avl_criar(void);
bool alv_inserir(AVL *T, int chave);
void avl_imprimir(AVL *T);
void avl_apagar(AVL **T);
bool avl_remover(AVL *T, int chave);
bool avl_busca(AVL *T, int chave);
bool avl_vazia(AVL *T);
#endif