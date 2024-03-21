/* Problem MK — эмулятор */

#include <stdio.h>
#include <stdlib.h>

enum reg_t {
  A = 0,
  B,
  C,
  D,
  RLAST
};

enum opcode_t {
  MOVI = 0,
  ADD = 8,
  SUB = 9,
  MUL = 10,
  DIV = 11,
  IN,
  OUT,
  OPLAST
};

union operand_t {
  struct {
    int rd, rs;
  } ops;
  int rop;
  int imm;
};

struct instr_t {
  enum opcode_t opcode;
  union operand_t opnd;
};

unsigned char reg_count = 4;
unsigned char reg_state[4] = {0};
const char *regnames[] = {"A", "B", "C", "D"};
const char *arithnames[] = {"ADD", "SUB", "MUL", "DIV"};

unsigned read_hex() {
  unsigned tmp;
  if (scanf("%x", &tmp) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  return tmp;
}

struct instr_t decode_command(unsigned char cmd) {
  struct instr_t instr;
  int rf1, rf2;

  if ((cmd >> 7) == 0) {
    instr.opcode = MOVI;
    instr.opnd.imm = cmd;
    return instr;
  }

  if (((cmd >> 6) & 1) == 1) {
    instr.opnd.rop = cmd & 0x3;
    if ((cmd >> 2) == 0x30)
      instr.opcode = IN;
    else if ((cmd >> 2) == 0x31)
      instr.opcode = OUT;
    else {
      fprintf(stderr, "Unrecognized in/out %x\n", (unsigned)cmd);
      abort();
    }
    instr.opnd.rop = cmd & 0x3;
    return instr;
  }

  rf1 = cmd & 0x3;
  rf2 = (cmd >> 2) & 0x3;
  instr.opnd.ops.rs = rf1;
  instr.opnd.ops.rd = rf2;
  switch (cmd >> 4) {
    case 8:
      instr.opcode = ADD;
      return instr;
    case 9:
      instr.opcode = SUB;
      return instr;
    case 10:
      instr.opcode = MUL;
      return instr;
    case 11:
      instr.opcode = DIV;
      return instr;
  }

  fprintf(stderr, "Unrecognized inst %x\n", (unsigned)cmd);
  abort();
}

void print_instr(struct instr_t instr) {
  switch (instr.opcode) {
    case MOVI:
      printf("MOVI %d\n", instr.opnd.imm);
      break;
    case IN:
      printf("IN %s\n", regnames[instr.opnd.rop]);
      break;
    case OUT:
      printf("OUT %s\n", regnames[instr.opnd.rop]);
      break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
      printf("%s %s, %s\n", arithnames[instr.opcode - 8], regnames[instr.opnd.ops.rd], regnames[instr.opnd.ops.rs]);
      break;
    default:
      fprintf(stderr, "Unsupported opcode\n");
      abort();
  }
}

void execute_command(struct instr_t instr) {
  switch (instr.opcode) {
    case MOVI:
      reg_state[D] = instr.opnd.imm;
      break;
    case OUT:
      printf("%u\n", reg_state[instr.opnd.rop]);
      break;
    case IN:
      if (scanf("%hhu", &reg_state[instr.opnd.rop]) != 1) {
        fprintf(stderr, "Execute error: Input error\n");
        abort();
      }      
      break;
    case ADD:
      reg_state[instr.opnd.ops.rd] += reg_state[instr.opnd.ops.rs];
      break;
    case SUB:
      reg_state[instr.opnd.ops.rd] -= reg_state[instr.opnd.ops.rs];
      break;
    case MUL:
      reg_state[instr.opnd.ops.rd] *= reg_state[instr.opnd.ops.rs];
      break;
    case DIV:
      reg_state[instr.opnd.ops.rd] /= reg_state[instr.opnd.ops.rs];
      break;
    default:
      fprintf(stderr, "Execute error: Unsupported opcode\n");
      abort();
  }

}

void print_state() {
  printf("STATE: A: %u B: %u C: %u D: %u\n", reg_state[A], reg_state[B], reg_state[C], reg_state[D]);
}


int main(int argc, char **argv) {
  FILE *prog;
  unsigned command;

  if (argc < 2) {
    fprintf(stderr, "Input error, usage ./a.out \"programm text\"\n");
    return 1;
  }

  prog = fopen(argv[1], "r");

  while (fscanf(prog, "%x", &command) == 1) {
    struct instr_t instr;
    unsigned char cmd = command & 0xFF;
    instr = decode_command(cmd);
    execute_command(instr);
#if 0
    print_instr(instr);
    print_state();
    printf("=======\n");
#endif    
  }
}