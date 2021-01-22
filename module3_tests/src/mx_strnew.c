#include "../inc/module_three.h"

char *mx_strnew(const int size) {
    int i = 0;

    if (size < 0)
        return 0;
    char *str = (char *)malloc(size + 1);
    while (i < size) {
        str[i] = '\0';
        i++;
    }
    str[i] = '\0';
    return str;
}
