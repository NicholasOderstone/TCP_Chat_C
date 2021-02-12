#include "../inc/header.h"

// Отправить все пользователям
void send_to_all_members(char *p_chat_id, struct command cmd, buff_t *Info) {
	user_t *user[MAX_CLIENTS];
	int num_of_memb = 0;
	for(; 1; num_of_memb++ ) {
		user[num_of_memb] = pack_chat_members(atoi(p_chat_id));
		if(user[num_of_memb] == NULL) {
			break;
		}
	}
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i] != NULL){
				for(int j = 0; j < num_of_memb; j++) {
					if(user[j] != NULL){
						if(strcmp(user[j]->user_name, Info->serv_inf->clients[i]->name) == 0) {
							send_cmd(cmd, Info->serv_inf->clients[i]);
							break;
						}
					}
				}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}
// Отправить все пользователям special edition for delete
void send_to_all_members_delete_special(struct command cmd, buff_t *Info, user_t **user, int num_of_memb) {
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i] != NULL){
				for(int j = 0; j < num_of_memb; j++) {
					if(user[j] != NULL){
						if(strcmp(user[j]->user_name, Info->serv_inf->clients[i]->name) == 0) {
							send_cmd(cmd, Info->serv_inf->clients[i]);
							break;
						}
					}
				}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}
// Отправить все пользователям special edition for send
void send_to_all_members_send_special(char *p_chat_id, int msg_id, struct command cmd, buff_t *Info) {
	user_t *user[MAX_CLIENTS];
	int num_of_memb = 0;
	int chat_id = atoi(p_chat_id);

	for(; 1; num_of_memb++ ) {
		user[num_of_memb] = pack_chat_members(chat_id);
		if(user[num_of_memb] == NULL) {
			break;
		}
	}
	
	int is_online;
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int j = 0; j < num_of_memb; j++) {
		is_online = 0;
		int user_id = atoi(user[j]->user_id);
		printf("Sending msg to %s: %d\n", user[j]->user_name, user_id);

		for(int i=0; i<MAX_CLIENTS; ++i) { //общий массив пользователей онлайн
			if(Info->serv_inf->clients[i] != NULL && user[j] != NULL){ 

				if(strcmp(user[j]->user_name, Info->serv_inf->clients[i]->name) == 0) { // Если имена совпадают
					is_online = 1;
					printf("%s is online\n", user[j]->user_name);
					if(Info->serv_inf->clients[i]->active_id_chat == chat_id) { // Если чат активный
						printf("1\n");
						send_cmd(cmd, Info->serv_inf->clients[i]);
						break;
					}
					else {
						printf("2\n");
						send_cmd(cmd, Info->serv_inf->clients[i]);
						if(getUNREAD(chat_id, user_id) == -1) {
							printf("3\n");
							setUNREAD(chat_id, user_id, msg_id);
							break;
						}
						else {
							printf("4\n");
							break;
						}
					}
				}
			}
		}

		if(is_online == 0) {
			printf("%s is offline\n", user[j]->user_name);
			printf("## getUNREAD: %d -- chat_id: %d, user_id: %d", getUNREAD(chat_id, user_id), chat_id, user_id);
			if(getUNREAD(chat_id, user_id) == -1) {
				printf("5\n");
				setUNREAD(chat_id, user_id, msg_id);
			}
			else {
				is_online = 0;
				printf("6\n");
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}
// Список чатов
void chat_list(char *p_login, buff_t *Info) {
	int mass_of_chats[128];
	int i = 0;
	char *temp_char;
	char users_chat[BUFFER_SZ]; // in first used for ALL users chats. in second as 1 user chat
	char send_to_client[BUFFER_SZ];
	char chat_name[BUFFER_SZ];


	getUserChats(getIdUserByUserName(p_login), users_chat);
	temp_char = strtok(users_chat, ",");
	while(temp_char != NULL) {
		mass_of_chats[i] = atoi(temp_char);
		temp_char = strtok(NULL, ",");
		if(temp_char != NULL) {
			i++;
		}
	}
	bzero(users_chat, BUFFER_SZ);

	struct command arr_of_chats[i];
	for(int j = 0; j < i; j++) {
		arr_of_chats[j].command = "<ADD_CHAT>";

		itoa(mass_of_chats[j], users_chat, 10);
		getChatName(mass_of_chats[j], chat_name);
		str_trim_lf (chat_name, strlen(chat_name));
		printf("chat_id: %d\n", mass_of_chats[j]);
		snprintf(send_to_client, BUFFER_SZ, " <%s> <%s> <%d> <%d>", users_chat, chat_name, getUNREAD(mass_of_chats[j], getIdUserByUserName(p_login)), getLastMsgTime(mass_of_chats[j]));
		arr_of_chats[j].params = send_to_client;

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		send_cmd(arr_of_chats[j], Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);

		bzero(send_to_client, BUFFER_SZ);
		bzero(users_chat, BUFFER_SZ);
		bzero(chat_name, BUFFER_SZ);
	}
}
// Все сообщения из чатов
void f_chat_msg(char *params, buff_t *Info) {
	char *p_chat_id = take_param(params, 1);
	struct command cmd;
	char send_to_client[BUFFER_SZ];
	char user_name[BUFFER_SZ];
	char sender[BUFFER_SZ];

	int ch_id = atoi(p_chat_id);
	Info->client->active_id_chat = ch_id;

	int uid = Info->client->uid;

	Info->serv_inf->clients[uid]->active_id_chat = ch_id;
	
	setUNREAD(ch_id, getIdUserByUserName(Info->client->name), -1);

	while(1) {
		msg_t *new_mess = pack_msg_from_chat(ch_id);
		if(new_mess == NULL) {
			break;
		}
		cmd.command = "<SEND>";

		getUserName(atoi(new_mess->sender), sender);
		str_trim_lf(sender, strlen(sender));
		getNickByUserName(sender, user_name);
		str_trim_lf(user_name, strlen(user_name));
		snprintf(send_to_client, BUFFER_SZ, " <%s> <%s> <%s> <%s> <%s> <%s> <%s>", p_chat_id, new_mess->msg_id, sender, user_name, new_mess->time, new_mess->text, new_mess->is_read);
		cmd.params = strdup(send_to_client);

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i]){
				if(Info->serv_inf->clients[i]->uid == Info->uid){
					send_cmd(cmd, Info->serv_inf->clients[i]);
				}
			}
		}
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		bzero(send_to_client, BUFFER_SZ);
		bzero(user_name, BUFFER_SZ);
		bzero(sender, BUFFER_SZ);
		free(new_mess);
		new_mess = NULL;
	}
}
// Функция логина
void f_login(char *params, buff_t *Info) {
    char user_pass[BUFFER_SZ];
	char client_join[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<LOGIN>";
    char *p_login = take_param(params, 1);
    char *p_pass = take_param(params, 2);
	if(strlen(p_login) <= 2) {
		printf("Не вводи логин <= 2\n");
		return;
	}

	/* Check for mistakes */
	if(getIdUserByUserName(p_login) == 0){
		//Oшибка: неправильный логин
		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		printf("Incorrect user_name\n");
		cmd.params = " <ERROR> <INCORRECT_LOGIN>";
		send_cmd(cmd, Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		return;
	}
	getUserPassword(getIdUserByUserName(p_login), user_pass);
	str_trim_lf(user_pass, strlen(user_pass));
	if(strcmp(user_pass, p_pass) != 0) {
		//Ошибка: неправильный пароль
		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		printf("Incorrect password\n");
		cmd.params = " <ERROR> <INCORRECT_PASS>";
		send_cmd(cmd, Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		return;
	}

    strcpy(Info->client->name, p_login);
	// заджойнился (пусть живет)
    sprintf(client_join, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", client_join);

	cmd.params = " <SUCCESS>";
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid == Info->uid){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	chat_list(p_login, Info);
	bzero(user_pass, BUFFER_SZ);
	bzero(client_join, BUFFER_SZ);
}
// Отправка сообщений
void f_send(char *params, buff_t *Info) {
	char *p_chat_id = take_param(params, 1);
	char *p_text = take_param(params, 2);
	char *p_time = take_param(params, 3);
	char *p_identificator = take_param(params, 4);
	struct command cmd;
	char send_to_client[BUFFER_SZ];
	char user_name[BUFFER_SZ];
	if(strlen(p_text) == 0) { // If message is empty(dont insert to database, and dont return anything to client)
		return;
	}

	cmd.command = "<SEND>";
	int new_msg_id = insertMessage(atoi(p_chat_id), getIdUserByUserName(Info->client->name), p_text, atoi(p_time), p_identificator);
	getNickByUserName(Info->client->name, user_name);
	str_trim_lf(user_name, strlen(user_name));
	snprintf(send_to_client, BUFFER_SZ, " <%s> <%d> <%s> <%s> <%s> <%s> <%s>", p_chat_id, new_msg_id, Info->client->name, user_name, p_time, p_text, p_identificator);


	cmd.params = send_to_client;
	send_to_all_members_send_special(p_chat_id, new_msg_id, cmd, Info);
	bzero(send_to_client, BUFFER_SZ);
	bzero(user_name, BUFFER_SZ);
}
// Регистрация
void f_register(char *params, buff_t *Info) {
	char client_join[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<REGISTER>";
	char *p_username = take_param(params, 1);
	char *nickname = take_param(params, 2);
	char *password = take_param(params, 3);
	char *rep_password = take_param(params, 4);
	if(getIdUserByUserName(p_username) != 0){
		//Oшибка: юзернейм уже существует
		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		printf("Username already exists\n");
		cmd.params = " <ERROR> <USERNAME_EXIST>";
		send_cmd(cmd, Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		return;
	}
	if(strcmp(password, rep_password) != 0) {
		//Oшибка: пароли не равны
		printf("Password is incorrect\n");
		cmd.params = " <ERROR> <PASS_NOT_MATCH>";
		send_cmd(cmd, Info->client);
		return;
	}
	insertUser(p_username, password, nickname, "");
	printf("Insertion complete");
	cmd.params = " <SUCCESS>";

	strcpy(Info->client->name, p_username);
    sprintf(client_join, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", client_join);
	bzero(client_join, BUFFER_SZ);

	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid == Info->uid){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}
// 
void f_del_msg(char *params, buff_t *Info) {
	char send_to_client[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<DELETE_MSG>";
	char *p_msg_id = take_param(params, 1);
	char *p_chat_id = take_param(params, 2);
	deleteMessage(p_msg_id);
	snprintf(send_to_client, BUFFER_SZ, " <%s>", p_msg_id);
	cmd.params = send_to_client;

	send_to_all_members(p_chat_id, cmd, Info);

	bzero(send_to_client, BUFFER_SZ);
}

void f_edit_msg(char *params, buff_t *Info) {
	char send_to_client[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<EDIT_MSG>";
	char *p_msg_id = take_param(params, 1);
	char *p_chat_id = take_param(params, 2);
	char *p_new_text = take_param(params, 3);
	updateTextMessage(atoi(p_msg_id), p_new_text);
	snprintf(send_to_client, BUFFER_SZ, " <%s>", p_chat_id);
	cmd.params = send_to_client;

	send_to_all_members(p_chat_id, cmd, Info);

	bzero(send_to_client, BUFFER_SZ);
}

void f_new_chat(char *params, buff_t *Info) {
	char send_to_client[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<ADD_CHAT>";
	char *p_new_chat_name = take_param(params, 1);
	int chat_id = createChat(getIdUserByUserName(Info->client->name), p_new_chat_name);

	if(chat_id == -1) {
		return;
	}
	snprintf(send_to_client, BUFFER_SZ, " <%d> <%s> <%d> <%d>", chat_id, p_new_chat_name, getUNREAD(chat_id, getIdUserByUserName(Info->client->name)), getLastMsgTime(chat_id));
	cmd.params = send_to_client;
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid == Info->uid){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	bzero(send_to_client, BUFFER_SZ);
}

// ПЕРЕДЕЛАТЬ ПО-ЧЕЛОВЕЧЕСКИ, ТВОЮ МАТЬ
void f_add_user_to_chat(char *params, buff_t *Info) {
	char send_to_client[BUFFER_SZ];
	char chat_name[BUFFER_SZ];
	//char sender_nick[BUFFER_SZ]; Пока не нужно
	char nick_to_add[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<ADD_CHAT>";
	char *p_chat_id = take_param(params, 1);
	char *p_username = take_param(params, 2);
	if(getIdUserByUserName(p_username) == 0) {
		//Oшибка: такого пользователя нет
		printf("Incorrect_username\n");
		cmd.params = " <INCORRECT_USERNAME>";
		send_cmd(cmd, Info->client);
		return;
	}



	// Получение всех пользователей в чате
	user_t *user[MAX_CLIENTS];
	int num_of_memb = 0;
	for(; 1; num_of_memb++ ) {
		user[num_of_memb] = pack_chat_members(atoi(p_chat_id));
		if(user[num_of_memb] == NULL) {
			break;
		}
	}
	for(int i = 0; i < num_of_memb; i++) {
		if(strcmp(user[i]->user_name, p_username) == 0) {
			printf("%s you're dolbaeb\n", p_username);
			return;
		}
	}
	


	insertUSER_TO_CHAT(getIdUserByUserName(p_username), atoi(p_chat_id));
	//Получения ника и имени чата
	/*getNickByUserName(Info->client->name, sender_nick); // Хз зачем оно мне нужно было 
	str_trim_lf(sender_nick, strlen(sender_nick));*/
	getChatName(atoi(p_chat_id), chat_name);
	str_trim_lf(chat_name, strlen(chat_name));


	// Отправка сообщения клиенту
	snprintf(send_to_client, BUFFER_SZ, " <%s> <%s> <%d> <%d>", p_chat_id, chat_name, getUNREAD(atoi(p_chat_id), getIdUserByUserName(Info->client->name)), getLastMsgTime(atoi(p_chat_id))); //Nickname
	cmd.params = send_to_client;
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	// Отправить пользователю которого добавляют
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(strcmp(Info->serv_inf->clients[i]->name, p_username) == 0){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	bzero(send_to_client, BUFFER_SZ);


	/* Отправить всем что пользователь зашел в чат */

	getNickByUserName(p_username, nick_to_add);
	str_trim_lf(nick_to_add, strlen(nick_to_add));
	strcat(nick_to_add, " joined chat");
	snprintf(send_to_client, BUFFER_SZ, "<%s> <%s> <%d> <2>", p_chat_id, nick_to_add, ((int)time(NULL)));
	f_send(send_to_client, Info);
	
	bzero(nick_to_add, BUFFER_SZ);
	bzero(send_to_client, BUFFER_SZ);
	bzero(chat_name, BUFFER_SZ);
}

//В самом начале только Бог и я знали что в этом коде написано, теперь только Бог
// Я не хочу лезть в это дерьмо
void f_delete_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
    char buff_temp[BUFFER_SZ];
    char tempp[BUFFER_SZ];
    struct command cmd;
    char *p_chat_id = take_param(params, 1);
    cmd.command = "<DELETE_CHAT>";
    getOwner_Id_By_Chat_Id(atoi(p_chat_id), buff_temp);
    getUserName(atoi(buff_temp), tempp);
    str_trim_lf(tempp, strlen(tempp));
    if(strcmp(tempp, Info->client->name) != 0) {
        deleteFromChat(getIdUserByUserName(Info->client->name), atoi(p_chat_id));
        snprintf(buff_temp, BUFFER_SZ, " <%s>", p_chat_id);
        pthread_mutex_lock(&Info->serv_inf->clients_mutex);
        for(int i=0; i<MAX_CLIENTS; ++i){
            if(Info->serv_inf->clients[i]){
                if(strcmp(Info->serv_inf->clients[i]->name, Info->client->name) == 0){
                    send_cmd(cmd, Info->serv_inf->clients[i]);
                }
            }
        }
        pthread_mutex_unlock(&Info->serv_inf->clients_mutex);

		char buff_out156[BUFFER_SZ];

		getNickByUserName(Info->client->name, buff_out156);
		str_trim_lf(buff_out156, strlen(buff_out156));
		strcat(buff_out156, " left chat");
		snprintf(tempp, BUFFER_SZ, "<%s> <%s> <1612885395> <2>", p_chat_id, buff_out156);
		f_send(tempp, Info);
		bzero(buff_temp, BUFFER_SZ);
		bzero(buff_out156, BUFFER_SZ);
        bzero(tempp, BUFFER_SZ);

        return;
    }
    user_t *user[MAX_CLIENTS];
    int num_of_memb = 0;
    for(; 1; num_of_memb++ ) {
        user[num_of_memb] = pack_chat_members(atoi(p_chat_id));
        if(user[num_of_memb] == NULL) {
            break;
        }
    }
    for(int i = 0; i < num_of_memb; i++) {
        deleteFromChat(atoi(user[i]->user_id), atoi(p_chat_id));
    }
    deleteChat(p_chat_id);
    snprintf(buff_out, BUFFER_SZ, " <%s>", p_chat_id);
    cmd.params = buff_out;
    send_to_all_members_delete_special(cmd, Info, user, num_of_memb);

    bzero(buff_out, BUFFER_SZ);
    bzero(buff_temp, BUFFER_SZ);
}
// temporary unused
void f_delete_user_from_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	char *p_chat_id = take_param(params, 1);
	char *p_user_name = take_param(params, 2);
	cmd.command = "<DELETE_CHAT>";

	getOwner_Id_By_Chat_Id(atoi(p_chat_id), buff_temp);
	str_trim_lf (buff_temp, strlen(buff_temp)); // На всякий случай
	if(strcmp(p_user_name, Info->client->name) == 0) { // Если создатель хочет удалить сам себя
		bzero(buff_out, BUFFER_SZ);
		snprintf(buff_out, BUFFER_SZ, "<%s>", p_chat_id);
		f_delete_chat(buff_out, Info);

		snprintf(buff_temp, BUFFER_SZ, " <%s>", p_chat_id);
		cmd.params = buff_out;
		send_to_all_members(p_chat_id, cmd, Info);
		return;
	}
	if(strcmp(buff_temp, Info->client->name) == 0) { // Если комманду отсылает создатель
		// Some code
		deleteFromChat(getIdUserByUserName(p_user_name), atoi(p_chat_id));

		snprintf(buff_temp, BUFFER_SZ, " <%s>", p_chat_id);
		cmd.params = buff_temp;

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i]){
				if(strcmp(Info->serv_inf->clients[i]->name, p_user_name) == 0){
					send_cmd(cmd, Info->serv_inf->clients[i]);
				}
			}
		}
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		bzero(buff_out, BUFFER_SZ);
		bzero(buff_temp, BUFFER_SZ);
		return;
	}
	if(strcmp(p_user_name, Info->client->name) == 0) { // Если комманду отсылает пользователь, который хочет себя удалить
		// Some code
		deleteFromChat(getIdUserByUserName(p_user_name), atoi(p_chat_id));

		snprintf(buff_temp, BUFFER_SZ, " <%s>", p_chat_id);
		cmd.params = buff_temp;

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i]){
				if(strcmp(Info->serv_inf->clients[i]->name, p_user_name) == 0){
					send_cmd(cmd, Info->serv_inf->clients[i]);
				}
			}
		}
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		bzero(buff_out, BUFFER_SZ);
		bzero(buff_temp, BUFFER_SZ);
		return;
	}

	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	printf("NOT_OWNER");
	cmd.params = " <NOT_OWNER>";
	send_cmd(cmd, Info->client);
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);

	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}

void f_change_pass(char *params, buff_t *Info) {
	char *p_login = take_param(params, 1);
	char *p_new_pass = take_param(params, 2);
	updatePasswordUser(getIdUserByUserName(p_login), p_new_pass);
	(void)Info;
}

void f_change_nick(char *params, buff_t *Info) {
	char *p_login = take_param(params, 1);
	char *p_new_nick = take_param(params, 2);
	updateNick(getIdUserByUserName(p_login), p_new_nick);
	(void)Info;
}


void initialize_functions(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND", "REGISTER",
											"CHAT_MSG", "DELETE_MSG", "EDIT_MSG",
											"NEW_CHAT", "ADD_USER_TO_CHAT", "LEAVE_CHAT",
											"DELETE_USER_FROM_CHAT", "CHANGE_PASS", "CHANGE_NICK"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_send;
	arr_cmd_func[2].func = &f_register;
	arr_cmd_func[3].func = &f_chat_msg;
	arr_cmd_func[4].func = &f_del_msg;
	arr_cmd_func[5].func = &f_edit_msg;
	arr_cmd_func[6].func = &f_new_chat;
	arr_cmd_func[7].func = &f_add_user_to_chat;
	arr_cmd_func[8].func = &f_delete_chat;
	arr_cmd_func[9].func = &f_delete_user_from_chat;
	arr_cmd_func[10].func = &f_change_pass;
	arr_cmd_func[11].func = &f_change_nick;


    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
