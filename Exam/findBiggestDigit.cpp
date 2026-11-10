#include <iostream>
using namespace std;

int findBiggestDigit(int number){
    int n = abs(number);
    if ( n <= 9){
        return n;
    }

    int lastDigit = n % 10;
    int biggestInRest = n /10;

    if (lastDigit > biggestInRest){
        return lastDigit;
    }

    return biggestInRest;
}