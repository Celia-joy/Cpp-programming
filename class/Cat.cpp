
#include <iostream>
#include "Animal.cpp"
using namespace std;

class Cat : public Animal {
public:
    Cat(int code = 105) : Animal(code) {}

    void Sound() const override {
        cout << "Cat meows" << endl;
    }
};