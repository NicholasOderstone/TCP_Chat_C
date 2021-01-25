#include "../inc/module_three.h"

void send_cmd(command cmd) {
	char *msg = cmd_to_msg(cmd);
	printf("msg: %s\n",msg); // send to socket
}

int main() {
	command cmd;
	cmd.command = strdup("<JOIN>");
	cmd.params = strdup("<User>");
	send_cmd(cmd);
	return 0;
}
