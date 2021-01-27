#include "../inc/header.h"

void func_rpl_login(char *params) {
    char *p_rpl = param_1(params);
    if (strcmp(p_rpl, "ERROR") == 0) {
        printf("%s: %s\n", p_rpl, param_2(params));
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        printf("%s\n", p_rpl);
        sw_login = 0;
    }
}

void func_rpl_register(char *params) {
    char *p_rpl = param_1(params);
    printf("%s\n", p_rpl);
    char *p_username = strdup(username_str_s);
    char *p_nick = strdup(nick_str_s);
    char *p_pass = strdup(pass_str_s);
    char *p_r_pass = strdup(r_pass_str_s);
    printf("REGISTER: success.\n\tUsername: %s\n\tNickname: %s\n", p_username, p_nick);
    printf("\tPassword: %s\n\tRepeated password: %s\n", p_pass, p_r_pass);
}

void func_rpl_change_name(char *params) {
    char *p_new_nick = param_1(params);
    printf("CHANGE NAME: success.\n\tNew nickname: %s\n", p_new_nick);
}

void func_rpl_change_pass(char *params) {
    char *p_new_pass = param_1(params);
    printf("CHANGE PASSWORD: success.\n\tNew password: %s\n", p_new_pass);
}

void func_rpl_search_user(char *params) {
    char *p_username = param_1(params);
    printf("SEARCH USER: success.\n\tSearch user with username: %s\n", p_username);
}

void func_rpl_add_contact(char *params) {
    char *p_username = param_1(params);
    printf("ADD CONTACT: success.\n\tContact added: %s\n", p_username);
}

void func_rpl_del_contact(char *params) {
    char *p_username = param_1(params);
    printf("DELETE CONTACT: success.\n\tContact deleted: %s\n", p_username);
}

void func_rpl_block_user(char *params) {
    char *p_username = param_1(params);
    printf("BLOCK USER: success.\n\tUser blocked: %s\n", p_username);
}

void func_rpl_unblock_user(char *params) {
    char *p_username = param_1(params);
    printf("UNBLOCK USER: success.\n\tUser unblocked: %s\n", p_username);
}

void func_rpl_new_chnl(char *params) {
    char *p_chnlname = param_1(params);
    printf("NEW CHANNEL: success.\n\tChannel created: %s\n", p_chnlname);
}

void func_rpl_send(char *params) {
    char *p_message = param_1(params);
    printf("SEND: success.\n\tMessage: %s\n", p_message);
}

void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<CHANGE_NAME>",
                                "<CHANGE_PASS>", "<SEARCH_USER>", "<ADD_CONTACT>",
                                "<DEL_CONTACT>", "<BLOCK_USER>", "<UNBLOCK_USER>",
                                "<NEW_CHNL>", "<SEND>"};

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

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
