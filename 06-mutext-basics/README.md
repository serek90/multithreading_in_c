# 06-mutex-counter-fix

## Goal

Fix the race condition from the previous exercise by protecting the shared counter with a mutex.

The final counter value must always be:

```txt
1000000
```

---

## Background

In the previous task, multiple threads were incrementing the same shared variable without synchronization.

Because several threads accessed and modified the counter at the same time, the program produced inconsistent results due to a **race condition**.

This exercise introduces **mutexes** to ensure safe access to shared data.

---

## Requirements

### Program requirements

- Create multiple threads
- Each thread increments the same shared counter
- Use a mutex to protect the critical section
- The counter must always reach:

```txt
1000000
```

- Wait for all threads to finish before exiting the program

---

## Concepts Covered

- `pthread_mutex_t`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`
- critical sections
- thread synchronization
- race condition prevention

---

## Example Output

```txt
Final counter value: 1000000
```

---

## Build

```bash
gcc main.c -o app -lpthread
```

With additional warnings:

```bash
gcc main.c -o app -lpthread -Wall -Wextra -Werror
```

---

## Run

```bash
./app
```

---

## Suggested Improvements

After completing the exercise, try:

- measuring execution time
- comparing mutex vs no mutex
- using atomic operations instead of mutexes
- changing the number of threads
- experimenting with false sharing

---

## Learning Objective

Understand how mutexes protect shared resources and why synchronization is essential in multithreaded programs.