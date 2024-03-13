#include <stdio.h>
#include <stdlib.h>

int automat(int *cur_state, char c) {
  int state = *cur_state;

  switch (state) {
    case 1:
      switch (c) {
        case 'a':
          break;
        case 'b':
          state = 2;
          break;
        case 'c':
          state = 5;
          break;
      }
      break;
    case 2:
      switch (c) {
        case 'a':
          state = 1;
          break;
        case 'b':
          break;
        case 'c':
          state = 3;
          break;
      }
      break;
    case 3:
      switch (c) {
        case 'a':
          state = 5;
          break;
        case 'b':
          state = 4;
          break;
        case 'c':
          break;
      }
      break;
    case 4:
      switch (c) {
        case 'a':
          state = 5;
          break;
        case 'b':
          state = 4;
          break;
        case 'c':
          state = 3;
          break;
      }
      break;
    case 5:
      switch (c) {
        case 'a':
        case 'b':
        case 'c':
          state = 5;
          break;
      }
      break;
  }
  *cur_state = state;

  switch (state) {
    case 2:
    case 3:
    case 4:
      return 1;
  }
  return 0;
}

int main() {
  int res = 0, state = 1;
  char c;
  while (scanf("%c", &c) == 1) {
    res = automat(&state, c);
  }
  printf("%d\n", res);
}