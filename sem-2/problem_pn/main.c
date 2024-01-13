#include <stdio.h>
#include <stdlib.h>

int is_prime(int x) {
  if (x < 2) return 1;
  for (int i = 2; i * i <= x; ++i) 
    if ((x % i) == 0)
      return 0;

  return 1; 
}

int get_prime(int n) {
  int j = 0;
  if (n < 1) return 0;
  for (int i = 2; ; ++i) 
    if (is_prime(i)) {
      ++j;
      if (j == n) return i;
    }
}  

int main() {
  int res, n;
  res = scanf("%d", &n);
  if (res != 1) {
    fprintf(stderr, "Input error\n");
  }
  
  
  printf("%d\n", get_prime(n));

}
