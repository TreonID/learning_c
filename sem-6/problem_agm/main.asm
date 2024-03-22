// --- int f(int *x, int y, int z) ---
// edi = x
// esi = y
// edx = z
// return value = eax
  .globl  foo
  .type foo, @function
foo:
  xor r8d, r8d                          // int r8d = 0;
  test  edx, edx                        // if (z == 0) return 0;
  je  .L1                               // 
  mov eax, edx                          // int eax = z;
  sub eax, 1                            // eax -= 1;
  js  .L7                               // if (z - 1 < 0 ) return z;
  cdqe                                  // 
  jmp .L4                               // goto .L4;
.L5:                                                                                      
  mov DWORD PTR 4[rdi+rax*4], edx       //  x[z + 1] = z; 
  sub rax, 1                            //  z -= 1
  test  eax, eax                        // if (z == 0) goto .L1;
  js  .L1
.L4:
  mov edx, DWORD PTR [rdi+rax*4]        // z = x[z];
  mov r8d, eax                          // r8d = z;
  cmp edx, esi                          // if (z > y) goto .L5;
  jg  .L5                               // 
  add r8d, 1                            // r8d += 1
.L1:
  mov eax, r8d                          // return r8d
  ret
.L7:
  mov r8d, edx                          // r8d = z
  jmp .L1                               // goto .L1