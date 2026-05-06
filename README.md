# 🚀 Queue Simulation System
**Data Structures Project | First Year, Faculty of Computers and Artificial Intelligence**

## 📝 Overview
This project is a comprehensive simulation of a service-based system (e.g., a bank or a clinic). It utilizes a **Linked List-based Queue** to manage customer flow, featuring a robust **VIP Priority** system where VIP customers are strategically inserted into the queue to receive faster service.

## ✨ Key Features
*   **Dynamic Queue Management:** Implemented from scratch using a Linked List to ensure efficient memory usage.
*   **VIP Priority System:** Intelligent logic to handle VIP customers, allowing them to skip ahead of regular customers while maintaining order among fellow VIPs.
*   **Real-time Simulation Engine:** Tracks arrival times, service durations, and server availability through a "Time Tick" system.
*   **Interactive GUI:** A modern, technical interface built with **SFML** featuring:
    *   Live server status (Free/Busy/Remaining Time).
    *   Visual queue representation.
    *   Real-time statistics (Arrived vs. Served customers).
    *   A dynamic line graph showing queue size history.

## 🛠️ Tech Stack
*   **Language:** C++
*   **Library:** SFML 3.0.2 (Graphics, Window, System)
*   **Development Tools:** VS Code / Terminal

## 📂 Project Structure
```text
Data-Structure-project/
├── src/                # Header files (.h) and Source files (.cpp)
├── assets/             
│   └── fonts/          # UI fonts (font.ttf)
├── build/              # Executable (sim_app.exe) and SFML DLLs
├── report/             # Project documentation and analysis
├── .gitignore          # Rules for Git to ignore build files
└── README.md           # Project overview (This file)
```

## ⚙️ How to Compile & Run

### 1. Prerequisites
*   Ensure **SFML 3.0.2** is installed (Default path: `C:\SFML-3.0.2`).
*   Ensure your C++ compiler (g++) is added to your system Environment Variables.

### 2. Compilation
Open your terminal in the root directory and run the following command:
```bash
g++ src/main.cpp -I"C:\SFML-3.0.2\include" -L"C:\SFML-3.0.2\lib" -o build/sim_app -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Execution
Navigate to the `build` folder and run the application:
```bash
cd build
./sim_app
```

## 👥 Contributors
*   **Khaled**
*   **Adham**
*   **Asser**
*   **Ahmed**


---

