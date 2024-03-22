int foo(int *x, int y, int z) {

    int r8d = 0;
    int eax;
    if (z == 0) return 0;
    eax = z - 1;
    if (eax < 0) return z;
    goto L4;
L5:
    x[eax + 1] = z;
    eax -= 1;
    if (eax == 0) goto L1;
L4:
    z = x[eax];
    r8d = eax;
    if (z > y) goto L5;
    r8d += 1;
L1: 
    return r8d;
L7:
    r8d = z;
    goto L1;
}

