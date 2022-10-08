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
        return ;    
    }

    temp->next = TOS;
    TOS = temp;
    temp->data = Data;

}


int main()  {

    Stack S;
    S.isEmpty();
    getchar();

    return 0;

}