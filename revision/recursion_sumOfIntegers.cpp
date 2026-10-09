#include <iostream>
using namespace std;

int sumOfIntegers(int n){
    if( n == 1){
        return 1;
    }
    return n + sumOfIntegers(n - 1);
}

int main(){
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    cout<<"The sum from 1 to "<<n<< "is: "<<sumOfIntegers(n);
    return 0;
}