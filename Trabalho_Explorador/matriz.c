#include "matriz.h"

/**
 * @brief 
 */
Node* create_node(const char* name, NodeType type, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Falha ao alocar memoria para o no");
        exit(EXIT_FAILURE);}
    new_node->name = strdup(name); 
    if (!new_node->name) {
        perror("Falha ao alocar memoria para o nome do no");
        free(new_node);
        exit(EXIT_FAILURE);}
    new_node->type = type;
    new_node->parent = parent;
    new_node->children_head = NULL;
    new_node->next_sibling = NULL;
    return new_node;}

/**
 * @brief 
 */
void free_tree(Node* node) {
    if (node == NULL) {
        return;}
    free_tree(node->children_head);
    free_tree(node->next_sibling);
    free(node->name);
    free(node);}

/**
 * @brief 
 */

void add_child(Node* parent, Node* child) {
    if (parent->children_head == NULL) {
        parent->children_head = child;
    } else {
        Node* current = parent->children_head;
        while (current->next_sibling != NULL) {
            current = current->next_sibling;
        }
        current->next_sibling = child;}}

/**
 * @brief 
 */
Node* find_child(Node* parent, const char* name) {
    Node* child = parent->children_head;
    while (child != NULL) {
        if (strcmp(child->name, name) == 0) {
            return child;}
        child = child->next_sibling;}
    return NULL;}


/**
 * @brief 
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
            NodeType type = (next_token == NULL && strchr(token, '.') != NULL) ? FILE_TYPE : FOLDER_TYPE;
            next_node = create_node(token, type, current);
            add_child(current, next_node);}
        current = next_node;
        token = next_token;}
    free(path_copy);}

/**
 * @brief 
 */
void read_input_file(Node* root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Nao foi possivel abrir o arquivo in.txt");
        return;}
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if(strlen(line) > 0) {
            insert_path(root, line);}}
    fclose(file);}

/**
 * @brief 
 */
void list_directory(Node* current_dir) {
    if (current_dir->type != FOLDER_TYPE) {
        printf("Erro: '%s' nao e uma pasta.\n", current_dir->name);
        return;}
    Node* child = current_dir->children_head;
    if (child == NULL) {
        printf("(vazio)\n");
        return;}
    while (child != NULL) {
        printf("%s", child->name);
        if (child->type == FOLDER_TYPE) {
            printf("/");}
        printf("\n");
        child = child->next_sibling;}}

/**
 * @brief 
 */
Node* change_directory(Node* current_dir, const char* path) {
    if (strcmp(path, "..") == 0) {
        return (current_dir->parent != NULL) ? current_dir->parent : current_dir;}
    if (strcmp(path, "/") == 0 || strcmp(path, "root") == 0) {
        while(current_dir->parent != NULL) {
            current_dir = current_dir->parent;}
        return current_dir;}
    Node* target = find_child(current_dir, path);
    if (target != NULL && target->type == FOLDER_TYPE) {
        return target;
    } else if (target != NULL && target->type == FILE_TYPE) {
        printf("Erro: '%s' e um arquivo, nao uma pasta.\n", path);
        return current_dir;
    } else {
        Node* child = current_dir->children_head;
        int suggestions_found = 0;
        printf("Diretorio nao encontrado. Voce quis dizer:\n");
        while(child != NULL) {
            if(child->type == FOLDER_TYPE && strstr(child->name, path) != NULL) {
                printf("  %s/\n", child->name);
                suggestions_found++;}
            child = child->next_sibling;}
        if(!suggestions_found) {
            printf("  (Nenhuma alternativa encontrada)\n");}
        return current_dir;}}


/**
 * @brief 
 */
void search_recursive(Node* current, const char* name, bool* found) {
    if (current == NULL) return;
    if (strcmp(current->name, name) == 0) {
        *found = true;
        printf("Encontrado: ");
        print_path_to_node(current);
        printf("\n");}
    search_recursive(current->children_head, name, found);
    search_recursive(current->next_sibling, name, found);}

/**
 * @brief 
 */
void search_fs(Node* root, const char* name) {
    bool found = false;
    search_recursive(root->children_head, name, &found);
    if (!found) {
        printf("Arquivo ou pasta '%s' nao encontrado.\n", name);}}


/**
 * @brief 
 */
void remove_node(Node* current_dir, const char* name) {
    Node* child_to_remove = find_child(current_dir, name);
    if (child_to_remove == NULL) {
        printf("Erro: Arquivo ou pasta '%s' nao encontrado.\n", name);
        return;}
    if (current_dir->children_head == child_to_remove) {
        current_dir->children_head = child_to_remove->next_sibling;
    } else {
        Node* temp = current_dir->children_head;
        while (temp->next_sibling != child_to_remove) {
            temp = temp->next_sibling;}
        temp->next_sibling = child_to_remove->next_sibling;}
    child_to_remove->next_sibling = NULL; 
    free_tree(child_to_remove);
    printf("'%s' removido com sucesso.\n", name);}

/**
 * @brief 
 */
void create_directory(Node* current_dir, const char* name) {
    if (find_child(current_dir, name) != NULL) {
        printf("Erro: Ja existe um arquivo ou pasta com o nome '%s'.\n", name);
        return;}
    if (strchr(name, '.') != NULL || strchr(name, '/') != NULL){
        printf("Erro: Nome de pasta invalido.\n");
        return;}
    Node* new_dir = create_node(name, FOLDER_TYPE, current_dir);
    add_child(current_dir, new_dir);
    printf("Pasta '%s' criada.\n", name);}

/**
 * @brief 
 */
void print_path_to_node(Node* node) {
    if (node == NULL || node->parent == NULL) { 
        printf("root");
        return;}
    print_path_to_node(node->parent);
    printf("/%s", node->name);}

/**
 * @brief 
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
 * @brief 
 */
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


const char* get_directory_contents(Node* current_dir) {
    // Usamos um buffer estático para simplificar o gerenciamento de memória.
    // Isso significa que você deve copiar o resultado no Python antes de chamar a função novamente.
    static char buffer[4096]; 
    memset(buffer, 0, sizeof(buffer)); // Limpa o buffer

    if (current_dir->type != FOLDER_TYPE) {
        snprintf(buffer, sizeof(buffer), "ERRO: Nao e uma pasta.");
        return buffer;
    }

    Node* child = current_dir->children_head;
    if (child == NULL) {
        return ""; // Retorna string vazia se o diretório estiver vazio
    }

    char* current_pos = buffer;
    size_t remaining_size = sizeof(buffer);

    while (child != NULL) {
        int written;
        if (child->type == FOLDER_TYPE) {
            written = snprintf(current_pos, remaining_size, "%s/|", child->name);
        } else {
            written = snprintf(current_pos, remaining_size, "%s|", child->name);
        }

        if (written > 0) {
            current_pos += written;
            remaining_size -= written;
        }

        if (remaining_size <= 1) { // Checagem de segurança
            break;
        }
        child = child->next_sibling;
    }
    
    // Remove o último '|' se existir
    if (strlen(buffer) > 0) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    return buffer;
}


void build_path_recursive(Node* node, char* buffer, size_t buffer_size) {
    if (node == NULL || node->parent == NULL) {
        return;
    }
    build_path_recursive(node->parent, buffer, buffer_size);
    strncat(buffer, "/", buffer_size - strlen(buffer) - 1);
    strncat(buffer, node->name, buffer_size - strlen(buffer) - 1);
}

// Função principal que Python irá chamar
const char* get_node_path_string(Node* node) {
    static char path_buffer[1024];
    if (node == NULL) {
        snprintf(path_buffer, sizeof(path_buffer), "");
        return path_buffer;
    }
    snprintf(path_buffer, sizeof(path_buffer), "root");
    build_path_recursive(node, path_buffer, sizeof(path_buffer));
    return path_buffer;
}