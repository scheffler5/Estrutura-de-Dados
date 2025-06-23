#include "matriz.h"

/**
 * @brief Cria um novo nó (arquivo ou pasta).
 * Aloca memória para o nó e seu nome.
 */
Node* create_node(const char* name, NodeType type, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Falha ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    new_node->name = strdup(name); // strdup aloca memória e copia a string
    if (!new_node->name) {
        perror("Falha ao alocar memoria para o nome do no");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    new_node->type = type;
    new_node->parent = parent;
    new_node->children_head = NULL;
    new_node->next_sibling = NULL;
    return new_node;
}

/**
 * @brief Libera recursivamente toda a memória alocada para a árvore.
 */
void free_tree(Node* node) {
    if (node == NULL) {
        return;
    }
    // Libera recursivamente todos os filhos e irmãos
    free_tree(node->children_head);
    free_tree(node->next_sibling);

    // Libera o nó atual
    free(node->name);
    free(node);
}

/**
 * @brief Adiciona um nó filho à lista de filhos de um nó pai.
 */
void add_child(Node* parent, Node* child) {
    if (parent->children_head == NULL) {
        parent->children_head = child;
    } else {
        Node* current = parent->children_head;
        while (current->next_sibling != NULL) {
            current = current->next_sibling;
        }
        current->next_sibling = child;
    }
}

/**
 * @brief Procura por um filho com um nome específico.
 */
Node* find_child(Node* parent, const char* name) {
    Node* child = parent->children_head;
    while (child != NULL) {
        if (strcmp(child->name, name) == 0) {
            return child;
        }
        child = child->next_sibling;
    }
    return NULL;
}


/**
 * @brief Insere um caminho completo (ex: "Pasta/Subpasta/arquivo.txt") na árvore.
 */
void insert_path(Node* root, const char* path) {
    char* path_copy = strdup(path);
    if (!path_copy) return;

    Node* current = root;
    char* token = strtok(path_copy, "/");

    while (token != NULL) {
        Node* next_node = find_child(current, token);
        char* next_token = strtok(NULL, "/");

        if (next_node == NULL) {
            // Se o nó não existe, cria
            NodeType type = (next_token == NULL && strchr(token, '.') != NULL) ? FILE_TYPE : FOLDER_TYPE;
            next_node = create_node(token, type, current);
            add_child(current, next_node);
        }
        
        current = next_node;
        token = next_token;
    }

    free(path_copy);
}

/**
 * @brief Lê o arquivo de entrada (in.txt) e monta a árvore.
 */
void read_input_file(Node* root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Nao foi possivel abrir o arquivo in.txt");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove o caractere de nova linha, se houver
        line[strcspn(line, "\n")] = 0;
        if(strlen(line) > 0) {
            insert_path(root, line);
        }
    }

    fclose(file);
}

/**
 * @brief (list) Lista o conteúdo do diretório atual.
 */
void list_directory(Node* current_dir) {
    if (current_dir->type != FOLDER_TYPE) {
        printf("Erro: '%s' nao e uma pasta.\n", current_dir->name);
        return;
    }

    Node* child = current_dir->children_head;
    if (child == NULL) {
        printf("(vazio)\n");
        return;
    }

    while (child != NULL) {
        printf("%s", child->name);
        if (child->type == FOLDER_TYPE) {
            printf("/");
        }
        printf("\n");
        child = child->next_sibling;
    }
}

/**
 * @brief (cd) Muda o diretório atual.
 */
Node* change_directory(Node* current_dir, const char* path) {
    if (strcmp(path, "..") == 0) {
        return (current_dir->parent != NULL) ? current_dir->parent : current_dir;
    }
    
    if (strcmp(path, "/") == 0 || strcmp(path, "root") == 0) {
        while(current_dir->parent != NULL) {
            current_dir = current_dir->parent;
        }
        return current_dir;
    }

    Node* target = find_child(current_dir, path);

    if (target != NULL && target->type == FOLDER_TYPE) {
        return target;
    } else if (target != NULL && target->type == FILE_TYPE) {
        printf("Erro: '%s' e um arquivo, nao uma pasta.\n", path);
        return current_dir;
    } else {
        // Procura por alternativas
        Node* child = current_dir->children_head;
        int suggestions_found = 0;
        printf("Diretorio nao encontrado. Voce quis dizer:\n");
        while(child != NULL) {
            if(child->type == FOLDER_TYPE && strstr(child->name, path) != NULL) {
                printf("  %s/\n", child->name);
                suggestions_found++;
            }
            child = child->next_sibling;
        }
        if(!suggestions_found) {
            printf("  (Nenhuma alternativa encontrada)\n");
        }
        return current_dir;
    }
}


/**
 * @brief (search) Função auxiliar recursiva para a busca.
 */
void search_recursive(Node* current, const char* name, bool* found) {
    if (current == NULL) return;

    if (strcmp(current->name, name) == 0) {
        *found = true;
        printf("Encontrado: ");
        print_path_to_node(current);
        printf("\n");
    }

    search_recursive(current->children_head, name, found);
    search_recursive(current->next_sibling, name, found);
}

/**
 * @brief (search) Inicia a busca por um arquivo ou pasta.
 */
void search_fs(Node* root, const char* name) {
    bool found = false;
    search_recursive(root->children_head, name, &found);
    if (!found) {
        printf("Arquivo ou pasta '%s' nao encontrado.\n", name);
    }
}


/**
 * @brief (rm) Remove um arquivo ou uma pasta (e seu conteúdo).
 */
void remove_node(Node* current_dir, const char* name) {
    Node* child_to_remove = find_child(current_dir, name);

    if (child_to_remove == NULL) {
        printf("Erro: Arquivo ou pasta '%s' nao encontrado.\n", name);
        return;
    }

    // Desvincular da lista de irmãos
    if (current_dir->children_head == child_to_remove) {
        current_dir->children_head = child_to_remove->next_sibling;
    } else {
        Node* temp = current_dir->children_head;
        while (temp->next_sibling != child_to_remove) {
            temp = temp->next_sibling;
        }
        temp->next_sibling = child_to_remove->next_sibling;
    }

    // Isolar o nó removido para não apagar seus antigos irmãos
    child_to_remove->next_sibling = NULL; 
    
    // Liberar a sub-árvore
    free_tree(child_to_remove);
    printf("'%s' removido com sucesso.\n", name);
}

/**
 * @brief (mkdir) Cria uma nova pasta no diretório atual.
 */
void create_directory(Node* current_dir, const char* name) {
    if (find_child(current_dir, name) != NULL) {
        printf("Erro: Ja existe um arquivo ou pasta com o nome '%s'.\n", name);
        return;
    }
    if (strchr(name, '.') != NULL || strchr(name, '/') != NULL){
        printf("Erro: Nome de pasta invalido.\n");
        return;
    }
    Node* new_dir = create_node(name, FOLDER_TYPE, current_dir);
    add_child(current_dir, new_dir);
    printf("Pasta '%s' criada.\n", name);
}

/**
 * @brief Imprime o caminho completo de um nó até a raiz.
 */
void print_path_to_node(Node* node) {
    if (node == NULL || node->parent == NULL) { // Para na raiz
        printf("root");
        return;
    }
    print_path_to_node(node->parent);
    printf("/%s", node->name);
}

/**
 * @brief (help) Exibe a ajuda com todos os comandos.
 */
void show_help() {
    printf("--- Simulador de Linha de Comando ---\n");
    printf("Comandos disponiveis:\n");
    printf("  list          - Lista os arquivos e pastas no diretorio atual.\n");
    printf("  cd <pasta>    - Entra no diretorio <pasta>. Use 'cd ..' para voltar.\n");
    printf("  mkdir <pasta> - Cria uma nova pasta no diretorio atual.\n");
    printf("  rm <item>     - Remove uma pasta ou arquivo (recursivamente).\n");
    printf("  search <item> - Busca por um arquivo ou pasta e mostra seu caminho.\n");
    printf("  help          - Mostra esta mensagem de ajuda.\n");
    printf("  clear         - Limpa a tela do terminal.\n");
    printf("  exit          - Encerra o programa e libera a memoria.\n");
    printf("-------------------------------------\n");
}

/**
 * @brief (clear) Limpa a tela do console.
 */
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
