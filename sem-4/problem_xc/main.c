//
// Problem XC — подсчёт коллизий в хеш-функции
//

#include <stdio.h>
#include <stdlib.h>

typedef int (*get_hash_t)(const char *s);
const int HASH_MAX = 1000;

// Start solution

int ncollisions(char **strs, int n, get_hash_t f) {
  int *hash_count = calloc(HASH_MAX, sizeof(int));

  int collision = 0;
  for (int i = 0; i < n; ++i) {
    int hash = f(strs[i]);

    if (hash_count[hash] > 0)
      collision += 1;

    hash_count[hash] += 1;
  }

  free(hash_count);

  return collision;
}

// End solution

int hsum(const char *s) {
  int sum = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    sum += s[i];
  }
  return sum;
}

int main() {
  char *strs[6] = {"ad", "bc", "ad", "ad", "ee", "ee"};

  printf("%d\n", ncollisions(strs, 6, hsum));
}