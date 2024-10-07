#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>
#include <vector>

class editfun {
    public:
        enum Type { INSERT, DELETE };

        editfun();
        editfun(Type type, const std::string& text, size_t position);
        editfun(const editfun& other);

        Type getType() const;
        const std::string& getText() const;
        size_t getPosition() const;

        void setType(Type type);
        void setText(const std::string& text);
        void setPosition(size_t position);

    private:
        Type type_;
        std::string text_;
        size_t position_;
};

class textedit {
public:
    textedit();
    textedit(const textedit& other);

    void insertText(const std::string& text, size_t position);
    void deleteText(size_t start, size_t end);
    void undo();
    void redo();
    const std::string& getText() const;

private:
    std::string text_;
    std::vector<editfun> undoStack_;
    std::vector<editfun> redoStack_;
};


#endiff
