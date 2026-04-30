// Server file
#pragma once
#include <iostream>
#include "Customer.h"
using namespace std;

class Server {
    private:
    bool freeStatus;              
    int remainingTime;            
    int totalServedCount;
    Customer currentCustomer;     
public:
    Server(){
        this->freeStatus = true;
        this->remainingTime = 0;
        this->totalServedCount = 0;
    }
    
    // Getters
    bool isFree() const {
        return freeStatus;
    }

    bool isBusy() const {
        return !freeStatus;
    }

    int getRemainingTime() const {
        return remainingTime;
    }

    int getTotalServedCount() const {
        return totalServedCount;
    }

    // Assigns a customer to the server
    // The server becomes busy and starts serving the customer
    void assignCustomer(const Customer& customer) {
        this->currentCustomer = customer;
        this->freeStatus = false;
        this->remainingTime = customer.getServiceTime(); // Set service time based on the customer
    }

    // Decreases the remaining service time if the server is busy
    void updateTime(){
        if (remainingTime > 0) {
            remainingTime--;

            if (remainingTime == 0) {
               finishService();
            }
        }
    }

    // Returns the customer currently being served
    Customer getCurrentCustomer() const { return currentCustomer; }   

    void finishService() {
        freeStatus = true;
        totalServedCount++;
        currentCustomer = Customer(); // Reset current customer to an empty/default customer
    }
};