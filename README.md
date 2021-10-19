# 42-philosophers
Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems

For example, N philosophers are sitting at a round table and eating. A fork is placed between the philosophers, and the philosophers eat through the following process.

The philosopher repeats three actions: \
`eating ➔ sleeping ➔ thinking`.
When eating, both forks should be used.
If you lift both forks, eat for a certain amount of time.
When you're done eating, put down your fork.
Not a single philosopher should die due to lack of food for a certain period of time.
If all the philosophers were hungry and picked up the left forks at the same time, the right forks would have already been picked up by the philosopher sitting to their right, and everyone would be forever unable to hold the right forks. That is, there is no further progress, and the philosophers remain on standby forever. This phenomenon is called deadlock. Once in a `deadlock`, philosophers continue to suffer and die of starvation.
The task is to implement a program that solves this problem using `mutex` or `semaphore`

| External functs.    | Description | Form | Header |
| --- | ----------------------- | ---------- | ---------- |
| **memset**| `malloc() calloc()` initializes the memory allocated in or to a specific value. Usually, it is often used to initialize before doing any work. | `void *memset(void *s, int c, size_t n)`   | `#include <string.h>`  |
| **printf**  | It is a standard output function of the C language, and it allows you to output various types of data in various formats.  | `int printf(const char *format, ...)`    | `#include <stdio.h>`   |
| **malloc**   | Memory is dynamically allocated.   | `void *malloc(size_t size)`     | `#include <stdlib.h>`    |
| **free**    | `malloc() calloc()`memory allocated by or is returned to the system.    | `void free(void *ptr)`      | `#include <stdlib.h>`     |
| **write**  | open() Writes to a file opened with a function.  | `ssize_t write(int fd, const void *buf, size_t n)`    | `#include <unistd.h>`   |
| **usleep**   | Wait for a specified number of microseconds   | `int usleep(useconds_t microseconds)`     | `#include <unistd.h>`    |
| **gettimeofday**    | Jan. 1, a function to get the seconds and microseconds that have elapsed since 1970    | `int gettimeofday(struct timeval *restrict tp, void *restrict tzp)`      | `#include <sys/time.h>`     |
| **pthread_create**    | Create a thread    | `pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)`      | `#include <pthread.h>`     |
| **pthread_detach**    | Isolate a specific thread    | `int pthread_detach(pthread_t thread)`      | `#include <pthread.h>`     |
| **pthread_join**    | Waiting for a specific thread to exit. The joined thread (thread terminated) releases all resources.    | `int pthread_join(pthread_t thread, void **value_ptr)`      | `#include <pthread.h>`     |
| **pthread_mutex_init**    | Create a mutex    | `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)`      | `#include <pthread.h>`     |
| **pthread_mutex_destroy**    | Releases (returns) the allocated mutex.    | `int pthread_mutex_destroy(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **pthread_mutex_lock**    | (start critical section). Lock the mutex. If already locked, the calling thread blocks until a mutex is available.    | `int pthread_mutex_lock(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **pthread_mutex_unlock**    | (end critical section) If the mutex is locked, unlock it. Undefined behavior occurs when a mutex is not held by the calling thread.    | `int pthread_mutex_unlock(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **fork**    | Creates a copy process for the currently running process.    | `pid_t fork(void)`      | `#include <unistd.h>`     |
| **kill**    | Unlike the kill command, which kills a process in the shell, it sends a signal to the process. Sending SIGKILL to a process acts like a shell command kill.    | `int kill(pid_t pid, int sig)`      | `#include <signal.h>`     |
| **exit**    | Terminate the process.    | `void exit(int status)`      | `#include <stdlib.h>`     |
| **waitpid**    | `wait()` like a function, it waits until the child process exits. The difference is that the `wait()` function is released from the wait when any of the child processes exit, but waits `waitpid()` until the specific child process exits.    | `pid_t waitpid(pid_t pid, int *status, int options)`      | `#include <sys/wait.h>`     |
| **sem_open**    | Function to initialize and open a semaphore    | `sem_t *sem_open(const char *name, int oflag, ...)`      | `#include <semaphore.h>`     |
| **sem_close**    | Terminate the semaphore. Deallocates all resources allocated by the system so that the process uses the semaphore.    | `int sem_close(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_post**    | The semaphore is unlocked, the semaphore value is incremented, and all threads waiting on the semaphore are woken up.    | `int sem_post(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_wait**    | Lock the semaphore. If the current semaphore value is 0, the calling thread does `sem_wait()` not return until the call is aborted by a signal or locking the semaphore . If executed successfully, the `sem_post()` lock state is maintained until the lock is released with .    | `int sem_wait(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_unlink**    | Removes a named semaphore. If the current semaphore named by name is being referenced by any process, this function has no effect on that semaphore. If more than one process calls this function and the semaphore is open, `sem_close()` the removal of the semaphore is deferred until all referenced semaphores have been terminated, for example.    | `int sem_unlink(const char *name)`      | `#include <semaphore.h>`     |


## Difference between mutex and semaphore

Mutex and Semaphore are both techniques designed to achieve mutual exclusion of shared resources. In other words, it is the biggest task of concurrent programming, `a method for controlling (management) access to shared resources by multiple processes or threads,` and uses different methods as follows.

`Mutex` - mutual exclusion technique based on an `object` owned by a process (thread).
`Semaphore` - mutual exclusion technique in which a `counting variable value` indicating the number of processes (threads) that can access the current shared resource is placed

## Mutex is like a restaurant with only one toilet

To go to the bathroom, you need to get a key at the counter. If there is a key at the counter, it means that no one is in the bathroom and you can use that key to enter the bathroom.
Other customers cannot enter the bathroom and have to wait until the customer who is using the bathroom has finished and returned the key to the counter.

![Untitled-111](https://user-images.githubusercontent.com/84707645/137924693-f92898f0-5d13-4377-93c5-481a9f731eed.jpg)
![Untitled-122](https://user-images.githubusercontent.com/84707645/137924710-f11fbc8f-c92a-410e-bc53-db926ddeec7a.jpg)


* toilet == shared resource
* customers using the toilet == process (thread)
* waiting line == queue
* toilet key == any object (mutex) needed to access shared resources

A mutex is a variable with initial values ​​of 1 and 0. A value of 1 means that the counter has a toilet key.

When entering the critical section, a lock is applied to prevent other processes (threads) from accessing it, and the lock is unlocked when exiting the critical section.

## A semaphore is similar to a restaurant with multiple toilets, and at the entrance to the toilet there is an electronic sign indicating the number of empty toilets

When all toilets are in use, the number on the electronic sign 0, and guests have to wait until the number on the signboard changes to 1.
Customers who have finished their duties give +1 to the number on the electronic sign board when they leave the bathroom, and customers who have been waiting can use the bathroom after giving -1 to this number.

In other words, semaphores achieve mutual exclusion using a single value that they manage in common.

![3333](https://user-images.githubusercontent.com/84707645/137931999-9dcc483d-85f5-4de9-a2c9-327b13719521.jpg)
![Untitled-1444](https://user-images.githubusercontent.com/84707645/137932019-a937f327-9e33-40b2-a0dc-6c2cc8256574.jpg)
![55](https://user-images.githubusercontent.com/84707645/137932035-70f16c7f-9bc7-4343-aafd-102347435080.jpg)
![66](https://user-images.githubusercontent.com/84707645/137932058-66cfd74e-e21d-4fc5-b74c-ceae3cc95b62.jpg)
![777](https://user-images.githubusercontent.com/84707645/137932082-ddb7eed5-5671-407b-8ebb-2b8460502714.jpg)


* toilet == shared resource
* customers using the toilet == process (thread)
* waiting line == queue
* number of signboard == Some variable (semaphore) indicating the number of processes that can access shared resources

A semaphore is a variable with an integer value. The number means the number of processes that can access the shared resource. Create the following structure to use the semaphore.

* `semWait()` operation : Decreases the semaphore value. If the value becomes negative, the process that called semWait is blocked (locked). That is, if it is not negative, the process can continue.
* `semPost()` operation : Increases the semaphore value. If the value is negative, the processes blocked by the semWait operation are released.

The philosopher and the fork have the same number of forks, and the philosopher can eat only with two forks.

A philosopher should sleep after eating.
A philosopher begins to think after sleeping.
A philosopher dies if he does not eat for a certain period of time.
The program ends when one philosopher dies.
You have to do it to avoid deadlock.

## Deadlock

If the cars go straight at almost the same time, as shown at the right, each car has a resource and needs another resource (a, b, c, d), and thus a deadlock occurs.

<img width="698" alt="Screen Shot 2021-10-18 at 7 26 37 PM" src="https://user-images.githubusercontent.com/84707645/137771454-c59651a3-a0c4-4616-80f2-71a2021d0c39.png">

1. Mutual exclusion condition.
Only one process can use the resource at a time. That is, resources occupied by one process cannot be accessed by other processes.

2. Hold and wait condition A
process that already has a resource is waiting for another resource requesting it.

3. No preemption condition
Another process cannot forcibly seize the resources occupied by the process.

4. Circular wait condition A
closed chain exists between processes. That is, an annulus is created in the resource allocation graph. In a closed connection, a blocked process occupies a resource, and another process in the chain wants this resource and is waiting.
