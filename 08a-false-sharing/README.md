# 08a-false-sharing

## Goal

Learn how CPU cache lines can negatively impact multithreaded performance.

This exercise demonstrates a performance problem called **false sharing**.

Even when threads do not share logical data, performance can still degrade if multiple threads modify variables stored close together in memory.

---

## Task

Create two versions of the same program:

### Version 1 — False Sharing

- Create multiple threads
- Each thread increments its own counter many times
- Store all counters next to each other in memory
- Measure execution time

### Version 2 — Fixed Version

- Prevent false sharing using:
  - padding
  - or cache-line alignment
- Measure execution time again
- Compare the results

---

## Concepts Covered

- CPU cache lines
- cache invalidation
- false sharing
- memory layout
- multithreaded performance
- benchmarking

---

## Example Idea

```c
typedef struct s_data
{
    long long counter;
} t_data;
```

Fixed version:

```c
typedef struct s_data
{
    long long counter;
    char padding[56];
} t_data;
```

---

## Expected Result

The padded/aligned version should perform noticeably faster under heavy multithreaded workloads.

---

## Build

```bash
gcc main.c -o app -lpthread
```

---

## Run

```bash
time ./app
```

---

## Learning Objective

Understand that multithreaded performance depends not only on synchronization, but also on how data is stored in memory.