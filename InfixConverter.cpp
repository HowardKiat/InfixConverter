#include <iostream>
#include <string>

//INFIX TO Postfix is left to right Associative
//PREFIX is Right to Left Associative
// 
// HOWARD TAN HOW KIAT COPYRIGHT © Howard Kiat
using namespace std;

#define MAX 100

class Stack {
    char arr[MAX];
    int top;

public:
    Stack() 
    {
        top = -1;
    }

    void push(char c) {
        if (top >= (MAX - 1)) 
        {
            cout << "Stack Overflow";
        }
        else
        {
            arr[++top] = c;
        }
    }

    char pop()
    {
        if (top < 0) {
            cout << "Stack Underflow";
            return '\0';
        }
        else 
        {
            return arr[top--];
        }
    }

    char peek()
    {
        if (top < 0) 
        {
            return '\0';
        }
        else 
        {
            return arr[top];
        }
    }

    bool isEmpty() 
    {
        return top == -1;
    }
};

//Convert The strings of Infix to Postfix; Expression is the original Infix
string InfixToPostfix(string expression) 
{
    Stack S;
    string postFix = "";

    for (int i = 0; i < expression.length(); i++) 
    {

        // Skip space and , in the expression
        if (expression[i] == ' ' || expression[i] == ',')
            continue;
        if (isSymbol(expression[i])) 
        {
            postFix += expression[i];
        }
        // Push '(' to stack if read
        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }
        // Pop ')' to stack if read
        else if (expression[i] == ')') 
        {
            while (!S.isEmpty() && S.peek() != '(')
            {
                postFix += S.pop();
            }
            S.pop(); // Remove '(' from the stack
        }
        // If character is Symbol
        else if (isSymbol(expression[i])) 
        {
            while (!S.isEmpty() && S.peek() != '(' && PrecendencePriority(S.peek(), expression[i])) {
                postFix += S.pop();
            }
            S.push(expression[i]);
        }
    }
    // Pop all remaining symbol from the stack
    while (!S.isEmpty()) 
    {
        postFix += S.pop();
    }
    return postFix;
}

bool isRightAssociative(char symbol)
{
    return symbol == '$';
}

// Determine the Symbol Value (Value depends its priority) Priority Queue
int getSymbolValue(char symbol)
{
    // The Higher the number of priorityValue the higher the precedence
    int priorityValue = -1; //Start From 0; Empty Stack
    switch (symbol)
    {
    case '+':
    case '-':
        priorityValue = 1;
        break;
    case '*':
    case '/':
        priorityValue = 2;
    case '$':
        priorityValue = 3;
        break;
    }
    return priorityValue;
}

// Function to check for the operator/symbol on its precedence type like such as (, /, * etc. 
int PrecendencePriority(char symbol1, char symbol2)
{
    // Get the Precedence Value
    int symbolValue1 = getSymbolValue(symbol1);
    int symbolValue2 = getSymbolValue(symbol2);

    if (symbolValue1 == symbolValue2) {
        return !isRightAssociative(symbol1);
    }
    return symbolValue1 > symbolValue2;
}

// Function to know if it is a number or symbol/operator
bool isSymbol(char C) // C is to defining the character
{
    // '$' to check for wheter the association is left or right
    return C == '+' || C == '-' || C == '*' || C == '/' || C == '$';
}

bool isAlphaNumeric(char C)
{
    return (C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z');
}

int main() 
{
	string expression;
	cout << "Enter Infix Expression \n";
	getline(cin, expression);
	string postFix = InfixToPostfix(expression);
	cout << "Postfix Output: " << postFix << "\n";
}


