#include "../inc/header.h"

void *read_msg(void *arg) {
	struct read_msg_info_s *Info = (struct read_msg_info_s *)arg;
	char msg_buf[LENGTH];
	printf("read_msg msg_q_front addr: %p\n", (void *)*Info->msg_q_front);
	while (1) {
		if (Info->client->is_connected == 1) {
			int receive = recv(Info->client->sockfd, msg_buf, LENGTH, 0);
			if (receive > 0) {
				if (msg_buf[0] != 0)
					to_msg_q(msg_buf, Info->msg_q_front);
					printf("read_msg msg_q_front addr: %p\n", (void *)*Info->msg_q_front);
			}
			else if (receive == 0) {
					Info->client->is_connected = 0;
					//break;
			}
			else {
				printf("\r-- Disconnected from server --\n");
				break;
			}
			memset(msg_buf, 0, sizeof(msg_buf));
		}
	}
	int ret_val = 1;
	printf("3. Read message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *make_cmd(void *arg) {
	struct make_cmd_info_s *Info = (struct make_cmd_info_s *)arg;

	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
		else if (*Info->msg_q_front != NULL) {
			printf("msg_q_front != NULL\n");
			char *fst_msg = strdup(take_fst_msg_in_q(Info->msg_q_front));
			move_msg_q(Info->msg_q_front);
			command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd, Info->cmd_q_front);
			printf("cmd in cmd_q\n");
			free(fst_msg);
		}
		else {
			//printf("msg_q_front == NULL\n");
		}
	}
	int ret_val = 1;
	printf("4. Make command thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}
