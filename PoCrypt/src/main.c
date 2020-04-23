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
crypter_t *read_bin (char *name)
{
    int     fd;
    crypter_t *c;

    if ((c = malloc (sizeof(crypter_t))) == NULL)
        DIE1("malloc:");
    c->fname = strdup(name);
    if ((fd = open (name, O_RDONLY, 0)) < 0)
        DIE("open");
    c->bin_len = (get_file_size(fd));
    c->bin_content = malloc (c->bin_len);
    read (fd, c->bin_content, c->bin_len);
    close (fd);
    return c;
}

void save(crypter_t *crypt)
{
    int fd;

    /* Delete the file so we can write a modified image */
    if ((unlink (crypt->fname)) < 0)
        DIE("unlink:");
    if ((fd = open (crypt->fname, O_CREAT | O_TRUNC | O_RDWR,S_IRWXU)) == -1)
        DIE("open:");
    if (write (fd, crypt->bin_content, crypt->bin_len) < 0)
        DIE("write:");
    close (fd);
  return;
}

char *generate_key (unsigned char *p, int size)
{
    char *key = malloc(sizeof(size) + 1);
    int i;

    if (!key)
        return NULL;
    for (i = 0; i < size; i++){
        p[i] = (rand() % 255);
        key[i] = p[i];
    }
    return key;
}

/* Malware */
CRYPTED void payload(void)
{
    printf("Gros Malware\n");
}

/* main */
int main(int ac, char const * const *av)
{
    char key_sec[] = {POC, KEY, 0};
    crypter_t *crypter = read_bin(av[0]);

    srand (time(NULL));
    // decode_and_crypt();
    payload();
    return (0);
}