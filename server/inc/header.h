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
	#include <semaphore.h>


    /* DATA_BASE */
    #include <stdlib.h>
    #include <sqlite3.h>
    #include <math.h>

/* DEFINES */
    #define MAX_CLIENTS 100
    #define BUFFER_SZ 2048
    #define NAME_SZ 32
    #define AMOUNT_OF_CMD 12
    #define MAX_CHAT_USERS 1024


/* STRUCTURES */

    /* Handles all neccesary info about client */
    typedef struct{
        struct sockaddr_in address; /* Stores ip (sin_addr.s_addr), port (sin_port) and ip format (sin_family = AF_INET) */
        int sockfd;
        int uid;
        char name[32];
        int exit_flag;
        int active_id_chat;
    } client_t;

    /* Handles all neccessary info about server*/
    typedef struct
    {
        char *ipv4; /* IP in char* format. Standard 127.0.0.1*/
        int port; /* Port in int format*/
        struct sockaddr_in address; /*Server IP, Port and ip format */
        int listenfd; /* Main server socket*/
        // int uid; /* Used to set id for new clients*/
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

    //Structure that stores cmd function name and pointer to this function
    typedef struct {
	    char *name;
	    void (*func)(char *params, buff_t *serv_inf);
	} cmd_func;


    //Structure to pass client and message queue for read_msg Thread
	struct read_msg_info_s {
		client_t *client;
		//struct msg_q **msg_q_front;
        sem_t *sem_cmd_q;
        struct cmd_q **cmd_q_front;
	};

    //Structure to pass command queue and array of pointers to functions
    struct process_cmd_info_s {
		struct cmd_q **cmd_q_front;
        sem_t *sem_cmd_q;
		cmd_func arr_cmd_func[AMOUNT_OF_CMD];
        buff_t *buff_m;
	};

    // DB structure
    typedef struct message_s {
        char chat_id[10];
        char msg_id[10];
        char sender[32];
        char text[BUFFER_SZ];
        char time[50];
        char is_read[2];
    } msg_t;

    
    typedef struct chat_s {
        char chat_id[10];
        char chat_name[32];
    } chat_t;


    typedef struct user_s {
        char user_id[10];
        char user_name[32];
    } user_t;


//////////////////////////

/* FUNCTIONS */

    /* ORIGINAL FUNCTIONS */

    /* Add client to the clients array*/
    int client_add(client_t *cl, server_info_t *serv_inf);
    /* Remove client from the clients array*/
    void client_remove(int uid, server_info_t *serv_inf);


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
    // void print_client_addr(struct sockaddr_in addr);
    /* CONBERT INT TO CHAR* */
    char* itoa(int num, char* buffer, int base);
    /* SEND TO ALL CHAT MEMBERS */
    void send_to_all_members(char *p_chat_id, struct command cmd, buff_t *Info);


    // --- Functions that interact with messages and commands ---

    /* Convert message to command */
    struct command msg_to_cmd(char *msg);
    /* Convert command to message */
    char *cmd_to_msg(struct command cmd);
    /* Send command to the client */
    void send_cmd(struct command cmd, client_t *client);
    /* Chat list */
    void chat_list(char *p_login, buff_t *Info);


    // --- Functions that interact with command functions ---

    /* Initialize command functions */
    void initialize_functions();
    // Получить выбранный по номеру параметр
    char *take_param(char *params, int number);


    // --- Data Base functions ---
    int initDB();
    char* getOneUser(int id, char* rez); // Получить всю инфу по выбранному пользователю (по id)
    int insertUser(char* login, char* password, char* nick, char* status); // Создать юзера
    int getIdUserByUserName(char* login); // Получить id юзера по логину юзера
    char* getIdUserByNick(char* nick, char* rez);
    char* getAllUsers(char* rez); // Получить всех пользователей
    void deleteUser(char* id); // Удалить выбранного пользователя с выбранный id
    char* getUserName(int id, char* rez); // Получить имя пользователя по id
    char* getUserPassword(int id, char* rez); // Получить пароль пользователя по id
    char* getUserChats(int id, char* rez); // Получить все чаты пользователя
    int insertChat(char* name, int creator_id, char* description); // Создать чат с именем и описанием
    void insertInUserInChats(int user_id, int chat_id); // Поместить выбранного пользователя в выбранный чат
    int getIdChatByName(char* chat); // Получить id чата по имени чата
    char* getOneChats(int id, char* rez); // Возвращает все поля выбранного чата
    char* getChatName(int id, char* rez); // Получить имя чата по id
    void deleteChat(char* id); // Удалить выбранный чат
    void deleteFromChat(int user_id, int chat_id); //Удалить выбранного пользователя с выбранног чата
    int insertMessage(int chat_id, int user_id, char* message, int date, char* is_read); // Поместить сообщение в выбранный чат
    char* getAllChats(); //Получить все чаты
    msg_t *pack_msg_from_chat(int id); // Some useful functions
    void deleteMessage(char* id); // Delete message
    void updateTextMessage(int id, char* text); // Edit message
    int createChat(int creator_id, char *name); // Create chat and add the creator
    void insertInUserInChats(int user_id, int chat_id); // Insert user in chat
    user_t *pack_chat_members(int id); // 
    void deleteChat(char* id); // Delete chat by chat_id
    char* getOwner_Id_By_Chat_Id(int id, char* rez); // Получить id создателя чата по id этого чата
    char* getChatName(int id, char* rez); // Получить имя чата  по id чата
    char* getChat_Id_By_Msg_Id(int id, char* rez); // Get chat_id by msg_id
    void deleteChat(char* id); // Delete chat by chat_id
    char* getOwner_Id_By_Chat_Id(int id, char* rez); // Получить id создателя чата по id этого чата
    void send_to_all_members_delete_special(struct command cmd, buff_t *Info, user_t **user, int k); // special edition for delete_chat
    char* getNickByUserName(char* login, char* rez); // get Nick by login
    chat_t *pack_user_chats(int id);
    void insertUSER_TO_CHAT(int user_id, int chat_id);
    void updateNick(int id, char* name);
    void updatePasswordUser(int id, char* name);
    int getTimeLastMsg(int id);
    int getLastMsgTime(int id);
    void send_to_all_members_send_special(char *p_chat_id, int msg_id,struct command cmd, buff_t *Info); // special edition for command send
    void setUNREAD(int chat_id, int user_id, int unread);
    int getUNREAD(int chat_id, int user_id);

    // --- Daemonize ---
    void daemonize();

    pthread_mutex_t send_cmd_lock;


#endif



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



