#ifndef MODULE_THREE_H
#define MODULE_THREE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

struct command {
    char *command;
    char *params;
};

struct msg_q {
    char *data;
    struct msg_q *link;
} *msg_front;

struct cmd_q {
    struct command data;
    struct cmd_q *link;
} *cmd_front;


char *cmd_to_msg(struct command)

#endif
