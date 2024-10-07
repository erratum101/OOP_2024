#include "text_editor.h"
#include "undo_redo_del.h"
#include <iostream>

int main() {
    textedit editor;

    editor.insert("I", 0);
    editor.insert(" am alive", 1);
    std::cout << "text: " << editor.getText() << std::endl; 

    editor.deletet(1, 10);
    std::cout << "text: " << editor.getText() << std::endl; 

    editor.undo();
    std::cout << "text: " << editor.getText() << std::endl; 

    editor.redo();
    std::cout << "text: " << editor.getText() << std::endl; 
}
