#include "text_editor.h"
#ifndef undo_redo_del_h
#define undo_redo_del_h

editfun::editfun(Type type, const std::string& text, size_t position) :
  type_(type), text_(text), position_(position) {}

editfun::Type editfun::get_type() const {
  return type_;
}

const std::string& editfun::get_text() const {
  return text_;
}

size_t editfun::get_position() const {
  return position_;
}

textedit::textedit() {}

void textedit::insert(const std::string& text, size_t position) {
  text_.insert(position, text);
  undoStack_.push_back(editfun(editfun::INSERT, text, position));
  redoStack_.clear();
}

void textedit::deletet(size_t start, size_t end) {
  std::string deletedText = text_.substr(start, end - start);
  text_.erase(start, end - start);
  undoStack_.push_back(editfun(editfun::DELETE, deletedText, start));
  redoStack_.clear();
}

void textedit::undo() {
  if (!undoStack_.empty()) {
    editfun lastOperation = undoStack_.back();
    undoStack_.pop_back();

    if (lastOperation.get_type() == editfun::INSERT) {
      text_.erase(lastOperation.get_position(), lastOperation.get_text().size());
      redoStack_.push_back(lastOperation);
    } else if (lastOperation.get_type() == editfun::DELETE) {
      text_.insert(lastOperation.get_position(), lastOperation.get_text());
      redoStack_.push_back(lastOperation);
    }
  }
}

void textedit::redo() {
  if (!redoStack_.empty()) {
    editfun lastOperation = redoStack_.back();
    redoStack_.pop_back();

    if (lastOperation.get_type() == editfun::INSERT) {
      text_.insert(lastOperation.get_position(), lastOperation.get_text());
      undoStack_.push_back(lastOperation);
    } else if (lastOperation.get_type() == editfun::DELETE) {
      text_.erase(lastOperation.get_position(), lastOperation.get_text().size());
      undoStack_.push_back(lastOperation);
    }
  }
}

const std::string& textedit::getText() const {
  return text_;
}

#endif