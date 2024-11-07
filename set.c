#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "ArvB.h"
#define ARVBIN 1
struct set_
{
  ARVB *conjunto_arvB;
  int tipo;
};

SET *set_criar(int estrutura)
{
  SET *set = (SET *)malloc(sizeof(SET));
  if (set != NULL)
  {
    if (estrutura == ARVBIN)
    {
      set->tipo = estrutura;
      set->conjunto_arvB = arvB_criar();
    }
    return set;
  }

  return NULL;
}
bool set_apagar(SET **conjunto)
{
}
int set_remover_elemento(SET *conjunto, int chave)
{
}
void set_inserir_elemento(SET *conjunto, int chave)
{
  if (conjunto != NULL)
  {
    arvB_inserir(conjunto->conjunto_arvB, chave);
  }
}
void set_imprimir(SET *conjuntO)
{
  if (conjuntO != NULL)
  {
    arvB_percurso(conjuntO->conjunto_arvB, 1);
  }
}

void set_pertence(SET *set, int chave)
{
  if (set != NULL)
  {
    if (arvB_busca(set->conjunto_arvB, chave))
    {
      printf("\nPertence\n");
    }
    else
    {
      printf("\nNão pertence\n");
    }
  }
}
SET *set_uniao(SET *conjuntoA, SET *conjuntoB)
{
}
SET *interseccao(SET *conjuntoA, SET *conjuntoB)
{
}