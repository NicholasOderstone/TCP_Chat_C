#include "../inc/header.h"

void *process_cmd() {
	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
		if (cmd_front != NULL)
		{
			//command fst_cmd = take_fst_cmd_in_q();
			move_cmd_q();
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				//if (strcmp(fst_cmd.command, arr_cmd_func[j].name) == 0) {
					printf("--- %s ---\n", arr_cmd_func[j].name);
					//arr_cmd_func[j].func(fst_cmd.params);
				//}
			}
		}
	}
	int ret_val = 1;
	printf("5. Process command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}
