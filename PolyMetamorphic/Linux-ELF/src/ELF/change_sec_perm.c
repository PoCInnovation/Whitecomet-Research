/*
** EPITECH PROJECT, 2020
** Whitecomet-Research
** File description:
** change_sec_perm
*/

#include "PoCrypt.h"

/* ptr points to beg. of section */
void change_section_permissions(unsigned char *ptr, int seg_len, bool write)
{
    /* Change Permissions of section to decrypt code */
    unsigned char *ptr1 = ptr + seg_len; /* Points to end of section */
    size_t pagesize = sysconf(_SC_PAGESIZE); /* Get system page size */
    uintptr_t pagestart = (uintptr_t)ptr & -pagesize; /* Page of section */
    int psize = (ptr1 - (unsigned char*)pagestart); /* Pagestart size */

    /* Make the pages writable...*/
    if (write == true) {
        if (mprotect((void*)pagestart, psize, PROT_READ | PROT_WRITE | PROT_EXEC) < 0)
            DIE("allow_write_on_page");
    } else if (mprotect((void*)pagestart, psize, PROT_READ | PROT_EXEC) < 0)
        DIE("reset_page_perms");
}
