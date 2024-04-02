#include <math.h>

long foo(unsigned num) {
  double dnum = num;
  double dres = dnum * (log(dnum) + log(log(dnum)));
  return (long)round(dres);
}

int main() {
  printf("Foo: %lld\n", foo(100));
}