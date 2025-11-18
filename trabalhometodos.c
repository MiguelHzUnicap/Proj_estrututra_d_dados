#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario {
    char login[30];
    int senha;
    struct usuario* prox; // ponteiro para o próximo (encadeamento)
} Usuario;

typedef struct tabela {
    int capacidade;
    int qtd;
    Usuario **p; // vetor de ponteiros para listas de usuários
} Hash;

// Protótipos
Hash* Criar_Hash();
void Print_Hash(Hash *h);
int HashSenha(const char *senha);
int PosSenha(int chave, int size);
int CreateLogin(Hash* t, const char* nome, const char* senha);
int RemoveHash(Hash* tabela, const char* nome, int senhaHash);
int AprovarLogin(Hash* tabela, const char* nome, int senhaHash);
void Free_Hash(Hash* tabela);
Usuario* BuscaHash(Hash* tabela, const char* nome, int senhaHash);

// Cria a tabela hash
Hash* Criar_Hash() {
    Hash* tabela = malloc(sizeof(Hash));
    if (tabela != NULL) {
        tabela->capacidade = 31; // capacidade inicial
        tabela->qtd = 0;
        tabela->p = calloc(tabela->capacidade, sizeof(Usuario*));
    }
    return tabela;
}

// Insere login na tabela (com encadeamento)
int CreateLogin(Hash* t, const char* nome, const char* senha) {
    int senhaHash = HashSenha(senha);
    int pos = PosSenha(senhaHash, t->capacidade);

    Usuario* no = malloc(sizeof(Usuario));
    strcpy(no->login, nome);
    no->senha = senhaHash;
    no->prox = NULL;

    if (t->p[pos] == NULL) {
        t->p[pos] = no;
        t->qtd++;
        printf("Login %s cadastrado com senha hash %d\n", nome, no->senha);
        return 1;
    } else {
        Usuario* atual = t->p[pos];
        while (atual->prox != NULL) {
            if (strcmp(atual->login, nome) == 0 && atual->senha == senhaHash) {
                printf("Login %s já existe.\n", nome);
                free(no);
                return 0;
            }
            atual = atual->prox;
        }
        atual->prox = no;
        t->qtd++;
        printf("Login %s cadastrado com senha hash %d (colisão resolvida por encadeamento)\n", nome, no->senha);
        return 1;
    }
}

// Imprime a tabela
void Print_Hash(Hash* t) {
    printf("Tabela Hash (qtd = %d, capacidade = %d)\n", t->qtd, t->capacidade);
    for (int i = 0; i < t->capacidade; i++) {
        printf("[%d] = ", i);
        Usuario* atual = t->p[i];
        if (atual == NULL) {
            printf("NULL\n");
        } else {
            while (atual != NULL) {
                printf("%s -> ", atual->login);
                atual = atual->prox;
            }
            printf("NULL\n");
        }
    }
}

// Hash direto da senha
int HashSenha(const char *senha) {
    unsigned long hash = 0;
    int primo = 31;
    for (int i = 0; senha[i] != '\0'; i++) {
        hash = hash * primo + senha[i];
    }
    return (int)(hash & 0x7FFFFFFF);
}

// Reduz o valor para caber na tabela
int PosSenha(int chave, int size) {
    return chave % size;
}

// Remove login da tabela
int RemoveHash(Hash* tabela, const char* nome, int senhaHash) {
    if (tabela == NULL) return 0;

    int pos = PosSenha(senhaHash, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    Usuario* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0 && atual->senha == senhaHash) {
            if (anterior == NULL) {
                tabela->p[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            tabela->qtd--;
            printf("Login %s removido com sucesso.\n", nome);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Login %s com a senha hash %d não encontrado.\n", nome, senhaHash);
    return 0;
}

// Aprovar login (verifica se já existe)
int AprovarLogin(Hash* tabela, const char* nome, int senhaHash) {
    int pos = PosSenha(senhaHash, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0 && atual->senha == senhaHash) {
            return 0; // já existe
        }
        atual = atual->prox;
    }
    return 1; // não existe, pode aprovar
}

// Libera memória da tabela
void Free_Hash(Hash* tabela) {
    if (!tabela) return;

    for (int i = 0; i < tabela->capacidade; i++) {
        Usuario* atual = tabela->p[i];
        while (atual != NULL) {
            Usuario* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    free(tabela->p);
    free(tabela);
}

// Busca login na tabela
/*Usuario* BuscaHash(Hash* tabela, const char* nome, int senhaHash) {
    if (tabela == NULL) return NULL;

    int pos = PosSenha(senhaHash, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0 && atual->senha == senhaHash) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}*/

// Busca login na tabela usando nome e senha hash
Usuario* BuscaHash(Hash* tabela, const char* nome, int senhaHash) {
    if (tabela == NULL) return NULL;

    // Calcula posição pelo hash da senha
    int pos = PosSenha(senhaHash, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        // Verifica se login e senha hash coincidem
        if (strcmp(atual->login, nome) == 0 && atual->senha == senhaHash) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL; // não encontrado
}

