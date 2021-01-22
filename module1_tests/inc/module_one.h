#ifndef MODULE_ONE_H
#define MODULE_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_mutex_t print_lock;

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

void to_msg_q(char *data); // Insert the message into the message queue
void to_cmd_q(struct command data); // Insert the command into the command queue
void move_msg_q(); // Delete the first elememt from the message queue

char *take_fst_msg_in_q();
char *mx_file_to_str(const char *filename);
char *mx_strnew(const int size);

struct command msg_to_cmd(char *msg);

#endif
