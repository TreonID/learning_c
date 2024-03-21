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

// A -> 0, B -> 1, ...
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
    "^[[:blank:]]*MOVI[[:blank:]]+[[:digit:]]+[[:blank:]]*$",                          // MOVI_OPCODE
    "[[:digit:]]+",                                                                    // MOVi_IMM
    "^[[:blank:]]*OUT[[:blank:]]+[ABCD][[:blank:]]*$",                                 // OUT_OPCODE
    "[[:blank:]]+[ABCD][[:blank:]]*$",                                                 // IN_OUT_ROP
    "^[[:blank:]]*IN[[:blank:]]+[ABCD][[:blank:]]*$",                                  // IN_OPCODE
    "[[:blank:]]+[ABCD][[:blank:]]*,",                                                 // ARITH_OPS_RD
    ",[[:blank:]]*[ABCD][[:blank:]]*$",                                                // ARITH_OPS_RS
    "^[[:blank:]]*ADD[[:blank:]]+[ABCD][[:blank:]]*,[[:blank:]]*[ABCD][[:blank:]]*$",  // ADD_OPCODE
    "^[[:blank:]]*SUB[[:blank:]]+[ABCD][[:blank:]]*,[[:blank:]]*[ABCD][[:blank:]]*$",  // SUB_OPCODE
    "^[[:blank:]]*MUL[[:blank:]]+[ABCD][[:blank:]]*,[[:blank:]]*[ABCD][[:blank:]]*$",  // MUL_OPCODE
    "^[[:blank:]]*DIV[[:blank:]]+[ABCD][[:blank:]]*,[[:blank:]]*[ABCD][[:blank:]]*$",  // DIV_OPCODE

};

enum reg_patterns_t {
  MOVI_OPCODE = 0,
  MOVI_IMM,
  OUT_OPCODE,
  IN_OUT_ROP,
  IN_OPCODE,
  ARITH_OPS_RD,
  ARITH_OPS_RS,
  ADD_OPCODE,
  SUB_OPCODE,
  MUL_OPCODE,
  DIV_OPCODE,
  LAST_PATTERN
};

regex_t *reg_patterns_comp;

void init_regex(regex_t rarr[LAST_PATTERN]) {
  for (int i = MOVI_OPCODE; i < LAST_PATTERN; i++)
    regcomp(&rarr[i], reg_patterns[i], REG_EXTENDED);
  reg_patterns_comp = rarr;
}

void free_regex(regex_t rarr[LAST_PATTERN]) {
  for (int i = MOVI_OPCODE; i < LAST_PATTERN; i++)
    regfree(&rarr[i]);
}

char *match_to_word(char *cmd, regoff_t rm_eo, regoff_t rm_so) {
  int w_len = rm_eo - rm_so;
  char *word = calloc(w_len + 1, sizeof(char));
  if (word == NULL) {
    fprintf(stderr, "Error word allocation in cmd: >%s<", cmd);
    abort();
  }
  memcpy(word, cmd + rm_so, w_len);
  word[w_len] = '\0';
  return word;
}

struct instr_t get_movi(char *cmd) {
  int res;
  struct instr_t instr;
  regmatch_t matches[1];

  res = regexec(&reg_patterns_comp[MOVI_OPCODE], cmd, 0, NULL, 0);
  if (!res) {
    instr.opcode = MOVI;
    res = regexec(&reg_patterns_comp[MOVI_IMM], cmd, 1, matches, 0);
    if (!res) {
      char *word = match_to_word(cmd, matches[0].rm_eo, matches[0].rm_so);
      int value = atoi(word);
      if (value < 128)
        instr.opnd.imm = value;
      else {
        fprintf(stderr, "MOVI value out of range (0 <= ... < 128): %d \tcmd: >%s<\n", value, cmd);
        abort();
      }
      free(word);
    } else {
      fprintf(stderr, "Unrecognized MOVI value >%s<\n", cmd);
      abort();
    }
    return instr;
  }
  instr.opcode = OPLAST;
  return instr;
}

struct instr_t get_inout(char *cmd, enum opcode_t opcode) {
  int res;
  struct instr_t instr;
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

  res = regexec(&reg_patterns_comp[p1], cmd, 0, NULL, 0);
  if (!res) {
    instr.opcode = opcode;

    res = regexec(&reg_patterns_comp[p2], cmd, 1, matches, 0);
    if (!res) {
      char *word = match_to_word(cmd, matches[0].rm_eo, matches[0].rm_so);
      int value = str_to_rop(word);
      if (value != -1) {
        instr.opnd.rop = value;
      } else {
        fprintf(stderr, "Value out of range. cmd: >%s<\n", cmd);
        abort();
      }
      free(word);
    }
    return instr;
  }
  instr.opcode = OPLAST;
  return instr;
}

struct instr_t get_arith(char *cmd, enum opcode_t opcode) {
  int res;
  struct instr_t instr;
  regmatch_t matches[1];

  enum reg_patterns_t p1;
  switch (opcode) {
    case ADD:
      p1 = ADD_OPCODE;
      break;
    case SUB:
      p1 = SUB_OPCODE;
      break;
    case MUL:
      p1 = MUL_OPCODE;
      break;
    case DIV:
      p1 = DIV_OPCODE;
      break;

    default:
      fprintf(stderr, "Wrong get_inout call\n");
      abort();
  }

  res = regexec(&reg_patterns_comp[p1], cmd, 0, NULL, 0);
  if (!res) {
    instr.opcode = opcode;

    res = regexec(&reg_patterns_comp[ARITH_OPS_RD], cmd, 1, matches, 0);
    if (!res) {
      char *word = match_to_word(cmd, matches[0].rm_eo, matches[0].rm_so);

      int value = str_to_rop(word);
      if (value != -1) {
        instr.opnd.ops.rd = value;
      } else {
        fprintf(stderr, "Value RD out of range. cmd: >%s<\n", cmd);
        abort();
      }
      free(word);
    }

    res = regexec(&reg_patterns_comp[ARITH_OPS_RS], cmd, 1, matches, 0);
    if (!res) {
      char *word = match_to_word(cmd, matches[0].rm_eo, matches[0].rm_so);
      int value = str_to_rop(word);
      if (value != -1) {
        instr.opnd.ops.rs = value;
      } else {
        fprintf(stderr, "Value RS out of range. cmd: >%s<\n", cmd);
        abort();
      }
      free(word);
    }

    return instr;
  }
  instr.opcode = OPLAST;
  return instr;
}

struct instr_t encode_command(char *cmd) {
  struct instr_t instr;

  instr = get_movi(cmd);
  if (instr.opcode != OPLAST)
    return instr;

  for (int i = IN; i <= OUT; i++) {
    instr = get_inout(cmd, i);
    if (instr.opcode != OPLAST)
      return instr;
  }

  for (int i = ADD; i <= DIV; i++) {
    instr = get_arith(cmd, i);
    if (instr.opcode != OPLAST)
      return instr;
  }
  printf("\n");
  fprintf(stderr, "Unrecognized instr >%s<\n", cmd);
  abort();
}

void print_instr(const struct instr_t instr) {
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

void print_instr_code(const struct instr_t instr) {
  switch (instr.opcode) {
    case MOVI:
      printf("0x%x", instr.opnd.imm);
      break;
    case IN:
      printf("0x%x", (0x30 << 2) + instr.opnd.rop);
      break;
    case OUT:
      printf("0x%x", (0x31 << 2) + instr.opnd.rop);
      break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
      printf("0x%x", (instr.opcode << 4) + (instr.opnd.ops.rd << 2) + instr.opnd.ops.rs);
      break;
    default:
      fprintf(stderr, "Unsupported opcode\n");
      abort();
  }
}

int main() {
  char *cmd;
  struct instr_t instr;
  regex_t regex[LAST_PATTERN];

  init_regex(regex);

  while (read_string(&cmd) > 0) {
    instr = encode_command(cmd);
    print_instr_code(instr);
    printf(" ");
    free(cmd);
  }
  printf("\n");
  free(cmd);
  free_regex(regex);
}