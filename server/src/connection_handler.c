#include "../inc/header.h"

void *handle_client(void *arg){
	buff_t *inf = (buff_t *)arg;
	server_info_t *serv_inf = inf->serv_inf;

	pthread_t th_read_msg;
	pthread_t th_make_cmd;
	if (pthread_mutex_init(&cmd_lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return NULL;
    }
		if (pthread_mutex_init(&msg_lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return NULL;
    }
	struct msg_q *msg_q_front = NULL;
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
/*
	if(recv(client->sockfd, name, 32, 0) <= 0 || strlen(name) <  2 || strlen(name) >= 32-1){
		printf("Didn't enter the name.\n");
	} else {
		strcpy(client->name, name);
		sprintf(buff_out, "<JOIN> <%s>\n", client->name);
		printf("%s", buff_out);
		send_message(buff_out, client->uid, serv_inf);
	}
*/
	struct read_msg_info_s *read_msg_info = (struct read_msg_info_s *)malloc(sizeof(struct read_msg_info_s));
	read_msg_info->client = client;
	read_msg_info->msg_q_front = &msg_q_front;
	pthread_create(&th_read_msg, NULL, read_msg, (void *)read_msg_info);


	struct make_cmd_info_s *make_cmd_info = (struct make_cmd_info_s *)malloc(sizeof(struct make_cmd_info_s));
	make_cmd_info->cmd_q_front = &cmd_q_front;
	make_cmd_info->msg_q_front = &msg_q_front;
	pthread_create(&th_make_cmd, NULL, make_cmd, (void *)make_cmd_info);
	//pthread_join или leave_flag в струкстуру client
	pthread_join(th_read_msg, NULL);
	pthread_join(th_make_cmd, NULL);

	/* Delete client from queue and yield thread */
	close(client->sockfd);
	client_remove(client->uid, serv_inf);
	free(client);
	free(read_msg_info);
	free(make_cmd_info);
	pthread_detach(pthread_self());

	return NULL;
}
