#ifndef ARVB_H
#define ARVB_H
#include "set.h"
#include <stdbool.h>
typedef struct ArvB ARVB;

ARVB *arvB_criar();
void arvB_inserir(ARVB *arvB, int chave);
ARVB *arvB_remover_no(ARVB *arvB, int chave);
ARVB *arvB_apagar(ARVB **arvB);
bool arvB_busca(ARVB *arvB, int chave);
void arvB_percurso(ARVB *arvB, int tipo);
ARVB *arvB_altura(ARVB *arvB);

#endif