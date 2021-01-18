#ifndef HEADER_H
#define HEADER_H

// INCLUDES
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>
	#include <pthread.h>
	#include <sys/types.h>
	#include <ctype.h>

//////////////////////////

// DEFINES
	#define MAX_CLIENTS 100
	#define BUFFER_SZ 2048
	#define LENGTH 2048
	#define AMOUNT_OF_CMD 11
//////////////////////////

// STRUCTURES
// Handles all neccesary info about client
	typedef struct{
		struct sockaddr_in address; // Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET)
		int sockfd;
		int uid;
		char name[32];

		pthread_mutex_t mutex;
	} client_t;

	typedef struct {
	    char *command;
	    char *params;
	} command;

	typedef struct {
	    char *name;
	    void (*func)(char *params);
	} cmd_func;

	typedef struct {
		client_t *client;
		char *message;
	} msg_t;

	struct msg_q {
	    char *data;
	    struct msg_q *link;
	} *msg_front;

	struct cmd_q {
	    command data;
	    struct cmd_q *link;
	} *cmd_front;


//////////////////////////

// GLOBAL VARIABLES
	int ctrl_c_and_exit_flag;
	pthread_mutex_t lock;
	cmd_func arr_cmd_func[AMOUNT_OF_CMD];
//////////////////////////

// FUNCTIONS
	// add "> " at the beginning of the new line
	void str_overwrite_stdout();
	// trim \n
	void str_trim_lf (char* arr, int length);
	// Checks whether client left using CTRL+C
	void catch_ctrl_c_and_exit(void);
	// Handle sending messages
	void *send_msg_handler(void *arg);
	// Handle recieving messages
	void *recv_msg_handler(void *arg);
	int validate_number(char *str);
	int validate_ip(char *ip);
	int validate_port(char *port);
	// Insert the message into the message queue
	void to_msg_q(char *data);
	// Insert the command into the command queue
	void to_cmd_q(command data);
	// Delete the first elememt from the message queue
	void move_msg_q();
	void move_cmd_q();

	void *read_msg(void *p);
	void *make_cmd();
	void *process_cmd();
	char *take_fst_msg_in_q();
	command take_fst_cmd_in_q();
	char *mx_strnew(const int size);

	void send_cmd(command cmd, client_t *client);
	command msg_to_cmd(char *msg);
	char *cmd_to_msg(command cmd);

	void init_funcs(void);

	char *param_1(char *params);
	char *param_2(char *params);
	char *param_3(char *params);
	char *param_4(char *params);
	char *param_5(char *params);

//////////////////////////

#endif
