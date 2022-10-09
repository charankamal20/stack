#include<bits/stdc++.h>

using namespace std;

template <typename T>
class Stack {

    private:
    Stack* link;
    Stack* TOS;
    T data;

    public:
    Stack() { 
        link = NULL;
        TOS = NULL;
    }
    void push(T Data);
    void pop();
    bool isEmpty();
    T tos();
    void printStack();
    T getData()  {
        return data;
    }
    Stack* getTOS() {
        return TOS;
    };
};

template <class T>
bool Stack<T> :: isEmpty() {
    if(TOS == NULL) return 1;

    else return 0 ;
}

template <class T>
void Stack<T>::push(T Data)   {
    
    Stack* temp = new Stack();
    if (isEmpty())  {
        cout << "\nFirst element in the stack\n";
        temp->link = NULL;
        temp->data = Data;
        TOS = temp;
        return ;    
    }

    temp->link = TOS;
    TOS = temp;
    temp->data = Data;
}

template <class T>
void Stack<T>::pop()   {
    Stack* temp;
    temp = TOS;
    TOS = TOS->link;
    delete(temp);
}

template <class T>
T Stack<T>::tos()    {
    return TOS->data;
}

template <class T>
void Stack<T>::printStack()    {
    Stack* temp;
    temp = TOS;
    while (temp != NULL)    {
        cout << temp->data << endl;
        temp = temp->link;
    }
}

bool IsOperator(char value)    {
    if (value == '+' || value == '-' || value == '*' || value == '/' || value == '^')   
        return 1;
    else return 0;
}

bool isOperand(char value)  {
    if (value >= '0' && value <= '9')   return 1;
    else return 0;
}

bool operatorPrecedence(char operatorRead, Stack<char>* TOS)  {
    
    if (TOS == NULL)    return 0;
    if ((TOS->getData() == '+' && operatorRead == '-') || (TOS->getData() == '-' && operatorRead == '+'))  return 1;    // condition for pop
    if ((TOS->getData() == '*' || TOS->getData() == '/') && (operatorRead == '-' || operatorRead == '+'))   return 1;

    return 0;
}

string infixToPostfix(string expression)   {

    Stack<char> stackForOperator;
    Stack<char> *temp;
    string postfix;
    postfix = "";

    for (int i = 0; expression[i] != '\0'; i++)    {
        if (expression[i] == '(' || expression[i] == ')' || expression[i] == ' ')   continue;

        if (isOperand(expression[i])) {
            while(isOperand(expression[i])) {
                postfix = postfix + expression[i];
                i++;
            }
            i--;
            postfix += " ";
        }
        else {

            if (operatorPrecedence(expression[i], stackForOperator.getTOS()))   {
                while (operatorPrecedence(expression[i], stackForOperator.getTOS()))    {
                    postfix = postfix + stackForOperator.tos() + " ";
                    stackForOperator.pop();
                }
                stackForOperator.push(expression[i]); 
            }
            else    {
                stackForOperator.push(expression[i]);

            }

        }
    }
    temp = stackForOperator.getTOS();
    while (!stackForOperator.isEmpty()) {
        postfix = postfix + stackForOperator.tos() + " ";
        stackForOperator.pop();
    }
    return postfix;
}

int operateExpression(int value1, int value2, char Operator)  {
    
    switch(Operator)    {
        case '-':
            return value1 - value2;
        case '+':
            return value1 + value2;
        case '*':
            return value1 * value2;
        case '/':
            return value1 / value2;
        default:
            cout << "\nUnexpected error occured";
            return -1;
    }
    return 0;
}

int evaluatePostfix(string expression)   {

    Stack<int> postfix;
    int val1, val2;
    int result = 0;

    for(int i = 0; i < expression[i] != '\0'; i++)  {

        if (expression[i] == ',' || expression[i] == ' ')   
            continue;

        if (IsOperator(expression[i]))  {
            val2 = postfix.tos();
            postfix.pop();
            val1 = postfix.tos();
            postfix.pop();
            result = operateExpression(val1, val2, expression[i]);
            postfix.push(result);
        }
        else {
            int operand = 0;
            while(isOperand(expression[i])) {
                operand = (operand*10) + (expression[i] - 48);
                i++;
            }
            i--;
            postfix.push(operand);
        }
    }
    return result;
}

int main()  {

    string expression;
    string result;
    int res;
    cout << "\nEnter an expression: ";
    getline(cin, expression);

    result = infixToPostfix(expression);
    cout << endl << result;

    res = evaluatePostfix(result);
    cout << endl << res;

    getchar();

    return 0;

}