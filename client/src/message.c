#include "../inc/header.h"

void *send_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
  	char message[LENGTH];
	char buffer[LENGTH + 32];

  while(1) {
  	str_overwrite_stdout();
    fgets(message, LENGTH, stdin);
    str_trim_lf(message, LENGTH);

    if (strcmp(message, "exit") == 0) {
			break;
    } else {
      pthread_mutex_lock(&client->mutex);
      sprintf(buffer, "%s: %s\n", client->name, message);
      send(client->sockfd, buffer, strlen(buffer), 0);
      pthread_mutex_unlock(&client->mutex);
    }

		bzero(message, LENGTH);
    bzero(buffer, LENGTH + 32);
  }
  catch_ctrl_c_and_exit(2);

  pthread_detach(pthread_self());
  return NULL;
}

void *recv_msg_handler(void *arg) {
	client_t *client = (client_t *)arg;
	char message[LENGTH];
  while (1) {
		int receive = recv(client->sockfd, message, LENGTH, 0);
    if (receive > 0) {
      printf("%s", message);
      str_overwrite_stdout();
    } else if (receive == 0) {
			break;
    } else {
			// -1
		}
		memset(message, 0, sizeof(message));
  }
  pthread_detach(pthread_self());
  return NULL;
}
