# 🚀 Queue Simulation System
**Data Structures Project | First Year, Faculty of CSIT**

## 📝 Overview
This project is a comprehensive simulation of a service-based system (e.g., a bank or a clinic). It utilizes a **Linked List-based Queue** to manage customer flow, featuring a robust **VIP Priority** system where VIP customers are strategically inserted into the queue to receive faster service.

## ✨ Key Features
*   **Dynamic Queue Management:** Implemented from scratch using a Linked List to ensure efficient memory usage.
*   **VIP Priority System:** Intelligent logic to handle VIP customers, allowing them to skip ahead of regular customers while maintaining order among fellow VIPs.
*   **Real-time Simulation Engine:** Tracks arrival times, service durations, and server availability through a "Time Tick" system.
*   **Interactive GUI:** A modern interface built with **SFML** featuring:
    *   Live server status (Free/Busy/Remaining Time).
    *   Visual queue representation.
    *   Real-time statistics (Arrived vs. Served customers).
    *   A dynamic line graph showing queue history.

## 🛠️ Tech Stack
*   **Language:** C++
*   **Library:** SFML 3.0.2 (Graphics, Window, System)
*   **Compiler:** g++

## 📂 Project Structure

Data-Structure-project/
├── src/                # Header files and Source files
│   ├── Controller.h
│   ├── Customer.h
│   ├── GUI.h
│   ├── Queue.h
│   ├── Server.h
│   ├── Simulation.h
│   └── main.cpp
├── assets/             
│   └── font.ttf        # UI font file
├── build/              # Executable and SFML DLLs
│   ├── sim_app.exe
│   └── sfml-xxx-3.dll  # Pre-included library dependencies
├── .gitignore          
└── README.md           


## ⚙️ How to Compile & Run

### 1. Prerequisites
*   Ensure **SFML 3.0.2** is installed in the path: `C:\SFML-3.0.2`.
*   Ensure the **Compiler** (g++) is added to your system Environment Variables.

### 2. Compilation
Execute the following command from the **root directory** to allow the **Compiler** to locate the **Header** files inside the `src` folder:
```bash
g++ src/main.cpp -I"C:\SFML-3.0.2\include" -L"C:\SFML-3.0.2\lib" -o build/sim_app -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Execution
The necessary **DLL** files are already included in the `build` folder. Simply run:
```bash
cd build
./sim_app
```

## ⚙️ Simulation Tweaks (Scenario Testing)
You can modify the simulation behavior by adjusting constants in the **Header** files:

*   **VIP Probability:** To change how often VIP customers appear, modify the probability logic in `Simulation.h` or `Controller.h`.
*   **Service Time:** To adjust how long a server stays "Busy," update the `serviceTime` variables in `Server.h`.
*   **Visual Assets:** If you change the font, ensure the new file is named `font.ttf` and placed in the `assets/` directory.

## 👥 Contributors
*   **Khaled**
*   **Adham**
*   **Asser**
*   **Ahmed**