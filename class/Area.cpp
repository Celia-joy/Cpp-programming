#include <iostream>
using namespace std;
double const Pi=3.14159265;
int doubleArea(double radius){
	return Pi*radius*radius;	
}
int main(){
	int radius;
	cout<<"Enter the radius: "<<endl;
	cin>>radius;
	cout<<"The circumference is: "<<2*Pi*radius<<endl;
	cout<<"The area is: "<<::doubleArea(radius)<<endl;
	return 0;
}