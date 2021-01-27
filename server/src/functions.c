#include "../inc/header.h"

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
	// Потом убрать
    sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", buff_out);

	cmd.command = "<LOGIN>";
	cmd.params = " <SUCCESS>";
	printf("%s\n", cmd.params);

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

void f_send(char *params, buff_t *Info) {
	struct command cmd;
	char buff_out[BUFFER_SZ];
	cmd.command = "<SEND>";
	strcat(buff_out, " <SUCCES> ");
	cmd.params = strdup(strcat(buff_out, params));
	bzero(buff_out, BUFFER_SZ);
	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid != Info->uid){
				send_cmd(cmd, Info->serv_inf->clients[i]);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
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



void initialize_functions(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND", "REGISTER"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_send;
	arr_cmd_func[2].func = &f_register;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
