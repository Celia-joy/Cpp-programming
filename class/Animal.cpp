
#include <iostream>
#include <string>
using namespace std;

class Animal {
private:
    int code;

public:
    Animal(int code = 105) : code(code) {}

    int getCode() const {
        return code;
    }

    virtual void Sound() const {
        cout << "Animal makes sound" << endl;
    }

    virtual ~Animal() = default;
};