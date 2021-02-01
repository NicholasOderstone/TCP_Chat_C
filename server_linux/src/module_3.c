#include "../inc/header.h"

void send_cmd(struct command cmd, client_t *client) {
	char buffer[LENGTH + 32];
	char *msg = cmd_to_msg(cmd);
	snprintf(buffer, BUFFER_SZ, "%s\n", msg);
	send(client->sockfd, buffer, strlen(buffer), 0);
	bzero(buffer, LENGTH + 32);
}
