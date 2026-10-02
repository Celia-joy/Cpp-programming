#include <iostream>
using namespace std;
template<typename T>
T addition (T a, T b){
	return a + b;
}

/*int addition (int a, int b){
    return a + b;
}

double addition (double a, double b){
    return a + b;
}

float addition (float a, float b){
    return a + b; 
}

string addition (string a, string b){
    return a + b;
}*/ 

int main() {
    cout<<"Integer addition: "<<addition<int>(1,4)<<endl;
    cout<<"Double addition: "<<addition<double>(9.72, 15.56)<<endl;
    cout<<"Many types addition: "<<addition<double>(2, 3.75)<<endl;
    cout<<"Float addition: "<<addition<float>(30.92f , 45.74f)<<endl;
    cout<<"String addition: "<<addition<string>("Hi ","Celia")<<endl;
    return 0;
}