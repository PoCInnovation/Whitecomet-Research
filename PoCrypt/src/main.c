/*
** PoC PROJECT, 2020
** Whitecomet-Research
** File description:
** main
*/

#include "PoCrypt.h"

static int get_file_size (int fd)
{
    struct stat _infos;

    if (fstat(fd, &_infos) != 0)
        DIE("fstat");
    return _infos.st_size;
}

/* Read binary data and store it */
static crypter_t *read_bin(const char *name)
{
    int fd;
    crypter_t *crypter;

    if ((crypter = malloc(sizeof(crypter_t))) == NULL)
        DIE1("malloc:");
    crypter->fname = strdup(name);
    if ((fd = open(name, O_RDONLY, 0)) < 0)
        DIE("open");
    crypter->bin_len = get_file_size(fd);
    crypter->bin_content = malloc(crypter->bin_len);
    if (read(fd, crypter->bin_content, crypter->bin_len) == -1)
        DIE("read");
    close(fd);
    return crypter;
}

static void save(crypter_t *crypt)
{
    int fd;

    /* Delete the file so we can write a modified image */
    if (unlink(crypt->fname) < 0)
        DIE("unlink:");
    if ((fd = open(crypt->fname, O_CREAT | O_TRUNC | O_RDWR,S_IRWXU)) == -1)
        DIE("open:");
    if (write(fd, crypt->bin_content, crypt->bin_len) < 0)
        DIE("write:");
    close (fd);
  return;
}

static char *generate_key (unsigned char *p, int size)
{
    int i;

    for (i = 0; i < size; i++){
        p[i] = (rand() % 255);
        key[i] = p[i];
    }
    return key;
}

/* Malware */
CRYPTED(CODE) void payload(void)
{
    int i = 0;
    char *a = malloc(sizeof(1) * 23);
    for (i = 0; i < 23; a++, i++)
        printf("Gros Malware\n");
    while (i--);
}

static void xor_segment(unsigned char *seg_start, int seg_len)
{
    int i = 0;
    int j = 0;

    for (;seg_len--; i++) {
        seg_start[i] ^= (key[i] - 1);
    }
}

static void decode_and_crypt(crypter_t *crypter)
{
    Elf64_Shdr *section = elfi_find_section(crypter->bin_content, CODE);
    int key_offset = -1;
    int key_len = -1;

    /* Get ELF infos : */
    /* ELF - On crypted code */
    if (section == NULL)
        DIE("elfi_find_section bin")
    crypter->seg_offset = section->sh_offset;
    crypter->seg_len = section->sh_size;
    key_len = crypter->seg_len; /* Because One Time Pad */

    /* ELF - On key */
    section = elfi_find_section(crypter->bin_content, KEY);
    if (section == NULL)
        DIE("elfi_find_section key");

    key_offset = section->sh_offset;

    /* Give W permission on .unix && crypt payload in binary + memory && Remove W permission */
    change_section_permissions(crypter->seg_offset, crypter->seg_len, true);
    xor_segment(BIN_START + crypter->seg_offset, crypter->seg_len);
    xor_segment(crypter->bin_content + crypter->seg_offset, crypter->seg_len);
    change_section_permissions(crypter->seg_offset, crypter->seg_len, false);

    /* Give W permission on .PoC_key && rewrite key in binary && Remove W perm on .PoC_key*/
    change_section_permissions(key_offset, crypter->seg_len, true);
    generate_key(crypter->bin_content + key_offset, crypter->seg_len);
    change_section_permissions(  key_offset, crypter->seg_len, false);

    /* Overwrite */
    xor_segment(crypter->bin_content + crypter->seg_offset, crypter->seg_len);
    save(crypter);
}

void remove_first_time(crypter_t *crypter)
{
    Elf64_Shdr *section = elfi_find_section(crypter->bin_content, ".unixb");
    int offset = section ? (int)section->sh_offset : -1;
    char *boolean_pos = crypter->bin_content + offset;

    write(1, "Program running for the first time.\n", 36);
    if (section == NULL){
        write(1, "Big problem in your program man\n", 32);
        return;
    }
    for (int i = 0; i < 4; i++)
        boolean_pos[i] = 0;
    for (int i = 0 ; i < CRYPTED_FUNC_SIZE; i++)
        key[i] = 1;
}

/* main */
int main(int ac, char const * const *av)
{
    crypter_t *crypter = read_bin(av[0]);

    if (first_time == true) /* Init a first-time key */
        remove_first_time(crypter);
    srand(time(NULL) * (intptr_t)crypter);  /* Make things really random */
    decode_and_crypt(crypter); /* Decode 😇 */
    payload(); /* 😈 */
    return (0);
}
