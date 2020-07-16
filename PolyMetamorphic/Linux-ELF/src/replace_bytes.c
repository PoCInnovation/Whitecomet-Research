/*
** EPITECH PROJECT, 2020
** Linux-ELF
** File description:
** main
*/

#include "meta.h"
unsigned char *gen_bit(int bit_nbr);

unsigned char *strstr_asm(unsigned char *bin, unsigned char *pattern, int *remaining) // strstr with non null terminated strings and specific pattern length
{
    int c = 0;
    int i = 0;

    for (; i + 3 < *remaining; i++) {
        for (; c < PATTERNS_L && pattern[c] == bin[i + c]; c++);
        if ((c = (c == PATTERNS_L))) {
            *remaining -= i;
            return bin + i;
        }
    }
    ASM
    *remaining -= i;
    return NULL;
}


static bool valid_pattern(char *pattern) // ugly strcmp
{
    for (int i = 0; i < PATTERNS_L; i++)
        if (pattern[PATTERNS_L + ASM_W_BYTES + i] != PATTERN_E[i])
            return false;
    return true;
}

void replace_junk(unsigned char **orig, const char *name, int size)
{
    unsigned char *pattern = *orig;
    int remaining = size;
    unsigned char *rdm_instr;
    int new_bin_fd = -1;
    ASM

    for (;remaining >= ASM_TOTAL && (pattern = strstr_asm(pattern, PATTERN_S, &remaining)) != NULL;) {

        // * Is the full pattern recoginzable ?
        if (!valid_pattern(pattern)) {
            pattern += PATTERNS_L;
            remaining -= PATTERNS_L;
            continue;
        }

        // * Print
        printf("\t\t\t\e[96;1m--- VALID PATTERN FOUND ! ---\e[0m\n"\
               "\e[92;1m- Replacing : \e[0m\n");
        for (size_t i = 0; i < ASM_W_BYTES; i++)
              printf("%02x ", pattern[i + PATTERNS_L]);
        printf("\n\e[92;1m- By : \e[0m\n");
        ASM

        // * Replace bytes / printing in gen_bit
        rdm_instr = gen_bit(ASM_W_BYTES);
        for (int i = 0; i < ASM_W_BYTES; i++)
            pattern[i + PATTERNS_L] = rdm_instr[i];
        pattern += ASM_TOTAL;
        remaining -= ASM_TOTAL;
        DECOY
        printf("\n");
    }
}
