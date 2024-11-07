#ifndef SET_H
#define SET_H
#include <stdbool.h>
typedef struct set_ SET;

SET *set_criar(int estrutura);
bool set_apagar(SET **conjunto);
int set_remover_elemento(SET *conjunto, int chave);
void set_inserir_elemento(SET *conjunto, int chave);
void set_imprimir(SET *conjuntO);
void set_pertence(SET *set, int chave);
SET *set_uniao(SET *conjuntoA, SET *conjuntoB);
SET *interseccao(SET *conjuntoA, SET *conjuntoB);

#endif