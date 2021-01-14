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
	#include <signal.h>
//////////////////////////

// DEFINES
	#define MAX_CLIENTS 100
	#define BUFFER_SZ 2048
	#define LENGTH 2048
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
//////////////////////////

// GLOBAL VARIABLES sorry...
	volatile sig_atomic_t ctrl_c_and_exit_flag;
//////////////////////////

// FUNCTIONS
	// add "> " at the beginning of the new line
	void str_overwrite_stdout();
	// trim \n
	void str_trim_lf (char* arr, int length);
	// Checks whether client left using CTRL+C
	void catch_ctrl_c_and_exit(int sig);
	// Handle sending messages
	void *send_msg_handler(void *arg);
	// Handle recieving messages
	void *recv_msg_handler(void *arg);
//////////////////////////

#endif
