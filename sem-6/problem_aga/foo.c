#include <stdio.h>

int foo(const int *x0, int w1) {
    int x3;
    int *x6;
    int w0, w2, w4, w5, w7;

    x6 = x0;
    w0 = *x0;
    if (w1 <= 1 ) goto L1;
    x3 = 1;
    w2 = 1;
    w7 = 1;
L6:
    w4 = *(x6 + x3);
    x3 += 1;
    w5 = w2 - 1;
                    
    w2 = (w4 != w0) ? w5 : w2 + 1;

    w0 = (w2 == 0) ? w4 : w0;
    w2 = (w2 != 0) ? w2 : w7;

    if (w1 > x3) goto L6;
L1:
    return w0;
}

int main() {
    int x[5] = {4, 8, 3, 6, 5};
    
    
    
    printf("%d\n", foo(x, 5));

}