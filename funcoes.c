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

//------
// A mesma coisa da de cima porém agora com senha!
//------
bool verificaCPFesenha(int cpf, int senha) {
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

      if (cpf == cliente.cpf & senha == cliente.senha) {
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

void Depositar() {
  // template bonitinho:
  printf("\n   +-------------------------------+");
  printf("\n   |            DEPÓSITO           |");
  printf("\n   +-------------------------------+ \n\n");
  int cpf_a_Depositar;
  int senha_a_depositar;
  float saldo_Incrementar;
  struct Cliente cliente;

  // Abra o arquivo de dados para leitura e gravação.
  FILE *arquivo = fopen("dados.txt", "r+");

  // Abra o arquivo de extrato para adicionar informações.
  FILE *arquivo2 = fopen("extrato.txt", "a");

  // Solicite o CPF e Senha do cliente.
  printf("      Digite o CPF de sua conta: ");
  scanf("%d", &cpf_a_Depositar);

  printf("      Digite A senha da sua conta: ");
  scanf("%d", &senha_a_depositar);

  // Verifique se o CPF existe no arquivo de dados.
  if (verificaCPFesenha(cpf_a_Depositar, senha_a_depositar) == 0) {
    printf("Cliente não cadastrado!\n");
    fclose(arquivo);
    fclose(arquivo2);
    return;
  } else {
    cliente.cpf = cpf_a_Depositar;
    cliente.senha = senha_a_depositar;
  }

  // Solicite o valor a ser depositado.
  printf("      Digite quanto deseja depositar: ");
  scanf("%f", &saldo_Incrementar);

  // Abra um arquivo temporário para escrever os dados atualizados.
  FILE *temp_arquivo = fopen("temp.txt", "w");

  int encontrado = 0;
  char linha[1000];

  // Percorra o arquivo de dados linha por linha.
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha,
               "{\"nome\":\"%99[^\"]\", \"Tconta\":\"%49[^\"]\", \"cpf\":%d, "
               "\"Senha\":%d, \"Saldo\":%f}",
               cliente.nome_cliente, cliente.tipo_conta, &cliente.cpf,
               &cliente.senha, &cliente.saldo) == 5) {
      if (cliente.cpf == cpf_a_Depositar) {
        encontrado = 1;
        cliente.saldo += saldo_Incrementar;
      }
      // Escreva os dados atualizados no arquivo temporário.
      fprintf(temp_arquivo,
              "{\"nome\":\"%s\", \"Tconta\":\"%s\", \"cpf\":%d, \"Senha\":%d, "
              "\"Saldo\":%.2f}\n",
              cliente.nome_cliente, cliente.tipo_conta, cliente.cpf,
              cliente.senha, cliente.saldo);
    }
  }

  //
  // aqui a lógica foi basicamente utilizar de variáveis já definidas no
  // programa para que quando fossesmos fazer o extrato, conseguissemos
  // re-utilizalas, sem alterar a estrutura do código inteira por isso também
  // estamos definindo essas contas + e alterando valor de tipo conta para o
  // valor de deposito, apenas estético e para ser usado no extrato!
  //
  snprintf(cliente.Tipo_Solicitacao, sizeof(cliente.Tipo_Solicitacao),
           "Depósito.         ");
  snprintf(cliente.nome_cliente, sizeof(cliente.nome_cliente), "+");

  char saldo_convertido[200];
  snprintf(saldo_convertido, sizeof(saldo_convertido), "%.2f",
           saldo_Incrementar);
  snprintf(cliente.tipo_conta, sizeof(cliente.tipo_conta), "%s",
           saldo_convertido);

  // Escreva as informações no arquivo de extrato.
  fprintf(arquivo2,
          "{\"TipoAction\":\"%s\",\"nome\":\"%s\", \"Tconta\":\"%s\", "
          "\"cpf\":%d, "
          "\"Senha\":%d, "
          "\"Saldo\":%.2f}\n",
          cliente.Tipo_Solicitacao, cliente.nome_cliente, cliente.tipo_conta,
          cliente.cpf, cliente.senha, cliente.saldo);

  // Feche os arquivos e renomeie o arquivo temporário para "dados.txt".
  fclose(arquivo);
  fclose(arquivo2);
  fclose(temp_arquivo);
  remove("dados.txt");
  rename("temp.txt", "dados.txt");

  // Exibir mensagem visual
  if (encontrado) {
    printf("      Foram depositados R$ %.2f \n\n", saldo_Incrementar);
  } else {
    printf("      Cliente com CPF %d não foi encontrado.\n", cpf_a_Depositar);
    remove("temp.txt"); // Remova o arquivo temporário, pois não foi necessário.
  }
}

//---------------------------------
// função para debitar, que verificar se existe cliente
// pucha linha por linha, guarda no extrato, e aplica as taxas, relativas ao
// tipo de conta.
//-------------
void Debitar() {

  // template bonitinho:
  printf("\n   +-------------------------------+");
  printf("\n   |            DEBITAR            |");
  printf("\n   +-------------------------------+ \n\n");
  int cpf_a_Depositar;
  float saldo_Decrementar;
  int senha_a_depositar;
  struct Cliente cliente;

  // Abra o arquivo de dados para leitura e gravação.
  FILE *arquivo = fopen("dados.txt", "r+");
  FILE *arquivo2 = fopen("extrato.txt", "a");

  // Solicite o CPF do cliente.
  printf("      Digite o CPF de sua conta: ");
  scanf("%d", &cpf_a_Depositar);

  printf("      Digite A senha da sua conta: ");
  scanf("%d", &senha_a_depositar);

  // Verifique se o CPF existe no arquivo de dados.
  if (verificaCPFesenha(cpf_a_Depositar, senha_a_depositar) == 0) {
    printf("Cliente não cadastrado!\n");
    fclose(arquivo);
    fclose(arquivo2);
    return;
  } else {
    cliente.cpf = cpf_a_Depositar;
    cliente.senha = senha_a_depositar;
  }

  // Solicite o valor a ser depositado.
  printf("      Digite quanto deseja debitar: ");
  scanf("%f", &saldo_Decrementar);

  // Abra um arquivo temporário para escrever os dados atualizados.
  FILE *temp_arquivo = fopen("temp.txt", "w");

  int encontrado = 0;
  char linha[1000];
  float taxa = 0;

  // Percorra o arquivo de dados linha por linha.
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha,
               "{\"nome\":\"%99[^\"]\", \"Tconta\":\"%49[^\"]\", \"cpf\":%d, "
               "\"Senha\":%d, \"Saldo\":%f}",
               cliente.nome_cliente, cliente.tipo_conta, &cliente.cpf,
               &cliente.senha, &cliente.saldo) == 5) {
      if (cliente.cpf == cpf_a_Depositar) {
        encontrado = 1;
        if (strcmp(cliente.tipo_conta, "Comum") == 0) {
          // Conta Comum
          if (cliente.saldo - saldo_Decrementar < -1000) {
            printf("\n   +-----------------------------+");
            printf("\n   | SALDO INSUFICIENTE (Comum)  |");
            printf("\n   +-----------------------------+ \n");
            fclose(arquivo);
            fclose(temp_arquivo);
            return;
          } else {
            taxa = (saldo_Decrementar * 0.05);
            cliente.saldo -= (saldo_Decrementar + taxa); // 5% de taxa
          }
        } else if (strcmp(cliente.tipo_conta, "Plus") == 0) {
          // Conta Plus
          if (cliente.saldo - saldo_Decrementar < -5000) {
            printf("\n   +-----------------------------+");
            printf("\n   | SALDO INSUFICIENTE (Plus)  |");
            printf("\n   +-----------------------------+ \n");
            fclose(arquivo);
            fclose(temp_arquivo);
            return;
          } else {
            taxa = (saldo_Decrementar * 0.03);
            cliente.saldo -= (saldo_Decrementar + taxa); // 3% de taxa
          }
        }
        // escrevendo no arquivo binário
        fprintf(
            temp_arquivo,
            "{\"nome\":\"%s\", \"Tconta\":\"%s\", \"cpf\":%d, \"Senha\":%d, "
            "\"Saldo\":%.2f}\n",
            cliente.nome_cliente, cliente.tipo_conta, cliente.cpf,
            cliente.senha, cliente.saldo);
      }
    }

    //
    // aqui a lógica foi basicamente, utilizar de variáveis já definidas no
    // programa para que quando fossesmos fazer o extrato, conseguissemos
    // puxalas, sem alterar a estrutura do código inteira por isso também
    // estamos definindo essas contas + e alterando valor de tipo conta para o
    // valor de deposito, apenas estético!
    //
    snprintf(cliente.Tipo_Solicitacao, sizeof(cliente.Tipo_Solicitacao),
             "Débito...         ");
    char taxaConvertida[200];
    snprintf(taxaConvertida, sizeof(taxaConvertida), "%.2f ", taxa);
    snprintf(cliente.nome_cliente, sizeof(cliente.nome_cliente), "%s",
             taxaConvertida);
    // transformei em string
    char saldo_convertido[200];
    snprintf(saldo_convertido, sizeof(saldo_convertido), "%.2f",
             saldo_Decrementar);
    snprintf(cliente.tipo_conta, sizeof(cliente.tipo_conta), "%s",
             saldo_convertido);

    // Escreva as informações no arquivo de extrato.
    fprintf(arquivo2,
            "{\"TipoAction\":\"%s\",\"nome\":\"%s\", \"Tconta\":\"%s\", "
            "\"cpf\":%d, "
            "\"Senha\":%d, "
            "\"Saldo\":%.2f}\n",
            cliente.Tipo_Solicitacao, cliente.nome_cliente, cliente.tipo_conta,
            cliente.cpf, cliente.senha, cliente.saldo);

    // Feche os arquivos e renomeie o arquivo temporário para "dados.txt".
    fclose(arquivo);
    fclose(arquivo2);
    fclose(temp_arquivo);
    remove("dados.txt");
    rename("temp.txt", "dados.txt");

    // Exiba uma mensagem com base no resultado.
    if (encontrado) {
      printf("      Foram Retirados R$ %.2f .\n", saldo_Decrementar);
    } else {
      printf("      Cliente com CPF %d não foi encontrado.\n", cpf_a_Depositar);
      remove(
          "temp.txt"); // Remova o arquivo temporário, pois não foi necessário.
    }
  }
}
//------------------------