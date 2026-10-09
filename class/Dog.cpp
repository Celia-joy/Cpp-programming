
#include <iostream>
#include "Animal.cpp"
using namespace std;

class Dog : public Animal {
public:
    Dog(int code = 105) : Animal(code) {}

    void Sound() const override {
        cout << "Dog barks" << endl;
    }
};