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
	#define NAME_SZ 32
	#define AMOUNT_OF_CMD 11
//////////////////////////

// STRUCTURES
	// Handles all neccesary info about client
	typedef struct{
		struct sockaddr_in address; // Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET)
		int sockfd;
		int uid;
		char name[32];

		int is_connected;
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
	// Add "> " at the beginning of the new line
	void str_overwrite_stdout();
	// Trim \n
	void str_trim_lf (char* arr, int length);
	// Checks whether client left using CTRL+C
	void catch_ctrl_c_and_exit(void);
	// Validate functions
	int validate_number(char *str);
	int validate_ip(char *ip);
	int validate_port(char *port);
	// Input client name (with correctness check)
	void get_client_name(char *name);
	// Init client info and settings
	void init_client(client_t *client, char *ip, char *port);
	// Init command functions
	void init_funcs(void);
	char *mx_strnew(const int size);

	// --- Thread functions ---

	// Handles sending messages
	void *send_msg_handler(void *arg);
	// Handles recieving messages
	void *recv_msg_handler(void *arg);
	// Handles reconnect
	void *connect_to_server(void *cnct_inf);
	// Handles reading messages
	void *read_msg(void *p);
	// Handles making command from message
	void *make_cmd();
	// Handles processing recieved commands
	void *process_cmd();

	// --- Queue functions ---

	// Inserts the message into the message queue
	void to_msg_q(char *data);
	// Inserts the command into the command queue
	void to_cmd_q(command data);
	// Deletes the first elememt from the message queue
	void move_msg_q();
	// Deletes the first elememt from the command queue
	void move_cmd_q();
	// Takes first message from msg_q
	char *take_fst_msg_in_q();
	// Takes first command from cmd_q
	command take_fst_cmd_in_q();


	void send_cmd(command cmd, client_t *client);

	// --- Utility functions ---

	command msg_to_cmd(char *msg);
	char *cmd_to_msg(command cmd);
	char *param_1(char *params);
	char *param_2(char *params);
	char *param_3(char *params);
	char *param_4(char *params);
	char *param_5(char *params);

//////////////////////////

#endif
