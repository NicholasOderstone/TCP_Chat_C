#include "../inc/header.h"

void *send_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
  	char message[LENGTH];
	char buffer[LENGTH + 32];

	while(1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}		
			
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
			str_overwrite_stdout();
		
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
	char msg_buf[LENGTH];

	while (1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}
		if (client->is_connected == 1) {
			int receive = recv(message->client->sockfd, msg_buf, LENGTH, 0);
			if (receive > 0) {
				message->message = strdup(msg_buf);
				printf("%s", message->message);
				str_overwrite_stdout();
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
					printf("Server disconnected\n");
					client->is_connected = 0;
			}
			else {
				printf("Disconnected\n");
				break;
			}
			memset(msg_buf, 0, sizeof(msg_buf));
		}
		
	}

	int ret_val = 1;
	printf("\nRecv message thread terminated\n");
    pthread_exit(&ret_val);
  	return NULL;
}
