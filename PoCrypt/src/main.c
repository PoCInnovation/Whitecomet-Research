/*
** PoC PROJECT, 2020
** Whitecomet-Research
** File description:
** main
*/

#include "PoCrypt.h"

int main(int ac, char const * const *av)
{
    char key_sec[] = {POC, KEY, 0};

    STRING_CIPHER(key_sec);
    printf("%s\n", key_sec);
    STRING_CIPHER(key_sec);
    printf("%s\n", key_sec);
    return (0);
}