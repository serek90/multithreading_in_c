# multithreading_in_c

Learning multithreading and concurrency in C using POSIX threads (`pthreads`).

This repository contains small projects and exercises that gradually introduce:

- thread creation
- synchronization
- mutexes
- condition variables
- semaphores
- thread pools
- lock-free programming
- deadlocks
- performance optimization

## Structure

| Project | Topic |
|---|---|
| 01-hello-thread | Creating threads |
| 02-thread-arguments | Passing data to threads |
| 03-multiple-threads | Create multiple threads |
| 04-threads-sleeping | Multiple threads working |
| 05-race-condition | Race conditions |
| 06-mutex-basics | Mutex synchronization |
| 07-semaphore-basics | Semaphore synchronization |
| 08-parallel-array-sum | Parallel array processing |
| 08a-false-sharing | Cache line loading problem |


## Build

Example:

```bash
gcc main.c -o app -lpthread
```

Or with warnings:

```bash
gcc main.c -o app -lpthread -Wall -Wextra -Werror
```

## Run

```bash
./app
```

## Tools

Useful debugging tools:

- ThreadSanitizer
- Valgrind / Helgrind
- gdb

Example with ThreadSanitizer:

```bash
gcc main.c -fsanitize=thread -g -lpthread
```

## Goals

The purpose of this repository is to understand:

- how threads work internally
- synchronization problems
- race conditions
- deadlocks
- CPU parallelism
- cache and memory effects
- writing safer concurrent code

## License

MIT