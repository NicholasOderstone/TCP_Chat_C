#include "../inc/header.h"

void *read_msg(void *arg) {
	struct read_msg_info_s *Info = (struct read_msg_info_s *)arg;

	char buff_out[BUFFER_SZ];
	while(1) {
		int receive = recv(Info->client->sockfd, buff_out, BUFFER_SZ, 0);
		if (receive > 0){
			if(strlen(buff_out) > 0){
				struct command cmd = msg_to_cmd(buff_out);
				to_cmd_q(cmd, Info->cmd_q_front);
				sem_post(Info->sem_cmd_q);
			}
		} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
			Info->client->exit_flag = 1;
			// printf("Client Disconnected!\n");
			break;
		} else {
			// printf("ERROR: -1\n");
			Info->client->exit_flag = 1;
			break;
		}
		memset(buff_out, 0, sizeof(buff_out));
	}
	pthread_exit(NULL);
	return NULL;
}
