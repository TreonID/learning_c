// START SOLUTION

int foo(int x, int y) {
    int x0 = x;
    x0 *= x;
    x0 *= x;
    if (x0 < 0) {
        int edx = 17;
        y *= y;
        x += x;
        edx = edx - x;
        edx = edx - y;
        x0 += edx;
        return x0;
    }
    return x0;
}

// END SOLUTION
