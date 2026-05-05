#pragma once
#include "Simulation.h"
#include "GUI.h"

class Controller {
private:
    Simulation sim;
    GUI gui; //

public:
    void initializeSystem() {
        // The settings configuration and connecting the controller to the simulation
        sim.initializeSimulation(); 
        gui.initializeWindow(); 
        gui.connectToSimulation(&sim);
    }

    void startSimulation() {
        // When the app is running the system is updated using the function updateSystem
        while (gui.isOpen()) {
            updateSystem();
        }
    }

    //The function updateSystem updates the system status 
    void updateSystem() {
        gui.handleEvents(); // Handleing the user input 
        
        if (sim.getIsRunning()) {
            sim.updateSimulation();
        }

        gui.updateGUI(); // Updates what appears on the screen
    }
};