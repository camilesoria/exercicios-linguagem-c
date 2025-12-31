#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_STRING 100

#define exibirMenu()

typedef struct {
        char nome[MAX_STRING];
        char autor[MAX_STRING];
        char editora[MAX_STRING];
        int edicao;
    }Livro;

int main() {

    Livro biblioteca[MAX_LIVROS];
    char continuar = 'S';
    int i = 0;
    int opcao = 0;

    printf("Bem-vindo ao sistema de biblioteca!\n");

    do {
        printf("Para começar, selecione uma opção:\n");
        printf("1. Cadastrar um novo livro\n");
        printf("2. Ver livros cadastrados\n");  
        printf("3. Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            do {    
            printf("Para começar, digite o nome do livro: \n");
            fgets(biblioteca[i].nome, sizeof(biblioteca[i].nome), stdin);
            biblioteca[i].nome[strcspn(biblioteca[i].nome, "\n")] = 0;

            printf("Muito obrigado! Agora digite o nome do autor: \n");
            fgets(biblioteca[i].autor, sizeof(biblioteca[i].autor), stdin);
            biblioteca[i].autor[strcspn(biblioteca[i].autor, "\n")] = 0;

            printf("Ótimo! Agora digite o nome da editora: \n");
            fgets(biblioteca[i].editora, sizeof(biblioteca[i].editora), stdin);
            biblioteca[i].editora[strcspn(biblioteca[i].editora, "\n")] = 0;
            
            printf("Certo! Por fim, digite a edição do livro (apenas números!): \n");
            scanf("%d", &biblioteca[i].edicao);
            getchar();

            printf("Muito obrigado! Aqui estão os dados do livro que você cadastrou:\n\n");
            printf("Nome: %s \n Autor: %s \n Editora: %s \n Edição %d \n", biblioteca[i].nome, biblioteca[i].autor, biblioteca[i].editora, biblioteca[i].edicao);
            
            printf("Deseja cadastrar outro livro? (S/N): \n");
            scanf(" %c", &continuar);
            getchar();

            while(continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
                printf("Entrada inválida. Por favor, digite 'S' para sim ou 'N' para não: \n");
                scanf(" %c", &continuar);
                getchar();
            }

            i++;
            } while((continuar == 'S' || continuar == 's') && i < MAX_LIVROS);
            if (i == MAX_LIVROS) {
                printf("Número máximo de livros cadastrados.\n");
            }
            else if(continuar == 'N' || continuar == 'n') {
                printf("Obrigado por usar o sistema de biblioteca! Voltando ao menu principal...\n");
            }
            break;

        case 2:
        if (i == 0) {
                printf("Nenhum livro cadastrado ainda. \n");
            }
            else {
                for (int j = 0; j < i; j++) {
                    printf("Livro n° %d:\n", j + 1);
                    printf("Nome: %s \n Autor: %s \n Editora: %s \n Edição %d \n\n", biblioteca[j].nome, biblioteca[j].autor, biblioteca[j].editora, biblioteca[j].edicao);
                }
            }
            break;

            case 3:
            printf("Encerrando o programa. Obrigado por usar o sistema de biblioteca!\n");
            break;
        
        default:
            printf("Opção inválida. Encerrando o programa.\n");
            break;
        }    
    } while(opcao != 3);

    return 0;
}