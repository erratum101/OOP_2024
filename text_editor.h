#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>
#include <vector>

class editfun {
public:
    enum Type { INSERT, DELETE };

    editfun(Type type, const std::string& text, size_t position);

    Type get_type() const;
    const std::string& get_text() const;
    size_t get_position() const;

private:
    Type type_;
    std::string text_;
    size_t position_;
};

class textedit {
public:
    textedit();

    void insert(const std::string& text, size_t position);
    void deletet(size_t start, size_t end);
    void undo();
    void redo();
    const std::string& getText() const;

private:
    std::string text_;
    std::vector<editfun> undoStack_;
    std::vector<editfun> redoStack_;
};

#endif
