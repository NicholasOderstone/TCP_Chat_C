#include "../inc/header.h"

void *process_cmd(void *arg) {
	struct process_cmd_info_s *Info = (struct process_cmd_info_s *)arg;

	if (pthread_mutex_init(&send_cmd_lock, NULL) != 0)
	{
	  // printf("Mutex initialization failed.\n");
	  return NULL;
	}
	while(1) {
		// write(1, "1\n", 2);
		sem_wait(Info->sem_cmd_q);
		if(Info->buff_m->client->exit_flag == 1) {
			break;
		}
		// write(1, "2\n", 2);
		if (*Info->cmd_q_front != NULL) {
		
			// write(1, "3\n", 2);
			struct command fst_cmd = take_fst_cmd_in_q(Info->cmd_q_front);
			move_cmd_q(Info->cmd_q_front);
			// write(1, "1\n", 1);
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				if (strcmp(fst_cmd.command, Info->arr_cmd_func[j].name) == 0) {
					// printf("--- %s ---\n", Info->arr_cmd_func[j].name);
					Info->arr_cmd_func[j].func(fst_cmd.params, Info->buff_m);
				}
			}
		}
	}

	return NULL;
}
