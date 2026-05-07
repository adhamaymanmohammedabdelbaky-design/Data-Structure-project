#pragma once
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "Server.h"
#include "Queue.h"

class Simulation {
private:
    int currentTime;
    int maxSimulationTime;
    int totalCustomersArrived;
    int totalCustomersServed;
    int totalWaitingTime;      // Accumulated waiting time of all served customers
    int nextArrivalTime;

    std::vector<Server> servers;
    Queue customerQueue;
    std::vector<int> queueHistory; // Tracks the queue length over time

    bool isRunning; // Indicates whether the simulation is running
    bool isPaused;  // Indicates whether the simulation is paused

    // Random number generator used to generate random arrivals, service times, and VIP status
    std::mt19937 rng; // Mersenne Twister random number generator

    // Returns a random integer between min and max inclusive
    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Randomly decides if a customer is VIP with a 20% chance
    bool getRandomVIP() {
        std::uniform_int_distribution<int> dist(1, 100);
        return dist(rng) <= 20; // 20% chance of being VIP
    }

public:
    // Constructor
    Simulation() {
        this->currentTime = 0;
        this->maxSimulationTime = 0;
        this->totalCustomersArrived = 0;
        this->totalCustomersServed = 0;
        this->totalWaitingTime = 0;
        this->nextArrivalTime = 0;
        this->isRunning = false;
        this->isPaused = false;

        // Initialize random number generator with a random seed
        rng.seed(std::random_device{}());
    }

    // Initializes the simulation settings
    // This function should be called before running the simulation
    void initializeSimulation() {
        currentTime = 0;
        maxSimulationTime = 80; // Default max simulation time

        totalCustomersArrived = 0;
        totalCustomersServed = 0;
        totalWaitingTime = 0;
        nextArrivalTime = 0;

        isRunning = true;
        isPaused = false;

        customerQueue.clearQueue(); // Clear the queue directly using the new public function
        queueHistory.clear();       // Clear old queue history

        int numServers = 3;         // Default number of servers
        servers.clear();
        servers.resize(numServers);

        // Set the first customer arrival time after 1 or 2 time ticks
        nextArrivalTime = currentTime + getRandomInt(1, 2);
    }

    // Updates the whole simulation by one time tick
    // This function is usually called repeatedly by the Controller
    void updateSimulation() {
        if (!isRunning || isPaused) {
            return; // Do nothing if the simulation is not running or is paused
        }

        // Stop the simulation when the maximum simulation time is reached
        if (currentTime >= maxSimulationTime) {
            isRunning = false;
            return;
        }

        updateServers();                                        // Update the status of all servers
        processArrival();                                       // Handle new customer arrivals
        assignCustomersToServers();                             // Assign waiting customers to free servers
        customerQueue.updateWaitingTimes(currentTime);         // Update waiting time for all queued customers

        // Save the current queue size for graph drawing
        queueHistory.push_back(customerQueue.getQueueSize());

        currentTime++; // Move to the next time tick
    }

    // Handles new customer arrival
    // A new customer is created when currentTime reaches nextArrivalTime
    void processArrival() {
        if (currentTime == nextArrivalTime) {
            totalCustomersArrived++; // Increment total customers arrived

            // Create a new customer with random service time and VIP status
            int serviceTime = getRandomInt(5, 10); // Random service time between 5 and 10
            bool isVip = getRandomVIP();            // Randomly determine if the customer is VIP

            // Create a new customer with ID, arrival time, service time, and VIP status
            Customer newCustomer(
                totalCustomersArrived,
                currentTime,
                serviceTime,
                isVip
            );

            // Add the new customer to the queue
            customerQueue.enqueueCustomer(newCustomer);

            // Schedule the next customer arrival after 1 or 2 time ticks
            nextArrivalTime = currentTime + getRandomInt(1, 2);
        }
    }

    // Updates all servers by one time tick
    void updateServers() {
        for (int i = 0; i < servers.size(); i++) {
            bool wasBusy = servers[i].isBusy();

            // Capture the waiting time of the current customer before service ends
            // This is the moment they leave — their final waiting time is recorded here
            int waitingTimeBeforeFinish = servers[i].getCurrentCustomer().getWaitingTime();

            servers[i].updateTime();

            // If the server was busy and became free, then one customer has finished service
            if (wasBusy && servers[i].isFree()) {
                totalCustomersServed++;
                totalWaitingTime += waitingTimeBeforeFinish; // Accumulate their waiting time
            }
        }
    }

    // Assigns customers from the queue to free servers
    void assignCustomersToServers() {
        for (int i = 0; i < servers.size(); i++) {
            if (servers[i].isFree() && !customerQueue.isQueueEmpty()) {
                Customer nextCustomer = customerQueue.dequeueCustomer();
                servers[i].assignCustomer(nextCustomer);
            }
        }
    }

    // Writes a summary report to a text file when the simulation ends
    void printFinalReport() {
        std::ofstream reportFile("simulation_report.txt");

        if (!reportFile.is_open()) {
            return; // If the file can't be opened, silently exit
        }

        // Calculate average waiting time
        double avgWaitingTime = 0.0;
        if (totalCustomersServed > 0) {
            avgWaitingTime = (double)totalWaitingTime / totalCustomersServed;
        }

        // Calculate peak queue size from history
        int peakQueueSize = 0;
        for (int i = 0; i < queueHistory.size(); i++) {
            if (queueHistory[i] > peakQueueSize) {
                peakQueueSize = queueHistory[i];
            }
        }

        // Calculate how many customers are still unserved
        int customersInSystem = totalCustomersArrived - totalCustomersServed;

        reportFile << "========================================\n";
        reportFile << "         SIMULATION FINAL REPORT        \n";
        reportFile << "========================================\n\n";

        reportFile << "Simulation Duration  : " << maxSimulationTime << " ticks\n";
        reportFile << "Number of Servers    : " << servers.size() << "\n\n";

        reportFile << "----------------------------------------\n";
        reportFile << "CUSTOMER STATISTICS\n";
        reportFile << "----------------------------------------\n";
        reportFile << "Total Arrived        : " << totalCustomersArrived << "\n";
        reportFile << "Total Served         : " << totalCustomersServed << "\n";
        reportFile << "Still in System      : " << customersInSystem << "\n\n";

        reportFile << "----------------------------------------\n";
        reportFile << "PERFORMANCE STATISTICS\n";
        reportFile << "----------------------------------------\n";
        reportFile << "Average Waiting Time : " << avgWaitingTime << " ticks\n";
        reportFile << "Peak Queue Size      : " << peakQueueSize << " customers\n\n";

        reportFile << "----------------------------------------\n";
        reportFile << "SERVER STATISTICS\n";
        reportFile << "----------------------------------------\n";
        for (int i = 0; i < servers.size(); i++) {
            reportFile << "Server " << (i + 1) << "             : "
                       << servers[i].getTotalServedCount() << " customers served\n";
        }

        reportFile << "\n========================================\n";
        reportFile << "           END OF REPORT               \n";
        reportFile << "========================================\n";

        reportFile.close();
    }

    // Getters used by the GUI to read simulation data

    // Returns the current simulation time
    int getCurrentTime() const { return currentTime; }

    // Returns the maximum simulation time
    int getMaxTime() const { return maxSimulationTime; }

    // Returns the total number of customers that arrived
    int getArrivedCount() const { return totalCustomersArrived; }

    // Returns the total number of customers that finished service
    int getServedCount() const { return totalCustomersServed; }

    // Returns whether the simulation is still running
    bool getIsRunning() const { return isRunning; }

    // Returns all servers for GUI display
    const std::vector<Server>& getServers() const { return servers; }

    // Returns the customer queue for GUI display
    const Queue& getQueue() const { return customerQueue; }

    // Returns queue size history for drawing the graph
    const std::vector<int>& getQueueHistory() const { return queueHistory; }

    // Switches the pause state between paused and not paused
    void togglePause() {
        isPaused = !isPaused;
    }

    // Returns whether the simulation is paused
    bool getIsPaused() const {
        return isPaused;
    }
};