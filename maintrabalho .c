#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhometodos.c"
// aqui entram os seus typedefs e funções já implementadas...

int main() {
    Hash* tabela = Criar_Hash();
    int opcao;
    char nome[30]; 
    char senha[30];

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar login\n");
        printf("2 - Imprimir tabela\n");
        printf("3 - Remover login\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o login: ");
                scanf("%s", nome);

                if (AprovarLogin(tabela, nome)) {
                    CreateLogin(tabela, nome, senha);
                } else {
                    printf("Login %s já existe.\n", nome);
                }
                break;

            case 2:
                Print_Hash(tabela);
                break;

            case 3:
                printf("Digite o login para remover: ");
                scanf("%s", nome);
                Remove_Login(tabela, nome);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}
