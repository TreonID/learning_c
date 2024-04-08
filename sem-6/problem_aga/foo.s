foo:                                            // foo(int x0)
        mov     x6, x0                          // x6 = x0
        ldr     w0, [x0]                        // w0 = *x0
        cmp     w1, 1                           // if w1 <= 1
        ble     .L1                             // goto .L1
        mov     x3, 1                           // x3 = 1
        mov     w2, w3                          // w2 = 1
        mov     w7, w3                          // w7 = 1                                          
.L6:
        ldr     w4, [x6, x3, lsl 2]             //w4 = *(x6 + x3 << 2)
        sub     w5, w2, #1                      //w5 = s2 - 1
        add     x3, x3, 1                       //x3 += 1
        cmp     w4, w0                          
        csinc   w2, w5, w2, ne                  // w2 = (w4 != w0) ? w5 : w2 + 1;
        cmp     w2, 0                           // 
        csel    w0, w4, w0, eq                  // w0 = (w2 == 0) ? w4 : w0;
        csel    w2, w2, w7, ne                  // w2 = (w2 != 0) ? w2 : w7;
        cmp     w1, w3                          
        bgt     .L6                             // if (w1 > w3) got .L6;
.L1:
        ret                                     // return x0;