#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario {
    char login[30]; 
    char senha;      
    struct usuario* prox; // ponteiro para o próximo (encadeamento)
} Usuario;

typedef struct tabela {
    int capacidade;   
    int qtd;   
    Usuario **p; // vetor de ponteiros para listas de usuários
} Hash;

Hash* Criar_Hash();
void Print_Hash(Hash *h);
int TransformaCharacterEmInteiro(const char *a);
int HashSenha(const char *senha);
int PosSenha(int chave, int size);
int CreateLogin(Hash* t, const char* nome,char *senha);
int Remove_Login(Hash* tabela, const char* nome);
int AprovarLogin(Hash* tabela, const char* nome);
void Free_Hash(Hash* tabela);
Usuario* BuscaHash(Hash* tabela, const char* nome);

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
int CreateLogin(Hash* t, const char* nome, char *senha) {
    int chave = TransformaCharacterEmInteiro(senha);
    int pos = PosSenha(chave, t->capacidade);

    // cria novo usuário
    Usuario* no = malloc(sizeof(Usuario));
    strcpy(no->login, nome);
    no->senha = HashSenha(senha);
    no->prox = NULL;

    // se posição está vazia, insere direto
    if (t->p[pos] == NULL) {
        t->p[pos] = no;
        t->qtd++;
        printf("Login %s cadastrado com senha hash %d\n", nome, no->senha);
        return 1;
    } else {
        // encadeamento: percorre lista
        Usuario* atual = t->p[pos];
        while (atual->prox != NULL) {
            if (strcmp(atual->login, nome) == 0) {
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

// Imprime a tabela (mostra listas encadeadas)
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

// Função de hash para string -> inteiro
int TransformaCharacterEmInteiro(const char *a) {
    int val = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        val = 31 * val + a[i];
    }
    return val;
}

// Reduz o valor para caber na tabela
int PosSenha(int chave, int size) {
    return chave % size;
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

// Remove login da tabela (percorrendo lista encadeada)
int Remove_Login(Hash* tabela, const char* nome) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    Usuario* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            if (anterior == NULL) {
                tabela->p[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            tabela->qtd--;
            printf("Login %s removido.\n", nome);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Login %s não encontrado.\n", nome);
    return 0;
}

// Aprovar login (verifica se já existe na lista)
int AprovarLogin(Hash* tabela, const char* nome) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            return 0; // já existe
        }
        atual = atual->prox;
    }
    return 1; // não existe, pode aprovar
}


void Free_Hash(Hash* tabela) {
    if (!tabela) return;    // Verifica se a tabela existe

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

// Busca um login na tabela hash
Usuario* BuscaHash(Hash* tabela, const char* nome) {
    if (tabela == NULL || nome == NULL) {
        return NULL; // tabela ou nome inválido
    }

    // calcula posição na tabela
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    // percorre lista encadeada na posição
    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            return atual; // encontrado
        }
        atual = atual->prox;
    }

    return NULL; // não encontrado
}
