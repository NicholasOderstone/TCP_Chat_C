#include "../inc/header.h"

void send_to_all_members(char *p_chat_id, struct command cmd, buff_t *Info) {
	user_t *user[MAX_CHAT_USERS];
	for(int i = 0; 1; i++ ) {
		user[i] = pack_chat_members(atoi(p_chat_id));
		if(user[i] == NULL) {
			printf("No users in chat\n");
			break;
		}
		//printf("chat member id: %s\n", user[i]->user_id);
	}
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i] != NULL){
				for(int j = 0; j < MAX_CHAT_USERS; j++) {
					if(user[j] != NULL){	
						str_trim_lf(user[j]->user_name, strlen(user[i]->user_name));
						if(strcmp(user[j]->user_name, Info->serv_inf->clients[i]->name) == 0) {
							send_cmd(cmd, Info->serv_inf->clients[i]);
							break;
						}
					}
					else {
						break;
					}
				}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}

void chat_list(char *p_login, buff_t *Info) {
	int mass_of_chats[128];
	int i = 0;
	char *temp;
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	char buff_temp2[BUFFER_SZ];


	getUserChats(getIdUserByUserName(p_login), buff_temp);
	temp = strtok(buff_temp, ",");
	while(temp != NULL) {
		mass_of_chats[i] = atoi(temp);
		temp = strtok(NULL, ",");
		if(temp != NULL) {
			i++;
		}
	}
	bzero(buff_temp, BUFFER_SZ);

	struct command arr_of_chats[i];
	for(int j = 0; j < i; j++) {
		arr_of_chats[j].command = "<ADD_CHAT>";

		itoa(mass_of_chats[j], buff_temp, 10);
		getChatName(mass_of_chats[j], buff_temp2);
		str_trim_lf (buff_temp2, strlen(buff_temp2));
		snprintf(buff_out, BUFFER_SZ, " <%s> <%s>", buff_temp, buff_temp2);
		arr_of_chats[j].params = buff_out;

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		send_cmd(arr_of_chats[j], Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);

		bzero(buff_out, BUFFER_SZ);
		bzero(buff_temp, BUFFER_SZ);
		bzero(buff_temp2, BUFFER_SZ);
	}
}

void f_chat_msg(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);
	struct command cmd;
	char buff_out[BUFFER_SZ];
	char sender[BUFFER_SZ];
	while(1) {
		msg_t *new_mess = pack_msg_from_chat(atoi(p_chat_id));
		if(new_mess == NULL) {
			printf("No messages in chat\n");
			break;
		}
		cmd.command = "<SEND>";

		getUserName(atoi(new_mess->sender), sender);
		str_trim_lf(sender, strlen(sender));
		snprintf(buff_out, BUFFER_SZ, " <%s> <%s> <%s> <%s> <%s>", p_chat_id, new_mess->msg_id, sender, new_mess->time, new_mess->text);
		cmd.params = strdup(buff_out);

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i]){
				if(Info->serv_inf->clients[i]->uid == Info->uid){
					send_cmd(cmd, Info->serv_inf->clients[i]);
				}
			}
		}
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		bzero(buff_out, BUFFER_SZ);
		bzero(sender, BUFFER_SZ);
		free(new_mess);
		new_mess = NULL;
	}
}

void f_login(char *params, buff_t *Info) {
    char buff_out[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<LOGIN>";
	printf("%s\n", params);
    char *p_login = param_1(params);
    char *p_pass = param_2(params);

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
	getUserPassword(getIdUserByUserName(p_login), buff_out);
	str_trim_lf(buff_out, strlen(buff_out));
	if(strcmp(buff_out, p_pass) != 0) {
		//Ошибка: неправильный пароль
		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		printf("Incorrect password\n");
		cmd.params = " <ERROR> <INCORRECT_PASS>";
		send_cmd(cmd, Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		return;
	}
	bzero(buff_out, BUFFER_SZ);

    strcpy(Info->client->name, p_login);
	// заджойнился (пусть живет)
    sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", buff_out);
	bzero(buff_out, BUFFER_SZ);

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
}

void f_send(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);
	char *p_text = param_2(params);
	char *p_time = param_3(params);
	struct command cmd;
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];

	cmd.command = "<SEND>";
	int new_msg_id = insertMessage(atoi(p_chat_id), getIdUserByUserName(Info->client->name), p_text, atoi(p_time), "0");
	snprintf(buff_out, BUFFER_SZ, " <%s> <%s> <%s> <%s> <%s>", p_chat_id, itoa(new_msg_id, buff_temp, 10), Info->client->name, p_time, p_text);


	cmd.params = buff_out;
	send_to_all_members(p_chat_id, cmd, Info);
	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}

void f_register(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<REGISTER>";
	char *p_username = param_1(params);
	char *nickname = param_2(params);
	char *password = param_3(params);
	char *rep_password = param_4(params);
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
    sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", buff_out);
	bzero(buff_out, BUFFER_SZ);

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

void f_del_msg(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<DELETE_MSG>";
	char *p_msg_id = param_1(params);
	deleteMessage(p_msg_id);
	snprintf(buff_out, BUFFER_SZ, " <%s>", p_msg_id);
	cmd.params = buff_out;

	getChat_Id_By_Msg_Id(atoi(p_msg_id), buff_temp);
	send_to_all_members(buff_temp, cmd, Info);

	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}

void f_edit_msg(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<EDIT_MSG>";
	char *p_msg_id = param_1(params);
	char *p_new_text = param_2(params);
	updateTextMessage(atoi(p_msg_id), p_new_text);
	snprintf(buff_out, BUFFER_SZ, " <%s> <%s>", p_msg_id, p_new_text);
	cmd.params = buff_out;

	getChat_Id_By_Msg_Id(atoi(p_msg_id), buff_temp);
	send_to_all_members(buff_temp, cmd, Info);

	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}

void f_new_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<ADD_CHAT>";
	char *p_new_chat_name = param_1(params);
	int chat_id = createChat(getIdUserByUserName(Info->client->name), p_new_chat_name);
	printf("f_new_chat -> createChat: %d\n", chat_id);
	if(chat_id == -1) {
		return;
	}
	snprintf(buff_out, BUFFER_SZ, " <%s> <%s>", itoa(chat_id, buff_temp, 10), p_new_chat_name);
	cmd.params = buff_out;
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid == Info->uid){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}


void f_add_user_to_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	char buff_temp2[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<ADD_CHAT>";
	char *p_chat_id = param_1(params);
	char *p_username = param_2(params);
	insertInUserInChats(getIdUserByUserName(p_username), atoi(p_chat_id));
	snprintf(buff_out, BUFFER_SZ, " <%s> <%s>", p_chat_id, getChatName(atoi(p_chat_id), buff_temp2));
	cmd.params = buff_out;
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->name == p_username){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
	bzero(buff_temp2, BUFFER_SZ);

}

void f_delete_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	char *p_chat_id = param_1(params);
	cmd.command = "<DELETE_CHAT>";


	getOwner_Id_By_Chat_Id(atoi(p_chat_id), buff_temp);
	str_trim_lf (buff_temp, strlen(buff_temp)); // На всякий случай
	if(strcmp(buff_temp, Info->client->name) != 0) {
		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		printf("NOT_OWNER\n");
		cmd.params = " <NOT_OWNER>";
		send_cmd(cmd, Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		return;
	}

	deleteChat(p_chat_id);
	snprintf(buff_out, BUFFER_SZ, " <%s>", p_chat_id);
	cmd.params = buff_out;
	
	send_to_all_members(p_chat_id, cmd, Info);
	
	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}

void f_delete_user_from_chat(char *params, buff_t *Info) {
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd;
	char *p_chat_id = param_1(params);
	char *p_user_name = param_2(params);
	cmd.command = "<DELETE_CHAT>";

	getOwner_Id_By_Chat_Id(atoi(p_chat_id), buff_temp);
	str_trim_lf (buff_temp, strlen(buff_temp)); // На всякий случай
	if(strcmp(p_user_name, Info->client->name) == 0) { // Если создатель хочет удалить сам себя
		// Some code
		//f_delete_chat(, Info);
	}
	if(strcmp(buff_temp, Info->client->name) == 0) { // Если комманду отсылает создатель
		// Some code
	}
	if(strcmp(p_user_name, Info->client->name) == 0) { // Если комманду отсылает пользователь, который хочет себя удалить
		// Some code
	}

	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	printf("NOT_OWNER");
	cmd.params = " <NOT_OWNER>";
	send_cmd(cmd, Info->client);
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);

	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
}


void initialize_functions(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND", "REGISTER", 
											"CHAT_MSG", "DELETE_MSG", "EDIT_MSG", 
											"NEW_CHAT", "ADD_USER_TO_CHAT", "DELETE_CHAT", 
											"DELETE_USER_FROM_CHAT"};

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



    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
