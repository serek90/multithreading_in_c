# 07-semaphore-access-control

## Goal

Learn how semaphores can be used to limit access to shared resources in a multithreaded environment.

In this exercise, a printer can only handle **2 threads at the same time**.

---

## Task

Create a simulation of a shared printer system using POSIX semaphores.

### Requirements

- Create **8 threads**
- Each thread wants to use the printer
- Simulate printing with:

```c
sleep(10);
```

- Use a semaphore to allow only **2 threads simultaneously**
- Remaining threads must wait until a printer slot becomes available

---

## Example Output

```txt
Thread 0: waiting for printer...
Thread 0: printing...

Thread 1: waiting for printer...
Thread 1: printing...

Thread 2: waiting for printer...
Thread 3: waiting for printer...
Thread 4: waiting for printer...
Thread 5: waiting for printer...
Thread 6: waiting for printer...
Thread 7: waiting for printer...

Thread 0: finished printing
Thread 2: printing...

Thread 1: finished printing
Thread 3: printing...

Thread 2: finished printing
Thread 4: printing...

Thread 3: finished printing
Thread 5: printing...
```

Only two threads should be inside the printing section simultaneously.