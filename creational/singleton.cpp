#include <iostream>

using namespace std;

class Singleton {
private:
    Singleton() { // private constructor 
    }

    ~Singleton() = default;

public:
    // = delete --> is modern way to disable certain function 
    Singleton(const Singleton&) = delete; // delete the copy constructor
    Singleton& operator = (const Singleton&) = delete; // delete the copy assignment

    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void display() {
        cout<<"instance is created\n";
    }
};

int main() {
    Singleton& instance1 = Singleton::getInstance();
    Singleton& instance2 = Singleton::getInstance();

    if (&instance1==&instance2) {
        cout<<"both the instances are same\n";
    }

    return 0;
}

/*
Important Points

1. Copy Constructor 
    ClassName(const ClassName&);

2. Copy Assignment Opertaot
    ClassName& operator=(const ClassName&); 

3. In >= C++11, local static variables are initialised in thread safe manner. Before C++11, we need to
   explicitly lock the object creation with mutex.

4. default --> compiler generates the code for that specific function. 
*/