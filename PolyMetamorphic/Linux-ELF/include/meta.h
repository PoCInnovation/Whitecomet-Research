/*
** EPITECH PROJECT, 2020
** Linux-ELF
** File description:
** Meta
*/


#ifndef META_H_
#define META_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <keystone/keystone.h>

// ASM opcode pattern :
#define ASM __asm__(\
    "pushfq\n"\
    "pushq rax;\n"\
    "pushq rbx;\n"\
    "nop;\n"\
    "xor rax, rax;\n"\
    "xor rbx, rax;\n"\
    "xor rbx, rax;\n"\
    "nop;nop;nop;\n"\
    "xor rbx, rbx;\n"\
    "xor rbx, rax;\n"\
    "xor rax, rbx;\n"\
    "nop;\n"\
    "popq rbx;\n"\
    "popq rax;\n"\
    "popfq;");

#define DECOY __asm__("pushfq\n"\
    "pushq rax;\n"\
    "pushq rbx;\n" \
    "popq rbx;\n"\
    "nop;" \
    "cmp rax, rax;" \
    "popq rax;" \
    "popfq ;\n"\
    );

// ! This program is made on a x86-64 system !
#define PATTERN_S "\x9C\x50\x53" // Pattern beggining
#define PATTERN_E "\x5B\x58\x9D" // Pattern ending
#define PATTERNS_L 3 // Length E and S patterns
#define ASM_W_BYTES 23 // how many bytes are free/writable between E and S
#define ASM_TOTAL 29 // Total bytes ( 23 + 3 * 2 )

int op_cmp_jmp(const char *reg, int bit_nbr, char **code);
int op_inc_dec(const char *reg, int bit_nbr, char **code);
int op_nop(const char *reg, int bit_nbr, char **code);
int op_neg(const char *reg, int bit_nbr, char **code);
int op_not(const char *reg, int bit_nbr, char **code);
int op_shl(const char *reg, int bit_nbr, char **code);
int size_calc(char *code);
unsigned char * encoder(char *code);

int replace_bytes(int argc, char const *argv[]);
#endif /* !META_H_ */
