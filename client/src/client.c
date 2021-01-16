#include "../inc/header.h"

void get_client_name(char *name) {
	printf("Name must be less than 32 and more than 2 characters.\n");
	while (1) {
		printf("Please enter your name: ");
		fflush(stdin);
		fgets(name, NAME_SZ, stdin);
		str_trim_lf(name, strlen(name));
		if (strlen(name) < 2 || strlen(name) > NAME_SZ){
			printf("Name must be less than 32 and more than 2 characters.\n");
		}
		else {
			break;
		}
	}
	//return name;
}


void *connect_to_server(void *cnct_inf) {
	client_t *info = (client_t *)cnct_inf;

	while(1) {
		if (info->is_connected == 0) {
			close(info->sockfd);
			info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
			printf("Trying to connect to server\n");
			int err = connect(info->sockfd, (struct sockaddr *)&info->address, sizeof(info->address));
			if (err == -1) {
				printf("ERROR: connect\n");
				close(info->sockfd);
				sleep(5);
			}
			else {
				
				printf("Connected!\n");
				send(info->sockfd, info->name, NAME_SZ, 0);
				printf("Your name: \"%s\"\n", info->name);
				printf("=== WELCOME TO THE CHATROOM ===\n");
				str_overwrite_stdout();
				info->is_connected = 1;
			}
			
		}
	}
	return NULL;
}

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
	// Socket settings
	//client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	client.address.sin_family = AF_INET;
	client.address.sin_addr.s_addr = inet_addr(ip);
	client.address.sin_port = htons(atoi(port));
	client.is_connected = 0;
	pthread_mutex_init(&client.mutex, NULL);

	// Name

	get_client_name(client.name);

 	// Connect to Server
  	/*int err = connect(client.sockfd, (struct sockaddr *)&client.address, sizeof(client.address));
  	if (err == -1) {
		printf("ERROR: connect\n");
		return EXIT_FAILURE;
	}*/

	pthread_t server_connection_handler;

	if(pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)&client) != 0){
		perror("ERROR: pthread\n");
	return EXIT_FAILURE;
	}

	while (client.is_connected == 0) {}
	
	// Send name
	//send(client.sockfd, client.name, 32, 0);

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

	while (1) {
		if (ctrl_c_and_exit_flag) {
			printf("\nBye\n");
			break;
		}
	}
	pthread_mutex_destroy(&client.mutex);
	close(client.sockfd);
	exit(0);
	return EXIT_SUCCESS;
}
