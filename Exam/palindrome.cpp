#include <iostream>
#include <string>
using namespace std;

int isPalindrome (string str, int left, int right){
    if(left >= right){
        return true;
    }

    if(str[left] != str[right]){
        return false;        
    }

    return isPalindrome(str, left + 1, right - 1);
}