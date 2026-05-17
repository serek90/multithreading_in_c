# 10-producer-consumer

## Goal

Implement the classic **Producer-Consumer Problem** using threads, mutexes, and condition variables.

This exercise introduces thread synchronization with a shared circular buffer.

---

## Task

Create a program with:

- one **producer thread**
- one **consumer thread**
- a circular buffer with a capacity of:

```txt
10
```

The producer inserts numbers:

```txt
1 -> 20
```

into the buffer.

The consumer removes the numbers and prints them to the terminal.

---

## Requirements

### Producer

- generates numbers from `1` to `20`
- inserts numbers into the circular buffer
- waits if the buffer is full

### Consumer

- removes numbers from the buffer
- prints consumed values
- waits if the buffer is empty

---

## Synchronization

Use:

- `pthread_mutex_t`
- `pthread_cond_t`

to synchronize access to the shared buffer.

The program must avoid:

- race conditions
- busy waiting
- buffer overflows
- buffer underflows

---

## Buffer Rules

Implement the buffer as a **circular queue**.

Suggested variables:

```c
int buffer[10];
int head;
int tail;
int count;
```

---

## Concepts Covered

- producer-consumer problem
- mutex synchronization
- condition variables
- circular buffers
- thread communication
- blocking synchronization

---

## Example Output

```txt
Producer: inserted 1
Producer: inserted 2
Producer: inserted 3

Consumer: consumed 1
Consumer: consumed 2

Producer: inserted 4
Producer: inserted 5

Consumer: consumed 3
Consumer: consumed 4
```

---

## Suggested Functions

Example structure:

```c
void *producer(void *arg);
void *consumer(void *arg);
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

## Bonus Challenges

After completing the task, try:

- adding multiple producers
- adding multiple consumers
- dynamically resizing the buffer
- adding random delays with `sleep()`
- measuring throughput
- replacing condition variables with semaphores

---

## Learning Objective

Understand how threads coordinate access to shared resources and how condition variables enable efficient thread communication without busy waiting.