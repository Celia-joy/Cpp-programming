
#include <iostream>
#include <string>
using namespace std;

// Checks whether a word is a palindrome recursively
bool isPalindrome(const string& word, int left, int right) {

    // BASE CASE: All character pairs matched
    if (left >= right) {
        return true;
    }

    // If the outside characters differ, it is not a palindrome
    if (word[left] != word[right]) {
        return false;
    }

    // RECURSIVE CASE: Move toward the center
    return isPalindrome(word, left + 1, right - 1);
}

int main() {
    string word;

    cout << "Enter a word: ";
    cin >> word;

    // Start at the first and last character
    bool result = isPalindrome(word, 0, (int)word.length() - 1);

    if (result) {
        cout << "The word is a palindrome." << endl;
    } else {
        cout << "The word is not a palindrome." << endl;
    }

    return 0;
}
