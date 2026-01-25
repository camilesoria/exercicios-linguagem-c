#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_LIVROS 100
#define MAX_STRING 100
#define MAX_EMPRESTIMOS 100

// Estruturas
struct Livro {
        char nome[MAX_STRING];
        char autor[MAX_STRING];
        char editora[MAX_STRING];
        int edicao;
        int disponivel; // 1 para disponível, 0 para emprestado
    };

struct Emprestimo {
        int indiceLivro;
        char nomeUsuario[MAX_STRING];
    };

// Função para limpar o buffer do teclado
void LimparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main() {

// Declarações de arrays de ponteiros e variáveis
    struct Livro *biblioteca[MAX_LIVROS];
    struct Emprestimo *emprestimos[MAX_EMPRESTIMOS];

    // Alocação de memória para cada ponteiro de livros (array de ponteiros)
    for (int i = 0; i < MAX_LIVROS; i++){
        biblioteca[i] = (struct Livro *) calloc(1, sizeof(struct Livro));
        if (biblioteca[i] == NULL){
            printf("Erro: Falha ao alocar memória para livros\n");
            return 1;
        }
    }
    // Alocação de memória para cada ponteiro de empréstimos (array de ponteiros)
    for (int i = 0; i < MAX_EMPRESTIMOS; i++){
        emprestimos[i] = (struct Emprestimo *) malloc(sizeof(struct Emprestimo));
        if (emprestimos[i] == NULL){
            printf("Erro: Falha ao alocar memória para empréstimos\n");
            return 1;
        }
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;

    char continuar = 'S';
    int opcao = 0;

    printf("\nBem-vindo ao sistema de biblioteca!\n");
    
    do {
        printf("\nPara começar, selecione uma opção:\n");
        printf("1. Cadastrar um novo livro\n");
        printf("2. Ver livros cadastrados\n");  
        printf("3. Realizar empréstimo\n");
        printf("4. Ver empréstimos realizados\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        LimparBuffer();

        switch (opcao)
        {

        case 1:
            do {
                printf("\n--------------------------------------------------------------\n");
                printf("\nCadastro de livros\n");
                printf("Para começar, digite o nome do livro: \n");
                fgets(biblioteca[totalLivros]->nome, sizeof(biblioteca[totalLivros]->nome), stdin);
                biblioteca[totalLivros]->nome[strcspn(biblioteca[totalLivros]->nome, "\n")] = 0;

                printf("Muito obrigado! Agora digite o nome do autor: \n");
                fgets(biblioteca[totalLivros]->autor, sizeof(biblioteca[totalLivros]->autor), stdin);
                biblioteca[totalLivros]->autor[strcspn(biblioteca[totalLivros]->autor, "\n")] = 0;

                printf("Ótimo! Agora digite o nome da editora: \n");
                fgets(biblioteca[totalLivros]->editora, sizeof(biblioteca[totalLivros]->editora), stdin);
                biblioteca[totalLivros]->editora[strcspn(biblioteca[totalLivros]->editora, "\n")] = 0;
                
                printf("Certo! Por fim, digite a edição do livro (apenas números!): \n");
                scanf("%d", &biblioteca[totalLivros]->edicao);
                getchar();

                printf("Muito obrigado! Aqui estão os dados do livro que você cadastrou:\n\n");
                printf("Nome: %s \nAutor: %s \nEditora: %s \nEdição %d \n", biblioteca[totalLivros]->nome, biblioteca[totalLivros]->autor, biblioteca[totalLivros]->editora, biblioteca[totalLivros]->edicao);
                
                biblioteca[totalLivros] ->disponivel = 1; 
                totalLivros++;

                printf("\nDeseja cadastrar outro livro? (S/N): \n");
                scanf(" %c", &continuar);
                LimparBuffer();

                while(continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
                    printf("\nEntrada inválida. Por favor, digite 'S' para sim ou 'N' para não: \n");
                    scanf(" %c", &continuar);
                    LimparBuffer();
                }
            } while((continuar == 'S' || continuar == 's') && totalLivros < MAX_LIVROS);

            if (totalLivros == MAX_LIVROS) {
                printf("\nNúmero máximo de livros cadastrados.\n");
            } else if(continuar == 'N' || continuar == 'n') {
                printf("\nVoltando ao menu principal...\n");
            }
            break;

        case 2:
            printf("\n--------------------------------------------------------------\n");
            printf("\nVisualização de livros cadastrados\n");

            if (totalLivros == 0) {
                    printf("\nNenhum livro cadastrado ainda. \n");
            }
            else {
                for (int j = 0; j < totalLivros; j++) {
                    printf("Livro n° %d:\n", j + 1);
                    printf("Nome: %s \nAutor: %s \nEditora: %s \nEdição %d", biblioteca[j]->nome, biblioteca[j]->autor, biblioteca[j]->editora, biblioteca[j]->edicao);
                    if (biblioteca[j]->disponivel == 1){
                        printf("\nStatus: Disponível\n\n");
                    } else {
                        printf("\nStatus: Emprestado\n\n");
                    }
                }
            }
        break;

            case 3:

                printf("\n--------------------------------------------------------------\n");
                printf("\nRealização de empréstimos\n");

                if (totalLivros == 0) {
                    printf("\nNenhum livro cadastrado ainda. Não é possível realizar empréstimos.\n");
                }else if (totalEmprestimos >= MAX_EMPRESTIMOS){
                    printf("\nNúmero máximo de empréstimos atingido. Não é possível realizar novos empréstimos.\n");
                }else {
                    printf("\nLivros disponíveis para empréstimo:\n");

                    int disponiveis = 0;
                    for (int j = 0; j < totalLivros; j++){
                        if (biblioteca[j]->disponivel){
                            printf("Livro n° %d: %s \n", j + 1, biblioteca[j]->nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("\nNenhum livro disponível para empréstimo no momento.\n");
                    } else {
                        printf("\nDigite o número do livro que deseja emprestar: \n");
                        int numLivro;
                        scanf("%d", &numLivro);
                        LimparBuffer();

                        int indice = numLivro - 1; // Diminuir 1 para índice do array
                        if (indice <0 || indice >= totalLivros || !biblioteca[indice]->disponivel){
                                printf("\nNúmero de livro inválido ou livro indisponível.\n");
                        } else {
                            printf("\nDigite o nome do usuário que está realizando o empréstimo: \n");
                            fgets(emprestimos[totalEmprestimos]->nomeUsuario, sizeof(emprestimos[totalEmprestimos]->nomeUsuario), stdin);

                            emprestimos[totalEmprestimos]->indiceLivro = indice;
                            biblioteca[indice]->disponivel = 0; // Marca o livro como emprestado

                            totalEmprestimos++;
                            printf("\nEmpréstimo realizado com sucesso!\n");
                        }
                    }
                }
                printf("\nPressione Enter para continuar...");
                LimparBuffer();
            break;

            case 4:
            printf("\n--------------------------------------------------------------\n");
            printf("\nVisualização de empréstimos realizados\n");

            if (totalEmprestimos == 0){
                printf("\nNenhum empréstimo realizado ainda.\n");
            }
            else{
                for (int k = 0; k < totalEmprestimos; k++){
                    printf("Empréstimo n° %d:\n", k + 1);
                    printf("Livro: %s \nUsuário: %s \n\n", biblioteca[emprestimos[k]->indiceLivro]->nome, emprestimos[k]->nomeUsuario);
                }
                printf("\nUm total de %d empréstimos realizados.\n", totalEmprestimos);

                printf("\nDeseja devolver algum livro? (S/N): \n");
                char devolver;
                scanf(" %c", &devolver);
                LimparBuffer();

                if (devolver == 'S' || devolver == 's'){
                    printf("\nDigite o número do empréstimo que deseja devolver: \n");
                    int numEmprestimo;
                    scanf("%d", &numEmprestimo);
                    LimparBuffer();

                    int indice = numEmprestimo - 1;

                    if (indice < 0 || indice >= totalEmprestimos){
                        printf("\nNúmero de empréstimo inválido.\n");
                    }
                    else {
                        int indiceLivro = emprestimos[indice]->indiceLivro;
                        biblioteca[indiceLivro]->disponivel = 1; // Marca o livro como disponível

                        // Liberamos o espaço da memória aqui
                        free(emprestimos[indice]); 
                        // Corrigimos a numeração dos empréstimos removendo o espaço vazio
                        for (int m = indice; m < MAX_EMPRESTIMOS - 1; m++) {
                            emprestimos[m] = emprestimos[m + 1];
                        }
                        // Definimos o último ponteiro como NULL para evitar lixo de memória
                        emprestimos[MAX_EMPRESTIMOS - 1] = NULL;
                        totalEmprestimos--;

                        printf("\nLivro devolvido com sucesso!\n");
                    }
                }
            }

            break;

            case 0:
            printf("\nEncerrando o programa. Obrigado por usar o sistema de biblioteca!\n");
            break;
        
        default:
            printf("\nOpção inválida. Encerrando o programa.\n");
            break;
        }    
    } while(opcao != 0);
    

    for (int i = 0; i < MAX_LIVROS; i++){
        free(biblioteca[i]);
    }
    for (int i = 0; i < MAX_EMPRESTIMOS; i++){
        if (emprestimos[i] != NULL){
            free(emprestimos[i]);
            emprestimos[i] = NULL;
        }
    }
    return 0;
}