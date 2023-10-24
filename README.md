Bem-vindo ao nosso banco, ou melhor, ao banco QuemPoupaTem.

Este projeto é uma extensão do mesmo projeto que realizamos no primeiro semestre em Python, porém agora em C e com algumas diferenças técnicas.

Aqui, você encontrará diversas funcionalidades e inovações no setor bancário. Entre elas, posso citar algumas, tais como:

1. Cadastrar Cliente
2. Apagar Cliente
3. Listar Cliente
4. Depositar
5. Debitar
6. Extrato
7. Transferir

Cada função possui uma chamada simples na função principal, o que evita sobrecarregá-la. Além disso, com essa funcionalidade, centralizamos as funções em nosso arquivo "funcoes.c", tornando o código muito mais organizado.

As definições e parâmetros das funções estão no arquivo "funcoes.c".

Falando de aspectos mais técnicos, nosso banco tem capacidade de armazenar até 1000 contas. Utilizamos Jsons para salvar as informações em arrays, facilitando e tornando a manipulação dos dados mais prática.

Desenvolvemos também algumas funções auxiliares para tornar o programa mais rápido e menos repetitivo, são elas:

1. verificaCPFeSenha
2. verificarCPFExistente

Como os nomes já sugerem, uma função verifica o CPF e a senha, e a outra verifica apenas o CPF.

Um pouco mais sobre aspectos técnicos: no momento do cadastro do cliente, temos duas opções de conta: Plus ou Normal. Assim, ao longo do desenvolvimento do código, poderemos criar condições de taxas relativas ao tipo de conta.

Para melhores especificações técnicas, sintase a vontade para visualizar os comentários ao decorrer do código.
