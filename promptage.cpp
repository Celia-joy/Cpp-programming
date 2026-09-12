/*#include <stdio.h>
#include <iostream>
using namespace std;
int main(){
	int age;
	cout<<"Enter your age:\n";
	//printf("Enter your age:\n");
	//scanf("%d", &age);
	cin>>age;
	//printf("Your age is %d", age);
	cout<<"Your age is "<<age;
	cout<<"Your age is "<<age<<endl;
	//\n and endl are the same in C++
	return 0;
}*/

#include <iostream>
using namespace std;
int main(){
	int age;
	string gender;
	string name;
	/*cout<<"Enter your age:"<<endl;
	cin>>age;
	cout<<"Your age is "<<age<<endl;
	cout<<"Enter your gender:"<<endl;
	cin>>gender;
	cout<<"Your gender is "<<gender<<endl;
	cout<<"You are "<<age<<" years old and you are "<<gender<<endl;*/
	cout<<"Enter your age and gender: "<<endl;
	//>>:Extraction operator
	//<<:Insertion operator
	cin>> age>>gender;
	cout<<"Enter your name:"<<endl;
	//cin>>name;
	//Get user input in form of line
	cin.ignore();
	getline(cin,name);
	cout<<name<<" you are "<<age<<" years old and you are "<<gender<<endl;
	return 0;
}