#include "funcoes.h"
#include <stdio.h>

//--------funcao para o código-------
int seletor;
int continuar() {
  int option;
  printf("      Deseja Continuar [Sim = 1, Não = any]? ");
  scanf("%d", &option);
  if (option != 1) {
    seletor = 0;
  }
  return 0;
};
//---------------------------------------

int main(void) {
  struct Cliente cliente[1000];

  do {
    //------------Seletor---------------
    Menu();
    scanf("%d", &seletor);
    //----------------------------------
    switch (seletor) {
    case 1:
      Cadastrarcliente();
      continuar();      
      break;
    case 2:
      ApagarClientePorCPF();
      continuar();
      break;
    case 3:
      ListarTodos();
      continuar();
      break;
    case 4:
      Depositar();
      continuar();
      break;
    case 5:
      Debitar();
      continuar();
      break;
    case 6:
      Extrato();
      continuar();
      break;
    case 7:
      Transferir();
      continuar();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Digite uma opção válida");
      break;
    }
  } while (seletor != 0);
  return 0;
}