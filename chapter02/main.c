#include <stdbool.h>
#include <stdio.h>
#include <unistd.h> // sleep, POSIX only

// Function definition and usage before its implementation (further below).
void swap(int *, int *);

/*
In C, "objects" refer to storage areas in the execution environment representing
values. It has a "lifetime" (stack or heap I presume).

So variables are "objects".
Functions are not "objects".
*/

/*
Since this variable is declared in "file scope", it has a "static storage
duration". Meaning it is initialized before program start, and available
throughout the whole program execution.
*/
unsigned int HELLO_STATIC = 1;

// Requires `stdbool.h`
static bool IS_TRUE = true;
static bool IS_FALSE = false;

// Does not require `stdbool.h`
// NOTE: identifiers starting with `_[A-Z]` or `__` are reserved
// NOTE: identifiers starting with `_[a-z]` are ok to use (not reserved).
static _Bool IS_ALSO_TRUE = 1;
static _Bool IS_ALSO_FALSE = 0;

void inc(void) {
  /*
  Within a block scope, we can also declare an object with a "static storage
  duration" (like `HELLO_STATIC`).

  These objects persist after the function has exited;

  > You could achieve the same behavior by declaring `counter` with file scope.
  > However, it is good software engineering practice to limit the scope of an
  > object wherever possible.
  */
  static unsigned int counter = 0; // the counter value now "sticks around".
  counter++;
  printf("%d ", counter);
}

unsigned int get_memo(bool reset) {
  static unsigned int val = 0;
  if (reset) {
    val = 0;
  }
  if (val == 0) {
    puts("--> Computing memo value");
    sleep(1);
    val++;
  }

  return val;
}

enum days { sun, mon, tue, wed, thu, fri, sat };
enum months { jan = 1, feb, mar, apr, may, jun, jul, aug, sept, oct, nov, dec };

int main(void) {
  printf("Sunday's value is  : %d\n", sun);
  printf("Saturday's value is: %d\n", sat);
  puts("---");
  printf("January's value is   : %d\n", jan);
  printf("December's value is  : %d\n", dec);
  puts("---\n");

  puts("--> Static storage duration demo");
  for (int i = 0; i < 5; i++) {
    inc();
  }
  printf("\n\n");

  printf("main: HELLO_STATIC=%d\n", HELLO_STATIC);
  HELLO_STATIC++;
  printf("main: HELLO_STATIC=%d\n", HELLO_STATIC);
  printf("\n");

  // Using a static storage looks like an awesome way to do memoization
  printf("main: memo demo:%d\n", get_memo(false));
  printf("main: memo demo:%d\n", get_memo(false));
  printf("main: memo demo:%d\n", get_memo(false));
  printf("\n== RESETING VALUE -- WILL RECOMPUTE ==\n\n");
  printf("main: memo demo:%d\n", get_memo(true));
  printf("main: memo demo:%d\n", get_memo(false));
  printf("main: memo demo:%d\n", get_memo(false));
  printf("\n");

  int a = 1;
  int b = 2;
  printf("main: a=%d, b=%d\n", a, b);

  // We pass the addresses of the "objects" `a` and `b` to `swap`.
  swap(&a, &b);

  printf("main: a=%d, b=%d\n", a, b);

  return 0;
}

// We pass 2 "objects" to this fu
void swap(int *pa, int *pb) {
  int t = *pa;
  {
    // Demonstrating re-declaring/shadowing `t` within a new scope block.
    int t = 99;
  }
  *pa = *pb;
  *pb = t;
}