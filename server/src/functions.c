#include "../inc/header.h"


void f_chat_msg(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);

	struct command cmd;
	char buff_out[BUFFER_SZ];
	//struct command cmd_arr[50];
	printf("%s\n", params);

	while(1) {
		msg_t *new_mess = packMsg(atoi(p_chat_id));
		if(new_mess == NULL) {
			break;
		}
		cmd.command = "<SEND>";
		strcat(buff_out, " <");
		strcat(buff_out, p_chat_id);
		strcat(buff_out, "> <");
		strcat(buff_out, new_mess->msg_id);
		strcat(buff_out, "> <");
		strcat(buff_out, new_mess->sender);
		strcat(buff_out, "> <");
		strcat(buff_out, new_mess->time);
		strcat(buff_out, "> <");
		strcat(buff_out, new_mess->text);
		strcat(buff_out, ">");
		cmd.params = strdup(buff_out);
		//printf("%s\n", cmd.params);
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
	}
}

void f_new_chat(char *params, buff_t *Info) {
	//char buff_out[BUFFER_SZ];
	//struct command cmd;
	char *p_chat_name = param_1(params);
	p_chat_name = NULL;
	Info->uid++;
	Info->uid--;

	char *buff_temp = getAllChats();
	printf("%s\n", buff_temp);
	
}

void f_login(char *params, buff_t *Info) {
    char buff_out[BUFFER_SZ];
	struct command cmd;
	cmd.command = "<LOGIN>";

    char *p_login = param_1(params);
    char *p_pass = param_2(params);

	/* Check for mistakes */
	if(getIdUserByUserName(p_login) == 0){
		//Oшибка: неправильный логин
		printf("Incorrect user_name\n");
		cmd.params = " <ERROR> <INCORRECT_LOGIN>";
		send_cmd(cmd, Info->client);
		return;
	}
	getUserPassword(getIdUserByUserName(p_login), buff_out);
	str_trim_lf(buff_out, strlen(buff_out));
	if(strcmp(buff_out, p_pass) != 0) {
		//Ошибка: неправильный пароль
		printf("Incorrect password\n");
		cmd.params = " <ERROR> <INCORRECT_PASS>";
		send_cmd(cmd, Info->client);
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

	//f_chat_msg("<1>", Info);

	/* OTHER */
	getUserChats(getIdUserByUserName(p_login), buff_out);
	int mass_of_chats[128];
	int i = 0;
	char *temp;
	temp = strtok(buff_out, ",");
	while(temp != NULL) {
		mass_of_chats[i] = atoi(temp);
		temp = strtok(NULL, ",");
		if(temp != NULL) {
			i++;
		}
	}
	bzero(buff_out, BUFFER_SZ);
	char buff_temp[BUFFER_SZ];
	struct command arr_of_chats[i];
	for(int j = 0; j < i; j++) {
		arr_of_chats[j].command = "<ADD_CHAT>";
		strcat(buff_temp, " <");
		itoa(mass_of_chats[j], buff_out, 10);
		strcat(buff_temp, buff_out);
		bzero(buff_out, BUFFER_SZ);
		strcat(buff_temp, "> <");
		getChatName(mass_of_chats[j], buff_out);
		str_trim_lf (buff_out, strlen(buff_out));
		strcat(buff_temp, buff_out);
		bzero(buff_out, BUFFER_SZ);
		strcat(buff_temp, ">");
		arr_of_chats[j].params = buff_temp;
		printf("%s%s\n",arr_of_chats[j].command, arr_of_chats[j].params);
		/*pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		send_cmd(arr_of_chats[j], Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);*/
		bzero(buff_temp, BUFFER_SZ);
	}

	//insertMessage("1", itoa(getIdUserByUserName(p_login), buff_temp, 10), "some_msg", 1234954, "IS_READ");
	//bzero(buff_temp, BUFFER_SZ);
}

void f_send(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);
	char *p_text = param_2(params);
	char *p_time = param_3(params);

	struct command cmd;
	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	char buff_temp2[BUFFER_SZ];

	cmd.command = "<SEND>";
	strcat(buff_out, " <");
	strcat(buff_out, p_chat_id);
	strcat(buff_out, "> <");
	//msg_id
	strcat(buff_out, itoa(insertMessage(p_chat_id, itoa(getIdUserByUserName(Info->client->name), buff_temp2, 10), p_text, atoi(p_time), "NOT_READ"), buff_temp, 10));
	strcat(buff_out, "> <");
	strcat(buff_out, Info->client->name);
	strcat(buff_out, "> <");
	strcat(buff_out, p_time);
	strcat(buff_out, "> <");
	strcat(buff_out, p_text);
	strcat(buff_out, ">");

	printf("%s\n", buff_out);
	cmd.params = strdup(buff_out);
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			send_cmd(cmd, Info->serv_inf->clients[i]);
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
	bzero(buff_out, BUFFER_SZ);
	bzero(buff_temp, BUFFER_SZ);
	bzero(buff_temp2, BUFFER_SZ);
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
		printf("Username already exists\n");
		cmd.params = " <ERROR> <USERNAME_EXIST>";
		send_cmd(cmd, Info->client);
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
    //sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	//printf("%s", buff_out);
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

void initialize_functions(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND", "REGISTER", "CHAT_MSG", "NEW_CHAT"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_send;
	arr_cmd_func[2].func = &f_register;
	arr_cmd_func[3].func = &f_chat_msg;
	arr_cmd_func[4].func = &f_new_chat;


    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
