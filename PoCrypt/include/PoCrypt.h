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

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>

/* Basic string obfuscation */
#define XL(a, i) (char)(a ^ (0x1A4 * 0x2B5 * (i + 1) / 0x45)) /* XOR letter w/ index + keys */
#define STRING_CIPHER(str) {char *ptr = str ; for (int i = 0; *ptr; ptr++, i++) {*ptr = XL(*ptr, i);}}

/* Crypt ".PoC_", "key" */
#define POC XL('.', 0), XL('P', 1), XL('o', 2), XL('C', 3), XL('_', 4)
#define KEY XL('k', 5), XL('e', 6), XL('y', 7)

/* Attribute to move function bin content into CRYPTED_SECTION */
#define CRYPTED_SECTION ".unix"
#define CRYPTED __attribute__((section(CRYPTED_SECTION)))

/* Crypter */
typedef struct crypter_s
{
    /* Crypted segment */
    int seg_offset; /* Segment offset */
    int seg_len; /* Segment length */
    /* Binary file on disk */
    char *fname;
    void *bin_content;
    int bin_len;
} crypter_t;

#endif /* !POCRYPT_H_ */
