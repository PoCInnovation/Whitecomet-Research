/*
** PoC PROJECT, 2020
** Whitecomet-Research
** File description:
** PoCrypt
*/

#ifndef POCRYPT_H_
#define POCRYPT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>

/* Basic string obfuscation */
// #define XL(a, i) (char)(a ^ (0x1A4 * 0x2B5 * (i + 1) / 0x45)) /* XOR letter w/ index + keys */
// #define XOR_STR(str) {char *ptr = str ; for (int i = 0; *ptr; ptr++, i++) {*ptr = XL(*ptr, i);}}

/* Crypt ".PoC_", "key" */
// #define POC XL('.', 0), XL('P', 1), XL('o', 2), XL('C', 3), XL('_', 4)
// #define KEY XL('k', 5), XL('e', 6), XL('y', 7)

/* Attribute to move function bin content into CRYPTED_SECTION */
#define KEY ".PoC_key"
#define CODE ".unix"
#define CRYPTED(A) __attribute__((section(A)))

/* Error handling defines */
#define DIE(s) {perror(s);exit(1);}
#define DIE1(s) {fprintf(stderr, s);exit(1);}

/* Bin "top" address in memory here : */
#define BIN_START ((unsigned char*)0x400000)



/* -TEMPORARY- */
/* Key size and NULL XOR Key */
static CRYPTED(".unixb") bool first_time = true;
#define CRYPTED_FUNC_SIZE 363
static CRYPTED(KEY) char key[CRYPTED_FUNC_SIZE];

/* Crypter */
typedef struct crypter_s
{
    /* Crypted segment */
    int seg_offset; /* Segment offset */
    int seg_len; /* Segment length */
    /* Binary file on disk */
    char *fname; /* Bin name */
    void *bin_content;
    int bin_len;
} crypter_t;

/* ELF  functions */
Elf64_Shdr *elfi_find_section(void *data, char *name);
void change_section_permissions(int seg_offset, int seg_len, bool write);
#endif /* !POCRYPT_H_ */
