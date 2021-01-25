#include "../inc/module_three.h"

char *cmd_to_msg(command cmd) {
    int len1 = strlen(cmd.command);
    int len2 = strlen(cmd.params);
    char *msg = mx_strnew(len1 + len2 + 1);
    msg = strcat(msg, cmd.command);
    msg = strcat(msg, " ");
    msg = strcat(msg, cmd.params);
	return msg;
}
