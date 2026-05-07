// Customer file
#pragma once
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
        this->isVip = false;
        this->waitingTime= 0;
    }

    Customer(int id, int arrivalTime, int serviceTime, bool isVip){
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
        this->isVip = isVip;
         this->waitingTime = 0;
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
    bool getIsVIP() const {
        return isVip;
    }

    void calculateWaitingTime(int currentTime) {
    waitingTime = currentTime - arrivalTime;
    }

    int getWaitingTime() const {
    return waitingTime;
    }
};