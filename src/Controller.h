#pragma once
#include <SFML/System.hpp>
#include "Simulation.h"
#include "GUI.h"

class Controller {
private:
    Simulation sim;
    GUI gui; 
    
    sf::Clock tickClock;   // Real Clock used to control the simulation update speed
    float timePerTick;     // Connect between real time and simulation time (e.g., 1 second per simulation tick)

public:
    // Sets the simulation to update once every 1 second
    // 1 second = 1 simulation tick
    Controller() : timePerTick(1.0f) {} 
    

    void initializeSystem() {
        // The settings configuration and connecting the controller to the simulation
        sim.initializeSimulation(); 
        gui.initializeWindow(); 
        gui.connectToSimulation(&sim);
    }

    void startSimulation() {
        // When the app is running the system is updated using the function updateSystem
        while (gui.isOpen()) {
            gui.handleEvents(); // Handle keyboard, mouse, and window events
            updateSystem();     // Update simulation based on time
            gui.updateGUI();    // Redraw the GUI every frame
        }
    }

    // Updates the simulation based on the tick clock
    // The simulation updates only after timePerTick seconds have passed
    void updateSystem() {
        if (tickClock.getElapsedTime().asSeconds() >= timePerTick) {

            // Update simulation only if it is running and not paused
            if (sim.getIsRunning() && !sim.getIsPaused()) {
                sim.updateSimulation();
            }

            // Restart the clock to begin counting for the next tick
            tickClock.restart();
        }
    }
};