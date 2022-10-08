#include<bits/stdc++.h>

using namespace std;

class Stack {

    private:
    Stack* next;
    int data;
    
    public:
    Stack() {
        cout << "Welcome to the constructor\n";
        next = NULL;
    }
    void push(int Data);
    void pop();
    bool isEmpty();
    int tos();
    void printStack();

};

Stack* TOS = NULL;

bool Stack :: isEmpty() {
    if(TOS == NULL) return 1;
    
    else return 0 ;
}

void Stack::push(int Data )   {
    
    Stack* temp = new Stack();
    if (isEmpty())  {
        cout << "First element in the stack\n";
        temp->next = NULL;
        temp->data = Data;
        TOS = temp;
        printStack();
        return ;    
    }

    temp->next = TOS;
    TOS = temp;
    temp->data = Data;
    printStack();
}

void Stack::pop()   {
    TOS = TOS->next;
    printStack();
}

int Stack::tos()    {
    return TOS->data;
}

void Stack::printStack()    {
    Stack* temp;
    temp = TOS;
    while (temp != NULL)    {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

int main()  {

    Stack S;
    S.push(5);
    S.push(7);
    S.pop();
    S.push(8);

    getchar();

    return 0;

}