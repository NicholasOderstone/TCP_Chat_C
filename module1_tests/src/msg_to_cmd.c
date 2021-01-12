#include "../inc/module_one.h"

struct command msg_to_cmd(char *msg) {
    struct command cmd;

	cmd.command = strdup(msg);
	cmd.params = strdup("2");

	return cmd;
}
