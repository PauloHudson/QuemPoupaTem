#include "funcoes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Menu(continuar) {
  printf("\n");
  printf("          MENU PRINCIPAL:\n");
  printf("    Bem vindo ao banco QuemPoupaTem");
  printf("\n   +-------------------------------+ ");
  printf("\n   | (1) - Cadastrar novo cliente  |");
  printf("\n   | (2) - Apagar Cliente          |");
  printf("\n   | (3) - Listar                  |");
  printf("\n   | (4) - Depositar               |");
  printf("\n   | (5) - Debitar                 |");
  printf("\n   | (6) - Extrato                 |");
  printf("\n   | (7) - Transferir              |");
  printf("\n   | (0) - Sair                    |");
  printf("\n   +-------------------------------+ \n");
  printf("      OPÇÃO: ");
  return 0;
};

// ------CadastarCliente-----      até no máximo 1000 clientes
// Funcao que verificar se existe o cpf do usuario na lista de clientes, fiz ela
// pois aí economizaria código para não ter de criar todas as vezes a mesma
// coisa.

bool verificarCPFExistente(int cpf) {
  FILE *arquivo = fopen("dados.txt", "r");

  struct Cliente cliente;
  char linha[1000];
  bool cpfEncontrado = false;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha,
               "{\"nome\":\"%99[^\"]\", \"Tconta\":\"%49[^\"]\", \"cpf\":%d, "
               "\"Senha\":%d, \"Saldo\":%f}",
               cliente.nome_cliente, cliente.tipo_conta, &cliente.cpf,
               &cliente.senha, &cliente.saldo) == 5) {

      if (cpf == cliente.cpf) {

        cpfEncontrado = true;
        break;
      }
    }
  }

  fclose(arquivo);

  if (cpfEncontrado) {
    return true; //
  } else {
    return false; //
  }
}

void Cadastrarcliente() {
  struct Cliente cliente;

  // Abrir o arquivo em modo de anexação
  FILE *arquivo = fopen("dados.txt", "a");
  FILE *arquivo2 = fopen("extrato.txt", "a");

  if (arquivo == NULL || arquivo2 == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  // Template bonitinho:
  printf("\n   +-------------------------------+");
  printf("\n   |      CADASTRO DE CLIENTE      |");
  printf("\n   +-------------------------------+ \n\n");

  // Solicitar informações do cliente
  // aqui estamos colocando uma var que mostrará no extrato o que está
  // acontecendo!
  snprintf(cliente.Tipo_Solicitacao, sizeof(cliente.Tipo_Solicitacao),
           "Abertura");

  printf("      Digite seu Nome: ");
  scanf(" %[^\n]", cliente.nome_cliente);

  int cpf;
  printf("      Digite o CPF do cliente: ");
  scanf("%d", &cpf);

  if (verificarCPFExistente(cpf)) {
    printf("      Cliente já cadastrado!\n");
    fclose(arquivo);
    fclose(arquivo2);
    return;
  } else {
    cliente.cpf = cpf;
  }

  printf("      Digite o tipo de Conta: [Plus ou Comum] ");
  scanf(" %[^\n]", cliente.tipo_conta);

  printf("      Digite o valor inicial da conta: ");
  scanf("%f", &cliente.saldo);

  printf("      Digite uma senha de 6 dígitos [Números]: ");
  scanf("%d", &cliente.senha);

  // Salvar os dados do cliente no arquivo no formato JSON
  fprintf(arquivo,
          "{\"nome\":\"%s\", \"Tconta\":\"%s\", \"cpf\":%d, \"Senha\":%d, "
          "\"Saldo\":%.2f}\n",
          cliente.nome_cliente, cliente.tipo_conta, cliente.cpf, cliente.senha,
          cliente.saldo);
  // estamos colocando no extrato aqui!
  fprintf(arquivo2,
          "{\"TipoAction\":\"%s\",\"nome\":\"%s\", \"Tconta\":\"%s\", "
          "\"cpf\":%d, "
          "\"Senha\":%d, "
          "\"Saldo\":%.2f}\n",
          cliente.Tipo_Solicitacao, cliente.nome_cliente, cliente.tipo_conta,
          cliente.cpf, cliente.senha, cliente.saldo);

  fclose(arquivo);
  fclose(arquivo2);
  printf("\n   +--------------------------------+");
  printf("\n   | CLIENTE CADASTRADO COM SUCESSO |");
  printf("\n   +--------------------------------+ \n");
}

void ApagarClientePorCPF() {
  // template bonitinho:
  printf("\n   +-------------------------------+");
  printf("\n   |         APAGAR CLIENTE        |");
  printf("\n   +-------------------------------+ \n\n");

  int cpf_a_excluir;
  printf("      Digite o CPF do cliente a ser excluído: ");
  scanf("%d", &cpf_a_excluir);

  // abrindo em leitura
  FILE *arquivo = fopen("dados.txt", "r");

  // temp em escrita
  FILE *temp_arquivo = fopen("temp.txt", "w");

  int encontrado = 0;
  char linha[1000];

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    // Converter a linha para um cliente JSON
    struct Cliente cliente;
    // ----
    if (sscanf(linha,
               "{\"nome\":\"%99[^\"]\", \"Tconta\":\"%49[^\"]\", \"cpf\":%d, "
               "\"Senha\":%d, \"Saldo\":%f}",
               cliente.nome_cliente, cliente.tipo_conta, &cliente.cpf,
               &cliente.senha, &cliente.saldo) == 5) {
      // Verifica se o CPF do cliente atual é igual ao CPF a ser excluído
      if (cliente.cpf == cpf_a_excluir) {
        encontrado =
            1; // Cliente encontrado, não copia nada para o arquivo temporário
        continue;
      }
    }
    // Copia as linhas não relacionadas ao cliente
    fprintf(temp_arquivo, "%s", linha);
  }

  // Fechar ambos os arquivos
  fclose(arquivo);
  fclose(temp_arquivo);

  if (encontrado) {
    // Remover o arquivo original e renomear o arquivo temporário para o nome
    // original
    remove("dados.txt");
    rename("temp.txt", "dados.txt");
    printf("\n   +--------------------------------+");
    printf("\n   | CLIENTE EXCLUIDO COM SUCESSO   |");
    printf("\n   +--------------------------------+ \n");
  } else {
    printf("      Cliente com CPF %d não foi encontrado.\n", cpf_a_excluir);
  }
}

// funcão de listagem, quel lê linha por linha do arquivo,
// com isso é atribuido as vars, e assim consigo printar.
void ListarTodos() {
  // template bonitinho:
  printf("\n   +-------------------------------+");
  printf("\n   |        LISTAR CLIENTES        |");
  printf("\n   +-------------------------------+ \n\n");
  // Abrir o arquivo em modo de leitura.
  FILE *arquivo = fopen("dados.txt", "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  struct Cliente cliente;
  // armazena cada linha lida do dados.txt , é armazenada temporaraiamente
  // enquanto processa para extrair informações do cliente
  char linha[1000];

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    // Converter a linha para um cliente JSON scanf está analisando as infos
    if (sscanf(linha,
               "{\"nome\":\"%99[^\"]\", \"Tconta\":\"%49[^\"]\", \"cpf\":%d, "
               "\"Senha\":%d, \"Saldo\":%f}",
               cliente.nome_cliente, cliente.tipo_conta, &cliente.cpf,
               &cliente.senha, &cliente.saldo) == 5) {
      // Imprimir o nome do cliente
      printf("   ---------------------------\n");
      printf("   Nome: %s\n", cliente.nome_cliente);
      printf("   TipodeConta: %s\n", cliente.tipo_conta);
      printf("   CPF: %d\n", cliente.cpf);
      printf("   Senha: %d\n", cliente.senha);
      printf("   Saldo: %.2f\n", cliente.saldo);
      printf("   ---------------------------\n");
    }
  }

  // Fechar o arquivo.
  fclose(arquivo);
}