#include <iostream>


static const int MAXSIZE = 30;


template <class T> class Queue {

private:
    int rear, front, size;
    T array[MAXSIZE];

public:

    Queue() {
        rear = -1;
        size = front = 0;
    }

    void enqueue(T data) {
        if (size == MAXSIZE) {
            std::cout << "Queue is Full" << std::endl;
            return;
        }
        size++;
        rear = (rear + 1) % MAXSIZE;
        array[rear] = data;
    }

    T dequeue() {
        if (size == 0) {
            std::cout << "Queue is Empty" << std::endl;
            return NULL;
        }
        size--;
        T tmp = array[front];
        front = (front + 1) % MAXSIZE;
        return tmp;
    }

    void display() {
        if (size == 0) {
            std::cout << "Empty Queue" << std::endl;
        }
        else {
            std::cout << "Elements in Queue: ";
            for (int i = front; i != rear; i = (i + 1) % MAXSIZE) {
                std::cout << array[i] << "\t";
            }
            std::cout << array[rear] << "\n";
        }
    }

    int len() {
        return size;
    }

};


int main() {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.display();
    std::cout << queue.len() << std::endl;
    std::cout << queue.dequeue() << std::endl;
}