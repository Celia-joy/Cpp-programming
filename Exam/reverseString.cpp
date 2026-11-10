#include <iostream>
using namespace std;

void reverseString (string str, int index){
    if (index < 0){
        return;
    }

    cout <<str[index];
    reverseString(str, index-1);
}