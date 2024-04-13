
#include "tarefas.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;
  while (1) {

    printf("Entre com a prioridade(1-10): ");
    scanf("%d", &tarefas[*pos].prioridade);
    if (tarefas[*pos].prioridade > 10 || tarefas[*pos].prioridade <= 0) {
      printf("Prioridade invalida tem que ser entre 1 a 10\n");
      continue;
    } else
      break;
  }

  clearBuffer();
  printf("Entre com a categoria: ");
  fgets(tarefas[*pos].categoria, TAM_CATEGORIA, stdin);
  tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

  printf("Entre com a descricao: ");
  fgets(tarefas[*pos].descricao, TAM_DESC, stdin);
  tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

  *pos = *pos + 1;

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
  // teste se existem tarefas
  if (*pos == 0)
    return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
  if (*pos == 0)
    return SEM_TAREFAS;
  char categoria[TAM_CATEGORIA];
  char teste[TAM_CATEGORIA];
  printf("Entre com a categoria: ");
  clearBuffer();
  fgets(categoria, TAM_CATEGORIA, stdin);
  categoria[strcspn(categoria, "\n")] = '\0';
  strcpy(teste, categoria);
  for (int i = 0; i < *pos; i++) {
    if (tarefas[i].categoria[i] == *teste) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
      return OK;
    } else if (*teste == '\0'){
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    } 
    
    else {
      printf("Nenhuma tarefa encontrada foi encontada nessa categoria \n");
      return OK;
    }
  }
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  return OK;
}


void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
