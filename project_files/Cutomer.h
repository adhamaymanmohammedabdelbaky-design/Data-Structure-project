// Customer file
#pragma once
#include <iostream>
using namespace std;

class Customer {
    private:
    int id;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
    bool isVip;

public:
    Customer(){
        this->id = 0;
        this->arrivalTime = 0;
        this->serviceTime = 0;
        this->waitingTime = 0;
        this->isVip = false;
    }

    Customer(int id, int arrivalTime, int serviceTime, bool isVip){
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
        this->waitingTime = 0;
        this->isVip = isVip;
    }

    // Getters 
    int getId() const {
        return id;
    }
    int getArrivalTime() const {
        return arrivalTime;
    }
    int getServiceTime() const {
        return serviceTime;
    }
    int getWaitingTime() const {
        return waitingTime;
    }
    bool getIsVip() const {
        return isVip;
    }
    
    // Setters
    void setWaitingTime(int waitingTime) {
        this->waitingTime = waitingTime;
    }

    void calculateWaitingTime(int currentTime) {
        this->waitingTime = currentTime - this->arrivalTime;
    }

};