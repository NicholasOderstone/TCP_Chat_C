#include "../inc/header.h"

void *read_msg(void *arg) {
	client_t *client = (client_t *)arg;
	char buff_out[BUFFER_SZ];
	while(1) {
		int receive = recv(client->sockfd, buff_out, BUFFER_SZ, 0);
		if (receive > 0){
			if(strlen(buff_out) > 0){
				to_msg_q(buff_out);
			}
		} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
			// Комманда LEAVE;
			break;
		} else {
			printf("ERROR: -1\n");
			break;
		}
		bzero(buff_out, BUFFER_SZ);
	}
	pthread_exit(NULL);
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
	return NULL;
}
