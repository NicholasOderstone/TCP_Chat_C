#include "../inc/header.h"

void *read_msg(void *arg) {
	struct read_msg_info_s *Info = (struct read_msg_info_s *)arg;

	char buff_out[BUFFER_SZ];
	while(1) {
		int receive = recv(Info->client->sockfd, buff_out, BUFFER_SZ, 0);
		if (receive > 0){
			if(strlen(buff_out) > 0){
				to_msg_q(buff_out, Info->msg_q_front);
			}
		} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
			// Комманда LEAVE;
			break;
		} else {
			printf("ERROR: -1\n");
			break;
		}
		//bzero(buff_out, BUFFER_SZ);
		memset(buff_out, 0, sizeof(buff_out));
	}
	pthread_detach(pthread_self()); //pthread_detach
	return NULL;
}

void *make_cmd(void *arg) {
	struct make_cmd_info_s *Info = (struct make_cmd_info_s *)arg;
	while(1) {
		if (*Info->msg_q_front != NULL) {
			char *fst_msg = strdup(take_fst_msg_in_q(Info->msg_q_front));
			move_msg_q(Info->msg_q_front);
			if(fst_msg == NULL) {
				free(fst_msg);
				continue;
			}
			struct command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd, Info->cmd_q_front);
			free(fst_msg);
		}
	}
	pthread_detach(pthread_self());
	return NULL;
}
