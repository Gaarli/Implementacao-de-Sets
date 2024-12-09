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
  int FB;
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

NO *avl_cria_no(int chave)
{
  NO *no = (NO *)malloc(sizeof(NO));
  if (no != NULL)
  {
    no->chave = chave;
    no->fleft = NULL;
    no->fright = NULL;
    no->FB = 0;
    no->altura = 0;
    return no;
  }
  return NULL;
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
  // raiz->altura = max(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

  raiz = avl_balanceamento(raiz);
  return raiz;
}
NO *rotacaoDir(NO *a)
{
  NO *b;

  b = a->fleft;
  a->fleft = b->fright;
  b->fright = a;
  // a->altura = max(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  // b->altura = max(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  a->FB = b->FB = 0;
  return b;
}
NO *rotacaoEsq(NO *a)
{
  NO *b;

  b = a->fright;
  a->fright = b->fleft;
  b->fleft = a;
  // a->altura = max(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  // b->altura = max(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  a->FB = b->FB = 0;
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
NO *avl_balanceamento(NO *raiz)
{
  raiz->FB = (avl_altura_no(raiz->fleft)) - (avl_altura_no(raiz->fright));
  if (raiz->FB == -2)
    if (raiz->fright->FB <= 0)
      raiz = rodar_esquerda(raiz);
    else
      raiz = rodar_direita_esquerda(raiz);
  if (raiz->FB == 2)
    if (raiz->fleft->FB >= 0)
      raiz = rodar_direita(raiz);
    else
      raiz = rodar_esquerda_direita(raiz);

  return raiz;
}
bool alv_inserir(AVL *T, int chave)
{
  if (T != NULL)
  {
    return ((T->raiz = avl_inserir_no(T->raiz, chave)) != NULL);
  }
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

  if ((*raiz) != NULL)
    (*raiz) = avl_balanceamento((*raiz));

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