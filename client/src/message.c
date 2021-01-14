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
	char message[LENGTH];

	while (1) {
		if(ctrl_c_and_exit_flag) {
			break;
		}

		int receive = recv(client->sockfd, message, LENGTH, 0);
		if (receive > 0) {
		  printf("%s", message);
		  str_overwrite_stdout();
		}
		else if (receive == 0) {
				break;
		}
		else {
			printf("Server disconnected\n");
			break;
		}
		memset(message, 0, sizeof(message));
	}
	
	int ret_val = 1;
	printf("\nRecv message thread terminated\n");
    pthread_exit(&ret_val);
  	return NULL;
}
