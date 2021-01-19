#include "../inc/header.h"

void f_login(char *params) {
    char *p_login = param_1(params);
    char *p_pass = param_2(params);
    printf("LOGIN: success.\n\tLogin: %s\n\tPassword: %s\n", p_login, p_pass);
}

void f_register(char *params) {
    char *p_login = param_1(params);
    char *p_nick = param_2(params);
    char *p_username = param_3(params);
    char *p_pass = param_4(params);
    char *p_r_pass = param_5(params);
    printf("REGISTER: success.\n\tLogin: %s\n\tNickname: %s\n", p_login, p_nick);
    printf("\tUsername: %s\n\tPassword: %s\n\tRepeated password: %s\n", p_username, p_pass, p_r_pass);
}

void f_user_info(char *params) {
    char *p_username = param_1(params);
    printf("USER INFO: success.\n\tInfo of user with username: %s\n", p_username);
}

void f_change_name(char *params) {
    char *p_new_nick = param_1(params);
    printf("CHANGE NAME: success.\n\tNew nickname: %s\n", p_new_nick);
}

void f_change_pass(char *params) {
    char *p_new_pass = param_1(params);
    printf("CHANGE PASSWORD: success.\n\tNew password: %s\n", p_new_pass);
}

void f_search_user(char *params) {
    char *p_username = param_1(params);
    printf("SEARCH USER: success.\n\tSearch user with username: %s\n", p_username);
}

void f_add_contact(char *params) {
    char *p_username = param_1(params);
    printf("ADD CONTACT: success.\n\tContact added: %s\n", p_username);
}

void f_del_contact(char *params) {
    char *p_username = param_1(params);
    printf("DELETE CONTACT: success.\n\tContact deleted: %s\n", p_username);
}

void f_block_user(char *params) {
    char *p_username = param_1(params);
    printf("BLOCK USER: success.\n\tUser blocked: %s\n", p_username);
}

void f_unblock_user(char *params) {
    char *p_username = param_1(params);
    printf("UNBLOCK USER: success.\n\tUser unblocked: %s\n", p_username);
}

void f_new_chnl(char *params) {
    char *p_chnlname = param_1(params);
    printf("NEW CHANNEL: success.\n\tChannel created: %s\n", p_chnlname);
}

void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<USER_INFO>",
                                "<CHANGE_NAME>", "<CHANGE_PASS>", "<SEARCH_USER>",
                                "<ADD_CONTACT>", "<DEL_CONTACT>", "<BLOCK_USER>",
                                "<UNBLOCK_USER>", "<NEW_CHNL>"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_register;
    arr_cmd_func[2].func = &f_user_info;
    arr_cmd_func[3].func = &f_change_name;
    arr_cmd_func[4].func = &f_change_pass;
    arr_cmd_func[5].func = &f_search_user;
    arr_cmd_func[6].func = &f_add_contact;
    arr_cmd_func[7].func = &f_del_contact;
    arr_cmd_func[8].func = &f_block_user;
    arr_cmd_func[9].func = &f_unblock_user;
    arr_cmd_func[10].func = &f_new_chnl;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
