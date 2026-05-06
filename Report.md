
````markdown id="9cvgzh"
## How the Program Works

When the program starts, it begins from the `main.cpp` file. The main function creates an object from the `Controller` class, then calls two main functions: `initializeSystem()` and `startSimulation()`.

The `Controller` class is responsible for connecting the simulation logic with the graphical user interface. It controls the main program loop and decides when the simulation should be updated.
````
---
## System Initialization

First, the program calls:

```cpp
controller.initializeSystem();
````

This function prepares the whole system before the simulation starts.

It performs three main steps:

```cpp
sim.initializeSimulation();
gui.initializeWindow();
gui.connectToSimulation(&sim);
```

### 1. Initializing the Simulation

The simulation starts by setting the initial values:

* Current time starts from 0.
* Maximum simulation time is set to 80 ticks.
* Total arrived customers starts from 0.
* Total served customers starts from 0.
* The queue is reset.
* The queue history is cleared.
* Three servers are created.
* The first customer arrival time is randomly generated.

This prepares the simulation to start from a clean state.

### 2. Initializing the GUI

The GUI creates the SFML window, loads the font, and prepares the visual elements such as the pause button, panels, server display, queue area, and graph.

### 3. Connecting GUI with Simulation

The GUI receives a pointer to the simulation object. This allows the GUI to read simulation data such as the current time, queue size, server status, number of arrived customers, and number of served customers.

The GUI does not control the main logic. It only displays the current state of the simulation.

---

## Main Program Loop

After initialization, the program calls:

```cpp
controller.startSimulation();
```

This function contains the main loop:

```cpp
while (gui.isOpen()) {
    gui.handleEvents();
    updateSystem();
    gui.updateGUI();
}
```

As long as the window is open, the program keeps repeating three steps:

1. Handle user events, such as closing the window or clicking the pause button.
2. Update the simulation logic when a tick passes.
3. Redraw the GUI to show the latest simulation state.

---

## Time Tick System

The simulation does not update every frame. The GUI may refresh many times per second, but the simulation logic updates once every fixed time interval.

In the `Controller` class, the variable `timePerTick` is set to:

```cpp
timePerTick = 1.0f;
```

This means that one real second equals one simulation tick.

The `tickClock` measures real time. When one second passes, the controller calls:

```cpp
sim.updateSimulation();
```

Then the clock restarts to count the next tick.

---

## Simulation Update Process

The most important function in the simulation is:

```cpp
updateSimulation();
```

This function updates the whole system by one tick.

It performs the following steps:

```cpp
updateServers();
processArrival();
assignCustomersToServers();
customerQueue.updateWaitingTimes(currentTime);
queueHistory.push_back(customerQueue.getQueueSize());
currentTime++;
```

---

## 1. Updating Servers

The simulation first updates all servers.

Each server checks whether it is busy. If a server is serving a customer, its remaining service time decreases by one tick.

For example, if a customer has 5 ticks remaining:

```text
5 -> 4 -> 3 -> 2 -> 1 -> 0
```

When the remaining time reaches zero, the server finishes serving the customer. The server becomes free again, and the total served count increases.

---

## 2. Processing Customer Arrivals

After updating the servers, the simulation checks whether a new customer should arrive.

This happens when:

```cpp
currentTime == nextArrivalTime
```

If the condition is true, a new customer is created.

The customer is given:

* A unique ID
* Arrival time
* Random service time
* VIP or normal status

The service time is randomly chosen between 5 and 10 ticks. The VIP status is also randomly generated, with a 20% chance of being VIP.

After the customer is created, the customer is added to the queue.

Then, the next customer arrival time is generated randomly after 1 or 2 ticks.

---

## 3. Adding Customers to the Queue

Customers are stored in a linked list queue.

If the customer is normal, they are added to the rear of the queue.

If the customer is VIP, they are inserted before normal customers, but after any VIP customers who are already waiting.

For example, if the queue is:

```text
VIP1 -> VIP2 -> Normal1 -> Normal2
```

And a new VIP customer arrives, the queue becomes:

```text
VIP1 -> VIP2 -> VIP3 -> Normal1 -> Normal2
```

This means VIP customers have priority over normal customers, but they do not skip other VIP customers who arrived earlier.

---

## 4. Assigning Customers to Servers

After processing arrivals, the simulation assigns customers to free servers.

The system checks each server. If a server is free and the queue is not empty, the first customer in the queue is removed and assigned to that server.

This is done using:

```cpp
Customer nextCustomer = customerQueue.dequeueCustomer();
servers[i].assignCustomer(nextCustomer);
```

When a customer is assigned to a server:

* The server becomes busy.
* The customer becomes the current customer of the server.
* The server remaining time is set to the customer service time.

---

## 5. Updating Waiting Time

The simulation updates the waiting time for all customers who are still in the queue.

The waiting time is calculated using:

```cpp
waitingTime = currentTime - arrivalTime;
```

For example, if a customer arrived at time 5 and the current time is 9:

```text
waitingTime = 9 - 5 = 4 ticks
```

This allows the system to track how long each customer has been waiting.

---

## 6. Saving Queue History

At each tick, the simulation stores the current queue size in a vector called `queueHistory`.

This history is used by the GUI to draw the line graph that shows how the queue size changes over time.

For example:

```text
0, 1, 2, 2, 3, 1, 0
```

These values represent the queue size at different simulation ticks.

---

## 7. Increasing Current Time

At the end of each simulation update, the current time increases by one:

```cpp
currentTime++;
```

This moves the simulation to the next tick.

---

## GUI Display

The GUI is responsible for displaying the simulation visually.

It shows:

* Current simulation time
* Number of arrived customers
* Number of served customers
* Queue size
* Server status
* Current customer being served
* Remaining service time
* VIP customers
* Waiting queue
* Queue size graph
* Pause and resume button

The GUI reads data from the simulation object and redraws the window every frame.

---

## Pause and Resume

The GUI includes a pause button.

When the user clicks the button, the simulation switches between paused and running states.

If the simulation is paused, the `updateSimulation()` function does not run, so time, arrivals, servers, and queue updates stop temporarily.

When the simulation resumes, the updates continue from the same point.

---

## Simple Example

Assume the simulation starts at time 0.

At time 0:

```text
No customer has arrived yet.
All servers are free.
The queue is empty.
```

At time 1:

```text
A new customer arrives.
The customer is added to the queue.
If a server is free, the customer is immediately assigned to that server.
The server becomes busy.
```

At time 2:

```text
The server remaining time decreases by one.
Another customer may arrive.
If there is a free server, the next customer in the queue is assigned.
```

This process continues until the simulation reaches the maximum simulation time.

---

## Summary

The program works as a complete queue simulation system.

The `Controller` manages the main loop and connects the simulation with the GUI.

The `Simulation` class contains the main logic, including time updates, customer arrivals, queue management, server updates, and statistics.

The `Queue` class stores waiting customers using a linked list and applies VIP priority.

The `Server` class serves customers and tracks remaining service time.

The `Customer` class stores customer information.

The `GUI` class displays the system visually using SFML.

Overall, the program demonstrates how linked lists and queues can be used in a real simulation system with priority handling and graphical visualization.