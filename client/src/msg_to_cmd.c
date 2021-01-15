#include "../inc/header.h"

struct command msg_to_cmd(char *msg) {
    struct command cmd;

    char *start_cmd = strchr(msg, '<');
    char *end_cmd = strchr(msg, '>');
    int length_cmd = strlen(start_cmd) - strlen(end_cmd) - 1;

    char *start_params = strchr(end_cmd, '<');
    int length_params = strlen(start_params);
	cmd.command = strndup(&start_cmd[1], length_cmd);
	cmd.params = strndup(start_params, length_params);

	return cmd;
}
