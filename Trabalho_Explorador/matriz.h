#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @enum NodeType
 * @brief Enumeração para distinguir entre arquivos e pastas.
 */
typedef enum {
    FILE_TYPE,
    FOLDER_TYPE
} NodeType;

/**
 * @struct Node
 * @brief Estrutura de um nó da árvore de diretórios.
 *
 * Cada nó representa um arquivo ou uma pasta.
 * - name: Nome do arquivo ou pasta.
 * - type: Tipo do nó (FILE_TYPE ou FOLDER_TYPE).
 * - parent: Ponteiro para o nó pai (essencial para 'cd ..').
 * - children_head: Ponteiro para o primeiro filho na lista ligada de filhos.
 * - next_sibling: Ponteiro para o próximo irmão na lista de filhos.
 */
typedef struct Node {
    char* name;
    NodeType type;
    struct Node* parent;
    struct Node* children_head;
    struct Node* next_sibling;
} Node;

// --- Declarações das Funções ---

// Funções do núcleo da árvore
Node* create_node(const char* name, NodeType type, Node* parent);
void free_tree(Node* node);
void insert_path(Node* root, const char* path);
void read_input_file(Node* root, const char* filename);

// Funções de comando do shell
void list_directory(Node* current_dir);
Node* change_directory(Node* current_dir, const char* path);
void search_fs(Node* root, const char* name);
void remove_node(Node* current_dir, const char* name);
void create_directory(Node* current_dir, const char* name);

// Funções de utilidade
void print_path_to_node(Node* node);
void show_help();
void clear_screen();

#endif // MATRIZ_H
