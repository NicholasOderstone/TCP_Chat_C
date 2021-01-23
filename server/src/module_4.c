#include "../inc/header.h"

void *process_cmd(void *arg) {
	struct process_cmd_info_s *Info = (struct process_cmd_info_s *)arg;
	while(1) {
		if(Info->buff_m->client->exit_flag == 1) {
			break;
		}
		if (*Info->cmd_q_front != NULL)
		{	
			struct command fst_cmd = take_fst_cmd_in_q(Info->cmd_q_front);
			move_cmd_q(Info->cmd_q_front);
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				if (strcmp(fst_cmd.command, Info->arr_cmd_func[j].name) == 0) {
					printf("--- %s ---\n", Info->arr_cmd_func[j].name);
					Info->arr_cmd_func[j].func(fst_cmd.params, Info->buff_m);
				}
			}
		}
	}
	//printf("5. Process command thread terminated\n");
	pthread_detach(pthread_self());
	return NULL;
}
