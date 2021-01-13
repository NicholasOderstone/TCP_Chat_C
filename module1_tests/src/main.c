#include "../inc/module_one.h"

// change to recv() from socket
void *read_msg() {
	char *str = mx_file_to_str("text");
	char sep[1] = "\n";
	char *temp_str;

	temp_str = strtok(str,sep);
	while (temp_str != NULL)
	{
		to_msg_q(temp_str);
		sleep(1);
		temp_str = strtok(NULL, sep);
	}
	return NULL;
}

void *make_cmd() {
	while(1) {
		if (msg_front != NULL)
		{
			char *fst_msg = strdup(take_fst_msg_in_q());
			move_msg_q();

			struct command cmd = msg_to_cmd(fst_msg);
			to_cmd_q(cmd);
			free(fst_msg);
		}
		else
			msg_rear = NULL;
	}

	return NULL;
}


int main() {
	pthread_t th_read_msg;
	pthread_t th_make_cmd;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }
	msg_front = NULL;
	msg_rear = NULL;

    printf("Before Thread\n");
    pthread_create(&th_read_msg, NULL, read_msg, NULL);
	pthread_create(&th_make_cmd, NULL, make_cmd, NULL);

	pthread_join(th_read_msg, NULL);
	pthread_join(th_make_cmd, NULL);
    printf("After Thread\n");
    return 0;
	//while (msg_front->link)
}
