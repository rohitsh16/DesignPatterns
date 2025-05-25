#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() = 0;  // virtual function
    virtual ~Shape() = default; // default destructor
};

class Square : public Shape {
private:
public: 
    void draw() override {
        cout<<"Draw a circle\n";
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        cout<<"Draw a rectangle\n";
    }
};

class ShapeFactory {
public:
    static shared_ptr<Shape> createShape(const string &type) {
        if (type == "square")
            return std::make_unique<Square>();
        else if (type == "rectangle")
            return std::make_unique<Rectangle>();
        else
            return nullptr;
    }
};

int main() {
    auto shape1 = ShapeFactory::createShape("circle"); // user doesn't need to know the actual sub class
    auto shape2 = ShapeFactory::createShape("square");
    auto shape3 = ShapeFactory::createShape("rectangle");

    if (shape1) shape1->draw();
    if (shape2) shape2->draw();
    if (shape3) shape3->draw();
    return 0;
}

/*
Important Points
1. FactoryPattern --> To encapsulate object creation.
2. Virtual function --> subclass needs to implement
3. 
*/