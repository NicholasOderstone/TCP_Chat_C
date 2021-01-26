#ifndef MODULE_ONE_H
#define MODULE_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define AMOUNT_OF_CMD 19

struct command {
    char *command;
    char *params;
};


struct cmd_func {
    char *cmd_name;
    void (*func)(char *params);
};

struct cmd_func arr_cmd_func[AMOUNT_OF_CMD];

void initialize_functions();
char *return_param1(char*);
char *return_param2(char*);
char *return_param3(char*);
char *return_param4(char*);
char *return_param5(char*);

/* LIST_OF_FUNCTIONS */
void cmd_login(char *params);
void cmd_register(char *params);
void cmd_user_info(char *params);
void cmd_change_name(char *params);
void cmd_change_pass(char *params);
void cmd_search_user(char *params);
void cmd_add_contact(char *params);
void cmd_del_contact(char *params);
void cmd_block_user(char *params);
void cmd_unblock_user(char *params);
void cmd_new_chnl(char *params);
void cmd_chnl_list(char *params);
void cmd_del_msg(char *params);
void cmd_edit_msg(char *params);
void cmd_send_msg(char *params);
void cmd_del_chnl(char *params);
void cmd_add_user_to_chnl(char *params);
void cmd_del_user_fromm_chnl(char *params);
void cmd_change_chnl_name(char *params);

#endif
