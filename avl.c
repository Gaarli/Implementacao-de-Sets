#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"

typedef struct no NO;

struct no
{
  int chave;
  NO *fleft;
  NO *fright;
  int altura;
};
struct avl
{
  NO *raiz;
  int profundidade;
};

AVL *avl_criar(void)
{

  AVL *T = (AVL *)malloc(sizeof(AVL));
  if (T != NULL)
  {
    T->profundidade = -1;
    T->raiz = NULL;

    return T;
  }
}

NO *avl_cria_no(int chave)
{
  NO *no = (NO *)malloc(sizeof(NO));
  if (no != NULL)
  {
    no->chave = chave;
    no->fleft = NULL;
    no->fright = NULL;
    no->altura = 0;
    return no;
  }
  return NULL;
}

int avl_altura_no(NO *raiz) // altura do nó
{
  if (raiz == NULL)
    return -1;
  else
    return raiz->altura;
}
int altura(NO *raiz) // calcula a altura da árvore
{
  if (raiz == NULL)
    return -1;
  else
  {
    int left = altura(raiz->fleft);
    int right = altura(raiz->fright);
    return (left > right) ? left + 1 : right + 1;
  }
}

NO *avl_inseri_no(NO *raiz, int chave)
{
  if (raiz == NULL)
    raiz = avl_cria_no(chave);
  else if (chave < raiz->chave)
    raiz->fleft = avl_inseri_no(raiz->fleft, chave);
  else if (chave > raiz->chave)
    raiz->fright = avl_inseri_no(raiz->fleft, chave);

  // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
  raiz->altura = max(avl_altura_no(raiz->fleft), avl_altura_no(raiz->fright)) + 1;

  raiz = avl_balancear(raiz);
  return raiz;
}
bool alv_inserir(AVL *T, int chave)
{
  if (T != NULL)
  {
    return ((T->raiz = avl_inserir_no(T->raiz, chave)) != NULL);
  }
}
NO *rotacaoDir(NO *a)
{
  NO *b;

  b = a->fleft;
  a->fleft = b->fright;
  b->fright = a;
  a->altura = max(avl_altura_no(a->fleft), avl_altura_no(a->fright)) + 1;
  b->altura = max(avl_altura_no(b->fleft), avl_altura_no(b->fright)) + 1;

  return b;
}
NO *rotacaoEsq(NO *a)
{
  NO *b;

  b = a->fright;
  a->fright = b->fleft;
  b->fleft = a;
  a->altura = max(avl_altura_no(a->fleft), avl_altura_no(a->fright)) + 1;
  b->altura = max(avl_altura_no(b->fleft), avl_altura_no(b->fright)) + 1;

  return b;
}
NO *rotacaoEsqDir(NO *a)
{
  a->fleft = rotacaoEsq(a->fleft);
  return rotacaoDir(a);
}
NO *rotacaoDirEsq(NO *a)
{
  a->fright = rotacaoDir(a->fright);
  return rotacaoEsq(a);
}

int fator_balanceamento(NO *raiz)
{
  if (raiz)
    return (avl_altura_no(raiz->fleft) - avl_altura_no(raiz->fright));
  else
    return 0;
}
NO *avl_balancear(NO *raiz)
{

  int FB = fator_balanceamento(raiz);

  // Rotação à esquerda
  if (FB < -1 && fatorDeBalanceamento(raiz->fright) <= 0)
    raiz = rotacaoEsquerda(raiz);

  // Rotação à direita
  else if (FB > 1 && fatorDeBalanceamento(raiz->fleft) >= 0)
    raiz = rotacaoDireita(raiz);

  // Rotação dupla à esquerda
  else if (FB > 1 && fatorDeBalanceamento(raiz->fleft) < 0)
    raiz = rotacaoEsquerdaDireita(raiz);

  // Rotação dupla à direita
  else if (FB < -1 && fatorDeBalanceamento(raiz->fright) > 0)
    raiz = rotacaoDireitaEsquerda(raiz);

  return raiz;
}

void avl_apagar_nos(NO **raiz)
{
  if ((*raiz) != NULL)
  {
    avl_apagar(&(*raiz)->fleft);
    avl_apagar(&(*raiz)->fright);
    // item_apagar(&(*raiz)->item);
    free(*raiz);
    *raiz = NULL;
  }
};
void avl_apagar(AVL **T)
{
  if (*(T) != NULL)
  {
    avl_apagar_nos(&(*T)->raiz);
    free(*T);
    *T = NULL;
  }
}
void troca_left_max(NO *change, NO *raiz, NO *previous)
{
  if (change->fright != NULL)
  {
    troca_left_max(change->fright, raiz, change);
    return;
  }
  if (raiz == previous)
    previous->fleft = change->fleft;
  else
    previous->fright = change->fleft;

  raiz->chave = change->chave;
  free(change);
  change = NULL;
}

bool avl_remover_no(NO **raiz, int chave)
{
  if ((*raiz) == NULL)
    return false;
  if (item_get_chave((*raiz)->chave) == chave)
  {
    if ((*raiz)->fleft == NULL || (*raiz)->fright == NULL) // pega o 1 e 2 caso, 1 filho ou é folha
    {
      NO *p = (*raiz);
      if ((*raiz)->fleft == NULL)
        (*raiz) = (*raiz)->fright;
      else
        (*raiz) = (*raiz)->fleft;

      free(p);
      p = NULL;
    }
    else // 3 caso, tem 2 filhos
      troca_left_max((*raiz)->fleft, (*raiz), (*raiz));
  }
  else if (chave < item_get_chave((*raiz)->chave))
    return abb_remover_no(&(*raiz)->fleft, chave);
  else
    return abb_remover_no(&(*raiz)->fright, chave);

  (*raiz)->altura = max(avl_altura_no((*raiz)->fleft), avl_altura_no((*raiz)->fright)) + 1;

  raiz = avl_balancear(raiz);

  return true;
}
bool avl_remover(AVL *T, int chave)
{
  if (T != NULL)
    return abb_remover_no(&(T)->raiz, chave);

  return false;
}
bool busca_no(NO *raiz, int chave)
{
  while (raiz != NULL)
  {
    if (chave < raiz->chave)
      raiz = raiz->fleft;
    else if (chave > raiz->chave)
      raiz = raiz->fright;
    else
      return true;
  }
  return false;
}
bool arvB_busca(AVL *T, int chave)
{
  return (busca_no(T->raiz, chave));
}

bool avl_vazia(AVL *T)
{
  if (T != NULL)
  {
    return (T->raiz == NULL) ? true : false;
  }
}
void avl_imprimir(AVL *T)
{
}