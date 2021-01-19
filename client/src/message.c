#include "../inc/header.h"

void *send_msg_handler(void *arg) {
	struct send_msg_info_s *Info = (struct send_msg_info_s *)arg;
  	char message[LENGTH];

	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
		str_overwrite_stdout();
		fgets(message, LENGTH, stdin);
		str_trim_lf(message, LENGTH);

		if (strcmp(message, "exit") == 0) {
			catch_ctrl_c_and_exit();
		}
		else {
		  pthread_mutex_lock(&Info->client->mutex);
		  command cmd = msg_to_cmd(message);
		  send_cmd(cmd, Info->client);
		  pthread_mutex_unlock(&Info->client->mutex);
		}
		bzero(message, LENGTH);
	}

	int ret_val = 1;
	printf("1. Send message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *recv_msg_handler(void *arg) {
	struct recv_msg_info_s *Info = (struct recv_msg_info_s *)arg;
	//printf("Recv_msg_handler msg_q_front addr: %p\n", (void *)Info->msg_q_front);
	printf("Recv_msg_handler cmd_q_front addr: %p\n", (void *)*Info->cmd_q_front);
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
	  printf("Mutex initialization failed.\n");
	  return NULL;
	}

	struct read_msg_info_s *read_msg_info = (struct read_msg_info_s *)malloc(sizeof(struct read_msg_info_s));
	read_msg_info->client = Info->client;
	read_msg_info->msg_q_front = Info->msg_q_front;

	if (read_msg_info->msg_q_front == NULL) {
		printf("MSG_q_front get\n");
	}

	pthread_t th_read_msg;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)read_msg_info);

	struct make_cmd_info_s *make_cmd_info = (struct make_cmd_info_s *)malloc(sizeof(struct make_cmd_info_s));
	make_cmd_info->cmd_q_front = Info->cmd_q_front;
	make_cmd_info->msg_q_front = Info->msg_q_front;

	pthread_t th_make_cmd;
	pthread_create(&th_make_cmd, NULL, make_cmd, (void *)make_cmd_info);

	while (1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
	}

	int ret_val = 1;
	printf("2. Recv message thread terminated\n");
    pthread_exit(&ret_val);
  	return NULL;
}
