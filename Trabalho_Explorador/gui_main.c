#include "raylib.h"
#include "matriz.h" // Sua lógica de sistema de arquivos não muda!

// Para a interface, vamos usar raygui
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Estrutura para manter o estado da nossa UI
typedef struct {
    Node *root_node;
    Node *current_dir;
    Vector2 right_panel_scroll;
    int selected_item_index;
} AppState;


// Função para desenhar o conteúdo do diretório no painel direito
void DrawDirectoryContent(Rectangle panel_bounds, AppState* state) {
    // Desenha uma lista de arquivos/pastas
    Node* child = state->current_dir->children_head;
    int item_count = 0;
    while(child != NULL) {
        item_count++;
        child = child->next_sibling;
    }

    Rectangle view = GuiScrollPanel(panel_bounds, NULL, (Rectangle){ panel_bounds.x, panel_bounds.y, panel_bounds.width - 20, item_count * 30.0f }, &state->right_panel_scroll);
    
    BeginScissorMode(view.x, view.y, view.width, view.height);

        child = state->current_dir->children_head;
        int i = 0;
        while (child != NULL) {
            // Define a área de cada item da lista
            Rectangle item_rect = { 
                panel_bounds.x + state->right_panel_scroll.x + 10, 
                panel_bounds.y + state->right_panel_scroll.y + (i * 30) + 5, 
                panel_bounds.width - 40, 
                25 
            };
            
            // Determina o texto (ex: "pasta/" ou "arquivo.txt")
            char item_text[256];
            if (child->type == FOLDER_TYPE) {
                sprintf(item_text, "#1#%s/", child->name); // #1# é um ícone de pasta em raygui
            } else {
                sprintf(item_text, "#7#%s", child->name); // #7# é um ícone de arquivo
            }
            
            // Desenha o botão e verifica se foi clicado
            if (GuiButton(item_rect, item_text)) {
                // Se for uma pasta, entra nela
                if (child->type == FOLDER_TYPE) {
                    state->current_dir = child;
                    state->right_panel_scroll = (Vector2){ 0, 0 }; // Reseta o scroll
                } else {
                    // Se for um arquivo, podemos imprimir uma mensagem
                    printf("Arquivo '%s' clicado!\n", child->name);
                }
            }
            
            child = child->next_sibling;
            i++;
        }

    EndScissorMode();
}

// Função para gerar o caminho atual como uma string
void get_current_path_string(char* buffer, size_t buffer_size, Node* current_node) {
    if (current_node == NULL || current_node->parent == NULL) {
        snprintf(buffer, buffer_size, "root");
        return;
    }
    // Buffer temporário para construir o caminho de trás para frente
    char temp_path[1024] = {0};
    Node* temp = current_node;
    while(temp != NULL && temp->parent != NULL) {
        char segment[256];
        sprintf(segment, "/%s", temp->name);
        strcat(segment, temp_path);
        strcpy(temp_path, segment);
        temp = temp->parent;
    }
    snprintf(buffer, buffer_size, "root%s", temp_path);
}


int main(void) {
    // --- Configuração Inicial ---
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Explorador de Arquivos com Raylib");
    SetTargetFPS(60);

    // --- Carrega os dados do sistema de arquivos ---
    AppState state = {0};
    state.root_node = create_node("root", FOLDER_TYPE, NULL);
    state.current_dir = state.root_node;
    read_input_file(state.root_node, "in.txt"); // Lê a estrutura inicial do arquivo in.txt
    state.selected_item_index = -1;
    state.right_panel_scroll = (Vector2){ 0, 0 };

    // --- Loop Principal (o "Game Loop") ---
    while (!WindowShouldClose()) {
        // --- Lógica de Atualização (a cada quadro) ---
        
        // --- Desenho (a cada quadro) ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- Desenha a Toolbar Superior ---
        Rectangle top_bar_rect = { 0, 0, screenWidth, 40 };
        GuiPanel(top_bar_rect, NULL);

        // Botão "Cima"
        if (GuiButton((Rectangle){ 5, 5, 30, 30 }, "#121#")) { // Ícone de seta para cima
            if (state.current_dir->parent != NULL) {
                state.current_dir = state.current_dir->parent;
                state.right_panel_scroll = (Vector2){ 0, 0 }; // Reseta o scroll
            }
        }

        // Barra de Endereço
        char path_buffer[1024];
        get_current_path_string(path_buffer, sizeof(path_buffer), state.current_dir);
        GuiTextBox((Rectangle){ 40, 5, screenWidth - 45, 30 }, path_buffer, 1024, false);


        // --- Desenha o Painel de Conteúdo ---
        Rectangle right_panel_rect = { 5, 45, screenWidth - 10, screenHeight - 50 };
        DrawDirectoryContent(right_panel_rect, &state);

        EndDrawing();
    }

    // --- Limpeza ---
    free_tree(state.root_node);
    CloseWindow();
    return 0;
}