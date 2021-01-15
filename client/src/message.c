#include "../inc/header.h"

void *send_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
  	char message[LENGTH];
	char buffer[LENGTH + 32];

	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}

		str_overwrite_stdout();
		fgets(message, LENGTH, stdin);
		str_trim_lf(message, LENGTH);

		if (strcmp(message, "exit") == 0) {
			catch_ctrl_c_and_exit(2);
		}
		else {
		  pthread_mutex_lock(&client->mutex);
		  snprintf(buffer, BUFFER_SZ, "%s: %s\n", client->name, message);
		  send(client->sockfd, buffer, strlen(buffer), 0);
		  pthread_mutex_unlock(&client->mutex);
		}

		bzero(message, LENGTH);
		bzero(buffer, LENGTH + 32);
	}

	int ret_val = 1;
	printf("\nSend message thread terminated\n");
	pthread_exit(&ret_val);
	return NULL;
}

void *recv_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
	msg_t *message = (msg_t *)malloc(sizeof(msg_t));
	message->client = client;

	while (1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}

		int receive = recv(message->client->sockfd, message->message, LENGTH, 0);
		if (receive > 0) {
			printf("msg recieved\n");

			/*pthread_t th_read_msg;
			pthread_t th_make_cmd;

			if (pthread_mutex_init(&lock, NULL) != 0)
			{
			  printf("Mutex initialization failed.\n");
			  return NULL;
			}
			msg_front = NULL;
			printf("Before Thread\n");
			pthread_create(&th_read_msg, NULL, read_msg, (void *)message);
			pthread_create(&th_make_cmd, NULL, make_cmd, NULL);

			//pthread_join(th_read_msg, NULL);
			//pthread_join(th_make_cmd, NULL);
			printf("After Thread\n");*/
		}
		else if (receive == 0) {
				break;
		}
		else {
			printf("Server disconnected\n");
			break;
		}
		memset(message->message, 0, sizeof(message->message));
	}

	int ret_val = 1;
	printf("\nRecv message thread terminated\n");
    pthread_exit(&ret_val);
  	return NULL;
}
