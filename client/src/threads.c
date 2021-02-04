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

    return NULL;
}

void *init_threads(void *data) {

// --- Message and command queue threads ---
	client_t *client = (client_t *)data;
    static struct msg_q *msg_q_front = NULL;
	static struct cmd_q *cmd_q_front = NULL;

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
	while (1) {
		if (client->exit == 1) {
			pthread_join(recv_msg_thread, NULL);
			pthread_join(th_process_cmd, NULL);
			break;
		}
	}

	int ret_val = 1;
	printf("-- Init threads thread terminated --\n");
	pthread_exit(&ret_val);
	return NULL;
}
