#include <iostream>
using namespace std;

class Mammals {
public:
    void printMammal(){
        cout << "I'm a mammal" <<endl;
    }
};

class MarineAnimals {
public:
    void printMarineAnimal(){
        cout<< "I'm a marine animal" <<endl;
    }
};

class BlueWhale : public Mammals, public MarineAnimals {

};

int main (){
    BlueWhale bw;
    bw.printMammal();
    bw.printMarineAnimal();
    return 0;
}