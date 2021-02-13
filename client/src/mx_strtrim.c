#include "../inc/header.h"

char *mx_strtrim(const char *str) {
    int len = 0;
    char *new = NULL;

    while (isspace(*str))
        str++;
    len = strlen(str);
    while (isspace(str[len - 1]))
        len--;
    new = strndup(str, len);
    return (char *)new;

}
