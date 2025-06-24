#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @enum 
 * @brief
 */
typedef enum {
    FILE_TYPE,
    FOLDER_TYPE
} NodeType;

/**
 * @struct 
 * @brief 
 */
typedef struct Node {
    char* name;
    NodeType type;
    struct Node* parent;
    struct Node* children_head;
    struct Node* next_sibling;
} Node;
Node* create_node(const char* name, NodeType type, Node* parent);
void free_tree(Node* node);
void insert_path(Node* root, const char* path);
void read_input_file(Node* root, const char* filename);
void list_directory(Node* current_dir);
Node* change_directory(Node* current_dir, const char* path);
void search_fs(Node* root, const char* name);
void remove_node(Node* current_dir, const char* name);
void create_directory(Node* current_dir, const char* name);
void print_path_to_node(Node* node);
void show_help();
void clear_screen();
#endif 
const char* get_directory_contents(Node* current_dir);
const char* get_node_path_string(Node* node);