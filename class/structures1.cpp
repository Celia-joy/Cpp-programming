#include <iostream>
#include <string>
using namespace std;

struct Student {
    int code;
    string name;
    string school;

    Student (int id, string name, string school){
        code = id;
        name = name;
        school = school;
    }
    Student(){}

    void display(){
        cout<<code<<" "<<name<<" "<<school<<endl;
    }
};

int main (){
    Student S1(102, "John", "RCA");
    S1.display();

    Student S2;
    S2.code = 105;
    S2.name = "Mary";
    S2.school = "FAWE";
    S2.display();

    Student S3 = {107, "Claude", "RCA"};
    S3.display();

    Student *Sy = new Student(108, "Mark", "RCA");
    Sy -> display();

    Student S5{1010, "Ganza", "RCA"};
    S5.display();

    return 0;
}