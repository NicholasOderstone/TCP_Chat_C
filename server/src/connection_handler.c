#include "../inc/header.h"

void *handle_client(void *arg){
	buff_t *inf = (buff_t *)arg;
	server_info_t *serv_inf = inf->serv_inf;

	if (pthread_mutex_init(&cmd_lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return NULL;
    }
	struct cmd_q *cmd_q_front = NULL;

	int cid = -1; /* Client place in clients array*/
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (serv_inf->clients[i] == NULL) {
			continue;
		}
		if (serv_inf->clients[i]->uid == inf->uid) {
			cid = i;
			break;
		}
	}
	if (cid == -1) {
		printf("User id error!\n");
		exit(1);
	}

	client_t *client = serv_inf->clients[cid];
	client->exit_flag = 0;

	pthread_t th_read_msg;
	struct read_msg_info_s *read_msg_info = (struct read_msg_info_s *)malloc(sizeof(struct read_msg_info_s));
	read_msg_info->client = client;
	read_msg_info->cmd_q_front = &cmd_q_front;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)read_msg_info);

	pthread_t th_process_cmd;
	struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->cmd_q_front = &cmd_q_front;
	initialize_functions(process_cmd_info->arr_cmd_func);
	process_cmd_info->buff_m = inf;
	process_cmd_info->buff_m->client = client;
	pthread_create(&th_process_cmd, NULL, process_cmd, (void *)process_cmd_info);


	pthread_join(th_read_msg, NULL);
	pthread_detach(th_process_cmd);
	/* Delete client from queue and yield thread */
	close(client->sockfd);
	client_remove(client->uid, serv_inf);
	free(client);
	free(read_msg_info);
	free(process_cmd_info);
	pthread_detach(pthread_self());

	return NULL;
}
