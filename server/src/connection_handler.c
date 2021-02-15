#include "../inc/header.h"

void *handle_client(void *arg){
	buff_t *inf = (buff_t *)arg;
	server_info_t *serv_inf = inf->serv_inf;

	if (pthread_mutex_init(&cmd_lock, NULL) != 0)
    {
        // printf("Mutex initialization failed.\n");
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
		// printf("User id error!\n");
		exit(1);
	}

	client_t *client = serv_inf->clients[cid];
	client->exit_flag = 0;

	sem_t *sem_cmd_q;
	char sem_name[100] = "uchat_sem_client_";
	char buff[BUFFER_SZ];
	strcat(sem_name, itoa(inf->uid, buff, 10));
	// printf(" ## sem_name for %d: \"%s\"\n", inf->uid, sem_name);
	sem_cmd_q = sem_open(sem_name, O_CREAT, 0666, 0);

	// Поток чтения сообщений
	pthread_t th_read_msg;

	struct read_msg_info_s *read_msg_info = (struct read_msg_info_s *)malloc(sizeof(struct read_msg_info_s));
	read_msg_info->client = client;
	read_msg_info->cmd_q_front = &cmd_q_front;
	// read_msg_info->sem_cmd_q = sem_cmd_q;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)read_msg_info);

	// Поток обработки комманд
	pthread_t th_process_cmd;
	struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->cmd_q_front = &cmd_q_front;
	initialize_functions(process_cmd_info->arr_cmd_func);
	process_cmd_info->buff_m = inf;
	process_cmd_info->buff_m->client = client;
	// process_cmd_info->sem_cmd_q = sem_cmd_q;
	pthread_create(&th_process_cmd, NULL, process_cmd, (void *)process_cmd_info);

	
	pthread_join(th_read_msg, NULL);
	close(client->sockfd);
	client_remove(client->uid, serv_inf);
	pthread_cancel(th_process_cmd);
	/* Delete client from queue and yield thread */
	
	write(1, "1\n", 2);
	sem_close(sem_cmd_q);
	write(1, "2\n", 2);
	sem_unlink(sem_name);
	write(1, "3\n", 2);

	free(client);
	write(1, "4\n", 2);
	//free(read_msg_info);
	//free(process_cmd_info); // Если ты раскомментируешь это у тебя будет вылетать сервер в 1 из 20 случаев при закрытии клиента
	pthread_detach(pthread_self());

	return NULL;
}




/* 
 * Dorabotat` napil`nikom.
 * 15.02.2021
 * Odarchenko M. S. 
 * Asemiletov A. I.
 * Kuleshova D. A. 
 * Botezat V. K.
 * Ivanov M. M.
 * 
 */



