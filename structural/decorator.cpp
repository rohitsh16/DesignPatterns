#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
};

class SimpleCoffee : public Coffee {
public:
    string getDescription() const override {
        return "Simple Coffee";
    }

    double getCost() const override {
        return 5.0;  // base price
    }
};

class CoffeeDecorator : public Coffee {
public:
    CoffeeDecorator(shared_ptr<Coffee> c) : coffee(move(c)) {}

protected:
    shared_ptr<Coffee> coffee;
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(shared_ptr<Coffee> c) : CoffeeDecorator(move(c)) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() const override {
        return coffee->getCost() + 1.5; // added milk cost
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(shared_ptr<Coffee> c) : CoffeeDecorator(move(c)) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() const override {
        return coffee->getCost() + 0.5; // added sugar cost
    }
};

int main() {
    shared_ptr<Coffee> coffee = make_shared<SimpleCoffee>();

    coffee = make_shared<MilkDecorator>(coffee);

    coffee = make_shared<SugarDecorator>(coffee);

    cout << "Order: " << coffee->getDescription() << "\n";
    cout << "Cost: $" << coffee->getCost() << "\n";

    return 0;
}

/*
Decorator Pattern Summary:

1. Allows dynamic addition of responsibilities to objects at runtime.
2. Avoids class explosion caused by subclassing every possible feature combination.
3. Promotes composition over inheritance.

Pattern Parts:
- Component       => `Coffee` (interface)
- Concrete        => `SimpleCoffee`
- Decorators      => `MilkDecorator`, `SugarDecorator`
- Base Decorator  => `CoffeeDecorator`
- Client          => `main()`

Real-world uses:
- UI frameworks (borders, scrollbars)
- I/O streams (buffering, compression)
- Game items (character power-ups)

*/
