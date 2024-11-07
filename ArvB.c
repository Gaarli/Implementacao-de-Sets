#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "ArvB.h"
#define PRE_ORDEM 0
#define EM_ORDEM 1
#define POS_ORDEM 2

typedef struct No NO;
struct No
{
  int chave;
  NO *left;
  NO *right;
};

struct ArvB
{
  int tam;
  NO *raiz;
  int profundidade;
};

// protótipos
NO *arvB_cria_no(int);
void arvB_PreOrdem(NO *);
void arvB_PosOrdem(NO *);
void arvB_EmOrdem(NO *);

ARVB *arvB_criar()
{

  ARVB *arvB = (ARVB *)malloc(sizeof(ARVB));
  if (arvB != NULL)
  {
    arvB->tam = 0;
    arvB->raiz = NULL;
    arvB->profundidade = -1;
    return arvB;
  }

  return NULL;
}
NO *arvB_cria_no(int chave)
{
  NO *new_no = (NO *)malloc(sizeof(NO));
  if (new_no != NULL)
  {
    new_no->chave = chave;
    new_no->left = NULL;
    new_no->right = NULL;
    return new_no;
  }
}

/*Ainda não é o método mais eficiente*/
NO *inserir_no(NO *raiz, int chave)
{
  if (raiz == NULL)
  {
    return arvB_cria_no(chave);
  }
  else
  {
    if (chave < raiz->chave)
    {
      raiz->left = inserir_no(raiz->left, chave);
    }
    else if (chave > raiz->chave)
    {
      raiz->right = inserir_no(raiz->right, chave);
    }

    return raiz;
  }
}
void arvB_inserir(ARVB *arvB, int chave)
{
  if (arvB != NULL)
  {
    arvB->raiz = inserir_no(arvB->raiz, chave);
  }
}

bool busca_no(NO *raiz, int chave)
{
  while (raiz != NULL)
  {
    if (chave < raiz->chave)
      raiz = raiz->left;
    else if (chave > raiz->chave)
      raiz = raiz->right;
    else
      return true;
  }
  return false;
}
bool arvB_busca(ARVB *arvB, int chave)
{
  return (busca_no(arvB->raiz, chave));
}

void arvB_EmOrdem(NO *raiz)
{
  if (raiz != NULL)
  {
    arvB_EmOrdem(raiz->left);
    printf(" [%d] ", raiz->chave);
    arvB_EmOrdem(raiz->right);
  }
}
void arvB_PreOrdem(NO *raiz)
{
  if (raiz != NULL)
  {
    printf(" [%d] ", raiz->chave);
    arvB_PreOrdem(raiz->left);
    arvB_PreOrdem(raiz->right);
  }
}
void arvB_PosOrdem(NO *raiz)
{
  if (raiz != NULL)
  {
    arvB_PosOrdem(raiz->left);
    arvB_PosOrdem(raiz->right);
    printf(" [%d] ", raiz->chave);
  }
}

void arvB_percurso(ARVB *arvB, int tipo)
{

  if (arvB != NULL)
  {
    if (tipo == PRE_ORDEM)
    {
      arvB_PreOrdem(arvB->raiz);
    }
    else if (tipo == EM_ORDEM)
    {
      arvB_EmOrdem(arvB->raiz);
    }
    else
    {
      arvB_PosOrdem(arvB->raiz);
    }
  }
}

ARVB *arvB_remover_no(ARVB *arvB, int chave);
ARVB *arvB_apagar(ARVB **arvB);
ARVB *arvB_altura(ARVB *arvB);
