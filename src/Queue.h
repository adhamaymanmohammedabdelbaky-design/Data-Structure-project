// Implementation of a Queue class using a linked list ;)
#pragma once
#include <iostream>
#include "Customer.h" 

using namespace std;

class Queue {
private:
    // Encapsulated Node structure: Hidden from outside the class
    struct Node {
        Customer data;
        Node* next;
        
        // Node constructor
        Node(Customer c) {
            data = c;
            next = NULL;
        }
    };

    Node* front; // Pointer to the front of the queue
    Node* rear;  // Pointer to the rear of the queue
    int count;   // Number of customers currently in the queue

    // Helper function to append a node at the end (used in copy operations)
    void appendNode(Customer c) {
        Node* newNode = new Node(c);
        if (front == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    };

public:
    // Default Constructor
    Queue() {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Copy Constructor (Deep Copy)
    Queue(const Queue& other) {
        front = NULL;
        rear = NULL;
        count = 0;
        
        Node* temp = other.front;
        while (temp != NULL) {
            appendNode(temp->data);
            temp = temp->next;
        }
    }

    // Copy Assignment Operator (Deep Copy)
    Queue& operator=(const Queue& other) {
        if (this != &other) { // Protect against self-assignment
            clearQueue();     // Free existing resources
            
            Node* temp = other.front;
            while (temp != NULL) {
                appendNode(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // Destructor 
    ~Queue() {
        clearQueue();
    }

    // Helper function to clear the queue (Now Public)
    void clearQueue() {
        Node* temp = front;
        while (temp != NULL) {
            Node* delptr = temp;
            temp = temp->next;
            delete delptr; // Free memory
        }
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Enqueue customer, maintaining VIP priority
    void enqueueCustomer(Customer c) {
        Node* newNode = new Node(c);

        // Case 1: If the queue is empty
        if (isQueueEmpty()) {
            front = rear = newNode;
            count++;
            return;
        }

        // Case 2: If the customer is normal, add to the rear of the queue
        if (!c.getIsVIP()) {
            rear->next = newNode;
            rear = newNode;
            count++;
            return;
        }

        
        // --- VIP Customer Handling ---
        // From here on, we know the new customer is a VIP

        // Case 3: If the front customer is normal, the VIP jumps to the front
        if (!front->data.getIsVIP()) {
            newNode->next = front;
            front = newNode;
            count++;
            return;
        }

        // Case 4: Find the last VIP in the queue to insert the new VIP after them
        Node* temp = front;
        
        // Traverse as long as the next node exists AND the next node is also a VIP
        while (temp->next != NULL && temp->next->data.getIsVIP()) {
            temp = temp->next;
        }

        // Insert the new VIP customer in the correct position
        newNode->next = temp->next;
        temp->next = newNode;

        // If the new VIP was inserted at the very end of the queue, update the rear pointer
        if (newNode->next == NULL) {
            rear = newNode;
        }

        count++;
    }

    // Dequeue the front customer and return it
    Customer dequeueCustomer() {
        if (isQueueEmpty()) {
            return Customer(); // Return a default customer if the queue is empty
        }

        Node* temp = front;
        Customer frontCustomer = temp->data; // Extract the data
        
        front = front->next; 
        delete temp;         
        count--;

        // If the queue becomes empty after dequeuing, reset the rear pointer as well
        if (front == NULL) {
            rear = NULL;
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
            return Customer(); // Return a default customer for invalid index
        }

        Node* temp = front;
        // Traverse the linked list until the desired index is reached
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        
        return temp->data;
    }


    // Updates the waiting time for every customer currently in the queue
   // Called every tick by the Simulation so wait times stay accurate
void updateWaitingTimes(int currentTime) {
    Node* temp = front;
    while (temp != NULL) {
        temp->data.calculateWaitingTime(currentTime);
        temp = temp->next;
    }


}};