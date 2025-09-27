#include <iostream>
#include <stdexcept>

using namespace std;

const int MAX_STACK_SIZE = 1000;

struct Node {
    int key;
    Node* next;
};

struct Stack {
    Node* head;
    int size;
};

void createStack(Stack* myStack) {
    myStack->head = nullptr;
    myStack->size = 0;
}

Node* createNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->next = nullptr;

    return newNode;
}

void push(Stack* myStack, int key) {
    
    if(myStack->size == MAX_STACK_SIZE)
    {
        throw overflow_error("Error: stack is full! Overflow might happen.");
        return;
    }
    
    Node* newNode = createNode(key);
    newNode->next = myStack->head;
    myStack->head = newNode;
    myStack->size += 1;
}

void pop(Stack* myStack) {

    if(myStack->size == 0)
    {
        throw underflow_error("Error: stack is empty! Nothing to delete.");
        return;
    }

    Node* toDelete = myStack->head;
    myStack->head = myStack->head->next;
    delete toDelete;
    myStack->size -= 1;
}

void print(Stack* stack) {

    if(stack->size == 0)
    {
        cout << "Stack is empty!";
        return;
    }

    Node* current = stack->head;
    cout << "nullptr";
    while(current != nullptr)
    {
        cout << " <- " << stack->head->key;
        current = current->next;
    }
    cout << endl;
}

void clean(Stack* stack) {

}

int main() {

    try
    {
        Stack* myStack = new Stack;
        createStack(myStack);

        push(myStack, 10);
        print(myStack);
        pop(myStack);
        print(myStack);

    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}