#include <iostream>
using namespace std;

void printNumbers(int n){
    if (n <= 0){
        return;
    }

    cout<<n<< " ";
    printNumbers(n-1);
    cout<<n<< " ";
}
int main(){
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    cout<<"The numbers are: ";
    printNumbers(n);
    return 0;
}