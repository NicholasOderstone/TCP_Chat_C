#include "../inc/header.h"

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage: %s <ipv4> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *ip = argv[1];
	int port = atoi(argv[2]);
	client_t client;
	pthread_t send_msg_thread;
	pthread_t recv_msg_thread;

	// Socket settings
	client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	client.address.sin_family = AF_INET;
	client.address.sin_addr.s_addr = inet_addr(ip);
	client.address.sin_port = htons(port);
	pthread_mutex_init(&client.mutex, NULL);

	while (1) {
		printf("Please enter your name: ");
		fgets(client.name, 32, stdin);
		str_trim_lf(client.name, strlen(client.name));

		if (strlen(client.name) > 32 || strlen(client.name) < 2){
			printf("Name must be less than 30 and more than 2 characters.\n");
		}
		else {
			break;
		}
	}

 	// Connect to Server
  	int err = connect(client.sockfd, (struct sockaddr *)&client.address, sizeof(client.address));
  	if (err == -1) {
		perror("ERROR: connect");
		return EXIT_FAILURE;
	}

	// Send name
	send(client.sockfd, client.name, 32, 0);

	printf("=== WELCOME TO THE CHATROOM ===\n");

	client_t *buff_client = (client_t *)malloc(sizeof(client_t));
	buff_client = &client;

	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)buff_client) != 0){
		perror("ERROR: pthread");
    	return EXIT_FAILURE;
	}

	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)buff_client) != 0){
		perror("ERROR: pthread");
		return EXIT_FAILURE;
	}

	while(1) {
		if(ctrl_c_and_exit_flag) {
			printf("\nBye\n");
			break;
    	}
	}
	pthread_mutex_destroy(&client.mutex);
	close(client.sockfd);
	exit(0);
	return EXIT_SUCCESS;
}
