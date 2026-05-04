//Queue Implementation

#include <iostream>
using namespace std;

#include "Customer.h"
#include "Server.h"

struct Node{
    Customer customer;
    Node* next;
};

class Queue{

    private:
    Node* front;
    Node* rear;
    int count;

    public:
    Queue(){
        front = NULL;
        rear = NULL;
        count = 0;
    }

    void enqueueCustomer(Customer c){
        Node* tempNode = new Node;
        tempNode->customer = c;
        tempNode->next = NULL;
        rear->next = tempNode;
        count++;
    }

    Customer dequeueCustomer(){
        Node* tempNode = front;
        Customer customerToReturn = tempNode->customer;
        front = front->next;
        delete tempNode;
        count--;
        return customerToReturn;
    }

    bool isQueueEmpty() const{
        return (count == 0);
    }

    int getQueueSize() const{
        return count;
    }

    Customer getCustomerAt(int index) const{
        Node* tempNode = front;
        for (int i = 1; i < index; i++){
            tempNode = tempNode->next;
        }
        return tempNode->customer;
    }

    void updateWaitingTimes(int currentTime){
        Node* tempNode = front;
        while (tempNode != rear){
            tempNode->customer.calculateWaitingTime(currentTime);
            tempNode = tempNode->next;
        }
        tempNode->customer.calculateWaitingTime(currentTime);
    }   

    ~Queue(){
        Node* tempNode = front;
        Node* prevNode = NULL;
        while(!isQueueEmpty()){
            dequeueCustomer();
        }
    }

};