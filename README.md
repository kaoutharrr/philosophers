# Philosophers Project

## Table of Contents
- [Introduction](#introduction)
- [Objectives](#objectives)
- [Concepts](#concepts)
- [Problem Description](#problem-description)
- [Implementation Details](#implementation-details)
- [Setup and Compilation](#setup-and-compilation)
- [Usage](#usage)
- [Example](#example)


## Introduction
The **Philosophers** project is part of the **42 curriculum**, designed to teach students about **threads**, **concurrency**, and **synchronization** in the context of the classic **Dining Philosophers Problem**. The project simulates a scenario where philosophers sit at a round table, alternating between thinking and eating. Each philosopher can only eat if they have access to two forks (one in each hand), but there are only as many forks as there are philosophers, which leads to contention.

## Objectives
- Learn how to manage **concurrency** using threads.
- Use **mutexes** to handle shared resources.
- Avoid **deadlock** and **race conditions** when managing shared data between threads.
- Create an efficient solution that ensures that all philosophers eat and think without starvation or crashing.

## Concepts

### Dining Philosophers Problem
The dining philosophers problem is a classic synchronization problem in computer science. A group of philosophers sits at a table, with one fork between each pair of adjacent philosophers. Philosophers must alternate between thinking and eating. In order to eat, a philosopher needs to pick up both forks adjacent to them (one fork on the left, and one on the right). After eating, they must put both forks down and go back to thinking.

### Threads and Concurrency
- Each philosopher is represented as a **thread**.
- Forks are represented as **shared resources** that multiple threads (philosophers) attempt to access.
- Using **mutexes** ensures that only one philosopher can pick up a fork at any time.
  
### Challenges
- **Deadlock**: If all philosophers pick up the fork on their left simultaneously, no one will be able to eat.
- **Race conditions**: Without proper synchronization, philosophers could pick up or put down forks in an inconsistent state, leading to undefined behavior.

## Problem Description
- Philosophers alternate between **eating**, **thinking**, and **sleeping**.
- They can only eat if they successfully pick up both the forks to their left and right.
- The simulation ends if a philosopher dies (i.e., they don't eat within a certain time limit).
  
### Key Variables:
- **Number of philosophers**: The number of philosophers at the table.
- **Time to die**: The maximum time a philosopher can go without eating.
- **Time to eat**: The time a philosopher spends eating.
- **Time to sleep**: The time a philosopher spends sleeping.
- **Number of meals**: Optional - the simulation can end if all philosophers have eaten a specified number of times.

## Implementation Details

### Threads
- Each philosopher is created as a separate **thread**.
- The philosopher threads run concurrently and compete for access to the shared forks (resources).

### Mutexes
- **Mutexes** are used to protect shared resources (forks) and avoid race conditions.
- Each fork is associated with a mutex, ensuring that only one philosopher can hold the fork at a time.

### Avoiding Deadlock
Common strategies for avoiding deadlock include:
- Ensuring that philosophers pick up forks in a particular order (e.g., always pick up the left fork first, then the right).
- Introducing a mechanism to detect deadlock and prevent it by forcing philosophers to put down forks if they cannot acquire both.

### State Management
The philosophers’ actions (eating, thinking, sleeping) and time constraints are monitored to ensure no philosopher dies from starvation. The simulation should print the state of each philosopher.

### Error Handling
The program should handle invalid arguments, invalid philosopher numbers, or time values gracefully and exit with an appropriate error message.

## Setup and Compilation

### Prerequisites
- **pthread**: The project uses the **pthread** library to manage threads and mutexes.
  
### Compilation
To compile the project, run:
```bash
make
```
## Usage

To run the simulation, provide the required arguments:

```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
### Arguments:

1. **number_of_philosophers**: The number of philosophers and forks.
2. **time_to_die** (in milliseconds): The maximum time a philosopher can go without eating.
3. **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat.
4. **time_to_sleep** (in milliseconds): The time a philosopher spends sleeping.
5. **[number_of_times_each_philosopher_must_eat]** (optional): If all philosophers eat this many times, the simulation ends.

### Example

```bash
./philosophers 5 800 200 200 7
```
This runs the simulation with 5 philosophers, where each philosopher must eat 7 times. Each philosopher dies if they don't eat within 800 milliseconds, they spend 200 milliseconds eating, and 200 milliseconds sleeping.

```csharp
    0 1 is thinking
    0 2 is thinking
    0 3 is thinking
    0 4 is thinking
    0 5 is thinking
    200 1 is eating
    400 2 is eating
    600 3 is eating
    800 4 is eating
    ...
```

