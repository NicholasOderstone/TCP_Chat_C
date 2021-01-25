#include "../inc/header.h"

void *read_msg(void *arg) {
	struct read_msg_info_s *Info = (struct read_msg_info_s *)arg;
	char msg_buf[LENGTH];

	if (pthread_mutex_init(&Info->lock, NULL) != 0)
	{
	  printf("Mutex initialization failed.\n");
	  return NULL;
	}

	while (1) {
		if (Info->client->is_connected == 1) {
			int receive = recv(Info->client->sockfd, msg_buf, LENGTH, 0);
			if (is_exit) {
				break;
			}
			if (receive > 0) {
				if (msg_buf[0] != 0)
					to_msg_q(msg_buf, Info->msg_q_front, Info->lock);
			}
			else if (receive == 0) {
					Info->client->is_connected = 0;
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
	pthread_mutex_destroy(&Info->lock);
	pthread_exit(&ret_val);
	return NULL;
}

void *make_cmd(void *arg) {
	struct make_cmd_info_s *Info = (struct make_cmd_info_s *)arg;

	if (pthread_mutex_init(&Info->lock, NULL) != 0)
	{
	  printf("Mutex initialization failed.\n");
	  return NULL;
	}
	while(1) {
		if (is_exit) {
			break;
		}
		if (*Info->msg_q_front != NULL) {
			char *fst_msg = strdup(take_fst_msg_in_q(Info->msg_q_front));
			move_msg_q(Info->msg_q_front, Info->lock);
			command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd, Info->cmd_q_front, Info->lock);
			free(fst_msg);
		}
	}
	int ret_val = 1;
	printf("4. Make command thread terminated\n");
	pthread_mutex_destroy(&Info->lock);
	pthread_exit(&ret_val);
	return NULL;
}
