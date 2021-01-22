#include "../inc/module_two.h"

command msg_to_cmd(char *msg) {
    command cmd;
    char *start_cmd = strchr(msg, '<');
    char *end_cmd = strchr(msg, '>');
    int length_cmd;
    if (start_cmd && end_cmd)
        length_cmd = strlen(start_cmd) - strlen(end_cmd) + 1;
    else {
        cmd.command = strdup("error");
        cmd.params = strdup("error");
        return cmd;
    }
    char *start_params = strchr(end_cmd, '<');
    int length_params;
    if (start_params)
        length_params = strlen(start_params);
    else {
        cmd.command = strdup("error");
        cmd.params = strdup("error");
        return cmd;
    }
    cmd.command = strndup(start_cmd, length_cmd);
    cmd.params = strndup(start_params, length_params);
    return cmd;
}
