![Logo](boids_simulator.png)

# Boids Simulator
![WIP](https://img.shields.io/badge/Work-In%20Progress-ffff00)
![Status](https://img.shields.io/badge/Status-Not%20Ready-ff0000)
[![C23](https://img.shields.io/badge/C-23-ffffaa)](https://cppreference.com/c/23)
[![C++26](https://img.shields.io/badge/C%2B%2B-26-aaffff)](https://cppreference.com/cpp/26)
[![EnTT](https://img.shields.io/badge/EnTT-v3.16.0-aaaaff)](https://github.com/skypjack/entt/releases/tag/v3.16.0)
[![SFML](https://img.shields.io/badge/SFML-3.1.0-aaffaa)](https://github.com/SFML/SFML/releases/tag/3.1.0)
![License](https://img.shields.io/badge/License-MIT-ffaaff)

A simple flocking simulation.
> **Disclaimer: This is a proof-of-concept. The current implementation is $O(n^2)$ and is poorly optimized. Refactoring and spatial partitioning are planned for future milestones.**

> **WARNING: The velocity of entities aren't still clamped. if the velocity is too high, it can cause total freeze.**

## Technical Architecture

- This project only supports **Windows** platform as it uses **Win32 API**.

| Specification | Value |
| :--- | :--- |
| **Toolchain** | CMake 4.0+ |
| **C++ Standard** | C++26 |
| **C Standard** | C23 |
| **Linking** | Fully ***Static*** |

### Dependencies
- **[EnTT](https://github.com/skypjack/entt/releases/tag/v3.16.0) v3.16.0** — Entity Component System (ECS)
- **[SFML](https://github.com/SFML/SFML/releases/tag/3.1.0) 3.1.0** — Multimedia & Rendering Layer

> **Note:** All dependencies are managed via CMake's `FetchContent`. They will be automatically cloned and linked during the configuration phase — no manual dependency installation required.

## The simulation logic

The simulation implements **Craig Reynolds' Steering Behaviors**:
- **Separation:** Local flockmates avoid crowding.
- **Alignment:** Entities steer towards the average heading of neighbors.
- **Cohesion:** Entities steer toward the local center of mass.

## Build instruction

1. Ensure you have **CMake 4.0+** and a **C++26 compatible compiler** (**MSVC 19.40+** or **Clang 18+**).
2. Run the following:
   ```bash
   cmake -B build
   cmake --build build --config Release
   ```