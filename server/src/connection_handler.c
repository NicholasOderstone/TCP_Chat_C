#include "../inc/header.h"

void *handle_client(void *arg){
	char buff_out[BUFFER_SZ];
	char name[32];
	int leave_flag = 0;

	buff_t *inf = (buff_t *)arg;
	server_info_t *serv_inf = inf->serv_inf;

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
	// Name
	if(recv(client->sockfd, name, 32, 0) <= 0 || strlen(name) <  2 || strlen(name) >= 32-1){
		printf("Didn't enter the name.\n");
		leave_flag = 1;
	} else {
		strcpy(client->name, name);
		sprintf(buff_out, "<JOIN> <%s>\n", client->name);
		printf("%s", buff_out);
		send_message(buff_out, client->uid, serv_inf);
	}

	bzero(buff_out, BUFFER_SZ);

	while(1){
		if (leave_flag) {
			break;
		}

		int receive = recv(client->sockfd, buff_out, BUFFER_SZ, 0);
		if (receive > 0){
			if(strlen(buff_out) > 0){
				send_message(buff_out, client->uid, serv_inf);

				str_trim_lf(buff_out, strlen(buff_out));
				printf("<SEND> <%s> %s\n", client->name, buff_out);
			}
		} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
			sprintf(buff_out, "<LEAVE> <%s>\n", client->name);
			printf("%s", buff_out);
			send_message(buff_out, client->uid, serv_inf);
			leave_flag = 1;
		} else {
			printf("ERROR: -1\n");
			leave_flag = 1;
		}

		bzero(buff_out, BUFFER_SZ);
	}

	/* Delete client from queue and yield thread */
		close(client->sockfd);
	client_remove(client->uid, serv_inf);
	free(client);

	pthread_detach(pthread_self());

	return NULL;
}
