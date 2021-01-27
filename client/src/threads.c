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

	/* Добавить здесь поверку айпи и порта, перед добаволением к клиенту
	* В случае успешной проверки, добавить айпи и порт к инфе о клиенте
	* Отдельная функция, а не init_client()
	* В случае провала проверки, вывести предупреждение об этом и предложить ввести данные снова
	* После этого, попробовать подключиться к серверу по предложенным данным
	* Если не успешно, то вывести предупреждение об этом и предложить пользователю попробовать еще раз
	*/

	while (client->is_connected == 0) {}

    return NULL;
}


void init_threads(client_t *client) {
	printf("init_threads client: %p\n", (void *)client);
	// --- Message and command queue threads ---
	struct msg_q *msg_q_front = NULL;
	struct cmd_q *cmd_q_front = NULL;
	printf("init_threads front_addr: %p\n", (void *)msg_q_front);

	// -- MODULE 3 --
	struct send_msg_info_s *send_msg_info = (struct send_msg_info_s *)malloc(sizeof(struct send_msg_info_s));
	send_msg_info->client = client;

	pthread_t send_msg_thread;
	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)send_msg_info) != 0){
		perror("ERROR: pthread\n");
	    return;
	}

	// -- MODULE 1 --
	struct recv_msg_info_s *recv_msg_info = (struct recv_msg_info_s *)malloc(sizeof(struct recv_msg_info_s));
	recv_msg_info->client = client;
	recv_msg_info->msg_q_front = &msg_q_front;
	recv_msg_info->cmd_q_front = &cmd_q_front;
	printf("init_threads front_addr: %p\n", (void *)*recv_msg_info->msg_q_front);

	pthread_t recv_msg_thread;
	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)recv_msg_info) != 0){
		perror("ERROR: pthread\n");
		return;
	}

	// -- MODULE 4 --
	/*struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->client = client;
	process_cmd_info->cmd_q_front = &cmd_q_front;
	init_funcs(process_cmd_info->arr_cmd_func);

	pthread_t th_process_cmd;
	if(pthread_create(&th_process_cmd, NULL, process_cmd, (void*)process_cmd_info) != 0){
		perror("ERROR: pthread\n");
		return;
	}
	while(1) {
		if (client->exit == 1) {
			pthread_join(send_msg_thread, NULL);
			pthread_join(recv_msg_thread, NULL);
			pthread_join(th_process_cmd, NULL);
			break;
		}
	}*/
	return;
}

/*void *init_threads(GtkWidget *widget, gpointer data) {
	UNUSED(widget);
	client_t *client = (client_t *)data;
	printf("init_threads client: %p\n", (void *)client);
	// --- Message and command queue threads ---
	struct msg_q *msg_q_front = NULL;
	struct cmd_q *cmd_q_front = NULL;
	printf("init_threads front_addr: %p\n", (void *)msg_q_front);

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
	printf("init_threads front_addr: %p\n", (void *)*recv_msg_info->msg_q_front);

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
		if (client->exit == 1) {
			pthread_join(send_msg_thread, NULL);
			pthread_join(recv_msg_thread, NULL);
			pthread_join(th_process_cmd, NULL);
			break;
		}
	}
	return NULL;
}*/
