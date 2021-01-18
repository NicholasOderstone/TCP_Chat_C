#ifndef HEADER_H
#define HEADER_H

/* INCLUDES */
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
    #include <netdb.h>

    /* MODULE_ONE */
    #include <fcntl.h>
//////////////////////////

/* DEFINES */
    #define MAX_CLIENTS 100
    #define BUFFER_SZ 2048
    #define LENGTH 2048

//////////////////////////

/* STRUCTURES */

    /* Handles all neccesary info about client */
    typedef struct{
        struct sockaddr_in address; /* Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET) */
        int sockfd;
        int uid;
        char name[32];
        int leave_flag;
    } client_t; 

    /* Handles all neccessary info about server*/
    typedef struct
    {
        char *ipv4; /* IP in char* format. Standard 127.0.0.1*/ 
        int port; /* Port in int format*/
        struct sockaddr_in address; /*Server IP, Port and ip format */
        int listenfd; /* Main server socket*/
        int uid; /* Used to set id for new clients*/
        client_t **clients; /* Array of clients*/
        pthread_mutex_t clients_mutex; /* Main server mutex*/
        pthread_t tid; /* Pthread to handle connections */

        _Atomic unsigned int cli_count; /* Client count. _Atomic is used as a built-in mutex */

    } server_info_t; 

    /* Buffer that is used to transfer info to the new thread*/
    typedef struct {
        server_info_t *serv_inf; /* Server info*/
        int uid; /* uid of client which connection is handled in this thread*/ 
        client_t *client;
    } buff_t; 


    /* MODULE_ONE */
    pthread_mutex_t lock;
    int leave_flag;

    struct command {
        char *command;
        char *params;
    };

    struct msg_q {
        char *data;
        struct msg_q *link;
    } *msg_front;

    struct cmd_q {
        struct command data;
        struct cmd_q *link;
    } *cmd_front;

    


//////////////////////////

/* FUNCTIONS */

    /* add "> " at the beginning of the new line*/
    void str_overwrite_stdout();
    /* trim /n*/
    void str_trim_lf (char* arr, int length); 
    /* Print client ipv4 address*/ 
    void print_client_addr(struct sockaddr_in addr);
    /* Add client to the clients array*/
    void client_add(client_t *cl, server_info_t *serv_inf);
    /* Remove client from the clients array*/
    void client_remove(int uid, server_info_t *serv_inf);
    /* Send message *s to all clients exept sender */
    void send_message(char *s, int uid, server_info_t *serv_inf);
    /* Handle all communication with the client */
    void *handle_client(void *arg);

    /* MODULE_ONE */
    void to_msg_q(char *data); // Insert the message into the message queue
    void to_cmd_q(struct command data); // Insert the command into the command queue
    void move_msg_q(); // Delete the first elememt from the message queue
    void move_cmd_q(); // Delete the first elememt from the command queue

    char *take_fst_msg_in_q();
    struct command take_fst_cmd_in_q();
    char *mx_strnew(const int size);

    struct command msg_to_cmd(char *msg);
    void *read_msg(void *arg);


    /* COMMANDS */


//////////////////////////

#endif
