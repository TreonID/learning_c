/* Problem AS2 — декодер */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *s_realloc(char *c, int new_size) {
  char *t_tmp;
  t_tmp = realloc(c, new_size);
  if (t_tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }
  return t_tmp;
}

int read_string(char **str) {
  int size = 10;
  char c;
  int count = 0;
  char *tmp = calloc(size, sizeof(char));
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }

  while (scanf("%c", &c) == 1) {
    if (c == '\n')
      break;

    if (count + 1 > size) {
      size *= 2;
      tmp = s_realloc(tmp, size);
    }
    tmp[count++] = c;
  }
  tmp[count] = '\0';

  size = count + 1;
  tmp = s_realloc(tmp, size);
  *str = tmp;
  return count;
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

  fprintf(stderr, "Unrecognized instr %x\n", (unsigned)cmd);
  abort();
}

int str_to_rop(char *str) {
  for (char *c = str; *c != '\0'; c++)
    switch (*c) {
      case 'A':
        return 0;
      case 'B':
        return 1;
      case 'C':
        return 2;
      case 'D':
        return 3;
    }
  return -1;
}

const char *reg_patterns[] = {
    "^[[:blank:]]*MOVI[[:blank:]]+[[:digit:]]+[[:blank:]]*$",  // MOVI_OPCODE
    "[[:digit:]]+",                                            // MOVi_IMM
    "^[[:blank:]]*OUT[[:blank:]]+[ABCD][[:blank:]]*$",         // OUT_OPCODE
    "[[:blank:]]+[ABCD][[:blank:]]*$",                         // IN_OUT_ROP
    "^[[:blank:]]*IN[[:blank:]]+[ABCD][[:blank:]]*$",          // IN_OPCODE
};

enum reg_patterns_t {
  MOVI_OPCODE = 0,
  MOVI_IMM,
  OUT_OPCODE,
  IN_OUT_ROP,
  IN_OPCODE,
  LAST_PATTERN
};


struct instr_t get_movi(char *cmd) {
  int res;
  struct instr_t instr;
  regex_t regex;
  regmatch_t matches[1];

  regcomp(&regex, reg_patterns[MOVI_OPCODE], REG_EXTENDED);
  res = regexec(&regex, cmd, 0, NULL, 0);
  regfree(&regex);
  if (!res) {
    instr.opcode = MOVI;
    regcomp(&regex, reg_patterns[MOVI_IMM], REG_EXTENDED);
    res = regexec(&regex, cmd, 1, matches, 0);
    if (!res) {
      char word[10];
      int w_len = matches[0].rm_eo - matches[0].rm_so;
      int value;
      memcpy(word, cmd + matches[0].rm_so, w_len);
      word[w_len] = '\0';
      value = atoi(word);
      if (value < 128)
        instr.opnd.imm = value;
      else {
        fprintf(stderr, "MOVI value out of range (0 <= ... < 128): %d \tcmd: >%s<\n", value, cmd);
        abort();
      }
    } else {
      fprintf(stderr, "Unrecognized MOVI value >%s<\n", cmd);
      abort();
    }
    regfree(&regex);
    return instr;
  }



  instr.opcode = OPLAST;
  return instr;
}


struct instr_t get_inout(char *cmd, enum opcode_t opcode) {
  int res;
  struct instr_t instr;
  regex_t regex;
  regmatch_t matches[1];

  enum reg_patterns_t p1, p2;
  switch (opcode) {
    case IN:
      p1 = IN_OPCODE;
      p2 = IN_OUT_ROP;
      break;
    case OUT:
      p1 = OUT_OPCODE;
      p2 = IN_OUT_ROP;
      break;
    default:
      fprintf(stderr, "Wrong get_inout call\n");
      abort();
  }

  regcomp(&regex, reg_patterns[p1], REG_EXTENDED);
  res = regexec(&regex, cmd, 0, NULL, 0);
  regfree(&regex);
  if (!res) {
    instr.opcode = opcode;

    regcomp(&regex, reg_patterns[p2], REG_EXTENDED);
    res = regexec(&regex, cmd, 1, matches, 0);
    if (!res) {
      char word[10];
      int w_len = matches[0].rm_eo - matches[0].rm_so;
      int value;
      memcpy(word, cmd + matches[0].rm_so, w_len);
      word[w_len] = '\0';
      value = str_to_rop(word);
      if (value != -1) {
        instr.opnd.rop = value;
      } else {
        fprintf(stderr, "Value out of range. cmd: >%s<\n", cmd);
        abort();
      }
    }
    return instr;
  }
  instr.opcode = OPLAST;
  return instr;
}


struct instr_t encode_command(char *cmd) {
  struct instr_t instr;

  // MOVI
  instr = get_movi(cmd);
  if (instr.opcode != OPLAST)
    return instr;

  // OUT
  instr = get_inout(cmd, OUT);
  if (instr.opcode != OPLAST)
    return instr;

  // IN
  instr = get_inout(cmd, IN);
  if (instr.opcode != OPLAST)
    return instr;

  fprintf(stderr, "Unrecognized instr >%s<\n", cmd);
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

int main() {
  char *cmd;
  struct instr_t instr;
  while (read_string(&cmd) > 0) {
    instr = encode_command(cmd);
    print_instr(instr);
    free(cmd);
  }
  free(cmd);
}