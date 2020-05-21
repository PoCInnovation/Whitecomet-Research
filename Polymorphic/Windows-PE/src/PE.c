#include "include/crypt_pe.h"

int get_headers(void *handle, IMAGE_NT_HEADERS **pe_header, IMAGE_OPTIONAL_HEADER32 *opt_header)
/* * Error handling on the executable and assign PE and Optional headers in the cryptor struct */
{
    if ((DOS_HEADER(handle)->e_magic) != IMAGE_DOS_SIGNATURE)
    EXIT("Wrong DOS signature.\n")

    (*pe_header) = (IMAGE_NT_HEADERS *) ((DWORD) handle + DOS_HEADER(handle)->e_lfanew);
    if (((*pe_header)->Signature) != IMAGE_NT_SIGNATURE)
    EXIT("Wrong signature.\n")

    *opt_header = (*pe_header)->OptionalHeader;
    if ((opt_header->Magic) != 0x10B)
    EXIT("Wrong magic number.\n")
    return opt_header->ImageBase; /* ? Return the base address of our program.*/
}

void get_seg_info(IMAGE_SECTION_HEADER *section, int nb_section,seg_info_t *seg_info, char *name)
{
    IMAGE_SECTION_HEADER *tmp_section = section;

    for (int i = 0; i < nb_section; i++, tmp_section++) {
        if (!strcmp((char *) tmp_section->Name, name)) {
            seg_info->off = tmp_section->PointerToRawData;
            seg_info->size = tmp_section->SizeOfRawData;
            seg_info->mem_off = tmp_section->VirtualAddress; /*  */
            return;
        }
    }
    EXIT("Couldn't find sections.\n")
}

static SYSTEM_INFO get_system_info(void)
{
    SYSTEM_INFO si;

    GetSystemInfo(&si);
    return si;
}

void change_section_permissions(unsigned char *start, int seg_offset, int seg_len, bool write)
{
    /* Change Permissions of section  SECTION to decrypt code */
    unsigned char *ptr = (start + seg_offset);
    unsigned char *ptr_end = (ptr + seg_len);
    SYSTEM_INFO sys_info = get_system_info();
    size_t sys_page_size = sys_info.dwPageSize; /* Get system page size */
    intptr_t page_start = (intptr_t)ptr & ~(sys_page_size - 1); /* Page of section */
    int p_size = (ptr_end - (unsigned char *)page_start); /* "Data" size */
    DWORD *before_changes;

    if (write == true && VirtualProtect((unsigned char *)page_start, p_size, PAGE_EXECUTE_READWRITE,
                                        (PDWORD) &before_changes) == 0)
        EXIT("allow_write_on_page")
    else if (write == false && VirtualProtect((unsigned char *) page_start, p_size,
                                              PAGE_EXECUTE_READ,
                                              (PDWORD) &before_changes) == 0)
        EXIT("reset_page_perms")
}