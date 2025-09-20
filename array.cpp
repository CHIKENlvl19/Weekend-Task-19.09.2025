/*Реализовать Массив. Операции: создание, добавление элемента (по индексу и в конец массива), 
получение элемента по индексу, удаление элемента по
индексу, замена элемента по индексу, длина массива, чтение.*/

#include <iostream>
#include <stdexcept>

using namespace std;

struct myArray {
    int* data;
    int size;
    int capacity;
};

void createArray(myArray& arr, int initialCapacity = 4) {
    if(initialCapacity <= 0)
    {
        initialCapacity = 4;
    }

    arr.data = new int[initialCapacity];
    arr.size = 0;
    arr.capacity = initialCapacity;
}

void push_back(myArray& arr, int value) {
    if(arr.size >= arr.capacity)
    {
        int newCapacity = arr.capacity * 2;
        int* newData = new int[newCapacity];

        for(int i = 0; i < arr.size; i++)
        {
            newData[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    arr.data[arr.size] = value;
    arr.size++;
}

void insert(myArray& arr, int index, int value) {
    if (index < 0 || index > arr.size)
    {
        throw out_of_range("Error: inserting failed due to invalid index.");
    }

    if(arr.size >= arr.capacity) {
        int newCapacity = arr.capacity * 2;
        int* newData = new int[newCapacity];
        
        for(int i = 0; i < arr.size; i++)
        {
            newData[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    for(int i = arr.size; i > index; --i)
    {
        arr.data[i] = arr.data[i - 1];
    }

    arr.data[index] = value;
    arr.size++;
}

int getElement(const myArray& arr, int index) {
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: getting an element failed due to invalid index.");
    }

    return arr.data[index];
}

void Delete(myArray& arr, int index) {
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: deleting an element failed due to invalid index.");
    }

    for(int i = index; i < arr.size; i++)
    {
        arr.data[i] = arr.data[i + 1];
    }

    arr.size--;
}

void swapElements(myArray& arr, int index, int value) {
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: swapping an element failed due to invalid index.");
    }

    arr.data[index] = value;
}

int size(myArray& arr) {
    return arr.size;
}

void print(const myArray& arr) {
    cout << "[";
    for(int i = 0; i < arr.size; i++)
    {
        cout << arr.data[i];
        if(i < arr.size - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

void clean(myArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

int main() {
    myArray arr;
    createArray(arr);

    push_back(arr, 10);
    push_back(arr, 20);
    print(arr);

    insert(arr, 1,  15);
    print(arr);

    cout << "Elemnt [1]: " << getElement(arr, 1) << endl;

    swapElements(arr, 0, 5);
    print(arr);

    Delete(arr, 0);
    print(arr);

    cout << "Massive length: " << size(arr);

    clean(arr);

    return 0;
}