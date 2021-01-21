#include "../inc/header.h"

void f_login(char *params, buff_t *Info) {
    char buff_out[BUFFER_SZ];
    char *p_login = param_1(params);
    //char *p_pass = param_2(params);
    strcpy(Info->client->name, p_login);
    sprintf(buff_out, "<JOIN> <%s>\n", Info->client->name);
	printf("%s", buff_out);

	//send_message(buff_out, Info->uid, Info->serv_inf);
	struct command cmd;
	cmd.params = params;
	cmd.command = "<LOGIN>";
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

void f_send(char *params, buff_t *Info) {
	struct command cmd;
    //char *p_msg = param_1(params);
    /*send_message(p_msg, Info->uid, Info->serv_inf);
	printf("%s -> %s\n", p_msg, Info->client->name);*/
	cmd.params = params;
	cmd.command = "<SEND>";

	pthread_mutex_lock(&Info->serv_inf->clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(Info->serv_inf->clients[i]){
			if(Info->serv_inf->clients[i]->uid != Info->uid){
				send_cmd(cmd, Info->client);
			}
		}
	}
	pthread_mutex_unlock(&Info->serv_inf->clients_mutex);
}


void initialize_functions(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "LOGIN", "SEND"};

    arr_cmd_func[0].func = &f_login;
    arr_cmd_func[1].func = &f_send;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
