#include "../inc/header.h"

void *recv_msg_handler(void *arg) {
	struct recv_msg_info_s *Info = (struct recv_msg_info_s *)arg;
	struct read_msg_info_s *read_msg_info = (struct read_msg_info_s *)malloc(sizeof(struct read_msg_info_s));
	read_msg_info->client = Info->client;
	read_msg_info->msg_q_front = Info->msg_q_front;

	pthread_t th_read_msg;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)read_msg_info);

	struct make_cmd_info_s *make_cmd_info = (struct make_cmd_info_s *)malloc(sizeof(struct make_cmd_info_s));
	make_cmd_info->client = Info->client;
	make_cmd_info->cmd_q_front = Info->cmd_q_front;
	make_cmd_info->msg_q_front = Info->msg_q_front;

	pthread_t th_make_cmd;
	pthread_create(&th_make_cmd, NULL, make_cmd, (void *)make_cmd_info);

	while (1) {
		if (Info->client->exit == 1) {
			break;
		}
	}

	pthread_join(th_read_msg, NULL);
	pthread_join(th_make_cmd, NULL);

	int ret_val = 1;
	printf("-- Recv message thread terminated --\n");
    pthread_exit(&ret_val);
  	return NULL;
}
