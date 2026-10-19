
#include <iostream>
using namespace std;

// Calculates 1 + 2 + ... + n using recursion
int sum(int n) {

    // BASE CASE: The sum of zero or fewer numbers is 0
    if (n <= 0) {
        return 0;
    }

    // RECURSIVE CASE: Add n to the sum of smaller numbers
    return n + sum(n - 1);
}

int main() {
    int n;

    cout << "Enter a positive number: ";
    cin >> n;

    cout << "Sum = " << sum(n) << endl;

    return 0;
}
