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

/* Attribute to move function bin content into CRYPTED_SECTION */
#define KEY ".PoC_key"
#define CODE ".unix"
#define CRYPTED(A) __attribute__((section(A)))

/* Error handling defines */
#define DIE(s) {perror(s);exit(1);}
#define DIE1(s) {fprintf(stderr, s);exit(1);}

/* Deprecated : Apparently doesn't work when compiling on Debian */
#define BIN_START ((unsigned char*)0x400000)

/* Key size and NULL XOR Key */
static CRYPTED(".unixb") bool first_time = true;
#define CRYPTED_FUNC_SIZE 228
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
void change_section_permissions(unsigned char *ptr, int seg_len, bool write);
#endif /* !POCRYPT_H_ */
