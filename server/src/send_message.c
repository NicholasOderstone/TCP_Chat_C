#include "../inc/header.h"

void send_message(char *s, int uid, server_info_t *serv_inf){
	pthread_mutex_lock(&serv_inf->clients_mutex);

	for(int i=0; i<MAX_CLIENTS; ++i){
		if(serv_inf->clients[i]){
			if(serv_inf->clients[i]->uid != uid){
				if(write(serv_inf->clients[i]->sockfd, s, strlen(s)) < 0){
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&serv_inf->clients_mutex);
}
