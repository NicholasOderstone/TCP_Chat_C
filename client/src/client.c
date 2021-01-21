#include "../inc/header.h"

void func_ipport() {
    char *p_ipv4 = strdup(ipv_str);
    char *p_port = strdup(port_str);
    printf("CONNECT TO SERVER: success.\n\tipv4: %s\n\tport: %s\n", p_ipv4, p_port);
}

int main(int argc, char **argv) {

// --- Checking IP & Port No ---

	if (argc != 3) {
		printf("Usage: %s <ipv4> <port>\n", argv[0]);
	}

	char *ip = argv[1];
	char *port = argv[2];
	while(!validate_ip(argv[1])) {
		printf("Error! IP is incorrect.\nTry one more time: ");
		scanf("%s", ip);
		printf("\n\r");
	}

	while(!validate_port(port)) {
		printf("Error! PORT is incorrect.\nTry one more time: ");
		scanf("%s", port);
		printf("\n\r");
	}

// --- Init client ---

    //GObject *signup_p;
    //GObject *login_b;
    GObject *connect_b;
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "connect_window"));
    gtk_builder_connect_signals(builder, NULL);

    //signup_p = gtk_builder_get_object (builder, "signup_p");
    //g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), NULL);

    //login_b = gtk_builder_get_object (builder, "login_b");
    //g_signal_connect(login_b, "clicked", G_CALLBACK(open_main_page), NULL);
    connect_b = gtk_builder_get_object (builder, "connect_b");
    g_signal_connect(connect_b, "clicked", G_CALLBACK(open_login_page), NULL);
	g_signal_connect(connect_b, "clicked", G_CALLBACK(func_ipport), NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    //gtk_main_iteration();

	client_t client;
	init_client(&client, ip, port);

// --- Connect to Server ---

	pthread_t server_connection_handler;
	if(pthread_create(&server_connection_handler, NULL, connect_to_server, (void*)&client) != 0){
		perror("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	while (client.is_connected == 0) {}

    gtk_main();

// --- Message and command queue threads ---

	struct msg_q *msg_q_front = NULL;
	struct cmd_q *cmd_q_front = NULL;

	// -- MODULE 3 --
	struct send_msg_info_s *send_msg_info = (struct send_msg_info_s *)malloc(sizeof(struct send_msg_info_s));
	send_msg_info->client = &client;

	pthread_t send_msg_thread;
	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void*)send_msg_info) != 0){
		perror("ERROR: pthread\n");
	return EXIT_FAILURE;
	}

	// -- MODULE 1 --
	struct recv_msg_info_s *recv_msg_info = (struct recv_msg_info_s *)malloc(sizeof(struct recv_msg_info_s));
	recv_msg_info->client = &client;
	recv_msg_info->msg_q_front = &msg_q_front;
	recv_msg_info->cmd_q_front = &cmd_q_front;

	pthread_t recv_msg_thread;
	if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void*)recv_msg_info) != 0){
		perror("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	// -- MODULE 4 --
	struct process_cmd_info_s *process_cmd_info = (struct process_cmd_info_s *)malloc(sizeof(struct process_cmd_info_s));
	process_cmd_info->client = &client;
	process_cmd_info->cmd_q_front = &cmd_q_front;
	init_funcs(process_cmd_info->arr_cmd_func);

	pthread_t th_process_cmd;
	if(pthread_create(&th_process_cmd, NULL, process_cmd, (void*)process_cmd_info) != 0){
		perror("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

// --- Checking for client exit ---

    while(1) {
        if (destroy() == TRUE) {
            client.exit = 1;
        }
        if (client.exit == 1) {
            printf("Bye!\n");
            break;
        }
    }
	close(client.sockfd);
	pthread_join(send_msg_thread, NULL);
	pthread_join(recv_msg_thread, NULL);
	pthread_join(th_process_cmd, NULL);

	pthread_mutex_destroy(&client.mutex);

	exit(0);
	return EXIT_SUCCESS;
}
