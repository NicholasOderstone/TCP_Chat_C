#ifndef MODULE_THREE_H
#define MODULE_THREE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h> 

typedef struct {
    char *command;
    char *params;
} command;

char *cmd_to_msg(command cmd);
char *mx_strnew(const int size);

#endif
