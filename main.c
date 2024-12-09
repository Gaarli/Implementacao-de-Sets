#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "avl.h"
#include "LLRBT.h"

int main()
{

  int num;
  SET *setA;
  SET *setB;

  setA = set_criar(1);
  setB = set_criar(1);

  for (int i = 0; i < 5; i++)
  {
    scanf("%d", &num);
    set_inserir_elemento(setA, num);
  }

  set_pertence(setA, 6);
  set_pertence(setA, 7);
  set_pertence(setA, 1);

  set_imprimir(setA);
  return 0;
}
