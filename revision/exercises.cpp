#include <iostream>
using namespace std;

int main(){
    //PART 0
    /*
    //1.
    int x=15;
    int y=23;
    cout<<"x,y:"<<x<<" and "<<y<<endl;
    cout<<"x,y"<<++x<< " and "<<y++<<endl;
    cout<<"x="<<--x<<" and y= "<<y--<<endl;
    ++x;
    y++;
    cout<<"x="<<x<<" and y= "<<y<<endl;
    --x;
    y--;
    cout<<"x="<<x<< " and y="<<y<<endl;
    */

    /*
    //2.
    int a, c;
    int x=7;
    int y=9;
    cout<<"x="<<x<< "and y="<<y<<endl;
    a=++x;
    c=y++;
    cout<<"x="<<x<<" and y="<<y<<endl;
    cout<<"a = "<<a<<" and c= "<<c<<endl;
    a=--x;
    c=y--;
    cout<<"x="<<x<<"and y="<<y<<endl;
    cout<<"a="<<a<<" and c= "<<c<<endl;
    */


    //3.
    int x=10, y=20, z=5, t=2, s=7, k,f,p,h,q;
    k=x/y%s*t+y/x*t;
	f=x*y/z%s*t-s*x/t;
	p=y/x*t;
	h=x*y/z%s*t-s*x/t+y/x*t;
	q=x*(y/z%s)*t-s*x/t+y/(x*t);
	
	cout<<"k"<<k<<endl;
	cout<<"f"<<f<<endl;
	cout<<"p"<<p<<endl;
	cout<<"h"<<h<<endl;
	cout<<"q"<<q<<endl;

    //PART A
    
    return 0;
}