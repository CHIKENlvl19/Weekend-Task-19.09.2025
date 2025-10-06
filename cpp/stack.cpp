#include <iostream>
#include <stdexcept>

using namespace std;

const int MAX_STACK_SIZE = 1000;

struct Stack;
void push(Stack& myStack, string value);

struct Node {
    string value;
    Node* next;
};

struct Stack {
    Node* head = nullptr;
    int size = 0;

    Stack() = default;

    Stack(const Stack& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while(current != nullptr)
        {
            push(*this, current->value);
            current = current->next;
        }
    }

    Stack& operator=(const Stack& other) {
        if(this == &other)
        {
            return *this;
        }

        clean();

        Node* current = other.head;
        while(current != nullptr)
        {
            push(*this, current->value);
            current = current->next;
        }

        return *this;
    }

    void clean() {
        while(head != nullptr)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
        size = 0;
    }

    ~Stack() {
        clean();
    }
};


Node* createNode(string value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    return newNode;
}

void push(Stack& myStack, string value) {
    
    if(myStack.size == MAX_STACK_SIZE)
    {
        throw overflow_error("Error: stack is full! Overflow might happen.");
        return;
    }
    
    Node* newNode = createNode(value);
    newNode->next = myStack.head;
    myStack.head = newNode;
    myStack.size += 1;
}

void pop(Stack& myStack) {

    if(myStack.size == 0)
    {
        throw underflow_error("Error: stack is empty! Nothing to delete.");
        return;
    }

    Node* toDelete = myStack.head;
    myStack.head = myStack.head->next;
    delete toDelete;
    myStack.size -= 1;
}

void print(Stack& stack) {

    if(stack.size == 0)
    {
        cout << "Stack is empty!" << endl;
        return;
    }

    Node* current = stack.head;
    cout << "nullptr";
    while(current != nullptr)
    {
        cout << " <- " << current->value;
        current = current->next;
    }
    cout << endl;
}

int main() {

    try
    {
        Stack myStack;
        
        push(myStack, "10");
        print(myStack);
        pop(myStack);
        print(myStack);
        //pop(myStack); // error simulation
        push(myStack, "10");
        push(myStack, "20");
        push(myStack, "30");
        print(myStack);

    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}