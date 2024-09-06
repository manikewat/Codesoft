#include <iostream>
using namespace std;

int main() {
    // Variables to store user inputs
    double num1, num2;
    char operation;
    
    // Display menu for operations
    cout << "Welcome to the Basic Calculator!" << endl;
    cout << "Please enter the first number: ";
    cin >> num1;
    
    cout << "Please enter the second number: ";
    cin >> num2;
    
    cout << "Choose an operation (+, -, *, /): ";
    cin >> operation;

    // Perform the chosen operation
    switch(operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << "Result: " << num1 / num2 << endl;
            } else {
                cout << "Error: Division by zero is not allowed." << endl;
            }
            break;
        default:
            cout << "Error: Invalid operation." << endl;
            break;
    }

    return 0;
}
