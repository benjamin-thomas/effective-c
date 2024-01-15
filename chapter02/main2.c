#include <stdio.h>
#include <string.h>

// echo ./main2.c | entr -c bash -c 'gcc ./main2.c && ./a.out'

// clang-format off
void pointer_gymnastics(void) {
  puts("Pointer gymnastics");
  int i = 123;    // a value
  int *i2 = &i;   // an int pointer (points to the address of `i`)
  int i3 = *i2;   // a new value, evaluated by by dereferencing the pointer to `i` (a new address)
  int *i4 = &*i2; // a pointer to the addr of another pointer (points to addr of `i`)
  printf("i=%d, i2=%d, i3=%d, i4=%d\n", i, *i2, i3, *i4);
  printf("i=%p, i2=%p, i3=%p, i4=%p\n", &i, i2, &i3, i4);
  puts("");
}

// clang-format on
void print_digits1(void) {
  char str[11]; // 10 digits + null char
  for (unsigned int i = 0; i < 10; ++i) {

    /*
        (gdb) p '0'
        $1 = 48 '0'
        (gdb) p '0' + 1
        $2 = 49

        >>> ord('0')
        48
        >>> ord('1')
        49
        >>> chr(48)
        '0'
        >>> chr(49)
        '1'

    `str[i]` is identical to `*(str + i)`
    When `str[i]` is invoked, `str` is converted to a pointer,
    shifted by i*(object size)
    */
    str[i] = '0' + i;
  }
  str[10] = '\0';

  printf("All digits1: %s\n", str);
}

void print_digits2(void) {
  char str[11]; // 10 digits + null char
  for (unsigned int i = 0; i < 10; ++i) {
    // str is a pointer.
    // addr is shifted by the object size * i
    *(str + i) = '0' + i;
  }
  str[10] = '\0';

  printf("All digits2: %s\n\n", str);
}

void type_aliases_and_structs(void) {
  // We can create type aliases with `typedef`
  typedef unsigned int pos;
  pos n = 1;
  printf("n=%d\n", n);

  // We refer to the struct via a type alias
  struct sig_record {
    int num;
    char name[20];
    char desc[100];
  } sig, *sig_p;

  puts("\n---\n\nSUMMARY\t\t\tDESCR");
  sig.num = 15;
  strcpy(sig.name, "SIGTERM");
  strcpy(sig.desc, "Program termination");
  printf("name: %s(%d)\t%s\n", sig.name, sig.num, sig.desc);

  sig_p = &sig;
  sig_p->num = 9;
  strcpy(sig_p->name, "SIGKILL");
  strcpy(sig_p->desc, "Immediate program termination");
  printf("name:  %s(%d)\t%s\n", sig_p->name, sig_p->num, sig_p->desc);
  puts("");
}

int main(void) {
  pointer_gymnastics();
  print_digits1();
  print_digits2();
  type_aliases_and_structs();
}