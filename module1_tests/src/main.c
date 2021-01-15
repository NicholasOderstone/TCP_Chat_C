#include "../inc/module_one.h"

void display(struct msg_q *head)
{
    struct msg_q *temp;
    temp = head;
    int cnt = 0;
	pthread_mutex_lock(&lock);
    if (head == NULL)
        printf("Queue underflow\n");
    else {
        printf("The elements of the stack are:\n");
        while (temp) {
            printf("%d: %s\n", cnt, temp->data);
            temp = temp->link;
            cnt++;
        }
    }
	pthread_mutex_unlock(&lock);
}

// change to recv() from socket
void *read_msg() {
	/*char *str = mx_file_to_str("text");
	char sep[1] = "\n";
	char *temp_str;
	temp_str = strtok(str,sep);
	while (temp_str != NULL)
	{
		to_msg_q(temp_str);
		temp_str = strtok(NULL, sep);
	}
	//display(msg_front);*/
	char *arr[120] = {"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>",
					"<PASS> <1234>", "<NICK> <nick>", "<LOGIN> <(name)Ann> <(password)4321>"};
	for (int i = 0; i < 120; i++) {
		to_msg_q(arr[i]);
		usleep(5);
	}
	return NULL;
}

void *make_cmd() {
	//sleep (10);
	while(1) {
		if (msg_front != NULL)
		{
			char *fst_msg = strdup(take_fst_msg_in_q());
			struct command cmd = msg_to_cmd(fst_msg);
			move_msg_q();
			
			to_cmd_q(cmd);
			
			free(fst_msg);
		}
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
	if (pthread_mutex_init(&print_lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }

	msg_front = NULL;
    printf("Before Thread\n");
    pthread_create(&th_read_msg, NULL, read_msg, NULL);
	pthread_create(&th_make_cmd, NULL, make_cmd, NULL);

	pthread_join(th_read_msg, NULL);
	pthread_join(th_make_cmd, NULL);
    printf("After Thread\n");
    return 0;
}
