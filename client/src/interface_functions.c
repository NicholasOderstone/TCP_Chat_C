#include "../inc/interface.h"

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
    g_signal_connect(login_p, "clicked", G_CALLBACK(func_login), NULL);
    gtk_widget_show(window);
}
void func_login() {
    char *p_login = strdup(username_str);
    char *p_pass = strdup(passoword_str);
    printf("LOGIN: success.\n\tLogin: %s\n\tPassword: %s\n", p_login, p_pass);
}


void open_login_page()
{
    GObject *signup_p;
    GObject *login;
    GObject *password;
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_builder_connect_signals(builder, NULL);
    signup_p = gtk_builder_get_object (builder, "signup_p");
    g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), NULL);
    login = gtk_builder_get_object(builder, "login");
    password = gtk_builder_get_object(builder, "password");
    gtk_widget_show(window);
}

void open_main_page()
{
    //GObject *signup_p;
    GtkWidget *view;
    GtkTextBuffer *buffer;
    GObject *send_b;
    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    view = GTK_WIDGET(gtk_builder_get_object(builder, "messages_field"));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_insert_interactive_at_cursor (buffer, username_str, -1, TRUE);
    gtk_text_buffer_insert_interactive_at_cursor (buffer, passoword_str, -1, TRUE);
    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);
    //send_message(send_b, buffer);
    g_signal_connect(send_b, "clicked", G_CALLBACK(send_message), NULL);
}
void send_message(GtkTextBuffer *buffer) {
    //printf("%s\n", message_str);
    gtk_text_buffer_insert_interactive_at_cursor (buffer, message_str, -1, TRUE);
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
    sprintf(passoword_str, "%s", gtk_entry_get_text(e));
}
void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}

gboolean destroy (){
    gtk_main_quit();
    return TRUE;
}
// called when window is closed
/*void on_window_main_destroy()
{
    gtk_main_quit();
}*/
