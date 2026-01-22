# Dining Philosophers Problem - Solution

A multi-threaded C implementation of the classic Dining Philosophers synchronization problem using POSIX threads and mutexes.

## Overview

This solution simulates the famous Dining Philosophers problem, where multiple philosophers sit around a table trying to eat, think and sleep. Each philosopher needs two forks to eat, but there are only as many forks as philosophers. The challenge is to prevent deadlocks and starvation while ensuring proper synchronization.

## Problem Description

- **N philosophers** sit at a round table
- Each philosopher alternates between **eating**, **thinking**, and **sleeping**
- Between each philosopher are **forks** (resources)
- A philosopher must acquire **both adjacent forks** to eat
- If a philosopher doesn't eat within a specified time, they **die**
- The simulation ends when a philosopher dies, or all philosophers have eaten the required number of meals

## Features

- **Thread-safe implementation** using POSIX threads (`pthread`)
- **Mutex-based synchronization** to prevent race conditions
- **No deadlocks** - careful fork acquisition and release strategy
- **Starvation prevention** - ensures fair access to resources
- **Real-time monitoring** - tracks philosopher states with timestamps
- **Graceful shutdown** - clean thread termination and resource cleanup

## Project Structure

```
philo/
├── main.c              # Entry point, argument parsing, and cleanup
├── init.c              # Initialization of table, philosophers, and forks
├── simulation.c        # Simulation loop and philosopher threads
├── philo_actions.c     # Philosopher actions (eating, sleeping, thinking)
├── util.c              # Utility functions and helpers
├── philosophers.h      # Header file with structures and declarations
├── Makefile            # Build configuration
└── README.md           # This file
```

## Building and Running

### Compilation

```bash
make              # Build the executable
make clean        # Remove object files
make fclean       # Remove object files and executable
make re           # Rebuild from scratch
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers and forks (must be > 0) |
| `time_to_die` | Time in milliseconds before a philosopher dies (must be > 0) |
| `time_to_eat` | Time in milliseconds a philosopher spends eating (must be > 0) |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping (must be > 0) |
| `number_of_times_each_philosopher_must_eat` | (Optional) Number of times each philosopher must eat; simulation stops when this is reached for all philosophers |

### Examples

Run simulation with 5 philosophers, die after 800ms of not eating, 200ms to eat, 200ms to sleep:
```bash
./philo 5 800 200 200
```

Run simulation where each philosopher must eat 7 times:
```bash
./philo 4 800 200 200 7
```

## Implementation Details

### Data Structures

**t_fork**: Represents a fork with synchronization primitives
- `lock` - Mutex for fork access
- `in_use` - Boolean flag indicating if fork is in use
- `in_use_lock` - Mutex protecting the in_use flag

**t_philo**: Represents a philosopher
- `index` - Philosopher identifier
- `times_eaten` - Number of times the philosopher has eaten
- `fork_left` / `fork_right` - Adjacent fork pointers
- `time_to_eat`, `time_to_sleep`, `time_to_die` - Timing parameters
- `last_time_eaten` - Timestamp of last meal (for starvation detection)
- `start_time` - Simulation start time
- `thread` - POSIX thread identifier
- `table` - Pointer to the shared table

**t_table**: Represents the dining table
- `philosophers` - Array of philosophers
- `forks` - Array of forks
- `philo_count` - Number of philosophers
- `stop_simulation` - Flag to stop the simulation
- Various mutexes for synchronization

### Synchronization Strategy

1. **Fork Acquisition**: Each fork has its own mutex protecting access
2. **State Tracking**: Philosopher state (eating, thinking, sleeping) is protected
3. **Death Detection**: A reaper function monitors if any philosopher has exceeded `time_to_die` without eating
4. **Write Safety**: All output is protected by a write lock to prevent garbled messages

### Key Functions

- `main()` - Entry point, validates arguments, initializes table, starts simulation
- `init_table()` - Allocates memory and initializes philosophers and forks
- `start_simulation()` - Creates philosopher threads and starts execution
- `philo_routine()` - Main loop executed by each philosopher thread
- `eating()` - Philosopher acquires forks and eats
- `thinking()` - Philosopher thinks
- `sleeping()` - Philosopher sleeps
- `reaper()` - Monitors philosophers health (starvation detection)
- `print_action()` - Thread-safe output of philosopher actions

## Output Format

The program outputs philosopher actions with timestamps:
```
[timestamp] Philosopher X has taken a fork
[timestamp] Philosopher X is eating
[timestamp] Philosopher X is sleeping
[timestamp] Philosopher X is thinking
[timestamp] Philosopher X died
```

## Compilation Flags

- `-Wall` - Enable all common warnings
- `-Wextra` - Enable extra warnings
- `-Werror` - Treat warnings as errors
- `-g` - Include debugging symbols

## Technical Notes

- Threads are joined in `clean_up()` to ensure proper termination
- All mutexes are destroyed after threads finish
- Memory is freed to prevent leaks
- The solution handles edge cases like a single philosopher (who cannot eat)
- Time is measured in milliseconds for precision

## Author

dtrendaf

---

*This is a solution to the Dining Philosophers synchronization problem, a classic exercise in concurrent programming and deadlock avoidance.*
