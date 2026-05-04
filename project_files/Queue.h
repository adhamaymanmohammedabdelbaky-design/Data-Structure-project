// Queue Implementation Using Dynamic Circular Array
#pragma once
#include "Customer.h"

class Queue {
    private:
    Customer* queueArray; // Dynamic array to hold customers in the queue
    int front;
    int rear;
    int capacity;
    int count;

    public:
    // Constructor with default capacity of 100
    Queue(int capacity = 100) {
        this->capacity = capacity;
        this->queueArray = new Customer[capacity];
        this->front = 0;
        this->rear = -1;
        this->count = 0;
    }

    // Copy Constructor (Deep Copy)
    Queue(const Queue& other) {
        this->capacity = other.capacity;
        this->queueArray = new Customer[capacity];
        this->front = other.front;
        this->rear = other.rear;
        this->count = other.count;

        for (int i = 0; i < capacity; i++) {
            queueArray[i] = other.queueArray[i];
        }
    }

    // Copy assignment operator (Deep Copy)
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] queueArray; // Free existing resources

            this->capacity = other.capacity;
            this->queueArray = new Customer[capacity];
            this->front = other.front;
            this->rear = other.rear;
            this->count = other.count;

            for (int i = 0; i < capacity; i++) {
                queueArray[i] = other.queueArray[i];
            }
        }
        return *this;
    }

    // Destructor 
    ~Queue() {
        delete[] queueArray;
    }

    // Enqueue customer, maintaining VIP priority
    void enqueueCustomer(Customer c){
        // If capacity is reached, double the size
        if (count == capacity) {
            cout<<"The Queue Is Full"<<endl;
            return;
        }

        // If the queue is empty or the customer is normal, add to the rear of the queue
        if (isQueueEmpty()|| !c.getIsVip()) {
            rear = (rear + 1) % capacity;
            queueArray[rear] = c;
            count++;
            return;
        }

        // If the customer is VIP, find the correct position to insert
        int insertPos = front;
        int itemsChecked = 0;

        // Find the first normal customer to insert the VIP before them
        while (itemsChecked < count) {
            int physicalIndex = (front + itemsChecked) % capacity;

            if (!queueArray[physicalIndex].getIsVip()) {
                break; // Found the first normal customer
            }
            insertPos = (physicalIndex + 1) % capacity;
            itemsChecked++;
        }

        // If all customers in the queue are VIPs, insert at the rear
        if(itemsChecked == count) {
            rear = (rear + 1) % capacity;
            queueArray[rear] = c;
        } else 
            {
                // Shift normal customers to the right to make room
                int currentPos = rear;
                while (currentPos != insertPos) {
                    int prevPos = (currentPos - 1 + capacity) % capacity;
                    queueArray[currentPos] = queueArray[prevPos];
                    currentPos = prevPos;
                }

                // Insert the VIP customer in the correct position
                queueArray[insertPos] = c; 
                rear = (rear + 1) % capacity; // Update rear position
            }
            count++;
        }

    // Dequeue the front customer and return it
    Customer dequeueCustomer() {
        if (isQueueEmpty()) {
            cout<<"The Queue Is Empty"<<endl;
            return Customer(); // Return a default customer if the queue is empty
        }

        Customer frontCustomer = queueArray[front];
        front = (front + 1) % capacity; // Move front to the next position
        count--;

        // Reset indices if the queue becomes empty
        if (isQueueEmpty()) {
            front = 0;
            rear = -1;
        }
        return frontCustomer;
    }

    // Check if the queue is empty
    bool isQueueEmpty() const {
        return count == 0;
    }

    // Get the current size of the queue
    int getQueueSize() const {
        return count;
    }

    // Get customer data at a specific index
    Customer getCustomerAtIndex(int index) const {
        if (index < 0 || index >= count) {
            cout<<"Invalid Index"<<endl;
            return Customer(); // Return a default customer for invalid index
        }
        int physicalIndex = (front + index) % capacity; // Calculate the physical index in the circular array
        return queueArray[physicalIndex];
    }

    // Update waiting times for all customers in the queue
    void updateWaitingTimes(int currentTime) {
        for (int i = 0; i < count; i++) {
            int physicalIndex = (front + i) % capacity; // Calculate the physical index in the circular array
            queueArray[physicalIndex].calculateWaitingTime(currentTime); // Update waiting time for each customer
        }
    }
};
