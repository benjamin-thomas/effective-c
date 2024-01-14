#include <stdio.h>
#include <stdlib.h>

// clang-format off
#define WAT =    1;
#define NOK =   10;
// clang-format on

/*
  cc ./hello.c && ./a.out
  gcc ./hello.c && ./a.out
  clang ./hello.c && ./a.out
*/
int main(void) {
  if (puts("Hello, world!") == EOF /* checks for (unlikely) write error */) {
    return EXIT_FAILURE;
  }

  if (printf("%s\n", "Hello, world!!") == EOF) {
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}
