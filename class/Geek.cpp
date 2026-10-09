#include <iostream>
#include 
using namespace std;

class Geek{
    private:
    int code;
    string name;
    string school;

    public:
    Geek(){}
    void display(){
        cout<<code<<" "<<name<<" "<<school<<endl;
    }

    int get_Code(){
        return code;
    }
    void set_Code(int code){
        this->code = code;
    }
    void set_name(string name){
        this->name = name;
    }
    void set_school(string school){
        this->school = school;
    }        
};


