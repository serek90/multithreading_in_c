# 12-thread-return-value

## Goal

Learn how to return values from a thread using `pthread_join()`.

This exercise introduces basic thread result handling and dynamic memory sharing between threads and the main program.

---

## Task

Create a thread that:

- receives a number `n` as an argument
- calculates the factorial of `n`
- returns the result back to the main thread

The main thread should:

- wait for the worker thread using `pthread_join()`
- retrieve the returned value
- print the final result

---

## Requirements

### Worker Thread

- receive an integer argument
- calculate:

```txt
n!
```

- return the result to the main thread

### Main Thread

- create the worker thread
- wait for completion using:

```c
pthread_join()
```

- retrieve the returned value
- print the result

---

## Important

The returned value must remain valid after the thread exits.

Do not return pointers to local stack variables.

Use dynamic memory allocation if needed.

---

## Suggested Functions

Example:

```c
void *factorial(void *arg);
```

---

## Example Output

```txt
Input: 5
Factorial: 120
```

---

## Concepts Covered

- thread return values
- `pthread_join`
- dynamic memory allocation
- passing arguments to threads
- thread lifecycle management

---

## Example Idea

```c
uint64_t *result = malloc(sizeof(uint64_t));
```

Return the pointer from the thread:

```c
return result;
```

Retrieve it in `main`:

```c
void *result;
pthread_join(thread, &result);
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

- calculating multiple factorials in parallel
- using multiple worker threads
- handling very large numbers
- comparing recursive vs iterative factorial
- measuring execution time

---

## Learning Objective

Understand how threads can return data back to the main thread and how thread synchronization works with `pthread_join()`.