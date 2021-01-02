//
// Created by Edouard on 14/05/2020.
//

#ifndef PoCrypt_PE
#define PoCrypt_PE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h> // ...
#include <stdio.h> // -> printf and such
#include <stdlib.h> // Lil randomness
#include <time.h> // Lil randomness
#include <unistd.h> // unlink
#include <stdbool.h> // true/false  (:
#include <sys/types.h> // for open, etc
#include <sys/stat.h> // for open, etc
#include <fcntl.h> // for open, etc
// * Author compiled with MinGW on W10 x64

#define CEIL(x) (int)(x + (int) ((float)(x) != (int)(x)) )
#define MAX(x, y) (x > y ? x : y)
#define KEY_SIZE 1536 // ? Size of the segment to have an OTP
#define VAR_OFFSET 32.0 // ? Bytes to skip before accessing to the variables in the sections.
#define OK (0)
#define DOS_HEADER(x) ((IMAGE_DOS_HEADER *)(x)) /* ? Easy access from the module handle to the h.*/
#define FAIL (-1)
#define EXIT(error) {printf(error);exit(FAIL);} // Red button
#define TOO_MUCH_MEM 100000000

#define IN_SECTION(x) __attribute__((section(x)))


// * Fake keys to slow down reverse
#define FAKE_KEYS_NB 3.0
static unsigned char fake_key[MAX(KEY_SIZE, 35)] = "This program has not been run yet.";
static unsigned char false_key[MAX(KEY_SIZE, 56)] = "Try to \"strings\" this again after having it "
                                                    "run once.";
static unsigned char not_real_key[MAX(KEY_SIZE, 14)] = "Interesting..";
// * --------------------------------
static unsigned char key[MAX(KEY_SIZE, 4)] = "\1\1\1\1"; // ? Init. to put the key in .data

#define N_KEYS_OFFSET(x) CEIL((VAR_OFFSET + x * KEY_SIZE * sizeof(char))/32.0) * 32

#define REAL_KEY_OFFSET N_KEYS_OFFSET(FAKE_KEYS_NB)
// ? Offset to the x + 1 static string (keys) in memory


typedef struct segment_info {
    DWORD off; // ? Offset of segment in file
    DWORD size; // ? Size of the segment
    DWORD mem_off; // ? Offset of segment in memory at runtime
} seg_info_t;

typedef struct cryptor {
    seg_info_t code_seg; // ? Storage for the ".code" segment information
    seg_info_t key_seg; // ? Storage for the ".data" segment information
    IMAGE_NT_HEADERS *pe_header; // ? Bin. header
    IMAGE_OPTIONAL_HEADER32 opt_header; // ? Additional information about the binary
    DWORD image_base; // ? It's the address pointing to the beginning of the current process memory
    int section_nb; // ? Number of sections
    unsigned char *new_file;
    int new_file_sz;
} cryptor_t;

#endif //PoCrypt_PE
