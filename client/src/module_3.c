#include "../inc/header.h"

void send_cmd(command cmd, client_t *client) {
	char buffer[BUFFER_SZ];
	char *msg = cmd_to_msg(cmd);
	snprintf(buffer, BUFFER_SZ, "%s", msg);
	send(client->sockfd, buffer, strlen(buffer), 0);
	printf(" <  output: \"%s\"\n", buffer);
	bzero(buffer, BUFFER_SZ);
}
