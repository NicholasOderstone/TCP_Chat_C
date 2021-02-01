#include "../inc/header.h"

void *th_connect_to_server(GtkWidget *widget, gpointer data) {
// --- Init client ---
	UNUSED(widget);
	client_t *info = (client_t *)data;
	init_client(info, ipv_str, port_str);
	while(1) {
        if(info->exit == 1) {
			break;
		}
		if (info->is_connected == 0) {
            // gtk_spinner_start(connection_spin);
			close(info->sockfd);
			info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
			printf("Trying to connect to server\n");
			int err = connect(info->sockfd, (struct sockaddr *)&info->address, sizeof(info->address));
			if (err == -1) {
				printf("ERROR: connect\n");
				close(info->sockfd);
				sleep(3);
			}
			else {
                // gtk_spinner_stop (connection_spin);
				printf("Connected!\n");
				info->is_connected = 1;
				break;
			}
		}
	}
// --- Connect to Server ---
	pthread_t server_connection_handler;
	if (pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)info) != 0){
		perror("ERROR: pthread\n");
		return NULL;
	}

	// while (client->is_connected == 0) {}

    return NULL;
}
