#include "../inc/header.h"

int main(int argc, char **argv){
	if (argc != 3) {
		printf("Usage: %s <ipv4> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *ip = argv[1];
	char *port = argv[2];
	while(!validate_ip(argv[1])) {
		printf("Error! IP is incorrect.\nTry one more time: ");
		scanf("%s", ip);
		printf("\n\r");
	}

	while(!validate_port(port)) {
		printf("Error! PORT is incorrect.\nTry one more time: ");
		scanf("%s", port);
		printf("\n\r");
	}

	client_t client;
	init_client(&client, ip, port);
	init_funcs();
	
	// Connect to Server
	pthread_t server_connection_handler;

	if(pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)&client) != 0){
		perror("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	while (client.is_connected == 0) {}

	client_t *buff_client = (client_t *)malloc(sizeof(client_t));
	buff_client = &client;

	pthread_t send_msg_thread;
	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)buff_client) != 0){
		perror("ERROR: pthread\n");
	return EXIT_FAILURE;
	}

	pthread_t recv_msg_thread;
	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)buff_client) != 0){
		perror("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	while(1) {
		if (ctrl_c_and_exit_flag) {
			printf("Bye!\n");
			break;
		}
	}
	pthread_mutex_destroy(&client.mutex);
	close(client.sockfd);
	exit(0);
	return EXIT_SUCCESS;
}
