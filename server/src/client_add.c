#include "../inc/header.h"


static void function(server_info_t *serv_inf) {

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(serv_inf->clients[i] != NULL){
			// printf("%d\n", serv_inf->clients[i]->uid);
		}
	}
}


int client_add(client_t *cl, server_info_t *serv_inf){
	
	int new_client_uid;
	pthread_mutex_lock(&serv_inf->clients_mutex);
	// printf("serv_inf_p: %p\n", (void *)serv_inf);
	new_client_uid = -1;
	for(int i=0; i < MAX_CLIENTS; ++i){
		if(!serv_inf->clients[i]){
			new_client_uid = i;

			serv_inf->clients[i] = cl;
			serv_inf->clients[i]->uid = new_client_uid;
			serv_inf->cli_count++;
			break;
		}
	}
	pthread_mutex_unlock(&serv_inf->clients_mutex);
	function(serv_inf);

	return new_client_uid;
}
