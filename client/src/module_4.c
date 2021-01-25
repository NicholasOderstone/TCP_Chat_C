#include "../inc/header.h"

void *process_cmd(void *arg) {
	struct process_cmd_info_s *Info = (struct process_cmd_info_s *)arg;
	while(1) {
		/*if (destroy()) {
			break;
		}*/
		if (*Info->cmd_q_front != NULL)
		{
			command fst_cmd = take_fst_cmd_in_q(Info->cmd_q_front);
			move_cmd_q(Info->cmd_q_front);
			for (int j = 0; j < AMOUNT_OF_CMD; j++) {
				analyse_cmd(fst_cmd, Info->arr_cmd_func[j]);
			}
		}
	}
	int ret_val = 1;
	printf("5. Process command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void analyse_cmd(command fst_cmd, cmd_func function) {
	if (strcmp(fst_cmd.command, function.name) == 0) {
		printf("--- %s ---\n", function.name);
		function.func(fst_cmd.params);
		/*if (strcmp(param_1(fst_cmd.params), "success") == 0) {
			printf("--- %s ---\n", function.name);
			function.func(fst_cmd.params);
		}
		else if (strcmp(param_1(fst_cmd.params), "error") == 0) {
			printf("--- NO SUCH COMMAND ---\n");
		}*/
	}
}
