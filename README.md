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
| ---------- | --------- | ---------- | ---------- |
| **memset**| `malloc() calloc()` initializes the memory allocated in or to a specific value. Usually, it is often used to initialize before doing any work. | `void *memset(void *s, int c, size_t n)`   | `#include <string.h>`  |
| **printf**  | It is a standard output function of the C language, and it allows you to output various types of data in various formats.  | `int printf(const char *format, ...)`    | `#include <stdio.h>`   |
| **malloc**   | Memory is dynamically allocated.   | `void *malloc(size_t size)`     | `#include <stdlib.h>`    |
| **free**    | `malloc() calloc()`memory allocated by or is returned to the system.    | `void free(void *ptr)`      | `#include <stdlib.h>`     |
| **write**  | open() Writes to a file opened with a function.  | ssize_t `write(int fd, const void *buf, size_t n)`    | `#include <unistd.h>`   |
| **usleep**   | Wait for a specified number of microseconds   | `int usleep(useconds_t microseconds)`     | `#include <unistd.h>`    |
| **gettimeofday**    | Jan. 1, a function to get the seconds and microseconds that have elapsed since 1970    | `int gettimeofday(struct timeval *restrict tp, void *restrict tzp)`      | `#include <sys/time.h>`     |
| **pthread_create**    | Create a thread    | `pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)`      | `#include <pthread.h>`     |
| **pthread_detach**    | Isolate a specific thread    | `int pthread_detach(pthread_t thread)`      | `#include <pthread.h>`     |
| **pthread_join**    | Waiting for a specific thread to exit. The joined thread (thread terminated) releases all resources.    | `int pthread_join(pthread_t thread, void **value_ptr)`      | `#include <pthread.h>`     |
| **pthread_mutex_init**    | Create a mutex    | `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)`      | `#include <pthread.h>`     |




