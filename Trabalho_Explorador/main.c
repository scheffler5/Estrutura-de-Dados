#include "matriz.h"
#include <ctype.h>

/**
 * @brief Remove espaços em branco do início e do fim de uma string.
 */
char* trim_whitespace(char* str) {
    char* end;

    // Trim à esquerda
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0) // String toda de espaços
        return str;

    // Trim à direita
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Escreve novo terminador nulo
    end[1] = '\0';

    return str;
}


int main() {
    // Cria o nó raiz da árvore
    Node* root = create_node("root", FOLDER_TYPE, NULL);
    Node* current_dir = root;

    // Lê o arquivo de entrada para popular a árvore
    read_input_file(root, "in.txt");

    char input_buffer[1024];
    char* command;
    char* argument;

    printf("Simulador de Sistema de Arquivos. Digite 'help' para ajuda.\n");

    while (1) {
        // Exibe o prompt
        print_path_to_node(current_dir);
        printf("> ");

        // Lê o comando do usuário
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            break; // Fim da entrada (Ctrl+D)
        }

        // Processa o comando
        char* trimmed_input = trim_whitespace(input_buffer);
        command = strtok(trimmed_input, " ");
        argument = strtok(NULL, " ");

        // Remove nova linha do argumento se ele for a última palavra
        if (argument) {
            argument[strcspn(argument, "\n")] = 0;
        }

        if (command == NULL) {
            continue; // Linha vazia
        }

        if (strcmp(command, "exit") == 0) {
            break; // Sai do loop para encerrar
        } else if (strcmp(command, "help") == 0) {
            show_help();
        } else if (strcmp(command, "list") == 0) {
            list_directory(current_dir);
        } else if (strcmp(command, "clear") == 0) {
            clear_screen();
        } else if (strcmp(command, "cd") == 0) {
            if (argument) {
                current_dir = change_directory(current_dir, argument);
            } else {
                printf("Uso: cd <pasta>\n");
            }
        } else if (strcmp(command, "mkdir") == 0) {
             if (argument) {
                create_directory(current_dir, argument);
            } else {
                printf("Uso: mkdir <nome_da_pasta>\n");
            }
        } else if (strcmp(command, "rm") == 0) {
             if (argument) {
                remove_node(current_dir, argument);
            } else {
                printf("Uso: rm <arquivo_ou_pasta>\n");
            }
        } else if (strcmp(command, "search") == 0) {
             if (argument) {
                search_fs(root, argument);
            } else {
                printf("Uso: search <nome_do_item>\n");
            }
        }
        else {
            printf("Comando desconhecido: '%s'. Digite 'help' para ver a lista de comandos.\n", command);
        }
        printf("\n");
    }

    // Libera toda a memória alocada para a árvore antes de sair
    free_tree(root);
    printf("Sistema encerrado. Memoria liberada.\n");

    return 0;
}
