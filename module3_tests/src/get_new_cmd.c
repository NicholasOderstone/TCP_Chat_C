#include "../inc/header.h"

struct command get_new_cmd(){
    struct command cmd;

    if (cmd_front == NULL) {
        cmd = NULL;
    }
    else {
        cmd = cmd_front->data;
    }
    move_cmd_q();
    return cmd;
}
