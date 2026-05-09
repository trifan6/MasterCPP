# 📚 Master C++ | Tutorial Management Application

A full-stack C++ desktop application engineered to manage educational video content. Built on a strict Layered Architecture with a custom Qt Framework graphical user interface, the application leverages advanced Object-Oriented Programming (OOP) principles, efficient memory management, and robust design patterns to deliver a seamless user experience.

## ✨ Key Features

* **Strict Layered Architecture:** Completely decoupled codebase separated into Domain, Repository, Service, and UI layers for scalable and maintainable code.
* **Polymorphic Undo/Redo:** Implemented the **Command Design Pattern** utilizing abstract classes and polymorphism to provide robust, multi-level undo and redo functionality without corrupting application state.
* **Dynamic Persistence Layer:** Custom File I/O system utilizing inheritance to seamlessly serialize and deserialize application state into both **CSV** and **HTML** formats.
* **Qt UI & MVC Integration:** A fully responsive graphical interface leveraging Qt's `QAbstractTableModel` and STL containers (`std::vector`, `std::find`) to automatically sync frontend visuals with backend data logic.
* **Real-time Video Integration:** Automatically opens tutorial links in the user's default web browser directly from the Qt application.

## 🏗️ Architecture Overview

1. **Domain:** Contains the core `Tutorial` entity and strict data validation utilizing `const`-correctness to ensure memory safety.
2. **Repository:** Manages the dynamic storage of data utilizing STL vectors, handling direct File I/O operations and memory allocation.
3. **Service:** The controller layer that handles business logic, validates interactions, and manages the Undo/Redo polymorphic execution stacks.
4. **UI:** A Qt-based graphical interface utilizing `QStackedWidget` for seamless menu navigation and Model-View integration for live data updates.

## 💻 Tech Stack

* **Language:** C++ (C++20)
* **Framework:** Qt 6 (QtWidgets, QtGui, QtCore)
* **Build System:** CMake
* **Core Concepts:** OOP, Command Pattern, Polymorphism, MVC, Memory Management, File Serialization.

## 📸 Screenshots
*(Coming Soon)*

## 🚀 Getting Started

### Prerequisites
* A C++20 compatible compiler (Clang/GCC/MSVC)
* CMake (3.10+)
* Qt 6 Framework installed and configured
