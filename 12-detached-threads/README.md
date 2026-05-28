# 12-detached-threads

## Goal

Learn how detached threads work and how they differ from joinable threads.

This exercise introduces thread lifecycle management using detached threads.

---

## Task

Create:

- **5 detached threads**

The main thread should:

- create all worker threads in detached mode
- NOT use `pthread_join()`
- sleep for 3 seconds
- terminate the program

Each worker thread should:

- print its thread number
- sleep for 1 second
- finish independently

---

## Requirements

### Worker Threads

Each thread should:

```txt
- print its id
- sleep for 1 second
- exit automatically
```

### Main Thread

The main thread should:

```txt
- create detached threads
- not wait for them
- sleep for 3 seconds
- terminate
```

---

## Detached Threads

Detached threads release their resources automatically after finishing execution.

Unlike joinable threads:

- they cannot be joined using `pthread_join()`
- the main thread does not wait for them explicitly

---

## Concepts Covered

- detached threads
- thread lifecycle
- `pthread_detach`
- automatic resource cleanup
- joinable vs detached threads

---

## Example Output

```txt
Thread 0 started
Thread 1 started
Thread 2 started
Thread 3 started
Thread 4 started

Thread 0 finished
Thread 1 finished
Thread 2 finished
Thread 3 finished
Thread 4 finished

Main thread exiting...
```

---

## Suggested Functions

Example:

```c
void *thread_func(void *arg);
```

---

## Important

Detached threads must either:

- call:

```c
pthread_detach(pthread_self());
```

or be created with detached thread attributes.

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

## Bonus Challenges

After completing the task, try:

- creating detached threads dynamically
- comparing detached vs joinable threads
- using thread attributes (`pthread_attr_t`)
- creating long-running background workers

---

## Learning Objective

Understand how detached threads manage their own lifecycle and when they are useful in concurrent applications.