#include "../inc/header.h"

int connect_to_server(client_t *info, int argc, char** argv) {
// --- Init client --

	if(argc != 3) {
		printf("Usage: %s <ipv4> <port>\n", argv[0]);
		return 1;
	}

	char *ip = argv[1];
	char *port = argv[2];

    if (validate_ip(ip) != 1) {
		printf("<ipv4> \"%s\" is incorrect \n", ip);
		return 1;
	}

	if (validate_port(port) != 1) {
		printf("<port> \"%s\" is incorrect \n", port);
		return 1;
	}

	init_client(info, ip, port);
	while(1) {
        if(info->exit == 1) {
			break;
		}
		if (info->is_connected == 0) {
            // gtk_spinner_start(connection_spin);
			close(info->sockfd);
			info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
			// printf("Trying to connect to server\n");
			int err = connect(info->sockfd, (struct sockaddr *)&info->address, sizeof(info->address));
			if (err == -1) {
				// printf("ERROR: connect\n");
				close(info->sockfd);
				sleep(3);
			}
			else {
                // gtk_spinner_stop (connection_spin);
				// printf("Connected!\n");
				info->is_connected = 1;
				break;
			}
		}
		sleep(3);
	}


    return 0;
}

void *init_threads(void *data) {

// --- Message and command queue threads ---
	client_t *client = (client_t *)data;
    static struct msg_q *msg_q_front = NULL;
	static struct cmd_q *cmd_q_front = NULL;

	// --- Connect to Server ---
	pthread_t server_connection_handler;
	if (pthread_create(&server_connection_handler, NULL, reconnect_to_server, (void*)client) != 0){
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
	while (1) {
		// printf("-- Init threads");
		sem_wait(sem_exit);
		if (client->exit == 1) {
			pthread_cancel(th_process_cmd);
			// printf("-- Init threads -- th_process_cmd");
			pthread_cancel(server_connection_handler);
			// printf("-- Init threads -- server_connection_handler");
			pthread_join(recv_msg_thread, NULL);
			// printf("-- Init threads -- recv_msg_thread");
			break;
		}
	}

	int ret_val = 1;
	// printf("-- Init threads thread terminated --\n");
	pthread_exit(&ret_val);
	return NULL;
}

void send_client_info_to_server(client_t *client) {
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<LOGIN> <%s> <%s>", client->login, client->pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
	// printf("%s\n", buffer);
    bzero(buffer, BUFFER_SZ);
    while (sw_login == -1) { }
    switch(sw_login) {
        case 0:
            sw_login = -1;
            break;
        case 1:
            // printf("## INCORRECT_LOGIN\n");
            sw_login = -1;
            break;
        case 2:
            // printf("## INCORRECT_PASS\n");
            sw_login = -1;
            break;
        default:
            break;
    }
}

void *reconnect_to_server(void *cnct_inf) {
	client_t *info = (client_t *)cnct_inf;
	// printf("Reconnect is ready\n");
	while(1) {
		sem_wait(sem_reconnect);
        if(info->exit == 1) {
			break;
		}
		while (info->is_connected == 0) {
			if(info->exit == 1) {
				break;
			}
            gtk_spinner_start(connection_spin);
			close(info->sockfd);
			info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
			// printf("Trying to reconnect to server\n");
			int err = connect(info->sockfd, (struct sockaddr *)&info->address, sizeof(info->address));
			if (err == -1) {
				// printf("ERROR: connect\n");
				close(info->sockfd);
				sleep(3);
			}
			else {
                gtk_spinner_stop (connection_spin);
				// printf("Connected!\n");
				info->is_connected = 1;
				send_client_info_to_server(info);
			}

		}
		sleep(3);
	}
    int ret_val = 1;
	// printf("-- Connect to server thread terminated --\n");
	pthread_exit(&ret_val);
	return NULL;
}






/* 
 * Dorabotat` napil`nikom.
 * 15.02.2021
 * Odarchenko M. S. 
 * Asemiletov A. I.
 * Kuleshova D. A. 
 * Botezat V. K.
 * Ivanov M. M.
 * 
 */


