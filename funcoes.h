#include <stdbool.h>

struct Cliente {
  char Tipo_Solicitacao[50];
  int cpf;
  char nome_cliente[100];
  char tipo_conta[50];
  int senha;
  float saldo;
};

int Menu();
void Cadastrarcliente();
void ApagarClientePorCPF();
void ListarTodos();
void Depositar();
bool verificarCPFExistente(int cpf);
bool verificaCPFesenha(int cpf, int senha);
void Debitar();

