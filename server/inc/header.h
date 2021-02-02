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
    #include <fcntl.h>
    #include <sys/stat.h>
    

    /* DATA_BASE */
    #include <stdlib.h>
    #include <sqlite3.h>
    #include <math.h>

/* DEFINES */
    #define MAX_CLIENTS 100
    #define BUFFER_SZ 2048
    #define NAME_SZ 32
    #define AMOUNT_OF_CMD 4


/* STRUCTURES */

    /* Handles all neccesary info about client */
    typedef struct{
        struct sockaddr_in address; /* Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET) */
        int sockfd;
        int uid;
        char name[32];
        int exit_flag;
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


    pthread_mutex_t cmd_lock; //Mutex for commands

    //Structure for commands
    struct command {
        char *command;
        char *params;
    };

    //A queue for commands
    struct cmd_q {
        struct command data;
        struct cmd_q *link;
    };

    //Structure to pass client and message queue for read_msg Thread
	struct read_msg_info_s {
		client_t *client;
		//struct msg_q **msg_q_front;
        struct cmd_q **cmd_q_front;
	};

    //Structure that stores cmd function name and pointer to this function
    typedef struct {
	    char *name;
	    void (*func)(char *params, buff_t *serv_inf);
	} cmd_func;

    //Structure to pass command queue and array of pointers to functions
    struct process_cmd_info_s {
		struct cmd_q **cmd_q_front;
		cmd_func arr_cmd_func[AMOUNT_OF_CMD];
        buff_t *buff_m;
	};



//////////////////////////

/* FUNCTIONS */

    /* ORIGINAL FUNCTIONS */

    /* Add client to the clients array*/
    void client_add(client_t *cl, server_info_t *serv_inf);
    /* Remove client from the clients array*/
    void client_remove(int uid, server_info_t *serv_inf);
    /* Send message *s to all clients exept sender */
    void send_message(char *s, int uid, server_info_t *serv_inf);


    // --- Thread functions ---

    /* Handle all communication with the client */
    void *handle_client(void *arg);
    /* Read data from socket and move to message queue */
    void *read_msg(void *arg);
    // Handles processing recieved commands
	void *process_cmd(void *arg);




    // --- Queue functions ---

    /* Insert the command into the command queue */
    void to_cmd_q(struct command data, struct cmd_q **cmd_q_front);
    /* Delete the first elememt from the command queue */
    void move_cmd_q(struct cmd_q **cmd_q_front);
    /* Return the first command of the queue */
    struct command take_fst_cmd_in_q(struct cmd_q **cmd_q_front);


    // --- Utility functions ---

    /* Make new string */
    char *mx_strnew(const int size);
    /* add "> " at the beginning of the new line*/
    void str_overwrite_stdout();
    /* trim /n*/
    void str_trim_lf (char* arr, int length);
    /* Print client ipv4 address*/
    void print_client_addr(struct sockaddr_in addr);
    /* CONBERT INT TO CHAR* */
    char* itoa(int num, char* buffer, int base);
    /* DELETE EVERYONE FROM DB */
    void Delete_From_DB();


    // --- Functions that interact with messages and commands ---

    /* Convert message to command */
    struct command msg_to_cmd(char *msg);
    /* Convert command to message */
    char *cmd_to_msg(struct command cmd);
    /* Send command to the client */
    void send_cmd(struct command cmd, client_t *client);


    // --- Functions that interact with command functions ---

    /* Initialize command functions */
    void initialize_functions();
    /* Get parametr 1 */
    char *param_1(char *params);
    /* Get parametr 2 */
	char *param_2(char *params);
    /* Get parametr 3 */
	char *param_3(char *params);
    /* Get parametr 4 */
	char *param_4(char *params);
    /* Get parametr 5 */
	char *param_5(char *params);


    // --- Data Base functions ---
    void initDB();
    char* getOneUser(int id, char* rez);
    void insertUser(char* login, char* password, char* nick, char* status);
    int getIdUserByUserName(char* login);
    char* getAllUsers(char* rez);
    void deleteUser(char* id);
    char* getUserName(int id, char* rez);
    char* getUserPassword(int id, char* rez);
    char* getUserChats(int id, char* rez);
    void insertChat(char* name, char* description);
    void insertInUserInChats(int user_id, int chat_id);
    int getIdChatByName(char* chat);
    char* getOneChats(int id, char* rez);
    char* getChatName(int id, char* rez);
    void deleteChat(char* id);
    void deleteFromChat(int user_id, int chat_id);


    // --- Daemonize ---
    void daemonize();

    pthread_mutex_t send_cmd_lock;

#endif
