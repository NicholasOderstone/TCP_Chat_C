#include "../inc/header.h"

void client_remove(int uid, server_info_t *serv_inf){
	pthread_mutex_lock(&serv_inf->clients_mutex);
	// printf("serv_inf_p: %p\n", (void *)serv_inf);
	for(int i=0; i < MAX_CLIENTS; ++i){
		if(serv_inf->clients[i]){
			if(serv_inf->clients[i]->uid == uid){
				// free(serv_inf->clients[i]);
				serv_inf->clients[i] = NULL;
				serv_inf->cli_count--;
				break;
			}
		}
	}

	pthread_mutex_unlock(&serv_inf->clients_mutex);
}
