#include "tarefas.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  Tarefa tarefas[TOTAL];
  int pos;
  ERROS erro = fs[4](tarefas, &pos);
  if (erro != OK)
    pos = 0;

  int opcao;
  ERROS a;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    opcao--;
    if (opcao > 2)
      printf("Opcao invalida\n");
    else if (opcao >= 0) {
      a = fs[opcao](tarefas, &pos);
      switch (a) {
      case 0:
        printf("sem erros\n");
        break;
      case 1:
        printf("erro no maximo de tarefas\n");
        break;
      case 2:
        printf("erro na falta de tarefas\n");
        break;
      case 3:
        printf("arquivo não encontrado\n");
        break;
      case 4:
        printf("erro ao abrir o arquivo\n");
        break;
      case 5:
        printf("erro ao fechar o arquivo\n");
        break;
      case 6:
        printf("erro ao escrever no arquivo\n");
        break;
      case 7:
        printf("erro ao ler o arquivo\n");
        break;
      }
    } else
      printf("Sair...\n");

  } while (opcao >= 0);

  fs[3](tarefas, &pos);
}