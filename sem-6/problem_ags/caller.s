 .text
  .globl  caller
  .type caller, @function
caller:
  push  r13
  push  r12
  push  rbp
  push  rbx
  sub rsp, 8
  mov r12d, 1
  test  esi, esi
  je  .L1
  mov eax, edi
  mov ebx, esi
  mov r13d, edx
  mov edx, 0
  div r13d
  mov rbp, rdx
  mov r12d, 1
  jmp .L5
.L3:
  mov edi, ebp
  mov edx, r13d
  mov esi, ebp
  call  callee
  mov ebp, eax
  shr ebx
.L4:
  test  ebx, ebx
  je  .L1
.L5:
  test  bl, 1
  je  .L3
  mov edx, r13d
  mov esi, ebp
  mov edi, r12d
  call  callee
  mov r12d, eax
  sub ebx, 1
  jmp .L4
.L1:
  mov eax, r12d
  add rsp, 8
  pop rbx
  pop rbp
  pop r12
  pop r13
  ret