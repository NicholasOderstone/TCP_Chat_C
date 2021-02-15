#include "../inc/header.h"

void str_overwrite_stdout() {
  // printf("%s", "> ");
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





void get_client_name(char *name) {
	// printf("Name must be less than 32 and more than 2 characters.\n");
	while (1) {
		// printf("Please enter your name: ");
		fflush(stdin);
		fgets(name, NAME_SZ, stdin);
		str_trim_lf(name, strlen(name));
		if (strlen(name) < 2 || strlen(name) > NAME_SZ){
			// printf("Name must be less than 32 and more than 2 characters.\n");
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
    client->last_chat_index = -1;
    client->active_chat_id = -1;
	pthread_mutex_init(&client->mutex, NULL);
    client->exit = 0;
}
