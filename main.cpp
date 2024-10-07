#include "text_editor.h"
#include "text_editorr.h"
#include <iostream>
#include <cassert>
void testEditOperation() {

    editfun operation1;
    assert(operation1.getType() == editfun::INSERT);
    assert(operation1.getText() == "");
    assert(operation1.getPosition() == 0);

    editfun operation2(editfun::DELETE, "test", 5);
    assert(operation2.getType() == editfun::DELETE);
    assert(operation2.getText() == "test");
    assert(operation2.getPosition() == 5);

    editfun operation3(operation2);
    assert(operation3.getType() == editfun::DELETE);
    assert(operation3.getText() == "test");
    assert(operation3.getPosition() == 5);

    operation3.setType(editfun::INSERT);
    operation3.setText("new text");
    operation3.setPosition(10);
    assert(operation3.getType() == editfun::INSERT);
    assert(operation3.getText() == "new text");
    assert(operation3.getPosition() == 10);
    std::cout << " editfun - succass " << std::endl;
}

void testTextEditor() {

    textedit editor1;
    assert(editor1.getText() == "");

    textedit editor2(editor1);
    assert(editor2.getText() == "");

    editor1.insertText("I, ", 0);
    assert(editor1.getText() == "I, ");

    editor1.insertText("am alive!", 3);
    assert(editor1.getText() == "I, am alive!");

    editor1.deleteText(3, 12);
    assert(editor1.getText() == "I, ");

    editor1.undo();
    assert(editor1.getText() == "I, am alive!");

    editor1.redo();
    assert(editor1.getText() == "I, ");
    std::cout << " textedit - succass " << std::endl;
}

int main() {
    testEditOperation();
    testTextEditor();

    return 0;
}