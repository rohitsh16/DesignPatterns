#include <iostream>
#include <memory>
#include <string>

using namespace std;

// the complex object
class Pizza {
public:
    void setDough(const string &dough_) {
        dough = dough_;
    }

    void setSauce(const std::string& sauce_) { 
        sauce = sauce_; 
    }

    void setTopping(const std::string& topping_) { 
        topping = topping_; 
    } 

    void showPizza() {
        std::cout << "Pizza with " << dough << " dough, "
                  << sauce << " sauce, and "
                  << topping << " topping.\n";
    }

private:
    string dough, sauce, topping; 
};

// define the building steps
class PizzaBuilder {
public: 
    virtual ~PizzaBuilder() = default;

    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

    // Returns the final product
    Pizza* getPizza() {  
        return pizza.release();  // releases the ownership of the object and returns the raw pointer
    }

protected:
    unique_ptr<Pizza> pizza = make_unique<Pizza>();
};

// implements the building steps
class SpicyPizzaBuilder : public PizzaBuilder {
public:
    void buildDough() override { 
        pizza->setDough("pan baked"); 
    }

    void buildSauce() override { 
        pizza->setSauce("spicy tomato"); 
    }

    void buildTopping() override { 
        pizza->setTopping("pepperoni and jalapenos"); 
    }
};

// Director
class Cook {
public:
    void makePizza(PizzaBuilder& builder) {
        builder.buildDough();
        builder.buildSauce();
        builder.buildTopping();
    }
};

int main() {
    SpicyPizzaBuilder builder;
    Cook cook;                 

    cook.makePizza(builder);   
    std::unique_ptr<Pizza> pizza(builder.getPizza());

    pizza->showPizza();

    return 0;
}

/*
Builder Design Pattern Summary:

1. Used for the creation of complex objects with multiple configurable parts.
2. Separates the construction process from the final representation.
3. Allows the same construction process to create different representations (e.g., SpicyPizzaBuilder vs VegPizzaBuilder).
4. Helps avoid telescoping constructors and improves readability and maintainability.

Roles:
- Product: Pizza
- Builder: PizzaBuilder (abstract)
- ConcreteBuilder: SpicyPizzaBuilder
- Director: Cook
- Client: main()
*/
