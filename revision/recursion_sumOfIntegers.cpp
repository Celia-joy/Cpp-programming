#include <iostream>
using namespace std;

int sumOfIntegers(int n){
    if (n == 0){
        return 0;
    }
    if( n == 1){
        return 1;
    }
    return n + sumOfIntegers(n - 1);
}

int main(){
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    if(n <= 0){
        cout<<"Invalid input for the exercise";
    }
    else{
        cout<<"The sum from 1 to "<<n<< " is: "<<sumOfIntegers(n)<<endl;
    }
    return 0;
}