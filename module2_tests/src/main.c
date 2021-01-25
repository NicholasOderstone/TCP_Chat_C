#include "../inc/module_two.h"

int main() {
	char *messages[3] = { "<LOGIN> <my_login> <my_password>\0",
							"<REGISTER> <my_login> <my_nickname> <my_username> <my_pass> <r_pass>\0",
							"<USER_INFO> <my_username>\0"};
	/*char *messages[3] = { "<CHANGE_NAME> <my_new_nickname>\0",
							"<CHANGE_PASS> <my_new_pass>\0",
							"<SEARCH_USER> <his/her_username>\0"};*/
	/*char *messages[3] = { "<ADD_CONTACT> <his/her_username>\0",
							"<DEL_CONTACT> <his/her_username>\0",
							"<BLOCK_USER> <his/her_username>\0"};*/
	/*char *messages[3] = { "<UNBLOCK_USER> <his/her_username>\0",
							"<NEW_CHNL> <my_chnlname>\0",
							"<CHNL_LIST> <my_chnlname>\0"};*/
	command commands[3];
	for (int i = 0; i < 3; i++)
	 	commands[i]= msg_to_cmd(messages[i]);

	init_funcs();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < AMOUNT_OF_CMD; j++) {
			if (strcmp(commands[i].command, arr_cmd_func[j].name) == 0) {
				printf("--- %s ---\n", arr_cmd_func[j].name);
				arr_cmd_func[j].func(commands[i].params);
			}
		}
	}

	return 0;
}
