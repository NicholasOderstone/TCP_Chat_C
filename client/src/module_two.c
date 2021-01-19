#include "../inc/header.h"

void *process_cmd(void *arg) {
	struct process_cmd_info_s *Info = (struct process_cmd_info_s *)arg;
	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
		if (*Info->cmd_q_front != NULL)
		{
			command fst_cmd = take_fst_cmd_in_q(Info->cmd_q_front);
			move_cmd_q(Info->cmd_q_front);
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				if (strcmp(fst_cmd.command, arr_cmd_func[j].name) == 0) {
					printf("--- %s ---\n", arr_cmd_func[j].name);
					arr_cmd_func[j].func(fst_cmd.params);
				}
			}
		}
	}
	int ret_val = 1;
	printf("5. Process command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}