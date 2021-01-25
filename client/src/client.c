#include "../inc/header.h"


int main(int argc, char **argv) {

// --- Checking IP & Port No ---

	/*if (argc != 3) {
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
	}*/

    //client_t *buff_client = (client_t *)malloc(sizeof(client_t));
    //buff_client = &client

    //GObject *signup_p;
    //GObject *login_b;
    is_exit = 0;
    static client_t client;
    client_t *p_client = (client_t *)malloc(sizeof(client_t *));
    p_client = &client;
    GObject *connect_b;
    gtk_init(&argc, &argv);

    /* По максимуму надо уменьшить мейн и разнести все по функциям
    * Функция, которая инициализирует потоки
    * Функция, которая инициализирует интерфейс
    * Главная суть в том, чтобы интерфейс и код клиента были связаны по минимуму, 
    * через переключатели, функции и т.п.
    * Это нужно для того, чтобы можно было заниматься отдельно кодом клиента и отдельно интерфейсом,
    * а не ломать одно, чтобы построить другое.
    */

    /* builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "connect_window"));
    gtk_builder_connect_signals(builder, NULL); */

    
    //signup_p = gtk_builder_get_object (builder, "signup_p");
    //g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), NULL);

    //login_b = gtk_builder_get_object (builder, "login_b");
    //g_signal_connect(login_b, "clicked", G_CALLBACK(open_main_page), NULL);

    /* connect_b = gtk_builder_get_object (builder, "connect_b");
// Add ip and port check when clicked on "Connect"
// If ip or port is incorrect, show message "IP or PORT is incorrect. Try again"(or smth like that)
    g_signal_connect(connect_b, "clicked", G_CALLBACK(open_login_page), NULL);
    printf("main client addr: %p\n", (void *) p_client);
	g_signal_connect(connect_b, "clicked", G_CALLBACK(th_connect_to_server), (gpointer) p_client);
    g_object_unref(builder); */
    init_interface(&builder, &window);
    init_connect_page(&connect_b, &builder, (gpointer) p_client);
    gtk_widget_show(window);
    
    //gtk_main_iteration();
    gtk_main();


	exit(0);
	return EXIT_SUCCESS;
}
