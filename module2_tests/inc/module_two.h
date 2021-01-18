#ifndef MODULE_TWO_H
#define MODULE_TWO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define AMOUNT_OF_CMD 11

typedef struct {
    char *name;
    void (*func)(char *params);
} cmd_func;

typedef struct {
    char *command;
    char *params;
} command;

cmd_func arr_cmd_func[AMOUNT_OF_CMD];

void init_funcs(void);
command msg_to_cmd(char *msg);

char *param_1(char *params);
char *param_2(char *params);
char *param_3(char *params);
char *param_4(char *params);
char *param_5(char *params);

#endif
