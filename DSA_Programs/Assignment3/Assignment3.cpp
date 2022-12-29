/**
 * @author SuyogPawar
**/

#include <iostream>

// Constant defining the max size of the queue.
static const int MAXSIZE = 30;


// Generic Circular Queue of type 'T' ('T' can be anything int, float, char etc)
template <class T> class Queue {

private:
    // 'rear' keeps track of the end of the queue where we insert new elements
    // 'front' keeps track of the start of the queue from where we remove elements
    // 'size' keeps track of the size of the queue
    int rear, front, size;

    // 'array' is an array of type 'T' which we stores all the data.
    T array[MAXSIZE];

public:

    // Default Constructor
    Queue() {
        rear = -1;
        size = front = 0;
    }

    // This method is used to insert data into the circular queue.
    void enqueue(T data) {

        // If queue is full then can't insert anymore elements so just return; 
        if (size == MAXSIZE) {
            std::cout << "Queue is Full" << std::endl;
            return;
        }

        // Increment the rear and place the data in that position.
        // Also increment the size.
        size++;
        rear = (rear + 1) % MAXSIZE;
        array[rear] = data;
    }


    // This method is used to remove and return elements from the queue.
    T dequeue() {

        // If queue is empty then there is nothing to remove so just return NULL.
        if (size == 0) {
            std::cout << "Queue is Empty" << std::endl;
            return NULL;
        }

        // Increment the front and place the data in that posiiton.
        // Also decrement the size.
        size--;
        T tmp = array[front];
        front = (front + 1) % MAXSIZE;
        return tmp;
    }

    // This method is used to display all the elements in the queue.
    void display() {

        if (size == 0) {
            std::cout << "Empty Queue" << std::endl;
        }

        else {
            std::cout << "Elements in Queue: ";

            // Iterating from the front of the queue till the rear.
            for (int i = front; i != rear; i = (i + 1) % MAXSIZE) {
                std::cout << array[i] << "\t";
            }

            std::cout << array[rear] << "\n";
        }
    }

    // This method is used to return the size of the queue
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