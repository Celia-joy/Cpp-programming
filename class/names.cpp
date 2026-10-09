#include <iostream>
using namespace std;
namespace myspace{
	int value = 30;
	int compute(){
		return value*value;
	}
}
	int value = 10;
int main(){
	double value = 20;
	cout<<"Local variable "<<value<<endl;
	//::Scope resolution operator
	cout<<"Global variable "<<::value<<endl;
	//Printing the value in myspace
	cout<<"The value in myspace is "<<myspace::value<<endl;
	cout<<myspace::compute();
	return 0;
}
