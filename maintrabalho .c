#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhometodos.c"  // ideal seria usar trabalhometodos.h

int main() {
    Hash* tabela = Criar_Hash();
    int opcao;
    char nome[30];
    char senha[30];
    int senhaHash = HashSenha(senha);
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar login\n");
        printf("2 - Buscar login\n");
        printf("3 - Remover login\n");
        printf("4 - Imprimir tabela\n");
        printf("5 - Liberar tabela\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o login: ");
                scanf("%s", nome);
                printf("Digite a senha: ");
                scanf("%s", senha);

                if (AprovarLogin(tabela, nome,senhaHash)) {
                    CreateLogin(tabela, nome, senha);
                } else {
                    printf("Login %s já existe.\n", nome);
                }
                break;

            case 2: {
                printf("Digite o login para buscar: ");
                scanf("%s", nome);
                Usuario* u = BuscaHash(tabela, nome,senhaHash);
                if (u != NULL) {
                    printf("Login encontrado: %s | Senha hash: %d\n", u->login, u->senha);
                } else {
                    printf("Login %s não encontrado.\n", nome);
                }
                break;
            }

            case 3:
                printf("Digite o login para remover: \n");
                scanf("%s", nome);
                printf("Digite sua senha: \n"); 
                scanf("%s",senha);
                RemoveHash(tabela, nome,HashSenha(senha));
                break;

            case 4:
                Print_Hash(tabela);
                break;

            case 5:
                Free_Hash(tabela);
                tabela = NULL; // evita uso após liberar
                printf("Tabela liberada da memória.\n");
                break;

            case 6:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 6);

    // garante liberação se o usuário não escolher opção 5
    if (tabela != NULL) {
        Free_Hash(tabela);
    }

    return 0;
}
