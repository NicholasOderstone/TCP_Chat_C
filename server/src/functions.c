#include "../inc/header.h"


void f_chat_msg(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);
	//char *p_text = param_2(params);
	//char *p_time = param_3(params);

	char buff_out[BUFFER_SZ];
	char buff_temp[BUFFER_SZ];
	struct command cmd_arr[50];
	printf("%s\n", params);
	for(int i = 0; i < 50; i++) {
		cmd_arr[i].command = "<SEND>";
		strcat(buff_out, " <");
		strcat(buff_out, p_chat_id);
		strcat(buff_out, "> <");
		//msg_id
		strcat(buff_out, "> <");
		strcat(buff_out, Info->client->name);




		//Получения сообщения
		strcat(buff_out, itoa(i, buff_temp, 10));
		strcat(buff_out, ">");
		cmd_arr[i].params = buff_out;
		//Вывод
		//printf("%s%s\n", cmd_arr[i].command, cmd_arr[i].params);
		/*pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		for(int i=0; i<MAX_CLIENTS; ++i){
			if(Info->serv_inf->clients[i]){
				if(Info->serv_inf->clients[i]->uid == Info->uid){
					send_cmd(cmd_arr[i], Info->serv_inf->clients[i]);
				}
			}
		}
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);*/
		//printf("%s%s\n", cmd_arr[i].command, cmd_arr[i].params);
		bzero(buff_out, BUFFER_SZ);
		bzero(buff_temp, BUFFER_SZ);
	}


}

void f_login(char *params, buff_t *Info) {
    char buff_out[BUFFER_SZ];
	struct command cmd;

    char *p_login = param_1(params);
    char *p_pass = param_2(params);

	/* Check for mistakes */
	if(getIdUserByUserName(p_login) == 0){
		//Oшибка: неправильный логин
		printf("Incorrect user_name\n");
		send(Info->client->sockfd, "<LOGIN> <ERROR> <INCORRECT_LOGIN>", strlen("<LOGIN> <ERROR> <INCORRECT_LOGIN>"), 0);
		return;
	}
	getUserPassword(getIdUserByUserName(p_login), buff_out);
	str_trim_lf(buff_out, strlen(buff_out));
	if(strcmp(buff_out, p_pass) != 0) {
		//Ошибка: неправильный пароль
		printf("Incorrect password\n");
		send(Info->client->sockfd, "<LOGIN> <ERROR> <INCORRECT_PASS>", strlen("<LOGIN> <ERROR> <INCORRECT_PASS>"), 0);
		return;
	}
	bzero(buff_out, BUFFER_SZ);

    strcpy(Info->client->name, p_login);
	// заджойнился (пусть живет)
    sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", buff_out);
	bzero(buff_out, BUFFER_SZ);

	cmd.command = "<LOGIN>";
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
	f_chat_msg(params, Info);




	/* OTHER */
	/*getUserChats(getIdUserByUserName(p_login), buff_out);
	printf("%s\n", buff_out);
	int mass_of_chats[128];
	int i = 0;
	char *temp;
	temp = strtok(buff_out, ",");
	while(temp != NULL) {
		mass_of_chats[i] = atoi(temp);
		temp = strtok(NULL, ",");
		printf("%d\n", mass_of_chats[i]);
		if(temp != NULL) {
			i++;
		}
	}
	bzero(buff_out, BUFFER_SZ);
	char buff_temp[BUFFER_SZ];
	struct command arr_of_chats[i];
	for(int j = 0; j < i; j++) {
		getChatName(mass_of_chats[j], buff_out);
		arr_of_chats[j].command = "<ADD_CHAT>";
		strcat(buff_temp, " <SUCCESS> ");
		strcat(buff_temp, "<");
		str_trim_lf (buff_out, strlen(buff_out));
		strcat(buff_temp, buff_out);
		bzero(buff_out, BUFFER_SZ);
		strcat(buff_temp, "> <");
		itoa(mass_of_chats[j], buff_out, 10);
		strcat(buff_temp, buff_out);
		bzero(buff_out, BUFFER_SZ);
		strcat(buff_temp, ">");
		arr_of_chats[j].params = buff_temp;

		pthread_mutex_lock(&Info->serv_inf->clients_mutex);
		send_cmd(arr_of_chats[j], Info->client);
		pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
		bzero(buff_temp, BUFFER_SZ);
	}*/
}

void f_send(char *params, buff_t *Info) {
	char *p_chat_id = param_1(params);
	printf("%s\n", p_chat_id);
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

	/*p_text = itoa(atoi(p_text), buff_temp2, 10);
	p_time = itoa(atoi(p_tp_timeext), buff_temp2, 10);*/
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
	char *p_username = param_1(params);
	char *nickname = param_2(params);
	char *password = param_3(params);
	char *rep_password = param_4(params);
	if(getIdUserByUserName(p_username) != 0){
		//Oшибка: юзернейм уже существует
		printf("Username already exists\n");
		send(Info->client->sockfd, "<REGISTER> <ERROR> <USERNAME_EXIST>", strlen("<REGISTER> <ERROR> <USERNAME_EXIST>"), 0);
		return;
	}
	if(strcmp(password, rep_password) != 0) {
		//Oшибка: пароли не равны
		printf("Password is incorrect\n");
		send(Info->client->sockfd, "<REGISTER> <ERROR> <PASS_NOT_MATCH>", strlen("<REGISTER> <ERROR> <PASS_NOT_MATCH>"), 0);
		return;
	}
	insertUser(p_username, password, nickname, "");
	printf("Insertion complete");
	cmd.command = "<REGISTER>";
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
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND", "REGISTER", "CHAT_MSG"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_send;
	arr_cmd_func[2].func = &f_register;
	arr_cmd_func[3].func = &f_chat_msg;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
