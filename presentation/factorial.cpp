
#include <iostream>
using namespace std;

// Calculates the factorial of a non-negative integer
int factorial(int n) {

    // BASE CASE: 0! = 1
    if (n == 0) {
        return 1;
    }

    // RECURSIVE CASE: Multiply n by (n - 1)!
    return n * factorial(n - 1);
}

int main() {
    int n;

    cout << "Enter a non-negative integer: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative integer." << endl;
    } else {
        cout << n << "! = " << factorial(n) << endl;
    }

    return 0;
}
