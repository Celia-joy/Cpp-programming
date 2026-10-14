#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string word, int left, int right){
    if (left >= right){
        return true;
    }
    if(word[left] != word[right]){
        return false;
    }

    return isPalindrome(word, left + 1, right - 1);
}

int main(){
    string word;

    cout<<"Enter a word:" ;
    cin>>word;

    bool result = isPalindrome(word, 0, word.length() -1);

    if(result){
        cout<<"is a palindrome! "<<endl;
    }

    else {
        cout << "isn't a palindrome!" <<endl;
    }
    return 0;
}