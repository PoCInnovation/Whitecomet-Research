/*
** EPITECH PROJECT, 2020
** Whitecomet-Research
** File description:
** xor_cypher
*/

#include "cypher.h"

static char get_rdm_value(void)
{
    int value = rand() % 255 + 1;
    return (value);
}

char *create_key(int len)
{
    char *key = NULL;
    char *ptr_key = NULL;

    if (len == 0)
        return (NULL);
    key = malloc(sizeof(char) * (len + 1));
    ptr_key = key;
    if (key == NULL)
        return (NULL);
    while (len--)
        *key++ = get_rdm_value();
    *key = '\0';
    return (ptr_key);
}