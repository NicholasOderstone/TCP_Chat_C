#ifndef MODULE_ONE_H
#define MODULE_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct command {
    char *command;
    char *params;
};


struct msg_q_elem {
    char *data;
    struct msg_q *link;
};

struct msg_q
{
    struct msg_q_elem *front;
    struct msg_q_elem *rear;
} message_q;


struct cmd_q_elem {
    struct command data;
    struct cmd_q *link;
};

struct cmd_q
{
    struct cmd_q_elem *front;
    struct cmd_q_elem *rear;
} command_q;


void to_msg_q(char *data); // Function used to insert the element into the queue
void to_cmd_q(struct command data);
void move_msg_q(); // Function used to delete the elememt from the queue
void display(); // Function used to display all the elements in the queue according to FIFO rule

char *take_fst_msg_in_q();
char *mx_file_to_str(const char *filename);
char *mx_strnew(const int size);

void read_msg(void);
void make_cmd(void);

struct command msg_to_cmd(char *msg);

#endif
