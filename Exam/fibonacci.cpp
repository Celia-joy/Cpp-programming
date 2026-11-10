#include <iostream>
using namespace std;

void printFibonacci(int n, int a =0 , int b = 1){
    if (n == 0){
        return;
    }
    cout << a <<" ";
    printFibonacci(n - 1, b, a + b);
}