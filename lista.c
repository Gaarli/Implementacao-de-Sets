#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

#ifndef STRUCTS_

#define STRUCTS_

struct lista_
{

  int lista[TAM_MAX];

  int inicio; // pos do primeiro item

  int fim; // pos do próximo espaço vazio

  int tamanho;
};

#endif

LISTA *lista_criar()
{
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
  if (lista != NULL)
  {
    lista->inicio = 0;
    lista->fim = 0;
    lista->tamanho = 0;

    return lista;
  }

  return NULL;
}
int lista_busca_ordenada(LISTA *lista, int chave)
{
  int inf = lista->inicio;
  int sup = lista->fim - 1; // fim é o próximo espaço vazio, então fim - 1 é o último item válido.
  int middle;

  if (lista != NULL && !lista_vazia(lista))
  {
    while (inf <= sup)
    {
      middle = (inf + sup) / 2;

      if (item_get_chave(lista->lista[middle]) == chave)
        return middle; // encontrou o item

      if (item_get_chave(lista->lista[middle]) > chave)
        sup = middle - 1;
      else
        inf = middle + 1;
    }
  }

  // Retorna 'inf', que será o local apropriado para inserção
  return inf;
}

bool lista_remover(LISTA *lista, int chave)
{
  if (lista == NULL || lista_vazia(lista))
  {
    return false; // Se a lista for nula ou estiver vazia, não há o que remover
  }

  // Busca pela posição do item usando a busca binária
  int pos = lista_busca_ordenada(lista, chave);

  // Verifica se o item na posição encontrada tem a chave que estamos buscando
  if (pos < lista->fim && item_get_chave(lista->lista[pos]) == chave)
  {
    // Item encontrado, agora precisaxmos remover
    int it = lista->lista[pos];
    free(lista->lista[pos]); // Libera a memória do item

    // Desloca todos os itens à direita da posição removida para a esquerda
    for (int i = pos; i < lista->fim - 1; i++)
    {
      lista->lista[i] = lista->lista[i + 1];
    }

    // Atualiza o fim e o tamanho da lista
    lista->fim--;
    lista->tamanho--;
    return it;
  }

  // Se a chave não foi encontrada
  return NULL;
}

bool lista_inserir(LISTA *lista, ITEM *item)
{
  if (lista != NULL)
  {

    if (lista_vazia(lista))
    {
      lista->lista[lista->fim] = item;
      lista->tamanho++;
      lista->fim++;
      return true;
    }

    int i;
    int x = lista_busca_ordenada(lista, item_get_chave(item)); // busca o local de inserção

    if (!lista_cheia(lista)) // verifica se a lista não está cheia
    {
      for (i = lista->fim; i > x; i--) // desloca os elementos para a direita
      {
        lista->lista[i] = lista->lista[i - 1];
      }

      lista->lista[x] = item; // insere o novo item
      lista->tamanho++;
      lista->fim++;
      return true;
    }
  }

  return false;
}

void lista_apagar(LISTA **lista)
{
  if (*lista != NULL && lista != NULL)
  {
    int i;
    for (i = 0; i < (*lista)->tamanho; i++)
    {
      item_apagar(&((*lista)->lista[i]));
      free((*lista)->lista[i]);
      (*lista)->lista[i] = NULL;
    }

    free(*lista);
    *lista = NULL;
  }
}

int lista_tamanho(LISTA *lista)
{
  if (lista != NULL)
  {
    return (lista->tamanho);
  }
  return -1;
}
bool lista_vazia(LISTA *lista)
{
  if (lista != NULL)
    return (lista->tamanho == 0) ? true : false;

  return true;
}
bool lista_cheia(LISTA *lista)
{
  if (lista != NULL)
    return (lista->tamanho == TAM_MAX) ? true : false;

  return false;
}
void lista_imprimir(LISTA *lista)
{
  if (lista != NULL && !lista_vazia(lista))
  {
    int i;

    for (i = 0; i < lista->fim; i++)
    {
      printf(" [%d]; ", item_get_chave(lista->lista[i]));
    }
  }
}