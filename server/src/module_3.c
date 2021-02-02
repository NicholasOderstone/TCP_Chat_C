#include "../inc/header.h"

void send_cmd(struct command cmd, client_t *client) {
	pthread_mutex_lock(&send_cmd_lock);
	char buffer[LENGTH + 32];
	char *msg = cmd_to_msg(cmd);
	snprintf(buffer, BUFFER_SZ, "%s\n", msg);
	send(client->sockfd, buffer, strlen(buffer), 0);
	bzero(buffer, LENGTH + 32);
	pthread_mutex_unlock(&send_cmd_lock);
}
