#include "../inc/header.h"


int main(int argc, char **argv) {

// --- Checking IP & Port No ---

    static client_t client;
    client_t *p_client = (client_t *)malloc(sizeof(client_t *));
    p_client = &client;

    /* По максимуму надо уменьшить мейн и разнести все по функциям
    * Функция, которая инициализирует потоки
    * Функция, которая инициализирует интерфейс
    */

    printf("main client: %p\n", (void *)&client);
    init_interface(&builder, &window, &argc, &argv, (gpointer) p_client);

// --- Message and command queue threads ---
	struct msg_q *msg_q_front = NULL;
	struct cmd_q *cmd_q_front = NULL;

	// -- MODULE 3 --
	struct send_msg_info_s *send_msg_info = (struct send_msg_info_s *)malloc(sizeof(struct send_msg_info_s));
	send_msg_info->client = &client;

	pthread_t send_msg_thread;
	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)send_msg_info) != 0){
		perror("ERROR: pthread\n");
	    return 1;
	}

	// -- MODULE 1 --
	struct recv_msg_info_s *recv_msg_info = (struct recv_msg_info_s *)malloc(sizeof(struct recv_msg_info_s));
	recv_msg_info->client = &client;
	recv_msg_info->msg_q_front = &msg_q_front;
	recv_msg_info->cmd_q_front = &cmd_q_front;

	pthread_t recv_msg_thread;
	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)recv_msg_info) != 0){
		perror("ERROR: pthread\n");
		return 1;
	}

	// -- MODULE 4 --
	struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->client = &client;
	process_cmd_info->cmd_q_front = &cmd_q_front;
	init_funcs(process_cmd_info->arr_cmd_func);

	pthread_t th_process_cmd;
	if(pthread_create(&th_process_cmd, NULL, process_cmd, (void*)process_cmd_info) != 0){
		perror("ERROR: pthread\n");
		return 1;
	}
    gtk_main();
    client.exit = 1;
    printf("Bye!\n");
// --- Checking for client exit ---

	close(client.sockfd);
	pthread_join(send_msg_thread, NULL);
	pthread_join(recv_msg_thread, NULL);
	pthread_join(th_process_cmd, NULL);
	pthread_mutex_destroy(&client.mutex);

	exit(0);
	return EXIT_SUCCESS;
}
