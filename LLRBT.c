#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LLRBT.h"

typedef struct no NO;

struct no
{
  NO *left;
  NO *right;
  int cor; // 0 = preto 1 = Vermelho
  int chave;
};
struct llrbt
{
  NO *raiz;
  int profundidade;
};
