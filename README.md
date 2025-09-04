# Philosophers

The classic **Dining Philosophers Problem** in C.  
This project explores **multithreading**, **synchronization**, and the eternal struggle of philosophers:  
> "How do you eat spaghetti without deadlocking your friends?"

---

## ✨ Project Description

- You have **N philosophers** sitting around a round table.  
- Each philosopher can:
  - **eat** 🍝
  - **sleep** 😴
  - **think** 💭  
- But to eat, they need **two forks** (left + right).  
- The catch? Each fork can only be held by **one philosopher at a time**.  

The challenge:  
Write a program where philosophers eat, sleep, and think without falling into **deadlock** or **race conditions**, while respecting timing rules.  

---

## ✨ Core Concepts
- **Threads**: Each philosopher is a separate thread.  
- **Mutexes**: Forks are represented by mutexes, ensuring only one philosopher can hold each fork.  
- **Timing**:  
  - `time_to_die`: max time a philosopher can go without eating  
  - `time_to_eat`: time spent eating  
  - `time_to_sleep`: time spent sleeping  
  - Optional: number of meals each philosopher must eat  

## ✨ Synchronization Strategy
- delayed start to ensure all threads (incl. the watcher) were created

### 1. Philosopher Logic (`do_logic`)
- **One philosopher**: takes a fork, waits, dies.
- **Odd number of philosophers**: odd IDs grab forks immediately, even IDs wait 1000, last philosopher waits 2000.  
- **Even number of philosophers**: odd IDs grab forks immediately, even IDs wait 1000.
- After eating: check meals, sleep, think (buffer time to synchronise philosophers), and repeat.

### 2. Fork Acquisition
- Philosopher locks **first fork**, checks stop condition, logs action.  
- Then locks **second fork**, checks stop, logs action.  
- Any failure unlocks previously locked forks safely.  
- Ensures **mutual exclusion** on forks.


### 3. Timing & Staggering Logic

| Philosopher Type | Start Delay             | Sleep Adjustments                                           |
|-----------------|--------------------------|-------------------------------------------------------------|
| Odd             | none (except last)      | If `sleep < 2 * eat`, sleep `(2*eat - sleep)` to balance turns |
| Even            | `usleep(time_to_eat*1000)` | If `sleep < eat`, sleep `(eat - sleep)` for synchronization  |
| Last (for odd num of philos)           | `usleep(time_to_eat*2000)` | Right fork first to avoid collisions                        |

- Prevents simultaneous fork grabs  
- Avoids starvation  
- Maintains accurate timing for `time_to_die`, `time_to_eat`, `time_to_sleep`

---

## ✨ Example Usage

```bash
$ ./philo 5 800 200 200
```
### It means:

5 philosophers

time_to_die: 800 ms

time_to_eat: 200 ms

time_to_sleep: 200 ms

### Example Output
```
0 1 is thinking
10 1 has taken a fork
10 1 has taken a fork
11 1 is eating
210 1 is sleeping
410 1 is thinking
412 2 has taken a fork
413 2 has taken a fork
414 2 is eating
...
```
## ✨ Summary:
This project taught me how to handle concurrency, timing, and resource sharing. It was a really interesting introduction to parallel programming and synchronization.
