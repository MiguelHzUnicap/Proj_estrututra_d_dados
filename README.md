#  Sistema de Login com Tabela Hash

Este projeto implementa um sistema simples de gerenciamento de logins utilizando **tabela hash com encadeamento** em linguagem C.  
O programa permite:

-  Cadastrar novos logins com senha (armazenada como hash)  
-  Imprimir toda a tabela hash  
-  Remover logins existentes  
-  Encerrar o programa  

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
