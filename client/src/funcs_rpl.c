#include "../inc/header.h"

void func_rpl_login(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "INCORRECT_LOGIN") == 0) {
            sw_login = 1;
        }
        else if (strcmp(take_param(params, 2), "INCORRECT_PASS") == 0) {
            sw_login = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_login = 0;
    }
}

void func_rpl_register(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "USERNAME_EXIST") == 0) {
            sw_register = 1;
        }
        else if (strcmp(take_param(params, 2), "PASS_NOT_MATCH") == 0) {
            sw_register = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_register = 0;
    }
}

void func_rpl_change_name(char *params, void *p) {
    UNUSED(p);
    char *p_new_nick = take_param(params, 1);
    printf("CHANGE NAME: success.\n\tNew nickname: %s\n", p_new_nick);
}

void func_rpl_change_pass(char *params, void *p) {
    UNUSED(p);
    char *p_new_pass = take_param(params, 1);
    printf("CHANGE PASSWORD: success.\n\tNew password: %s\n", p_new_pass);
}

void func_rpl_search_user(char *params, void *p) {
    UNUSED(p);
    char *p_username = take_param(params, 1);
    printf("SEARCH USER: success.\n\tSearch user with username: %s\n", p_username);
}

void func_rpl_add_contact(char *params, void *p) {
    UNUSED(p);
    char *p_username = take_param(params, 1);
    printf("ADD CONTACT: success.\n\tContact added: %s\n", p_username);
}

void func_rpl_del_contact(char *params, void *p) {
    UNUSED(p);
    char *p_username = take_param(params, 1);
    printf("DELETE CONTACT: success.\n\tContact deleted: %s\n", p_username);
}

void func_rpl_block_user(char *params, void *p) {
    UNUSED(p);
    char *p_username = take_param(params, 1);
    printf("BLOCK USER: success.\n\tUser blocked: %s\n", p_username);
}

void func_rpl_unblock_user(char *params, void *p) {
    UNUSED(p);
    char *p_username = take_param(params, 1);
    printf("UNBLOCK USER: success.\n\tUser unblocked: %s\n", p_username);
}

void func_rpl_new_chnl(char *params, void *p) {
    UNUSED(p);
    char *p_chnlname = take_param(params, 1);
    printf("NEW CHANNEL: success.\n\tChannel created: %s\n", p_chnlname);
}

void func_rpl_send(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 2);
    printf("## send: %s ##\n", p_rpl);
    // chat_id, msg_id, sender_name, time, text
}

void func_rpl_chat_list(char *params, void *p) {
    client_t *client = (client_t *)p;
    int p_id = atoi(take_param(params, 1));
    char *p_name = take_param(params, 2);
    to_chat_list(p_id, p_name, &client->chat_list_head);
    display(&client->chat_list_head);
}


void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<CHANGE_NAME>",
                                "<CHANGE_PASS>", "<SEARCH_USER>", "<ADD_CONTACT>",
                                "<DEL_CONTACT>", "<BLOCK_USER>", "<UNBLOCK_USER>",
                                "<NEW_CHNL>", "<SEND>", "<CHAT_LIST>"};

    arr_cmd_func[0].func = &func_rpl_login;
    arr_cmd_func[1].func = &func_rpl_register;
    arr_cmd_func[2].func = &func_rpl_change_name;
    arr_cmd_func[3].func = &func_rpl_change_pass;
    arr_cmd_func[4].func = &func_rpl_search_user;
    arr_cmd_func[5].func = &func_rpl_add_contact;
    arr_cmd_func[6].func = &func_rpl_del_contact;
    arr_cmd_func[7].func = &func_rpl_block_user;
    arr_cmd_func[8].func = &func_rpl_unblock_user;
    arr_cmd_func[9].func = &func_rpl_new_chnl;
    arr_cmd_func[10].func = &func_rpl_send;
    arr_cmd_func[11].func = &func_rpl_chat_list;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}

void init_switches(void) {
    sw_login = -1;
    sw_register = -1;
    sw_send = -1;
}
