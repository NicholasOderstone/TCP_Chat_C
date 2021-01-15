#include "../inc/header.h"

int validate_number(char *str) {
   while (*str) {
      if(!isdigit(*str)){ //if the character is not a number, return false
         return 0;
      }
      str++; //point to next character
   }
   return 1;
}
int validate_ip(char *ip) { //check whether the IP is valid or not
   int num, dots = 0;
   char *ptr;
   if (ip == NULL)
      return 0;
      ptr = strtok(ip, "."); //cut the string using dor delimiter
      if (ptr == NULL)
         return 0;
   while (ptr) {
      if (!validate_number(ptr)) //check whether the sub string is holding only number or not
         
         return 0;
         num = atoi(ptr); //convert substring to number
         if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, "."); //cut the next part of the string
            if (ptr != NULL)
               dots++; //increase the dot count
         } else {
            return 0;
		 }
    }
    if (dots != 3) { //if the number of dots are not 3, return false
       return 0;
	}
      return 1;
}

int validate_port(char *port) {
	int port_len = strlen(port);
	if (port_len > 5 || port_len < 3) {
		return 0;
	}
	if (!validate_number(port)) {
		return 0;
	}
	return 1;
}

int main(int argc, char **argv){
	if(argc != 3){
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
	/* Socket settings*/
	client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	client.address.sin_family = AF_INET;
	client.address.sin_addr.s_addr = inet_addr(ip);
	client.address.sin_port = htons(atoi(port));
	pthread_mutex_init(&client.mutex, NULL);

	signal(SIGINT, catch_ctrl_c_and_exit);

	/* Name */
	printf("Name must be less than 32 and more than 2 characters.\n");
	while (1) {
		printf("Please enter your name: ");
		//fgets(client.name, 32, stdin);
		scanf("%31s", client.name);
		str_trim_lf(client.name, strlen(client.name));
		printf("Your name: \"%s\"\n", client.name);
		if (strlen(client.name) < 2){
			printf("Name must be less than 32 and more than 2 characters.\n");
		}
		else {
			break;
		}
	}

 	// Connect to Server
  	int err = connect(client.sockfd, (struct sockaddr *)&client.address, sizeof(client.address));
  	if (err == -1) {
		printf("ERROR: connect\n");
		return EXIT_FAILURE;
	}

	// Send name
	send(client.sockfd, client.name, 32, 0);

	printf("=== WELCOME TO THE CHATROOM ===\n");

	client_t *buff_client = (client_t *)malloc(sizeof(client_t));
	buff_client = &client;

	pthread_t send_msg_thread;
  if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)buff_client) != 0){
		printf("ERROR: pthread\n");
    return EXIT_FAILURE;
	}

	pthread_t recv_msg_thread;
  if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)buff_client) != 0){
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	while (1){
		if(ctrl_c_and_exit_flag){
			printf("\nBye\n");
			break;
    }
	}
	free(buff_client);
	close(client.sockfd);

	return EXIT_SUCCESS;
}
