
#include <iostream>
#include <string>
using namespace std;

class Learner {
private:
    int code;
    string name;
    string school;

public:
    Learner() : code(0), name(""), school("") {}

    Learner(int code, const string& name, const string& school)
        : code(code), name(name), school(school) {}

    int getCode() const {
        return code;
    }

    string getName() const {
        return name;
    }

    string getSchool() const {
        return school;
    }

    void setCode(int newCode) {
        code = newCode;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setSchool(const string& newSchool) {
        school = newSchool;
    }

    void display() const {
        cout << "Code: " << code
             << ", Name: " << name
             << ", School: " << school << endl;
    }
};