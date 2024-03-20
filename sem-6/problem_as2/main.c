/* Problem AS2 — декодер */

#include <stdio.h>
#include <stdlib.h>

unsigned read_hex() {
  unsigned tmp;
  if (scanf("%x", &tmp) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  return tmp;
}

char rname(unsigned i) {
  switch (i) {
    case 0u:
      return 'A';
    case 1u:
      return 'B';
    case 2u:
      return 'C';
    case 3u:
      return 'D';
  }
  return '!';
}

char *b_opcode(unsigned i) {
  switch (i) {
    case 0u:
      return "ADD";
    case 1u:
      return "SUB";
    case 2u:
      return "MUL";
    case 3u:
      return "DIV";
  }
  return "ERROR";
}

int print_mnemo(unsigned m) {
  if (!(m & (1u << 7))) {
    printf("MOVI %d\n", m);
    return 1;
  }

  if (!(m & (1u << 6))) {
    int code = (m & (3u << 4)) >> 4;
    int r1 = (m & (3u << 2)) >> 2;
    int r2 = m & 3u;
    printf("%s %c, %c\n", b_opcode(code), rname(r1), rname(r2));
    return 1;
  }

  if ((m & (1u << 6)) && !(m & 7u << 3)) {
    if (m & (1u << 2)) {
      printf("OUT %c\n", rname(m & 3u));
      return 1;
    } else {
      printf("IN %c\n", rname(m & 3u));
      return 1;
    }
  }

  return -1;
}

int main() {
  unsigned m;
  while (scanf("%x", &m) == 1)
    if (print_mnemo(m) != 1) {
      printf("ERROR\n");
      break;
    }
}