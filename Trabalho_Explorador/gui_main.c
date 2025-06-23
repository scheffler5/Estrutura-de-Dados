#include <gtk/gtk.h>
#include "matriz.h"

// Enum para as colunas na nossa visualização de lista/árvore
// Para facilitar a leitura do código
enum {
    COLUMN_TEXT,
    COLUMN_ICON,
    COLUMN_NODE_POINTER, // Coluna oculta para armazenar o ponteiro para o nosso nó da árvore
    NUM_COLUMNS
};

// Estrutura para agrupar os widgets importantes da nossa aplicação
// Facilita o acesso a eles nas funções de callback
typedef struct {
    GtkWidget *window;
    GtkWidget *tree_view;
    GtkWidget *icon_view;
    GtkWidget *path_entry;
    Node *root_node;
    Node *current_dir;
    GtkTreeStore *tree_store;
    GtkListStore *list_store;
} AppWidgets;

// --- Protótipos das Funções ---

void update_path_bar(AppWidgets *widgets);
void update_icon_view(AppWidgets *widgets, Node *dir_node);
void populate_tree_store(GtkTreeStore *store, GtkTreeIter *parent_iter, Node *node, AppWidgets* widgets);
void on_tree_selection_changed(GtkTreeSelection *selection, gpointer data);
void on_icon_view_item_activated(GtkIconView *icon_view, GtkTreePath *path, gpointer data);

/**
 * @brief Atualiza a barra de endereço com o caminho do diretório atual.
 */
void update_path_bar(AppWidgets *widgets) {
    // Para construir a string do caminho
    char path_string[1024] = {0};
    
    // Usa uma função auxiliar para gerar a string do caminho
    GString* path_gstr = g_string_new("root");
    Node* temp = widgets->current_dir;
    
    // Sobe na árvore a partir do nó atual para construir o caminho
    while(temp->parent != NULL) {
        GString* old_path = g_string_new(path_gstr->str);
        g_string_printf(path_gstr, "%s/%s", temp->name, old_path->str);
        g_string_free(old_path, TRUE);
        temp = temp->parent;
    }
    
    // Define o texto na barra de endereço (GtkEntry)
    if(widgets->current_dir->parent != NULL){
       g_string_printf(path_gstr, "root/%s", widgets->current_dir->name);
    }

    gtk_entry_set_text(GTK_ENTRY(widgets->path_entry), path_gstr->str);
    g_string_free(path_gstr, TRUE);
}


/**
 * @brief Atualiza a visualização de ícones (painel direito) para mostrar o conteúdo de uma pasta.
 */
void update_icon_view(AppWidgets *widgets, Node *dir_node) {
    // Limpa a lista de ícones antiga
    gtk_list_store_clear(widgets->list_store);

    Node *child = dir_node->children_head;
    while (child != NULL) {
        GtkTreeIter list_iter;
        GdkPixbuf *pixbuf = NULL;
        GtkIconTheme *icon_theme = gtk_icon_theme_get_default();

        // Escolhe o ícone com base no tipo (pasta ou arquivo)
        if (child->type == FOLDER_TYPE) {
            pixbuf = gtk_icon_theme_load_icon(icon_theme, "folder-symbolic", 48, 0, NULL);
        } else {
            pixbuf = gtk_icon_theme_load_icon(icon_theme, "text-x-generic-symbolic", 48, 0, NULL);
        }

        // Adiciona o item à lista
        gtk_list_store_append(widgets->list_store, &list_iter);
        gtk_list_store_set(widgets->list_store, &list_iter,
                           COLUMN_TEXT, child->name,
                           COLUMN_ICON, pixbuf,
                           COLUMN_NODE_POINTER, child,
                           -1);
        
        if (pixbuf) g_object_unref(pixbuf);
        child = child->next_sibling;
    }
    // Atualiza o diretório atual e a barra de caminho
    widgets->current_dir = dir_node;
    update_path_bar(widgets);
}

/**
 * @brief Função recursiva para popular a árvore de diretórios (painel esquerdo).
 */
void populate_tree_store(GtkTreeStore *store, GtkTreeIter *parent_iter, Node *node, AppWidgets* widgets) {
    if (node == NULL) return;

    Node *child = node->children_head;
    while (child != NULL) {
        // Apenas pastas são mostradas na árvore da esquerda
        if (child->type == FOLDER_TYPE) {
            GtkTreeIter tree_iter;
            GdkPixbuf *pixbuf = NULL;
            GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
            pixbuf = gtk_icon_theme_load_icon(icon_theme, "folder-symbolic", 16, 0, NULL);

            gtk_tree_store_append(store, &tree_iter, parent_iter);
            gtk_tree_store_set(store, &tree_iter,
                               COLUMN_TEXT, child->name,
                               COLUMN_ICON, pixbuf,
                               COLUMN_NODE_POINTER, child,
                               -1);
            
            if (pixbuf) g_object_unref(pixbuf);

            // Chamada recursiva para os subdiretórios
            populate_tree_store(store, &tree_iter, child, widgets);
        }
        child = child->next_sibling;
    }
}


/**
 * @brief Callback: chamado quando a seleção na árvore da esquerda muda.
 */
void on_tree_selection_changed(GtkTreeSelection *selection, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    GtkTreeIter iter;
    GtkTreeModel *model;
    Node *selected_node = NULL;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Obtém o ponteiro para o nosso nó que foi armazenado na coluna oculta
        gtk_tree_model_get(model, &iter, COLUMN_NODE_POINTER, &selected_node, -1);
        if (selected_node) {
            update_icon_view(widgets, selected_node);
        }
    }
}

/**
 * @brief Callback: chamado quando um item é clicado/ativado no painel direito.
 */
void on_icon_view_item_activated(GtkIconView *icon_view, GtkTreePath *path, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    GtkTreeIter iter;
    Node *activated_node = NULL;

    if (gtk_tree_model_get_iter(GTK_TREE_MODEL(widgets->list_store), &iter, path)) {
        gtk_tree_model_get(GTK_TREE_MODEL(widgets->list_store), &iter, COLUMN_NODE_POINTER, &activated_node, -1);
        
        if (activated_node && activated_node->type == FOLDER_TYPE) {
            // Se for uma pasta, atualiza a visão para mostrar seu conteúdo
            update_icon_view(widgets, activated_node);
            
            // TODO: Também seria bom expandir e selecionar a pasta na árvore da esquerda
        } else if (activated_node) {
            // Se for um arquivo, apenas mostra uma mensagem por enquanto
            g_print("Arquivo '%s' ativado.\n", activated_node->name);
        }
    }
}

/**
 * @brief Callback: chamado quando o botão "Cima" é clicado.
 */
void on_up_button_clicked(GtkButton *button, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    if (widgets->current_dir->parent != NULL) {
        update_icon_view(widgets, widgets->current_dir->parent);
    }
}


/**
 * @brief Cria e configura todos os widgets da janela principal.
 */
void activate(GtkApplication *app, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    // --- Criação da Janela Principal ---
    widgets->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "Explorador de Arquivos");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 800, 600);

    // --- Layout Principal (Grid) ---
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widgets->window), grid);
    
    // --- Toolbar ---
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(grid), toolbar, 0, 0, 2, 1);

    GtkWidget *up_button = gtk_button_new_from_icon_name("go-up-symbolic", GTK_ICON_SIZE_BUTTON);
    g_signal_connect(up_button, "clicked", G_CALLBACK(on_up_button_clicked), widgets);
    gtk_box_pack_start(GTK_BOX(toolbar), up_button, FALSE, FALSE, 0);

    widgets->path_entry = gtk_entry_new();
    gtk_widget_set_hexpand(widgets->path_entry, TRUE);
    gtk_box_pack_start(GTK_BOX(toolbar), widgets->path_entry, TRUE, TRUE, 0);

    // --- Painel Dividido (Paned) ---
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_vexpand(paned, TRUE);
    gtk_grid_attach(GTK_GRID(grid), paned, 0, 1, 2, 1);
    
    // --- Painel Esquerdo (Árvore de Diretórios) ---
    GtkWidget *scrolled_window_tree = gtk_scrolled_window_new(NULL, NULL);
    gtk_paned_add1(GTK_PANED(paned), scrolled_window_tree);

    widgets->tree_store = gtk_tree_store_new(NUM_COLUMNS, G_TYPE_STRING, GDK_TYPE_PIXBUF, G_TYPE_POINTER);
    widgets->tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(widgets->tree_store));
    g_object_unref(widgets->tree_store); // O tree_view agora é dono do modelo

    GtkCellRenderer *renderer_text_tree = gtk_cell_renderer_text_new();
    GtkCellRenderer *renderer_pixbuf_tree = gtk_cell_renderer_pixbuf_new();
    GtkTreeViewColumn *column_tree = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(column_tree, renderer_pixbuf_tree, FALSE);
    gtk_tree_view_column_pack_start(column_tree, renderer_text_tree, TRUE);
    gtk_tree_view_column_add_attribute(column_tree, renderer_text_tree, "text", COLUMN_TEXT);
    gtk_tree_view_column_add_attribute(column_tree, renderer_pixbuf_tree, "pixbuf", COLUMN_ICON);

    gtk_tree_view_append_column(GTK_TREE_VIEW(widgets->tree_view), column_tree);
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(widgets->tree_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window_tree), widgets->tree_view);

    GtkTreeSelection *tree_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widgets->tree_view));
    g_signal_connect(tree_selection, "changed", G_CALLBACK(on_tree_selection_changed), widgets);

    // --- Painel Direito (Ícones) ---
    GtkWidget *scrolled_window_icons = gtk_scrolled_window_new(NULL, NULL);
    gtk_paned_add2(GTK_PANED(paned), scrolled_window_icons);

    widgets->list_store = gtk_list_store_new(NUM_COLUMNS, G_TYPE_STRING, GDK_TYPE_PIXBUF, G_TYPE_POINTER);
    widgets->icon_view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(widgets->list_store));
    g_object_unref(widgets->list_store); // O icon_view agora é dono do modelo

    gtk_icon_view_set_text_column(GTK_ICON_VIEW(widgets->icon_view), COLUMN_TEXT);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(widgets->icon_view), COLUMN_ICON);
    gtk_container_add(GTK_CONTAINER(scrolled_window_icons), widgets->icon_view);
    g_signal_connect(widgets->icon_view, "item-activated", G_CALLBACK(on_icon_view_item_activated), widgets);


    // --- Povoar os dados ---
    populate_tree_store(widgets->tree_store, NULL, widgets->root_node, widgets);
    update_icon_view(widgets, widgets->root_node); // Mostra o conteúdo da raiz inicialmente
    
    gtk_widget_show_all(widgets->window);
}


int main(int argc, char *argv[]) {
    // Aloca a estrutura que guardará nossos widgets
    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    // Cria a estrutura de dados em memória a partir do arquivo
    widgets->root_node = create_node("root", FOLDER_TYPE, NULL);
    widgets->current_dir = widgets->root_node;
    read_input_file(widgets->root_node, "in.txt");

    // Cria a aplicação GTK
    GtkApplication *app = gtk_application_new("com.example.file_explorer", G_APPLICATION_FLAGS_NONE);
    
    // Conecta o sinal "activate" para construir a UI quando a app for iniciada
    g_signal_connect(app, "activate", G_CALLBACK(activate), widgets);

    // Roda a aplicação
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // Libera a memória ao sair
    g_object_unref(app);
    free_tree(widgets->root_node);
    g_free(widgets);

    return status;
}
