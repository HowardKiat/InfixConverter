#include <iostream>
#include <string>

// INFIX TO Postfix is left to right Associative
// PREFIX is Right to Left Associative
using namespace std;

#define MAX 100

class Stack {
    char arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
        for (int i = 0; i < MAX; i++) {
            arr[i] = 0;  // Initialize stack array
        }
    }

    void push(char c) {
        if (top >= (MAX - 1)) {
            cout << "Stack Overflow";
        }
        else {
            arr[++top] = c;
        }
    }

    char pop() {
        if (top < 0) {
            cout << "Stack Underflow";
            return '\0';
        }
        else {
            return arr[top--];
        }
    }

    char peek() const {
        if (top < 0) {
            return '\0';
        }
        else {
            return arr[top];
        }
    }

    bool isEmpty() const {
        return top == -1;
    }
};

// Function declarations
bool isAlphaNumeric(char C);
bool isSymbol(char C);
int PrecedencePriority(char symbol1, char symbol2);
bool isRightAssociative(char symbol);
int getSymbolValue(char symbol);

// Convert infix expression to postfix
string InfixToPostfix(string expression) {
    Stack S;
    string postFix = "";

    for (int i = 0; i < expression.length(); i++) {
        // Skip spaces in the expression
        if (expression[i] == ' ' || expression[i] == ',')
            continue;

        // If character is alphanumeric, add it to the postfix expression
        if (isAlphaNumeric(expression[i])) {
            postFix += expression[i];
        }
        // Push '(' to stack if read
        else if (expression[i] == '(') {
            S.push(expression[i]);
        }
        // Pop ')' to stack if read
        else if (expression[i] == ')') {
            while (!S.isEmpty() && S.peek() != '(') {
                postFix += S.pop();
            }
            S.pop(); // Remove '(' from the stack
        }
        // If character is an operator
        else if (isSymbol(expression[i])) {
            while (!S.isEmpty() && S.peek() != '(' && PrecedencePriority(S.peek(), expression[i])) {
                postFix += S.pop();
            }
            S.push(expression[i]);
        }
    }

    // Pop all remaining operators from the stack
    while (!S.isEmpty()) {
        postFix += S.pop();
    }

    return postFix;
}

// Check if the operator is right associative
bool isRightAssociative(char symbol) {
    return symbol == '^';
}

// Determine the precedence of the symbol
int getSymbolValue(char symbol) {
    int priorityValue = -1; // Start from 0; Empty Stack
    switch (symbol) {
    case '+':
    case '-':
        priorityValue = 1;
        break;
    case '*':
    case '/':
        priorityValue = 2;
        break;
    case '^':
        priorityValue = 3; // Highest precedence for exponentiation
        break;
    }
    return priorityValue;
}

// Function to check for precedence between two operators
int PrecedencePriority(char symbol1, char symbol2) {
    int symbolValue1 = getSymbolValue(symbol1);
    int symbolValue2 = getSymbolValue(symbol2);

    // If precedence is the same, return based on associativity
    if (symbolValue1 == symbolValue2) {
        return !isRightAssociative(symbol1);
    }
    return symbolValue1 > symbolValue2;
}

// Function to know if it is an operator
bool isSymbol(char C) {
    return C == '+' || C == '-' || C == '*' || C == '/' || C == '^';
}

// Function to check if a character is alphanumeric
bool isAlphaNumeric(char C) {
    return (C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z');
}

int main() {
    string expression;
    cout << "Enter Infix Expression: ";
    getline(cin, expression);
    string postFix = InfixToPostfix(expression);
    cout << "Postfix Output: " << postFix << "\n";
    return 0;
}
