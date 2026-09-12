#include <iostream>
using namespace std;
#define numberOfDistricts 30
//const short numberOfDistricts = 30;
int myGlobal = 20;
int cout1(){
	return myGlobal*myGlobal;
}
namespace userDefined{
	int insideNamespace = 40;
	int cout2(){
		return insideNamespace;
	}
}
int main(){
	int cout3 = 30;
	cout<<"Local variable: "<<cout3<<endl;
	cout<<"The value inside userDefined: "<<userDefined::insideNamespace<<endl;
	cout<<"The value inside userDefined(function): "<<userDefined::cout2()<<endl;
	cout<<"Global variable:"<<::myGlobal<<endl;
	cout<<"Global variable function: "<<::cout1()<<endl;
	cout<<"Number of districts: "<<numberOfDistricts<<endl;
	return 0;		
}