#include <iostream>
#include <stdexcept>

using namespace std;

struct myQueue {
    string* data;
    int head;
    int tail;
    int size;
    int capacity;

    myQueue(int initialCapacity = 4) {
        if(initialCapacity <= 0)
        {
            initialCapacity = 4;
        }

        data = new string[initialCapacity];
        capacity = initialCapacity;
        size = 0;
        head = 0;
        tail = 0;
    }

    void clean() {
        delete[] data;
        head = 0;
        tail = 0;
        size = 0;
        capacity = 0;
    }

    ~myQueue() {
        clean();
    }
};

void push(myQueue& queue, const string value) {
    if(queue.size == queue.capacity)
    {
        int newCapacity = queue.capacity * 2;
        string* newData = new string[newCapacity];

        for(int i = 0; i < queue.size; i++)
        {
            newData[i] = queue.data[(queue.head + i) % queue.capacity];
        }

        delete[] queue.data;
        queue.data = newData;
        queue.capacity = newCapacity;
        queue.head = 0;
        queue.tail = queue.size;
    }

    queue.data[queue.tail] = value;
    queue.tail = (queue.tail + 1) % queue.capacity;
    queue.size++;
}

void pop(myQueue& queue) {
    if(queue.size == 0)
    {
        cerr << "Error: queue is empty, nothing to delete!" << endl;
        return;
    }

    queue.head = (queue.head + 1) % queue.capacity;
    queue.size--;
}

void print(const myQueue& queue) {
    for(int i = 0; i < queue.size; i++)
    {
        cout << queue.data[(queue.head + i) % queue.capacity] << " ";
    }
    cout << endl;
}

int main() {
    myQueue q;

    //cout << "Добавляем элементы A, B, C, D" << endl;
    push(q, "A");
    push(q, "B");
    push(q, "C");
    push(q, "D");
    print(q); // Ожидаем: A B C D

    //cout << "Удаляем два элемента" << endl;
    pop(q);
    pop(q);
    print(q); // Ожидаем: C D

    //cout << "Добавляем элементы E, F, G (проверка кольца и расширения)" << endl;
    push(q, "E");
    push(q, "F");
    push(q, "G");
    print(q); // Ожидаем: C D E F G

    //cout << "Удаляем все элементы" << endl;
    while (q.size > 0) pop(q);
    print(q); // Ожидаем пустую очередь

    //cout << "Попытка удалить из пустой очереди" << endl;
    pop(q); // Должно вывести ошибку

    return 0;
}