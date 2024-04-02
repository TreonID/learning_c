.globl  foo
  .type foo, @function
  .intel_syntax noprefix
foo:
  mov       edi, edi
  pxor      xmm1, xmm1
  sub       rsp, 24
  cvtsi2sd  xmm1, rdi
  movapd    xmm0, xmm1
  movsd     QWORD PTR [rsp], xmm1
  call      log
  movsd     QWORD PTR [rsp+8], xmm0
  movsd     xmm0, QWORD PTR [rsp]
  call      log
  call      log
  addsd     xmm0, QWORD PTR [rsp+8]
  mulsd     xmm0, QWORD PTR [rsp]
  call      round
  add       rsp, 24
  cvttsd2si rax, xmm0
  ret
