#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Strategy Interface
class TextFormatter {
public: 
    virtual ~TextFormatter() = default;
    virtual void format(const string &text) = 0;
};

class PlainText : public TextFormatter {
public: 
    void format(const string &text) override {
        cout << text << "\n";
    }
};

class HTMLText : public TextFormatter {
public: 
    void format(const string &text) override {
        cout << "<p>" << text << "</p>\n";
    }
};

class TextEditor {
public:
    // Allows changing the strategy at runtime
    void setFormatter(unique_ptr<TextFormatter> newFormatter) {
        formatter = move(newFormatter); // Transfer ownership of the strategy
    }

    // Delegates formatting to the current strategy
    void publishText(const string &text) {
        if (formatter) {
            formatter->format(text);
        } else {
            cout << "No formatter set.\n";
        }
    }

private:
    unique_ptr<TextFormatter> formatter; // Holds the current formatting strategy
};

// Client code
int main() {
    TextEditor editor;

    editor.setFormatter(make_unique<PlainText>());
    editor.publishText("Hello World"); 
    
    editor.setFormatter(make_unique<HTMLText>());
    editor.publishText("Hello World");

    return 0;
}

/*
Strategy Design Pattern Summary:

1. Allows you to switch behavior (algorithm) at runtime without modifying the context.
2. Promotes the Open/Closed Principle — new strategies can be added without changing existing code.

Pattern Components:
- Strategy Interface: `TextFormatter`
- Concrete Strategies: `PlainText`, `HTMLText`
- Context: `TextEditor`
- Client: `main()`

Real-World Use Case:
Text editors, games (enemy AI), payment systems, logging frameworks, sorting utilities.
*/
