/*
** EPITECH PROJECT, 2020
** Whitecomet-Research
** File description:
** find_section
*/

#include <stddef.h>
#include <elf.h>

Elf64_Shdr *elfi_find_section (void *data, char *name)
{
  char *sname;
  int i;
  Elf64_Ehdr* elf_hdr = (Elf64_Ehdr *) data; /*Get bin info */
  Elf64_Shdr *shdr = (Elf64_Shdr *)(data + elf_hdr->e_shoff); /* Get sections */
  Elf64_Shdr *sh_strtab = &shdr[elf_hdr->e_shstrndx]; /* Get sections names */
  const char *const sh_strtab_p = data + sh_strtab->sh_offset; /* Get sections names (pointer) */

  for (i = 0; i < elf_hdr->e_shnum; i++) {
      sname = (char *)(sh_strtab_p + shdr[i].sh_name); /* Find sections "name" */
      if (!strcmp (sname, name))
        return &shdr[i];
    }
  return NULL;
}
