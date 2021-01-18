#include "../inc/header.h"

void *read_msg(void *arg) {
	client_t *client = (client_t *)arg;
	char msg_buf[LENGTH];

	while (1)
	{
		int receive = recv(client->sockfd, msg_buf, LENGTH, 0);
		if (receive > 0) {
			if (msg_buf[0] != 0)
			{
				to_msg_q(msg_buf);
			}
		}
		else if (receive == 0) {
				break;
		}
		else {
			printf("-- Server disconnected --\n");
			break;
		}
		memset(msg_buf, 0, sizeof(msg_buf));
	}
	int ret_val = 1;
	printf("3. Read message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *make_cmd() {
	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
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
	printf("4. Make command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}
