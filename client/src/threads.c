#include "../inc/header.h"

void *th_connect_to_server(GtkWidget *widget, gpointer data) {
// --- Init client ---
	UNUSED(widget);
	client_t *client = (client_t *)data;

// --- Connect to Server ---
	pthread_t server_connection_handler;
    printf("th_connect_to_server client: %p\n", (void *)client);
	if (pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)client) != 0){
		perror("ERROR: pthread\n");
		return NULL;
	}

	while (client->is_connected == 0) {}

    return NULL;
}
