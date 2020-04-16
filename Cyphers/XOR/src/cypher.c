/*
** PoC PROJECT, 2020
** Whitecomet-Research
** File description:
** xor_cypher
*/

#include <cypher.h>

static int get_size(char *file_name)
{
    struct stat my_stat;

    if (file_name == NULL)
        return (-1);
    if (stat(file_name, &my_stat) == -1)
        exit (errno);
    return (my_stat.st_size);
}

static bool write_key(char *key_content, int size)
{
    FILE *new_key = fopen(".key", "w+");

    return !(new_key == NULL || size < 0 || fwrite(key_content, size, 1, new_key) != 1);
}

static char *get_key(FILE *key, char *key_name)
{
    int key_size = get_size(key_name);
    char *res = key_size > 0 ? malloc(sizeof(char) * key_size) : NULL;

    if (key_size < 0 || key == NULL
        || fread(res, key_size, 1, key) != 1)
        return NULL;
    return res;
}
int main(int ac, char *argv[])
{
    char *binary_name = ac >= 3 ? argv[1] : NULL;
    char *output_name = ac >= 3 ? argv[2] : NULL;
    char *key_name = ac == 4 ? argv[3] : NULL;

    bool mode = ac == 4;

    FILE *file = ac >= 3 ? fopen(binary_name, "rb") : NULL;
    FILE *output = ac >= 3 ? fopen(output_name, "wb+") : NULL;
    FILE *key_file = mode ? fopen(key_name, "rb") : NULL;

    int size = file ? get_size(binary_name) : -1;

    char *binary_content = size > 0 ? malloc(sizeof(char) * size) : NULL;
    char *key;

    if (binary_content == NULL
        || file == NULL || output == NULL
        || fread(binary_content, size, 1, file) != 1){
        printf("%s[ERROR WITH FILE INPUT OR OUTPUT]%s\n", BOLDRED, RESET);
        return (-1);
    }
    srand(time(NULL));
    if (mode == false){
        key = create_key(size);
        if (write_key(key, size) == false){
            printf("%s[ERROR WITH KEY FILE - writing]%s\n", BOLDRED, RESET);
            return (-1);
        }
    } else
        if ((key = get_key(key_file, key_name)) == NULL){
            printf("%s[ERROR WITH KEY FILE - getting]%s\n", BOLDRED, RESET);
            return (-1);
        }
    for (int i = 0; i < size; i++)
        binary_content[i] ^= key[i];
    fwrite(binary_content, size, 1, output);
    printf("%s[OK|ENCRYPTED]%s\n", BOLDGREEN, RESET);
    return 0;
}
