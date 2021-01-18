#include "../inc/header.h"

void *send_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
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
		  pthread_mutex_lock(&client->mutex);
		  command cmd = msg_to_cmd(message);
		  send_cmd(cmd, client);
		  pthread_mutex_unlock(&client->mutex);
		}
		bzero(message, LENGTH);
	}

	int ret_val = 1;
	printf("1. Send message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *recv_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;

	pthread_t th_read_msg;
	pthread_t th_make_cmd;
	pthread_t th_process_cmd;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
	  printf("Mutex initialization failed.\n");
	  return NULL;
	}

	msg_front = NULL;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)client);
	pthread_create(&th_make_cmd, NULL, make_cmd, NULL);
	pthread_create(&th_process_cmd, NULL, process_cmd, NULL);

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
