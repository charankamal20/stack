#include<bits/stdc++.h>

using namespace std;

class Stack {

    private:
    Stack* link;
    Stack* TOS;
    char data;

    public:
    Stack() { 
        cout << "Welcome to the constructor\n";
        link = NULL;
        TOS = NULL;
    }
    void push(char Data);
    void pop();
    bool isEmpty();
    char tos();
    void printStack();
    char getData()  {
        return data;
    }
    Stack* getTOS() {
        return TOS;
    };
};


bool Stack :: isEmpty() {
    if(TOS == NULL) return 1;

    else return 0 ;
}

void Stack::push(char Data)   {
    
    Stack* temp = new Stack();
    if (isEmpty())  {
        cout << "First element in the stack\n";
        temp->link = NULL;
        temp->data = Data;
        TOS = temp;
        return ;    
    }

    temp->link = TOS;
    TOS = temp;
    temp->data = Data;
}

void Stack::pop()   {
    Stack* temp;
    temp = TOS;
    TOS = TOS->link;
    delete(temp);
    printStack();
}

char Stack::tos()    {
    return TOS->data;
}

void Stack::printStack()    {
    Stack* temp;
    temp = TOS;
    while (temp != NULL)    {
        cout << temp->data << endl;
        temp = temp->link;
    }
}

bool Operator(char value)    {
    if (value == '+' || value == '-' || value == '*' || value == '/' || value == '^')   
        return 1;
    else return 0;
}

bool operatorPrecedence(char operatorRead, Stack* TOS)  {
    
    if (TOS == NULL)    return 0;
    if ((TOS->getData() == '+' && operatorRead == '-') || (TOS->getData() == '-' && operatorRead == '+'))  return 1;    // condition for pop
    if ((TOS->getData() == '*' || TOS->getData() == '/') && (operatorRead == '-' || operatorRead == '+'))   return 1;

    return 0;
}

string infixToPostfix(string expression)   {
    //int iexpression;
    Stack stackForOperator;
    string postfix;
    postfix = "";

    for (int i = 0; expression[i] != '\0'; i++)    {

        if (expression[i] == '(' || expression[i] == ')' || expression[i] == ' ')   continue;

        if (!Operator(expression[i])) {
            //iexpression = (int)expression[i] - 48;
            //cout << "\\" << iexpression << endl;
            postfix = postfix + expression[i];
        }
        else {
            if (operatorPrecedence(expression[i], stackForOperator.getTOS()))   {
                postfix = postfix + stackForOperator.tos();
                stackForOperator.pop();
                stackForOperator.push(expression[i]); 
            }
            else    {
                stackForOperator.push(expression[i]);
                
            }
        }
    }
    cout << "\n---------------\n" ;
    stackForOperator.printStack();
    return postfix;
}

int main()  {

    string expression;
    string result;

    cout << "\nEnter an expression: ";
    getline(cin, expression);

    result = infixToPostfix(expression);
    cout << endl << result;

    getchar();

    return 0;

}