
#include <iostream>
using namespace std;

// Prints numbers from n down to 1
void countdown(int n) {

    // BASE CASE: Stop when n reaches 0 or below
    if (n <= 0) {
        return;
    }

    // Print the current number
    cout << n << " ";

    // RECURSIVE CASE: Call the function with n - 1
    countdown(n - 1);
}

int main() {
    int n;

    cout << "Enter a number: ";
    cin >> n;

    countdown(n);

    cout << endl;
    return 0;
}
