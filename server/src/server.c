#include "../inc/header.h"

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage: %s <ip> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	/* Server settings */
	server_info_t server; /* Server info*/
	server.ipv4 = argv[1];
	server.port = atoi(argv[2]);
	server.listenfd = 0;
	server.cli_count = 0;
	pthread_mutex_init(&server.clients_mutex, NULL);
	server.clients = (client_t **)malloc(MAX_CLIENTS * sizeof(client_t *));

	for (int i = 0; i < MAX_CLIENTS; i++) {
		server.clients[i] = NULL;
	}
	
	int option = 1;
	int connfd = 0;
  	struct sockaddr_in cli_addr;
 	pthread_t tid;

	/* Socket settings */
	server.listenfd = socket(AF_INET, SOCK_STREAM, 0);
	server.address.sin_family = AF_INET;
	server.address.sin_addr.s_addr = inet_addr(server.ipv4);
	server.address.sin_port = htons(server.port);

  	/* Ignore pipe signals */
	signal(SIGPIPE, SIG_IGN);

	/* Set socket options*/
	if(setsockopt(server.listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&option,sizeof(option)) < 0){
		perror("ERROR: setsockopt failed");
    return EXIT_FAILURE;
	}

	/* Bind */
	if(bind(server.listenfd, (struct sockaddr*)&server.address, sizeof(server.address)) < 0) {
		perror("ERROR: Socket binding failed");
		return EXIT_FAILURE;
	}

 	/* Listen */
	if (listen(server.listenfd, 10) < 0) {
		perror("ERROR: Socket listening failed");
		return EXIT_FAILURE;
		}

	printf("=== WELCOME TO THE CHATROOM ===\n");

	while(1){
		socklen_t clilen = sizeof(cli_addr);
		/* Accept incoming connection */
		connfd = accept(server.listenfd, (struct sockaddr*)&cli_addr, &clilen);

		/* Check if max clients is reached */
		if((server.cli_count + 1) == MAX_CLIENTS){
			printf("Max clients reached. Rejected: ");
			print_client_addr(cli_addr);
			printf(":%d\n", cli_addr.sin_port);
			close(connfd);
			continue;
		}

		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = server.uid++;

		/* Convert to the buff_t to transfer to the new thread*/
		buff_t *clnt = (buff_t *)malloc(sizeof(buff_t));
		clnt->serv_inf = &server;
		clnt->uid = cli->uid;
		/* Add client to the client array and fork thread */
		client_add(cli, &server);

		pthread_create(&tid, NULL, &handle_client, (void*)clnt);

		/* Reduce CPU usage */
		sleep(1);
	}
	free(server.clients);
	close(server.listenfd);

	return EXIT_SUCCESS;
}
