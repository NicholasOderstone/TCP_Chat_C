#ifndef HEADER_H
#define HEADER_H

//////////////////////////
// Macroses
	#define UNUSED(x) (void)(x)

//////////////////////////
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
	#include <sqlite3.h>
	#include <time.h>

    #include "interface.h"

//////////////////////////

// DEFINES
	#define MAX_CLIENTS 100
	#define MAX_CHATS 1000
	#define BUFFER_SZ 2048
	#define NAME_SZ 32
	#define AMOUNT_OF_CMD 9
//////////////////////////

// STRUCTURES

// --- GTK structure ---
	typedef struct {
		GtkTextView *view ;
		GtkTextBuffer *buffer;
		GtkTextIter start;
		GtkTextIter end;
		GtkTextMark* mark;
		GtkListBox *box_message;
		GtkListBox *box_chat_list;
		GtkWidget *chat[MAX_CHATS];
		GtkButtonBox *b_box;
		GtkWidget *cancel_b;
		GtkWidget *edit_b;
		GtkWidget *delet_b;
		gint row_num_list_gtk;
		gint root_x ;
		gint root_y ;
	} gtk_utils_t;
// --- CHAT_LIST ---
	typedef struct chat_info {
		int chat_id;
		char *chat_name;
		struct chat_info *next;
	} chat_info_t;

// --- MSG_ID_QUEUE ---
	typedef struct msg_id_q_s {
		int msg_id;
		struct msg_id_q_s *next;
	} msg_id_q;

// --- CLIENT ---
	typedef struct{
		struct sockaddr_in address; // Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET)
		int sockfd;
		int uid;
		char *login;
		char *pass;
		gtk_utils_t *m;
		int is_connected;
		int exit;
		int active_chat_id;
		int last_chat_index;
		chat_info_t *chat_list_head;
		msg_id_q *msg_id_q_head;
		pthread_mutex_t mutex;
	} client_t;

// --- REQUEST structures ---
	typedef struct {
		chat_info_t *chat;
		client_t *client;
	} get_messages_request_s;

	typedef struct {
		char *new_chat_name;
		client_t *client;
	} new_chat_request_s;

	typedef struct {
		int msg_id;
		int chat_id;
		client_t *client;
	} del_msg_request_s;

	typedef struct {
		int chat_id;
		client_t *client;
	} del_chat_request_s;

	typedef struct {
		int msg_id;
		char *new_text;
		client_t *client;
	} edit_msg_request_s;

	typedef struct {
		int chat_id;
		char *username;
		client_t *client;
	} add_user_to_chat_request_s;

// --- msg, command, cmd function ---
	typedef struct received_s {
		client_t *client;
		int msg_id;
		int chat_id;
		char message[BUFFER_SZ];
		char time[BUFFER_SZ];
		char sender_name[NAME_SZ];
		char is_special[2];
	}	received_messages;

	typedef struct {
	    char *command;
	    char *params;
	} command;

	typedef struct {
	    char *name;
	    void (*func)(char *params, void *p);
	} cmd_func;

// --- QUEUES ---
	struct msg_q {
	    char *data;
	    struct msg_q *link;
	};

	struct cmd_q {
	    command data;
	    struct cmd_q *link;
	};

// --- THREAD INFO structures ---
	struct recv_msg_info_s {
		client_t *client;
		struct msg_q **msg_q_front;
		struct cmd_q **cmd_q_front;
	};

	struct process_cmd_info_s {
		client_t *client;
		struct cmd_q **cmd_q_front;
		cmd_func arr_cmd_func[AMOUNT_OF_CMD];
	};

	struct read_msg_info_s {
		client_t *client;
		struct msg_q **msg_q_front;
		pthread_mutex_t lock;
	};

	struct make_cmd_info_s {
		client_t *client;
		struct msg_q **msg_q_front;
		struct cmd_q **cmd_q_front;
		pthread_mutex_t lock;
	};

	typedef struct {
		chat_info_t *chat;
		client_t *client;
		int counter;
	} chat_show_info_s;

//////////////////////////

// FUNCTIONS
	// Add "> " at the beginning of the new line
	void str_overwrite_stdout();
	// Trim \n
	void str_trim_lf (char* arr, int length);
	// Input client name (with correctness check)
	void get_client_name(char *name);
	// Init client info and settings
	void init_client(client_t *client, char *ip, char *port);
	// Init command functions
	void init_funcs(cmd_func arr_cmd_func[]);
	char *mx_strnew(const int size);


// --- THREADS ---
	void *init_threads(void *client);
	// Handles recieving messages
	void *recv_msg_handler(void *arg);
	// Handles reading messages
	void *read_msg(void *p);
	// Handles making command from message
	void *make_cmd(void *arg);
	// Handles processing recieved commands
	void *process_cmd(void *arg);
	// Handles connection to server
	int connect_to_server();
	// Handles reconnect
	void *reconnect_to_server(void *cnct_inf);

// --- QUEUES ---
	// Inserts the message into the message queue
	void to_msg_q(char *data, struct msg_q **msg_q_front, pthread_mutex_t msg_lock);
	// Inserts the command into the command queue
	void to_cmd_q(command data, struct cmd_q **cmd_q_front, pthread_mutex_t cmd_lock);

	void to_msg_id_q(int msg_id, msg_id_q **msg_id_q_head);

	void clear_msg_id_q(msg_id_q **msg_id_q_head);

	void display_msg_id_q(msg_id_q **msg_id_q_head);

	void del_elem_msg_id_q(msg_id_q **msg_id_q_head, int msg_id);

	int get_index_by_msg_id(msg_id_q **msg_id_q_head, int msg_id);

	// Deletes the first elememt from the message queue
	void move_msg_q(struct msg_q **msg_q_front, pthread_mutex_t msg_lock);
	// Deletes the first elememt from the command queue
	void move_cmd_q(struct cmd_q **cmd_q_front);
	// Takes first message from msg_q
	char *take_fst_msg_in_q(struct msg_q **msg_q_front);
	// Takes first command from cmd_q
	command take_fst_cmd_in_q(struct cmd_q **cmd_q_front);

// --- CHAT LIST ---
	// Inserts the chat into the chat list
	void to_chat_list(int chat_id, char *chat_name, chat_info_t **chat_list_head);
	// Displays the chat list
	void display_chat_list(chat_info_t **chat_list_head);
	// Gets chat list size
	int chat_list_size(chat_info_t **chat_list_head);

	int get_index_by_chat_id(chat_info_t **chat_list_head, int chat_id);

	int is_chat_exists(chat_info_t **chat_list_head, int chat_id);

	void del_elem_chat_list(chat_info_t **chat_list_head, int chat_id);

// --- REQUESTS ---
	void get_msg_request(GtkWidget *widget, gpointer data);
	void new_chat_request(GtkWidget *widget, gpointer data);
	void delete_msg_request(del_msg_request_s *delete_msg_request);
	void leave_chat_request(GtkWidget *widget, gpointer data);
	void edit_msg_request(GtkWidget *widget, gpointer data);
	void add_user_to_chat_request(GtkWidget *widget, gpointer data);

// --- SWITCHES ---
	void init_switches(void);
	void func_login(GtkWidget *widget, gpointer data);
	void func_register(GtkWidget *widget, gpointer data);

// --- VALIDATES ---
	int validate_number(char *str);
	int validate_ip(char *ip);
	int validate_port(char *port);

// --- UTILITY ---
	command msg_to_cmd(char *msg);
	char *cmd_to_msg(command cmd);
	char *take_param(char *params, int number);
	char *itoa(int val, int base);

	void send_cmd(command cmd, client_t *client);
	void analyse_cmd(command fst_cmd, cmd_func function, client_t *client);

//////////////////////////

// GLOBAL VARIABLES
	int sw_login;
	int sw_register;

	pthread_mutex_t chat_lock;
	pthread_mutex_t add_chat_lock;
	pthread_mutex_t msg_id_lock;

//////////////////////////

#endif
