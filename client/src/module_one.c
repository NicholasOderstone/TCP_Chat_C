#include "../inc/header.h"

void *read_msg(void *p) {
	msg_t *arg = (msg_t *)p;
	char *msg = arg->message;
	//client_t *client = arg->client;
	while (1)
	{
		sleep(1);
		to_msg_q(msg);
		printf("%s", msg);
		str_overwrite_stdout();
	}
	int ret_val = 1;
	printf("\nRead message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *make_cmd() {
	while(1) {
		if (msg_front != NULL)
		{
			char *fst_msg = strdup(take_fst_msg_in_q());
			move_msg_q();
			struct command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd);
			free(fst_msg);
		}
	}
	int ret_val = 1;
	printf("\nMake command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}
