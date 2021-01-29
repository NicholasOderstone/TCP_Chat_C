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

// Add ip and port check when clicked on "Connect"
// If ip or port is incorrect, show message "IP or PORT is incorrect. Try again"(or smth like that)
    g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(open_login_page), gp_client);
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
    GObject *signup_b;
    UNUSED(widget);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_s"));
    login_p = gtk_builder_get_object (builder, "login_p");
    signup_b = gtk_builder_get_object (builder, "signup_b");
    g_signal_connect(login_p, "clicked", G_CALLBACK(open_login_page), gp_client);
    g_signal_connect(signup_b, "clicked", G_CALLBACK(open_main_page), gp_client);
    g_signal_connect(signup_b, "clicked", G_CALLBACK(func_register), gp_client);
    gtk_widget_show(window);
}

void open_login_page(GtkWidget *widget, gpointer gp_client)
{
	UNUSED(widget);
    GObject *signup_p;
    GObject *login_b;
    GObject *login;
    GtkEntry *password;
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
    //g_signal_connect(login_b, "clicked", G_CALLBACK(open_main_page), gp_client);
    login = gtk_builder_get_object(builder, "login");
    password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    gtk_entry_set_visibility (password, FALSE);
    gtk_entry_set_icon_from_icon_name(password, GTK_ENTRY_ICON_SECONDARY,"view-reveal-symbolic");
    gtk_widget_show(window);
}

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    UNUSED(widget);
    //struct message_struct *message_s = (struct message_struct*)malloc(sizeof(struct message_struct));
    static message_t m;
    message_t *message_s = (message_t *)malloc(sizeof(message_t *));
    message_s = &m;
    GObject *send_b;
    client_t *client = (client_t *)gp_client;
    GtkListBox *box;
    GtkWidget *child;
    GtkWidget *child2;
    GtkButton *menu_b;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    client->m = (message_t *)malloc(sizeof(message_t *));
    client->m = message_s;

    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    GtkWidget *menu_b_image = gtk_image_new_from_file ("client/resources/menu.png");

    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    //gtk_binding_set_find ("binding-set1");
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));
    message_s->view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "message_field"));
    message_s->buffer = gtk_text_view_get_buffer (message_s->view);
    box = GTK_LIST_BOX(gtk_builder_get_object(builder, "chat_list"));
    child = gtk_button_new_with_label ("contact1");
    child2 = gtk_button_new_with_label ("contact2");
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, username_str, -1, TRUE);
    //gtk_text_buffer_insert_interactive_at_cursor (message_s->buffer, passoword_str, -1, TRUE);
    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);
    menu_b = GTK_BUTTON(gtk_builder_get_object (builder, "main_menu"));
    gtk_button_set_image (menu_b, menu_b_image);

    gtk_text_buffer_get_iter_at_offset(message_s->buffer, &message_s->end, 0);
    //gchar *name;
    gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->end, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
    g_signal_connect(send_b, "clicked", G_CALLBACK(send_message), (gpointer)message_s);
    //gtk_binding_entry_add_signall()
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    //g_signal_connect(message_s->view, "move-cursor", G_CALLBACK(del_message), (gpointer)message_s->buffer);
    gdk_threads_add_idle (message_show, (gpointer)message_s);
    gtk_widget_show (GTK_WIDGET(child));
    gtk_widget_show (GTK_WIDGET(child2));
    gtk_list_box_insert(box, GTK_WIDGET(child), -1 );
    gtk_list_box_insert(box, GTK_WIDGET(child2), -1 );

}
int i = 0;
gboolean message_show(gpointer m) {
    message_t *mess = (message_t *)m;
    gtk_text_buffer_insert_interactive (mess->buffer, &mess->end, "bimbom", -1, TRUE );
    gtk_text_buffer_insert_interactive (mess->buffer, &mess->end, "\n", -1, TRUE );
    if (i >= 5)
        return FALSE;
    i++;
    return TRUE;
}

void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}

void message_send(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    client_t *client = (client_t *)data;
    char buffer[LENGTH + 32];
    snprintf(buffer, BUFFER_SZ, "<SEND> <%s>", message_str);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, LENGTH + 32);
}

void send_message(GtkWidget *widget, gpointer m) {
    UNUSED(widget);
    message_t *mess = (message_t *)m;
    (void)(widget);
    gtk_text_buffer_insert_interactive (mess->buffer, &mess->end, message_str, -1, TRUE );
    gtk_text_buffer_insert_interactive (mess->buffer, &mess->end, "\n", -1, TRUE );
    mess->mark = gtk_text_buffer_create_mark (mess->buffer, NULL, &mess->end, 1);
    gtk_text_view_scroll_to_mark (mess->view, mess->mark, 0.0, 0, 0.0, 1.0);
}

void message_clear() {
    gtk_entry_set_text(GTK_ENTRY(message_entry), "");
}

void username_changed(GtkEntry *e){
    sprintf(username_str,"%s", gtk_entry_get_text(e));
}

void password_changed(GtkEntry *e){
    //gtk_entry_set_visibility (e, FALSE);
    sprintf(passoword_str, "%s", gtk_entry_get_text(e));
}

void username_s_changed(GtkEntry *e){
    sprintf(username_str_s,"%s", gtk_entry_get_text(e));
}

void nick_s_changed(GtkEntry *e){
    sprintf(nick_str_s,"%s", gtk_entry_get_text(e));
}

void pass_s_changed(GtkEntry *e){
    gtk_entry_set_visibility (e, FALSE);
    sprintf(pass_str_s,"%s", gtk_entry_get_text(e));
}

void r_pass_s_changed(GtkEntry *e){
    gtk_entry_set_visibility (e, FALSE);
    sprintf(r_pass_str_s,"%s", gtk_entry_get_text(e));
}

void del_message(GtkTextBuffer *m){
    GtkTextMark * del_mark;
    GtkTextBuffer *mess = (GtkTextBuffer *)m;
    del_mark = gtk_text_buffer_get_selection_bound (mess);
    gtk_text_buffer_delete_mark(mess, del_mark);
    printf("%s\n", "work");
}

gboolean destroy() {
    gtk_main_quit();
    return TRUE;
}
