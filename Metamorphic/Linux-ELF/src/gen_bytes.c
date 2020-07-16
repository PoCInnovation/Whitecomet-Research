/*
** EPITECH PROJECT, 2020
** Linux-ELF
** File description:
** gen_bytes
*/

#include "meta.h"

// const char *reg_tab[] = {"EAX", "EBX", "ECX", "EDX", "esi", "edi", "ebp", "esp", NULL};
const char *reg_tab[] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP", NULL};
const int instr_size[6] = {8, 2, 2, 2, 2, 3};

int (*op_tab[6])(const char *, int, char **) = {
    &op_cmp_jmp,
    &op_inc_dec,
    &op_nop,
    &op_neg,
    &op_not,
    &op_shl
};

int op_cmp_jmp(const char *reg, int bit_nbr, char **code)
{
    char new[13];
    sprintf(new, "CMP %s,%s;", reg, reg);
    size_t size_instr = size_calc(new);
    if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 13);
    strcat(*code, new);
    return size_instr;
}

int op_inc_dec(const char *reg, int bit_nbr, char **code)
{
    char new[17];
    sprintf(new, "INC %s;DEC %s;", reg, reg);
    size_t size_instr = size_calc(new);
    if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 17);
    strcat(*code, new);
    return size_instr;
}

int op_nop(const char *reg, int bit_nbr, char **code)
{
    char new[5];
    sprintf(new, "NOP;");
    size_t size_instr = size_calc(new);
   if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 5);
    strcat(*code, new);
    return size_instr;
}

int op_not(const char *reg, int bit_nbr, char **code)
{
    char new[17];
    sprintf(new, "NOT %s;NOT %s;", reg, reg);
    size_t size_instr = size_calc(new);
    if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 17);
    strcat(*code, new);
    return size_instr;
}

int op_neg(const char *reg, int bit_nbr, char **code)
{
    char new[17];
    sprintf(new, "NEG %s;NEG %s;", reg, reg);
    size_t size_instr = size_calc(new);
    if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 17);
    strcat(*code, new);
    return size_instr;
}

int op_shl(const char *reg, int bit_nbr, char **code)
{
    char new[11];
    sprintf(new, "SHL %s,0;", reg);
    size_t size_instr = size_calc(new);
    if (bit_nbr - (int)size_instr < 0)
        return 0;
    *code = realloc(*code, strlen(*code) + 11);
    strcat(*code, new);
    return size_instr;
}

unsigned char *gen_bit(int bit_nbr)
{
    int rdm = 0;
    int rdm_reg = 0;
    size_t size;
    char *code = strdup("");
    unsigned char *gen_code = NULL;

    while (bit_nbr > 0) {
        rdm = rand() % 6;
        rdm_reg = rand()% 8;
        if ((size = op_tab[rdm](reg_tab[rdm_reg], bit_nbr, &code)))
            bit_nbr -= size;
    }
    gen_code = encoder(code);
    return gen_code;
}

unsigned char *encoder(char *code)
  {
      ks_engine *ks;
      ks_err err;
      size_t count;
      unsigned char *encode;
      unsigned char *encode_cpy;
      size_t size;

      err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
      if (err != KS_ERR_OK) {
          printf("ERROR: failed on ks_open(), quit\n");
          return (NULL);
      }
      if (ks_asm(ks, code, 0, &encode, &size, &count) != KS_ERR_OK) {
          printf("ERROR: ks_asm() failed & count = %lu, error = %u\n",
		         count, ks_errno(ks));
      } else {
          for (size_t i = 0; i < size; i++)
              printf("%02x ", encode[i]);
          printf("\n(Instructions : %s)", code);
          printf("\nCompiled: %lu bytes, statements: %lu\n", size, count);
      }
      encode_cpy = malloc(sizeof(char) * (size + 1));
      for (int i = 0; i < size ; i++) {
          encode_cpy[i] = encode[i];
      }
      encode_cpy[size] = 0;
      ks_free(encode);
      ks_close(ks);
      return (encode_cpy);
  }

int size_calc(char *code)
  {
      ks_engine *ks;
      ks_err err;
      size_t count;
      unsigned char *encode;
      size_t size;

      err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
      if (err != KS_ERR_OK) {
          printf("ERROR: failed on ks_open(), quit\n");
          return -1;
      }
      if (ks_asm(ks, code, 0, &encode, &size, &count) != KS_ERR_OK)
          printf("ERROR: ks_asm() failed & count = %lu, error = %u\n",
		         count, ks_errno(ks));
      ks_free(encode);
      ks_close(ks);
      return (size);
  }
