#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "avl.h"
#define AVL_TREE 1

struct set_
{
  AVL *avl_tree;
  int tipo;
};

SET *set_criar(int estrutura)
{
  SET *set = (SET *)malloc(sizeof(SET));
  if (set != NULL)
  {
    if (estrutura == 1)
    {
      set->tipo = estrutura;
      set->avl_tree = avl_criar();
    }
    else
    {
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
    arvB_inserir(conjunto->avl_tree, chave);
  }
}
void set_imprimir(SET *conjuntO)
{
  if (conjuntO != NULL)
  {
    arvB_percurso(conjuntO->avl_tree, 1);
  }
}

void set_pertence(SET *set, int chave)
{
  if (set != NULL)
  {
    if (arvB_busca(set->avl_tree, chave))
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