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

**memset**

`malloc() calloc()` initializes the memory allocated in or to a specific value. Usually, it is often used to initialize before doing any work.

header: `#include <string.h>`\
form : `void *memset(void *s, int c, size_t n)`\
`void *s` : memory start address to initialize\
`int c` : Initialization value\
`size_t size` : Initialize size\
return: `void *s` a pointer to if success, NULL if failure.

**printf**

It is a standard output function of the C language, and it allows you to output various types of data in various formats.

header: `#include <stdio.h>`\
form : `int printf(const char *format, ...)`\
argument: %[flag][width][.precision][length]specifier\
returns: the total number of characters printed if success, a negative number if failure

**malloc**

Memory is dynamically allocated.

header: `#include <stdlib.h>`
form : `void *malloc(size_t size)`
Argument: size of memory bytes required
Returns: On success, `void *` a pointer to allocated memory, on failure, NULL is returned.

**free**

`malloc() calloc()`memory allocated by or is returned to the system.

header: `#include <stdlib.h>`
form : `void free(void *ptr)`
Argument: a pointer to free memory
