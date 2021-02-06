#include "../inc/header.h"

void str_overwrite_stdout() {
  printf("%s", "> ");
  fflush(stdout);
}

void str_trim_lf(char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void send_client_info_to_server(client_t *client) {
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<LOGIN> <%s> <%s>", client->login, client->pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
	printf("%s\n", buffer);
    bzero(buffer, BUFFER_SZ);
    while (sw_login == -1) { }
    switch(sw_login) {
        case 0:
            sw_login = -1;
            break;
        case 1:
            printf("## INCORRECT_LOGIN\n");
            sw_login = -1;
            break;
        case 2:
            printf("## INCORRECT_PASS\n");
            sw_login = -1;
            break;
        default:
            break;
    }
}

void *connect_to_server(void *cnct_inf) {
	client_t *info = (client_t *)cnct_inf;
	printf("Reconnect is ready\n");
    // init_client(info, ipv_str, port_str);
	while(1) {
        if(info->exit == 1) {
			break;
		}
		if (info->is_connected == 0) {
			printf("Trying to reconnect\n");
            gtk_spinner_start(connection_spin);
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
                gtk_spinner_stop (connection_spin);
				printf("Connected!\n");
				info->is_connected = 1;
				send_client_info_to_server(info);
			}
		}
	}
    int ret_val = 1;
	printf("-- Connect to server thread terminated --\n");
	pthread_exit(&ret_val);
	return NULL;
}

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
}

void init_client(client_t *client, char *ip, char *port) {
    client->address.sin_family = AF_INET;
	client->address.sin_addr.s_addr = inet_addr(ip);
	client->address.sin_port = htons(atoi(port));
	client->is_connected = 0;
	client->login = NULL;
	client->pass = NULL;
    client->last_chat_index = 0;
	pthread_mutex_init(&client->mutex, NULL);
    //get_client_name(client->name);
    strcpy(client->name, "");
    client->exit = 0;
}
