#include "../inc/interface.h"

void init_interface(GtkBuilder **p_builder,  int *argc, char ***argv, gpointer p_client) {
    GObject *connect_b;
    gtk_init(argc, argv);
    *p_builder = gtk_builder_new();
    gtk_builder_add_from_file (*p_builder, "messanger.glade", NULL);

    init_connect_page(&connect_b, p_builder, p_client);
}

void init_connect_page(GObject **p_connect_b, GtkBuilder **p_builder, gpointer gp_client) {

    window = GTK_WIDGET(gtk_builder_get_object(*p_builder, "connect_window"));
    gtk_builder_connect_signals(*p_builder, NULL);
    *p_connect_b = gtk_builder_get_object (*p_builder, "connect_b");
    gtk_widget_show(window);
    ipv_entry = GTK_ENTRY(gtk_builder_get_object(builder, "ipv_field"));
    port_entry = GTK_ENTRY(gtk_builder_get_object(builder, "port_field"));

    printf("%d\n", validate_ip(ipv_str));

// Add ip and port check when clicked on "Connect"
// If ip or port is incorrect, show message "IP or PORT is incorrect. Try again"(or smth like that)
    g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(open_login_page), gp_client);
    // printf("main client addr: %p\n", (void *) p_client);
	g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(th_connect_to_server), gp_client);
    g_object_unref(*p_builder);
}
void ipv_changed(GtkEntry *e){
    gtk_entry_set_icon_from_icon_name(ipv_entry, GTK_ENTRY_ICON_SECONDARY,"gtk-no");
    gtk_entry_set_icon_tooltip_text(ipv_entry, GTK_ENTRY_ICON_SECONDARY,"IP is incorrect");
    sprintf(ipv_str,"%s", gtk_entry_get_text(e));
    if (validate_ip(ipv_str) > 0)
        gtk_entry_set_icon_from_icon_name(ipv_entry, GTK_ENTRY_ICON_SECONDARY, NULL);

}
void port_changed(GtkEntry *e){
    gtk_entry_set_icon_from_icon_name(port_entry, GTK_ENTRY_ICON_SECONDARY,"gtk-no");
    gtk_entry_set_icon_tooltip_text(port_entry, GTK_ENTRY_ICON_SECONDARY, "PORT is incorrect");
    sprintf(port_str,"%s", gtk_entry_get_text(e));
    if (validate_port(port_str) > 0)
        gtk_entry_set_icon_from_icon_name(port_entry, GTK_ENTRY_ICON_SECONDARY, NULL);
}

void open_signup_page(GtkWidget *widget, gpointer gp_client)
{
    GObject *login_p;
    UNUSED(widget);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_s"));
    login_p = gtk_builder_get_object (builder, "login_p");
    g_signal_connect(login_p, "clicked", G_CALLBACK(open_login_page), gp_client);
    gtk_widget_show(window);
}

/*void func_login(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	client_t *client = (client_t *)data;
    send(client->sockfd, "<LOGIN> <name> <pass>", strlen("<LOGIN> <name> <pass>"), 0);
    printf("func_login client: %p\n", (void *)client);
    char *p_login = strdup(username_str);
    char *p_pass = strdup(passoword_str);
    printf("LOGIN: success.\n\tLogin: %s\n\tPassword: %s\n", p_login, p_pass);
}*/

void open_login_page(GtkWidget *widget, gpointer gp_client)
{
	UNUSED(widget);
    GObject *signup_p;
    GObject *login_b;
    GObject *login;
    GObject *password;
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_l"));
    signup_p = gtk_builder_get_object (builder, "signup_p");
    login_b = gtk_builder_get_object (builder, "login_b");
    g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), gp_client);
    g_signal_connect(login_b, "clicked", G_CALLBACK(func_login), gp_client);
    g_signal_connect(login_b, "clicked", G_CALLBACK(open_main_page), gp_client);
    login = gtk_builder_get_object(builder, "login");
    password = gtk_builder_get_object(builder, "password");
    gtk_widget_show(window);
}

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    struct message_struct *message_s = (struct message_struct*)malloc(sizeof(struct message_struct));
    UNUSED(widget);
    GObject *send_b;

    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));
    /*if (client->is_connected == 0)
        gtk_spinner_start(connection_spin);
    else
        gtk_spinner_stop (connection_spin);*/
    message_s->view = GTK_WIDGET(gtk_builder_get_object(builder, "messages_field"));
    message_s->buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (message_s->view));
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, username_str, -1, TRUE);
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, passoword_str, -1, TRUE);
    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);
    g_signal_connect(send_b, "clicked", G_CALLBACK(send_message), (gpointer)message_s->buffer);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    gtk_text_buffer_get_iter_at_offset(message_s->buffer, &message_s->iter, 0);
    //gchar *name;
    gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->iter, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
}

void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}

void message_send(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    client_t *client = (client_t *)data;
    char buffer[LENGTH + 32];
    printf("message_str: %s\n", message_str);
    snprintf(buffer, BUFFER_SZ, "<SEND> <%s>", message_str);
    send(client->sockfd, buffer, strlen(buffer), 0);
    //send(client->sockfd, message_str, strlen(message_str), 0);
    bzero(buffer, LENGTH + 32);
}
void send_message(GtkWidget *widget, gpointer m) {
    UNUSED(widget);
    GtkTextBuffer *mess = GTK_TEXT_BUFFER((GtkTextBuffer *)m);
    (void)(widget);
    gtk_text_buffer_insert_interactive_at_cursor (mess, message_str, -1, TRUE);
    gtk_text_buffer_insert_interactive_at_cursor (mess, "\n", -1, TRUE);
}
void message_clear() {
    gtk_entry_set_text(GTK_ENTRY(message_entry), "");
}

void username_changed(GtkEntry *e){
    sprintf(username_str,"%s", gtk_entry_get_text(e));
}
void password_changed(GtkEntry *e){
    gtk_entry_set_visibility (e, FALSE);
    sprintf(passoword_str, "%s", gtk_entry_get_text(e));
}


gboolean destroy() {
    gtk_main_quit();
    return TRUE;
}
// called when window is closed
/*void on_window_main_destroy()
{
    gtk_main_quit();
}*/
