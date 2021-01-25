#include "../inc/interface.h"

void init_interface(GtkBuilder **p_builder, GtkWidget **p_window,  int *argc, char ***argv, gpointer p_client) {
    GObject *connect_b;
    gtk_init(argc, argv);
    *p_builder = gtk_builder_new();
    gtk_builder_add_from_file (*p_builder, "messanger.glade", NULL);
    *p_window = GTK_WIDGET(gtk_builder_get_object(*p_builder, "connect_window"));
    gtk_builder_connect_signals(*p_builder, NULL);
    init_connect_page(&connect_b, p_builder, p_client);
    gtk_widget_show(window);
}

void init_connect_page(GObject **p_connect_b,GtkBuilder **p_builder, gpointer gp_client) {
    *p_connect_b = gtk_builder_get_object (*p_builder, "connect_b");
// Add ip and port check when clicked on "Connect"
// If ip or port is incorrect, show message "IP or PORT is incorrect. Try again"(or smth like that)
    g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(open_login_page), gp_client);
    // printf("main client addr: %p\n", (void *) p_client);
	g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(th_connect_to_server), gp_client);
    g_object_unref(*p_builder);
}


void open_signup_page()
{
    GObject *login_p;
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    gtk_builder_connect_signals(builder, NULL);
    login_p = gtk_builder_get_object (builder, "login_p");
    g_signal_connect(login_p, "clicked", G_CALLBACK(open_login_page), NULL);
    gtk_widget_show(window);
}

void func_login() {
    char *p_login = strdup(username_str);
    char *p_pass = strdup(passoword_str);
    printf("LOGIN: success.\n\tLogin: %s\n\tPassword: %s\n", p_login, p_pass);
}

void open_login_page(gpointer gp_client)
{
    GObject *signup_p;
    GObject *login_b;
    GObject *login;
    GObject *password;
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_builder_connect_signals(builder, NULL);
    signup_p = gtk_builder_get_object (builder, "signup_p");
    login_b = gtk_builder_get_object (builder, "login_b");
    g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), NULL);
    g_signal_connect(login_b, "clicked", G_CALLBACK(func_login), NULL);
    g_signal_connect(login_b, "clicked", G_CALLBACK(open_main_page), gp_client);
    login = gtk_builder_get_object(builder, "login");
    password = gtk_builder_get_object(builder, "password");
    gtk_widget_show(window);
}

void open_main_page(gpointer gp_client)
{
    struct message_struct *message_s = (struct message_struct*)malloc(sizeof(struct message_struct));

    GObject *send_b;
    //GtkTextIter start, end;
    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    message_s->view = GTK_WIDGET(gtk_builder_get_object(builder, "messages_field"));
    message_s->buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (message_s->view));
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, username_str, -1, TRUE);
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, passoword_str, -1, TRUE);
    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);
    g_signal_connect(send_b, "clicked", G_CALLBACK(send_message), (gpointer)message_s->buffer);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    //gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    //gtk_text_buffer_insert_with_tags (buffer, &start, "name", -1,)
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
}
void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}

void message_send(gpointer p_client) {
    client_t *client = (client_t *)p_client;
    send(client->sockfd, message_str, strlen(message_str), 0);
}
void send_message(GtkWidget *widget, gpointer m) {
    GtkTextBuffer *mess = GTK_TEXT_BUFFER((GtkTextBuffer *)m);
    (void)(widget);
    gtk_text_buffer_insert_interactive_at_cursor (mess, message_str, -1, TRUE);
    gtk_text_buffer_insert_interactive_at_cursor (mess, "\n", -1, TRUE);
}
void message_clear() {
    gtk_entry_set_text(GTK_ENTRY(message_entry), "");
}
void ipv_changed(GtkEntry *e){
    sprintf(ipv_str,"%s", gtk_entry_get_text(e));
}
void port_changed(GtkEntry *e){
    sprintf(port_str,"%s", gtk_entry_get_text(e));
}
void username_changed(GtkEntry *e){
    sprintf(username_str,"%s", gtk_entry_get_text(e));
}
void password_changed(GtkEntry *e){
    gtk_entry_set_visibility (e, FALSE);
    sprintf(passoword_str, "%s", gtk_entry_get_text(e));
}


gboolean destroy() {
        is_exit = 1;
    gtk_main_quit();
    return TRUE;
}
// called when window is closed
/*void on_window_main_destroy()
{
    gtk_main_quit();
}*/
