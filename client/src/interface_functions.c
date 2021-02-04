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
    login = gtk_builder_get_object(builder, "login");
    password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    gtk_entry_set_visibility (password, FALSE);
    gtk_entry_set_icon_from_icon_name(password, GTK_ENTRY_ICON_SECONDARY,"view-reveal-symbolic");
    gtk_widget_show(window);
}

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    UNUSED(widget);
    static gtk_utils_t m;
    gtk_utils_t *message_s = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    message_s = &m;
    GObject *send_b;
    client_t *client = (client_t *)gp_client;
    GtkButton *menu_b;
    GtkMenu *menu;
    GtkWidget *menu_item;
    GtkListBox *box;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    client->m = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    client->m = message_s;

    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    GtkWidget *menu_b_image = gtk_image_new_from_file ("client/resources/menu.png");


    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));

    menu_b = GTK_BUTTON(gtk_builder_get_object (builder, "main_menu"));

    gtk_button_set_image (menu_b, menu_b_image);
    menu_item = gtk_menu_item_new_with_label ("Add Chat");
    menu = GTK_MENU(gtk_builder_get_object (builder, "menu"));
    gtk_menu_button_set_popup (GTK_MENU_BUTTON(menu_b), GTK_WIDGET(menu));
    gtk_menu_attach (menu, menu_item, 0, 1, 0, 1);
    box = GTK_LIST_BOX(gtk_builder_get_object(builder, "chat_list"));
    gtk_widget_show_all(GTK_WIDGET(menu));

    int i = 0;
    GtkWidget **chat = malloc(chat_list_size(&client->chat_list_head) * sizeof(GtkWidget *));
    chat_info_t *current = client->chat_list_head;

    while (current != NULL)
    {
        get_messages_request_s *get_messages_request = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        chat[i] = gtk_button_new_with_label(current->chat_name);
        gtk_widget_show(GTK_WIDGET(chat[i]));
        gtk_list_box_insert(box, GTK_WIDGET(chat[i]), -1);
        get_messages_request->chat = current;
        get_messages_request->client = client;
        get_messages_request_s *get_msg_buf = get_messages_request;
        g_signal_connect(chat[i], "clicked", G_CALLBACK(get_msg_request), (gpointer)get_msg_buf);

        current = current->next;
        i++;
    }

    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);

    message_s->box_message = GTK_LIST_BOX(gtk_builder_get_object(builder, "message_list"));
    //gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    //gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->end, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
    //g_signal_connect(send_b, "clicked", G_CALLBACK(show_my_msg), (gpointer)message_s);
    //gtk_binding_entry_add_signall()
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    gtk_list_box_set_selection_mode(message_s->box_message, GTK_SELECTION_SINGLE);
    gtk_list_box_set_activate_on_single_click (message_s->box_message, FALSE);
    gdk_threads_add_idle(is_edit_delet, (gpointer)client);
    message_s->cancel_b = GTK_WIDGET(gtk_builder_get_object (builder, "cancel_b"));
    message_s->edit_b = GTK_WIDGET(gtk_builder_get_object (builder, "ed_b"));
    message_s->delet_b = GTK_WIDGET(gtk_builder_get_object (builder, "del_b"));
    message_s->b_box = GTK_BUTTON_BOX(gtk_builder_get_object(builder, "ed_del_box"));
    gtk_widget_hide(GTK_WIDGET(message_s->b_box));
    gtk_widget_hide(message_s->cancel_b);
    gtk_widget_hide(message_s->edit_b);
    gtk_widget_hide(message_s->delet_b);
    g_signal_connect(message_s->delet_b, "clicked", G_CALLBACK(message_delet),gp_client);
    g_signal_connect(message_s->cancel_b, "clicked", G_CALLBACK(cancel_ch),gp_client);
    //g_signal_connect(message_s->view, "move-cursor", G_CALLBACK(del_message), (gpointer)message_s->buffer);

}
gboolean is_edit_delet(gpointer m) {
    client_t *client = (client_t *)m;

    if(gtk_list_box_get_selected_row (client->m->box_message)){
        gtk_widget_show(GTK_WIDGET(client->m->b_box));
        gtk_widget_show(client->m->cancel_b);
        gtk_widget_show(client->m->edit_b);
        gtk_widget_show(client->m->delet_b);
    }
    else
    {
        gtk_widget_hide(GTK_WIDGET(client->m->b_box));
        gtk_widget_hide(client->m->cancel_b);
        gtk_widget_hide(client->m->edit_b);
        gtk_widget_hide(client->m->delet_b);
    }
    if (client-> exit == 1 )
        return FALSE;
    return TRUE;
}
void message_delet(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;

    gtk_container_remove(GTK_CONTAINER(client->m->box_message),
            GTK_WIDGET(gtk_list_box_get_selected_row (client->m->box_message)));

    //printf("result: %d\n", client->m->last_msg_id);

    client->m->row_num_list_gtk--;
}
gboolean clean_listbox(gpointer data){
    GtkListBox *box = (GtkListBox *)data;
    if(gtk_list_box_get_row_at_index (box,(gint)0)){
        gtk_container_remove(GTK_CONTAINER(box),
                GTK_WIDGET(gtk_list_box_get_row_at_index (box, (gint)0)));
        return TRUE;
    }
    else{
        return FALSE;
    }
}
void message_edit(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    gint index;
    client_t *client = (client_t *)data;
    GTK_WIDGET(gtk_list_box_get_selected_row (client->m->box_message));
    index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row (client->m->box_message));
    gtk_list_box_unselect_all(client->m->box_message);
}
void cancel_ch(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;
    gtk_list_box_unselect_all(client->m->box_message);
}
gboolean message_show(gpointer m) {
    received_messages *received_mess = (received_messages *)m;
    GtkTextView *view ;
    GtkTextBuffer *buffer;
    GtkTextIter end;
    view = GTK_TEXT_VIEW(gtk_text_view_new ());
    gtk_text_view_set_editable (view, FALSE);
    buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_wrap_mode ( view, GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_buffer(view, buffer);
    gtk_text_buffer_get_iter_at_offset(buffer, &end, 0);
    char time_buf[BUFFER_SZ];
    if (received_mess->message[0] != 0) {
        time_t time = (time_t)(atoi(received_mess->time));
        struct tm *ptm = localtime(&time);
        if (ptm == NULL) {
            puts("The localtime() function failed");
            return FALSE;
        }
        snprintf(time_buf, BUFFER_SZ, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        gtk_text_buffer_insert_interactive (buffer, &end, time_buf, -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, "   ", -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, received_mess->sender_name, -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, ": ", -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, received_mess->message, -1, TRUE );
        bzero(time_buf, BUFFER_SZ);
        gtk_container_add (GTK_CONTAINER(received_mess->client->m->box_message), GTK_WIDGET(view));
        received_mess->client->m->row_num_list_gtk++;
        received_mess->client->m->last_msg_id = received_mess->msg_id;
        gtk_widget_show (GTK_WIDGET(view));
        memset(received_mess->message, 0, sizeof(received_mess->message));
        memset(received_mess->sender_name, 0, sizeof(received_mess->sender_name));
    }

    if (received_mess->client->exit == 1)
        return FALSE;
    return TRUE;
}

void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}

void message_send(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    client_t *client = (client_t *)data;
    command cmd;
    char buffer[BUFFER_SZ];

    time_t rawtime = time(NULL);

    if (rawtime == -1) {
        puts("The time() function failed");
        return;
    }

    snprintf(buffer, BUFFER_SZ, "<%d> <%s> <%d>", client->active_chat_id, message_str, (int)rawtime);
    cmd.command = "<SEND>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, client);
    bzero(buffer, BUFFER_SZ);
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
