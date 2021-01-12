#include "../inc/module_one.h"

char *mx_file_to_str(const char *filename) {
    int file;
    int i = 0;
    char buf;
    char *result = NULL;

    if((file = open(filename, O_RDONLY))!= -1)
    {
        while (read(file, &buf, 1))
            i++;
        close(file);
        if (i == 0) {
            return NULL;
        }
        file = open(filename, O_RDONLY);
        result = mx_strnew(i);
        i = 0;
        while(read(file, &buf, 1)) {
            result[i] = buf;
            i++;
        }
        result[i] = '\0';
        close(file);
        return result;
    }
    else
    {
        return NULL;
    }

}
