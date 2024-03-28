// caller - pow_mod   edi^esi mod edx    n^k mod m
// callee - mult_mod n*k mod m

unsigned callee(unsigned n, unsigned k, unsigned m) {

}

unsigned caller(unsigned n, unsigned k, unsigned m) {

  unsigned mult = n % m;
  unsigned prod = 1;
  while (k > 0) {
    if ((k % 2) == 1) {
      prod = callee(prod, mult, m);
      k = k - 1;
    }
    mult = callee(mult, mult, m);
    k = k / 2;
  }
  return prod;

}