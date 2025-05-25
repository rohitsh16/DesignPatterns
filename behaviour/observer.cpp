#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temp) = 0; // Gets called on temperature change
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(shared_ptr<Observer> observer) = 0;  // Add observer
    virtual void detach(shared_ptr<Observer> observer) = 0;  // Remove observer
    virtual void notify() = 0;                               // Notify all
};

class WeatherStation : public Subject {
public:
    void setTemp(float temp) {
        temperature = temp;
        notify();
    }

    void attach(shared_ptr<Observer> observer) override {
        observers.emplace_back(observer);
    }

    void detach(shared_ptr<Observer> observer) override {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notify() override {
        for (const auto& observer : observers) {
            if (observer) {
                observer->update(temperature);
            }
        }
    }

private:
    float temperature = 0.0f;
    vector<shared_ptr<Observer>> observers;
};

class Phone : public Observer {
public:
    void update(float temp) override {
        cout << "Phone Display: Current temperature is " << temp << "°C\n";
    }
};

class Computer : public Observer {
public:
    void update(float temp) override {
        cout << "Computer Display: Current temperature is " << temp << "°C\n";
    }
};

int main() {
    WeatherStation station;

    auto phone = make_shared<Phone>();
    auto computer = make_shared<Computer>();

    station.attach(phone);
    station.attach(computer);

    station.setTemp(25.0f);
    station.setTemp(30.5f);

    station.detach(phone);

    station.setTemp(28.0f);

    return 0;
}

/*
Observer Pattern Summary:

1. Used to notify a list of observers (subscribers) when the subject (publisher) state changes.
2. Decouples the subject from its observers — they don’t need to know about each other's concrete types.

Key Parts:
- Subject (Publisher): WeatherStation
- Observer (Subscriber): Phone, Computer
- Behavior: WeatherStation calls `update()` on all observers when temperature changes

Real-world Uses:
- GUI frameworks (button clicks)
- Messaging systems (chat apps, pub/sub)
- Game dev (event managers)
*/
