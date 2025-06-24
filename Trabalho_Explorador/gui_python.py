import customtkinter as ctk
import ctypes
import platform
import os
lib_name = ""
if platform.system() == "Windows":
    lib_name = "./matriz.dll"
elif platform.system() == "Linux":
    lib_name = "./matriz.so"
elif platform.system() == "Darwin": 
    lib_name = "./matriz.dylib"
else:
    raise RuntimeError("Sistema operacional não suportado")
try:
    c_lib = ctypes.CDLL(lib_name)
except FileNotFoundError:
    print(f"Erro: Biblioteca '{lib_name}' não encontrada.")
    print("Certifique-se de que você compilou o código C no mesmo diretório.")
    exit()
except OSError as e:
    print(f"Erro do Sistema Operacional ao carregar a DLL: {e}")
    print("Isso geralmente indica um conflito de arquitetura (32-bit vs 64-bit).")
    exit()
node_p = ctypes.c_void_p

c_lib.create_node.argtypes = [ctypes.c_char_p, ctypes.c_int, node_p]
c_lib.create_node.restype = node_p

c_lib.read_input_file.argtypes = [node_p, ctypes.c_char_p]
c_lib.read_input_file.restype = None

c_lib.change_directory.argtypes = [node_p, ctypes.c_char_p]
c_lib.change_directory.restype = node_p

c_lib.get_directory_contents.argtypes = [node_p]
c_lib.get_directory_contents.restype = ctypes.c_char_p

c_lib.get_node_path_string.argtypes = [node_p]
c_lib.get_node_path_string.restype = ctypes.c_char_p


class App(ctk.CTk):
    def __init__(self):
        super().__init__()
        self.title("Explorador de Arquivos (Python + C)")
        self.geometry("500x400")

        self.root = c_lib.create_node(b"root", 1, None) 
        self.current_dir = self.root
        c_lib.read_input_file(self.root, b"in.txt")

        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure(1, weight=1)

        self.top_frame = ctk.CTkFrame(self, fg_color="transparent")
        self.top_frame.grid(row=0, column=0, padx=10, pady=(10,0), sticky="ew")

        self.up_button = ctk.CTkButton(self.top_frame, text="Cima", width=50, command=self.go_up)
        self.up_button.pack(side="left")

        self.path_label = ctk.CTkLabel(self.top_frame, text="", anchor="w")
        self.path_label.pack(side="left", fill="x", expand=True, padx=10)

        self.scrollable_frame = ctk.CTkScrollableFrame(self)
        self.scrollable_frame.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")

        self.update_view()

    def update_view(self):
        """Atualiza o frame rolável com o conteúdo do diretório atual."""

        for widget in self.scrollable_frame.winfo_children():
            widget.destroy()

        contents_bytes = c_lib.get_directory_contents(self.current_dir)
        contents_str = contents_bytes.decode("utf-8")

        if contents_str:
            items = contents_str.split('|')
            for item in items:
                is_folder = item.endswith('/')
                icon = "📁" if is_folder else "📄"
                
                display_name = item.strip('/')
                
                label = ctk.CTkLabel(self.scrollable_frame, text=f"{icon} {display_name}", cursor="hand2")
                label.pack(anchor="w", padx=5, pady=3)
                
                label.bind("<Double-Button-1>", lambda event, current_item=item: self.on_item_double_click(current_item))
        else:
            ctk.CTkLabel(self.scrollable_frame, text="(Este diretório está vazio)").pack(anchor="w")

        path_bytes = c_lib.get_node_path_string(self.current_dir)
        path_str = path_bytes.decode("utf-8")
        self.path_label.configure(text=path_str)


    def go_up(self):
        """Sobe um nível no diretório."""
        if self.current_dir == self.root:
            return
            
        new_dir = c_lib.change_directory(self.current_dir, b"..")
        if new_dir:
            self.current_dir = new_dir
            self.update_view()

    def on_item_double_click(self, selected_item):
        """Entra em uma pasta quando o usuário dá um duplo clique."""
        if selected_item.endswith('/'):
            folder_name = selected_item[:-1] 
            
            new_dir = c_lib.change_directory(self.current_dir, folder_name.encode("utf-8"))
            
            if new_dir:
                self.current_dir = new_dir
                self.update_view()

if __name__ == "__main__":
    app = App()
    app.mainloop()