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

string infixToPostfix(string expression)   {
    //int iexpression;
    Stack stackForOperator;
    string postfix;
    postfix = "";

    for (int i = 0; expression[i] != '\0'; i++)    {
        if (!Operator(expression[i])) {
            //iexpression = (int)expression[i] - 48;
            //cout << "\\" << iexpression << endl;
            postfix = postfix + expression[i];
        }
        else {
            stackForOperator.push(expression[i]);
        }
    }
    cout << "\n---------------\n" ;
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