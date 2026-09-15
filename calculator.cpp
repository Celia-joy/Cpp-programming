/*
    SIMPLE ARITHMETIC CALCULATOR
    (Windows Calculator - Standard Mode style)

    This program asks the user for a first number, an operator,
    and (if needed) a second number, then shows the result.
    It repeats until the user chooses to stop.
*/

#include <iostream>
#include <cmath>   // needed for sqrt()
using namespace std;

// ---- Function declarations (the four basic operations) ----
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
bool divide(double a, double b, double &result); // returns false if b is 0

int main() {
    double firstNumber = 0.0;
    double secondNumber = 0.0;
    double result = 0.0;
    char operatorSymbol;
    char continueChoice;

    cout << "=========================================" << endl;
    cout << "        SIMPLE C++ CALCULATOR           " << endl;
    cout << "   (Windows Standard Calculator style)  " << endl;
    cout << "=========================================" << endl;

    do {
        // ---- Step 1: get the first number ----
        cout << "\nEnter first number: ";
        cin >> firstNumber;

        // ---- Step 2: get the operator ----
        cout << "Choose operator:\n";
        cout << "  +  add\n";
        cout << "  -  subtract\n";
        cout << "  *  multiply\n";
        cout << "  /  divide\n";
        cout << "  %  percentage (first number is what % of second)\n";
        cout << "  s  square (first number only)\n";
        cout << "  r  square root (first number only)\n";
        cout << "  i  reciprocal 1/x (first number only)\n";
        cout << "  n  change sign +/- (first number only)\n";
        cout << "Your choice: ";
        cin >> operatorSymbol;

        // Some operators need only ONE number (square, sqrt, 1/x, +/-)
        if (operatorSymbol == 's' || operatorSymbol == 'r' ||
            operatorSymbol == 'i' || operatorSymbol == 'n') {

            switch (operatorSymbol) {
                case 's':
                    result = firstNumber * firstNumber;
                    cout << firstNumber << " squared = " << result << endl;
                    break;

                case 'r':
                    if (firstNumber < 0) {
                        cout << "Error: cannot take the square root of a negative number." << endl;
                    } else {
                        result = sqrt(firstNumber);
                        cout << "Square root of " << firstNumber << " = " << result << endl;
                    }
                    break;

                case 'i':
                    if (firstNumber == 0) {
                        cout << "Error: cannot divide 1 by 0." << endl;
                    } else {
                        result = 1 / firstNumber;
                        cout << "1 / " << firstNumber << " = " << result << endl;
                    }
                    break;

                case 'n':
                    result = -firstNumber;
                    cout << "Result = " << result << endl;
                    break;
            }

        } else {
            // ---- Step 3: get the second number (needed for these operators) ----
            cout << "Enter second number: ";
            cin >> secondNumber;

            // ---- Step 4: calculate (this is the "=" step) ----
            switch (operatorSymbol) {
                case '+':
                    result = add(firstNumber, secondNumber);
                    cout << firstNumber << " + " << secondNumber << " = " << result << endl;
                    break;

                case '-':
                    result = subtract(firstNumber, secondNumber);
                    cout << firstNumber << " - " << secondNumber << " = " << result << endl;
                    break;

                case '*':
                    result = multiply(firstNumber, secondNumber);
                    cout << firstNumber << " * " << secondNumber << " = " << result << endl;
                    break;

                case '/':
                    if (!divide(firstNumber, secondNumber, result)) {
                        cout << "Error: cannot divide by zero." << endl;
                    } else {
                        cout << firstNumber << " / " << secondNumber << " = " << result << endl;
                    }
                    break;

                case '%':
                    result = (firstNumber * secondNumber) / 100;
                    cout << firstNumber << " is " << result << " percent-value of " << secondNumber << endl;
                    break;

                default:
                    cout << "Invalid operator! Please try again." << endl;
            }
        }

        // ---- Ask if the user wants another calculation ----
        cout << "\nCalculate again? (y = yes, n = exit): ";
        cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    cout << "\nThank you for using the calculator. Goodbye!" << endl;
    return 0;
}

// ---- Function definitions ----
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

bool divide(double a, double b, double &result) {
    if (b == 0) {
        return false; // signal "division by zero" to the caller
    }
    result = a / b;
    return true;
}
