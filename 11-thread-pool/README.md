# 11-thread-pool

## Goal

Implement a simple thread pool using worker threads, a shared task queue, mutexes, and condition variables.

This exercise introduces one of the most common concurrency patterns used in real-world systems.

---

## Task

Create a thread pool with:

- **4 worker threads**
- a shared task queue
- a shutdown mechanism

The worker threads should continuously:

1. wait for tasks
2. take tasks from the queue
3. execute them

---

## Requirements

### Thread Pool

- Create **4 worker threads**
- Workers must run in an infinite loop
- Workers wait when the queue is empty
- Workers wake up when new tasks arrive

### Tasks

- Add:

```txt
20 tasks
```

to the queue

- Each task should simulate work
- Example:
  - print task id
  - sleep for a short time

### Shutdown

The thread pool must support graceful shutdown.

Add a shutdown flag:

```c
int shutdown;
```

When shutdown is enabled:

- workers stop processing
- all threads exit cleanly
- main thread joins all workers

---

## Synchronization

Use:

- `pthread_mutex_t`
- `pthread_cond_t`

to protect the task queue and synchronize workers.

---

## Suggested Structures

Example task:

```c
typedef struct s_task
{
    int task_id;
} t_task;
```

Example thread pool:

```c
typedef struct s_thread_pool
{
    pthread_t workers[4];

    t_task queue[20];

    int task_count;
    int shutdown;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} t_thread_pool;
```

---

## Concepts Covered

- thread pools
- worker threads
- task queues
- producer-consumer pattern
- condition variables
- graceful shutdown
- concurrent task execution

---

## Example Output

```txt
Worker 0: processing task 1
Worker 2: processing task 2
Worker 1: processing task 3
Worker 3: processing task 4

Worker 0: finished task 1
Worker 0: processing task 5

Worker 2: finished task 2
Worker 2: processing task 6

Shutting down thread pool...
All worker threads exited.
```

---

## Suggested Functions

Example structure:

```c
void *worker_thread(void *arg);

void thread_pool_init(t_thread_pool *pool);

void thread_pool_add_task(t_thread_pool *pool, t_task task);

void thread_pool_destroy(t_thread_pool *pool);
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

- dynamic task allocation
- multiple producer threads
- task priorities
- dynamically growing queues
- work stealing
- benchmarking throughput
- adding futures/promises

---

## Learning Objective

Understand how thread pools reduce thread creation overhead and how worker threads efficiently process asynchronous tasks from a shared queue.