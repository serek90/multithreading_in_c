# 08-parallel-array-sum

## Goal

Learn how to split computational work between multiple threads and combine partial results into a final result.

This exercise introduces basic data parallelism by summing a large array using multiple threads.

---

## Task

Create a program that:

- generates an array of **1,000,000 random numbers**
- splits the array into **4 equal parts**
- creates one thread per part
- calculates the sum of each part in parallel
- combines all partial sums into one final result in `main`

---

## Requirements

### Program requirements

- Generate an array with:

```txt
1000000
```

random integers

- Create **4 threads**
- Each thread should process only its assigned range
- Store each partial sum separately
- Combine all partial sums in the main thread
- Print:
  - partial sums
  - final sum
  - execution time

---

## Important

Do not use global variables for thread ranges.

Pass thread data using a structure.

Example fields:

- start index
- end index
- partial sum
- pointer to array

---

## Suggested Structure

Example idea:

```c
typedef struct s_thread_data
{
    int *array;
    int start;
    int end;
    long long partial_sum;
} t_thread_data;
```

---

## Concepts Covered

- workload distribution
- parallel computation
- thread synchronization
- passing arguments to threads
- shared vs local data
- performance measurement

---

## Example Output

```txt
Thread 0 partial sum: 12498123
Thread 1 partial sum: 12544111
Thread 2 partial sum: 12477541
Thread 3 partial sum: 12500218

Final sum: 50019993

Execution time: 0.021 seconds
```

---

## Bonus Challenges

After completing the task, try:

- changing the number of threads
- comparing:
  - 1 thread
  - 2 threads
  - 4 threads
  - 8 threads
- measuring performance improvements
- testing larger arrays
- comparing static vs dynamic workload splitting

---

## Performance Hint

Measure execution time using:

```c
clock_gettime()
```

or

```c
gettimeofday()
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

## Learning Objective

Understand how CPU-intensive tasks can be parallelized using threads and how workload distribution impacts performance.