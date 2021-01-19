#include "../inc/module_one.h"

void initialize_functions() {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<USER_INFO>", "<CHANGE_NAME>",
                                            "<CHANGE_PASS>", "<SEARCH_USER>", "<ADD_CONTACT>", "<DEL_CONTACT>",
                                            "<BLOCK_USER>", "<UNBLOCK_USER>", "<NEW_CHNL>", "CHNL_LIST",
                                            "DEL_MSG", "EDIT_MSG", "SEND_MSG", "DEL_CHNL",
                                            "ADD_USER_TO_CHNL", "DEL_USER_FROM_CHNL", "CHANGE_CHNL_NAME"};
    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
    }
    arr_cmd_func[0].func = &cmd_login;
    arr_cmd_func[1].func = &cmd_register;
    arr_cmd_func[2].func = &cmd_user_info;
    arr_cmd_func[3].func = &cmd_change_name;
    arr_cmd_func[4].func = &cmd_change_pass;
    arr_cmd_func[5].func = &cmd_search_user;
    arr_cmd_func[6].func = &cmd_add_contact;
    arr_cmd_func[7].func = &cmd_del_contact;
    arr_cmd_func[8].func = &cmd_block_user;
    arr_cmd_func[9].func = &cmd_unblock_user;
    arr_cmd_func[10].func = &cmd_new_chnl;
    arr_cmd_func[11].func = &cmd_chnl_list;
    arr_cmd_func[12].func = &cmd_del_msg;
    arr_cmd_func[13].func = &cmd_edit_msg;
    arr_cmd_func[14].func = &cmd_send_msg;
    arr_cmd_func[15].func = &cmd_del_chnl;
    arr_cmd_func[16].func = &cmd_add_user_to_chnl;
    arr_cmd_func[17].func = &cmd_del_user_fromm_chnl;
    arr_cmd_func[18].func = &cmd_change_chnl_name;
}
