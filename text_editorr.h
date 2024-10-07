#include "text_editor.h"
#include <cassert>
#include <iostream>

#ifndef TEXT_EDITORR_H
#define TEXT_EDITORR_H

editfun:: editfun() : type_(Type::INSERT), text_(""), position_(0) {}


editfun::editfun(Type type, const std::string& text, size_t position) :
    type_(type), text_(text), position_(position) {}

editfun::editfun(const editfun& other) :
    type_(other.type_), text_(other.text_), position_(other.position_) {}

editfun::Type editfun::getType() const {
    return type_;
}

const std::string& editfun::getText() const {
    return text_;
}

size_t editfun::getPosition() const {
    return position_;
}

void editfun::setType(Type type) {
    type_ = type;
}

void editfun::setText(const std::string& text) {
    text_ = text;
}

void editfun::setPosition(size_t position) {
    position_ = position;
}



textedit::textedit() {}

textedit::textedit(const textedit& other) :
    text_(other.text_),
    undoStack_(other.undoStack_),
    redoStack_(other.redoStack_) {}

void textedit::insertText(const std::string& text, size_t position) {
    text_.insert(position, text);
    undoStack_.push_back(editfun(editfun::INSERT, text, position));
    redoStack_.clear();
}

void textedit::deleteText(size_t start, size_t end) {
    std::string deletedText = text_.substr(start, end - start);
    text_.erase(start, end - start);
    undoStack_.push_back(editfun(editfun::DELETE, deletedText, start));
    redoStack_.clear();
}

void textedit::undo() {
    if (!undoStack_.empty()) {
        editfun lastOperation = undoStack_.back();
        undoStack_.pop_back();

        if (lastOperation.getType() == editfun::INSERT) {
            text_.erase(lastOperation.getPosition(), lastOperation.getText().size());
            redoStack_.push_back(lastOperation);
        } else if (lastOperation.getType() == editfun::DELETE) {
            text_.insert(lastOperation.getPosition(), lastOperation.getText());
            redoStack_.push_back(lastOperation);
        }
    }
}

void textedit::redo() {
    if (!redoStack_.empty()) {
        editfun lastOperation = redoStack_.back();
        redoStack_.pop_back();

        if (lastOperation.getType() == editfun::INSERT) {
            text_.insert(lastOperation.getPosition(), lastOperation.getText());
            undoStack_.push_back(lastOperation);
        } else if (lastOperation.getType() == editfun::DELETE) {
            text_.erase(lastOperation.getPosition(), lastOperation.getText().size());
            undoStack_.push_back(lastOperation);
        }
    }
}

const std::string& textedit::getText() const {
    return text_;
}

#endif
