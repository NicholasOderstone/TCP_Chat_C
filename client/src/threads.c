#include "../inc/header.h"

void *th_connect_to_server(GtkWidget *widget, gpointer data) {
// --- Init client ---
	UNUSED(widget);
	client_t *client = (client_t *)data;

// --- Connect to Server ---
	/*pthread_t server_connection_handler;
    printf("th_connect_to_server &client: %p\n", (void *)&client);
    //printf("th_connect_to_server addr: %p\n", info);
	if(pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)&client) != 0){
		perror("ERROR: pthread\n");
		return NULL;
	}*/
	// Add ip and port check when clicked on "Connect"
	// If ip or port is incorrect, show message "IP or PORT is incorrect. Try again"(or smth like that)
	//printf("th_connect_to_server client addr: %p\n", (void *) client);

	/* Добавить здесь поверку айпи и порта, перед добаволением к клиенту
	* В случае успешной проверки, добавить айпи и порт к инфе о клиенте
	* Отдельная функция, а не init_client()
	* В случае провала проверки, вывести предупреждение об этом и предложить ввести данные снова
	* После этого, попробовать подключиться к серверу по предложенным данным
	* Если не успешно, то вывести предупреждение об этом и предложить пользователю попробовать еще раз
	*/
	/*if (argc != 3) {
		printf("Usage: %s <ipv4> <port>\n", argv[0]);
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
	}*/

	init_client(client, ipv_str, port_str);
	//while(1) {
	if (client->is_connected == 0) {
        //init_client(info, ipv_str, port_str);
		close(client->sockfd);
		client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("Trying to connect to server\n");
		int err = connect(client->sockfd, (struct sockaddr *)&client->address, sizeof(client->address));
		if (err == -1) {
			printf("ERROR: connect\n");
			close(client->sockfd);
			sleep(5);
		}
		else {

			printf("Connected!\n");
			//send(info->sockfd, info->name, NAME_SZ, 0);
			//printf("Your name: \"%s\"\n", info->name);
			//printf("=== WELCOME TO THE CHATROOM ===\n");
			client->is_connected = 1;
		}

	}

    while (client->is_connected == 0) {}

    printf("client name: %s\n", client->name);
    printf("client is_connected: %d\n", client->is_connected);
    printf("client exit: %d\n", client->exit);
// --- Message and command queue threads ---

	/*struct msg_q *msg_q_front = NULL;
	struct cmd_q *cmd_q_front = NULL;

	// -- MODULE 3 --
	struct send_msg_info_s *send_msg_info = (struct send_msg_info_s *)malloc(sizeof(struct send_msg_info_s));
	send_msg_info->client = client;

	pthread_t send_msg_thread;
	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)send_msg_info) != 0){
		perror("ERROR: pthread\n");
	    return NULL;
	}

	// -- MODULE 1 --
	struct recv_msg_info_s *recv_msg_info = (struct recv_msg_info_s *)malloc(sizeof(struct recv_msg_info_s));
	recv_msg_info->client = client;
	recv_msg_info->msg_q_front = &msg_q_front;
	recv_msg_info->cmd_q_front = &cmd_q_front;

	pthread_t recv_msg_thread;
	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)recv_msg_info) != 0){
		perror("ERROR: pthread\n");
		return NULL;
	}

	// -- MODULE 4 --
	struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->client = client;
	process_cmd_info->cmd_q_front = &cmd_q_front;
	init_funcs(process_cmd_info->arr_cmd_func);

	pthread_t th_process_cmd;
	if(pthread_create(&th_process_cmd, NULL, process_cmd, (void*)process_cmd_info) != 0){
		perror("ERROR: pthread\n");
		return NULL;
	}

    while(1) {
        if (is_exit)
            printf("Bye!");
    }
// --- Checking for client exit ---

	close(client->sockfd);*/
	/*pthread_join(send_msg_thread, NULL);
	pthread_join(recv_msg_thread, NULL);
	pthread_join(th_process_cmd, NULL);*/
    close(client->sockfd);
	pthread_mutex_destroy(&client->mutex);

    return NULL;
}
