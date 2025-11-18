#  Sistema de Login com Tabela Hash

Este projeto implementa um sistema simples de gerenciamento de logins utilizando **tabela hash com encadeamento** em linguagem C.  

O programa permite:

O programa apresenta um menu interativo com as seguintes opções:

Cadastrar login

Solicita um nome de usuário e uma senha.

Verifica se o login já existe na tabela.

Caso não exista, insere o novo login.

Buscar login

Solicita o nome de usuário.

Procura na tabela e exibe o login e o hash da senha, se encontrado.

Remover login

Solicita o nome de usuário e a senha.

Remove o login correspondente da tabela, caso exista.

Imprimir tabela

Exibe todos os logins armazenados na tabela hash.

Liberar tabela

Libera toda a memória alocada para a tabela hash.

Define o ponteiro da tabela como NULL para evitar uso indevido.

Sair

Encerra o programa.

Antes de finalizar, garante que a memória da tabela seja liberada.

---

##  Estrutura do Projeto

- `main.c` → contém a função principal e o menu interativo  
- `trabalhometodos.c` → contém as funções auxiliares e estruturas (`Hash`, `Usuario`, funções de hash, inserção, remoção, impressão etc.)  

> Observação: No código fornecido, o `main.c` inclui diretamente `"trabalhometodos.c"`.  
> Em projetos maiores, o ideal seria usar um arquivo `.h` (header) para declarar funções e incluir apenas ele no `main.c`.

---

##  Requisitos

- Compilador **GCC** ou compatível (Linux, macOS, Windows com MinGW ou WSL)  
- Sistema operacional com suporte a terminal/console  

---

##  Como Compilar

No terminal, dentro da pasta do projeto, execute:

```bash
gcc main.c -o programa
