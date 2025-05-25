#include <iostream>
#include <memory>

using namespace std;

// Abstract Prototype
class Shape {
public:
    virtual ~Shape() = default;  // Virtual destructor for proper cleanup
    virtual void draw() = 0;     // Interface for drawing
    virtual unique_ptr<Shape> clone() const = 0; // Prototype interface
};

// Concrete Prototype 1
class Square : public Shape {
public: 
    Square(int side) : side(side) {}

    void draw() override {
        cout << "Draw Square with side " << side << "\n";
    }

    unique_ptr<Shape> clone() const override {
        return make_unique<Square>(side);  // Clone with same state
    }

private:
    int side;
};

// Concrete Prototype 2
class Rectangle : public Shape {
public:
    Rectangle(int l, int b) : length(l), breadth(b) {}

    void draw() override {
        cout << "Draw Rectangle with length " << length << " and breadth " << breadth << "\n";
    }

    unique_ptr<Shape> clone() const override {
        return make_unique<Rectangle>(length, breadth); // Clone with same state
    }

private:
    int length, breadth;
};

int main() {
    // Original shape
    std::unique_ptr<Shape> original = std::make_unique<Square>(10);
    
    // Clone of the shape
    std::unique_ptr<Shape> copy = original->clone();

    // Both objects behave the same but are distinct
    original->draw();
    copy->draw();

    return 0;
}

/*
Prototype Design Pattern Summary:

1. Allows cloning of objects without knowing their exact class.
2. Used when object creation is costly (e.g., complex initialization, database fetch, etc.).
3. Each subclass implements its own `clone()` method to return a deep copy of itself.
4. Avoids the need for conditionals (like a Factory might use) by copying existing instances.
5. Useful in scenarios like graphics editors, game dev, and frameworks needing object duplication.

Roles:
- Prototype (interface): Shape
- Concrete Prototypes: Square, Rectangle
- Client: main()

*/
