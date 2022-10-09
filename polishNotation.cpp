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

bool operatorPrecedencePostfix(char operatorRead, Stack<char>* TOS)  {
    
    if (TOS == NULL)    return 0;
    if ((TOS->getData() == '+' && operatorRead == '-') || (TOS->getData() == '-' && operatorRead == '+'))  return 1;    // condition for pop
    if ((TOS->getData() == '*' || TOS->getData() == '/') && (operatorRead == '-' || operatorRead == '+'))   return 1;

    return 0;
}

bool operatorPrecedencePrefix(char operatorRead, Stack<char>* TOS)  {
    
    if (TOS == NULL)    return 0;
    if ((TOS->getData() == '+' && operatorRead == '-') || (TOS->getData() == '-' && operatorRead == '+'))  return 0;    // condition for pop
    if ((TOS->getData() == '*' || TOS->getData() == '/') && (operatorRead == '-' || operatorRead == '+'))   return 1;

    return 0;
}

string infixToPostfix(string expression, int* flag)   {

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
        else if(!IsOperator(expression[i]) && !IsOperator(expression[i])) {
            postfix = postfix + expression[i] + " ";
            *flag = 0;
        }
        else {

            if (operatorPrecedencePostfix(expression[i], stackForOperator.getTOS()))   {
                while (operatorPrecedencePostfix(expression[i], stackForOperator.getTOS()))    {
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

string infixToPrefix(string expression, int* flag)   {

    Stack<char> stackForOperator;
    Stack<char> *temp;
    string prefix;
    prefix = "";

    reverse(expression.begin(), expression.end());

    for (int i = 0; expression[i] != '\0'; i++)    {
        if (expression[i] == '(' || expression[i] == ')' || expression[i] == ' ')   continue;

        if (isOperand(expression[i])) {
            while(isOperand(expression[i])) {
                prefix = prefix + expression[i];
                i++;
            }
            i--;
            prefix += " ";
        }
        else if(!IsOperator(expression[i]) && !IsOperator(expression[i])) {
            *flag = 0;
            prefix = prefix + expression[i] + " ";
        }
        else {

            if (operatorPrecedencePrefix(expression[i], stackForOperator.getTOS()))   {
                while (operatorPrecedencePrefix(expression[i], stackForOperator.getTOS()))    {
                    prefix = prefix + stackForOperator.tos() + " ";
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
        prefix = prefix + stackForOperator.tos() + " ";
        stackForOperator.pop();
    }
    reverse(prefix.begin(),prefix.end());

    return prefix;
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

    for(int i = 0; expression[i] != '\0'; i++)  {

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

int evaluatePrefix(string expression)   {

    Stack<int> prefix;
    int val1, val2;
    int result = 0;

    for(int i = expression.length() - 1 ; i >= 0 ; i--)  {

        if (expression[i] == ',' || expression[i] == ' ')   
            continue;

        if (IsOperator(expression[i]))  {
            val1 = prefix.tos();
            prefix.pop();
            val2 = prefix.tos();
            prefix.pop();
            result = operateExpression(val1, val2, expression[i]);
            prefix.push(result);
        }
        else {
            int operand = 0;
            while(isOperand(expression[i])) {
                operand = (operand*10) + (expression[i] - 48);
                i--;
            }
            i++;
            prefix.push(operand);
        }
    }
    return result;
}

void printRules()   {
    cout << "\nRules for writing the expression: \n";
    cout << "Input expression must be in a desired format. "  << endl
         << "Operands must be integers and there should be space in between two operands" << endl
         << "Only '+'  ,  '-'  , '*' and '/'  operators are expected" << endl;
}

int main()  {

    string expression;
    string result;
    int res = 1, choice;
    int *flag;
    flag = &res;

    while(1)    {

    system("cls");
    cout << "\n--IMPLEMENTATION OF POLISH NOTATION USING STACK--\n";
    cout << "Available operations: \n";
    cout << "1. Infix to postfix" << endl   
         << "2. Infix to prefix" << endl
         << "3. Evaluate a prefix expression" << endl
         << "4. Evaluate a postfix expression" << endl
         << "5. Evaluate an infix expression" << endl 
         << "6. Exit" << endl
         << "Your choice: ";
    
    cin >> choice ;
    switch(choice)  {
        case 1: {
            cout << "\nEnter an expression: " ;
            getline(cin >> ws,expression);
            result = infixToPostfix(expression, flag);
            cout << "\nPostfix expression: " << result;
            if (*flag != 0) {
                cout << "\nDo you wish to evaluate this expression(1/0): ";
                cin >> choice;
                if (choice == 1)    {
                    cout << "\nResult after evaluation: " << evaluatePostfix(result);    
                }
            }
            break;
        }
        case 2: {
            cout << "\nEnter an expression: " ;
            getline(cin >> ws,expression);
            result = infixToPrefix(expression, flag);
            cout << "\nPrefix expression: " << result;
            if (*flag != 0) {
                cout << "\nDo you wish to evaluate this expression(1/0): ";
                cin >> choice;
                if (choice == 1)    {
                    cout << "\nResult after evaluation: " << evaluatePrefix(result);    
                }
            }
            break;
        }
        case 3: {
            printRules();
            cout << "\nEnter your prefix expression: " ;
            getline(cin >> ws,expression);
            cout << "\nResult after evaluation: " << evaluatePrefix(expression);
            break;
        }
        case 4: {
            printRules();
            cout << "\nEnter your postfix expression: " ;
            getline(cin >> ws,expression);
            cout << "\nResult after evaluation: " << evaluatePostfix(expression);
            break;
        }
        case 5: {
            cout << "\nEnter an expression: " ;
            getline(cin >> ws,expression);
            result = infixToPostfix(expression, flag); 
            cout << "\nResult after evaluation: " << evaluatePostfix(result);
            break;
        }
        case 6: {
            exit(0);
        }
        default:    {
            cout << "\nError: Invalid choice intered";
            break;
        }
    }

    getchar();
    }

    return 0;

}