#include "../inc/module_one.h"

int main() {
	read_msg();
	make_cmd();
	return 0;
}

// change to recv() from socket
void read_msg() {
	char *str = mx_file_to_str("text");
	char sep[10] = "\n";
	char *temp_str;

	temp_str = strtok(str,sep);
	while (temp_str != NULL)
	{
	   to_msg_q(temp_str);
	   temp_str = strtok(NULL, sep);
	}
}

void make_cmd() {
	char *fst_msg = strdup(take_fst_msg_in_q());
	move_msg_q();
	struct command cmd = msg_to_cmd(fst_msg);
	to_cmd_q(cmd);
	free(fst_msg);
}
