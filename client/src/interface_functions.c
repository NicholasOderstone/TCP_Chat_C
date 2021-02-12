#include "../inc/interface.h"

void init_interface(int *argc, char ***argv, gpointer p_client) {
    //GObject *connect_b;
    GtkWidget *widget =  NULL;
    client_t *client = (client_t *)p_client;
    static gtk_utils_t m;
    gtk_utils_t *message_s = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    message_s = &m;
    client->m = (gtk_utils_t *)malloc(sizeof(gtk_utils_t *));
    client->m = message_s;
    client->m->root_x = 0;
    client->m->root_y = 0;
    gtk_init(argc, argv);
    open_login_page(widget, p_client);
}

/*void init_connect_page(GObject **p_connect_b, GtkBuilder **p_builder, gpointer gp_client) {
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(*p_builder, "connect_window"));
    gtk_builder_connect_signals(*p_builder, NULL);
    *p_connect_b = gtk_builder_get_object (*p_builder, "connect_b");
    gtk_widget_show(window);
    ipv_entry = GTK_ENTRY(gtk_builder_get_object(builder, "ipv_field"));
    port_entry = GTK_ENTRY(gtk_builder_get_object(builder, "port_field"));
    g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(open_login_page), gp_client);
	g_signal_connect(*p_connect_b, "clicked", G_CALLBACK(th_connect_to_server), gp_client);
    g_object_unref(*p_builder);
}*/

void open_signup_page(GtkWidget *widget, gpointer gp_client)
{
    GObject *login_p;
    GObject *signup_b;
    UNUSED(widget);
    client_t *client = (client_t *)gp_client;
    gtk_widget_hide(window);
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_s"));
    diff_p = GTK_LABEL(gtk_builder_get_object(builder, "diff_p"));
    username_e = GTK_LABEL(gtk_builder_get_object(builder, "username_ex"));
    gtk_widget_hide(GTK_WIDGET(diff_p));
    gtk_widget_hide(GTK_WIDGET(username_e));
    GtkWidget *login_p_image = gtk_image_new_from_file ("client/resources/arr_gray.png");
    login_p = gtk_builder_get_object (builder, "login_p");
    gtk_button_set_image (GTK_BUTTON(login_p), login_p_image);
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
    //client_t *client = (client_t *)gp_client;

    //gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    //gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner_l"));
    signup_p = gtk_builder_get_object (builder, "signup_p");
    login_b = gtk_builder_get_object (builder, "login_b");
    g_signal_connect(signup_p, "clicked", G_CALLBACK(open_signup_page), gp_client);
    g_signal_connect(login_b, "clicked", G_CALLBACK(func_login), gp_client);
    incorrect_l = GTK_LABEL(gtk_builder_get_object(builder, "incorrect_l"));
    incorrect_p = GTK_LABEL(gtk_builder_get_object(builder, "incorrect_p"));
    gtk_widget_hide(GTK_WIDGET(incorrect_l));
    gtk_widget_hide(GTK_WIDGET(incorrect_p));
    login = gtk_builder_get_object(builder, "login");
    password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    gtk_entry_set_visibility (password, FALSE);
    gtk_entry_set_icon_from_icon_name(password, GTK_ENTRY_ICON_SECONDARY,"view-reveal-symbolic");
    gtk_widget_show(window);
}

gboolean is_edit_delet(gpointer m) {
    client_t *client = (client_t *)m;

    if(gtk_list_box_get_selected_row (client->m->box_message)){
        gtk_widget_show(GTK_WIDGET(client->m->b_box));
        gtk_widget_show(client->m->cancel_b);
        gtk_widget_show(client->m->edit_b);
        gtk_widget_show(client->m->delet_b);
        gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), FALSE);
    }
    else
    {
        gtk_widget_hide(GTK_WIDGET(client->m->b_box));
        gtk_widget_hide(client->m->cancel_b);
        gtk_widget_hide(client->m->edit_b);
        gtk_widget_hide(client->m->delet_b);

    }
    if (client-> exit == 1)
        return FALSE;
    return TRUE;
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

void cancel_ch(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;
    gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), TRUE);
    gtk_list_box_unselect_all(client->m->box_message);
}

void new_chat(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    client_t *client = (client_t *)data;
    GtkWidget  *chat_name;
    static int i = 0;
    // printf("index new_chat: %d\n", i);
    i++;

    chat_name_d  = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name"));
    gtk_window_move(GTK_WINDOW(chat_name_d), client->m->root_x, client->m->root_y);
    gtk_widget_show(chat_name_d);
    chat_name = GTK_WIDGET(gtk_builder_get_object(builder, "name"));
    chatname_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name"));
}

void chat_menu(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    client_t *client = (client_t *)data;

    chat_menu_wind = GTK_WIDGET(gtk_builder_get_object(builder, "chat_dialog"));
    gtk_window_move(GTK_WINDOW(chat_menu_wind), client->m->root_x, client->m->root_y);
    gtk_widget_show(chat_menu_wind);
}

gboolean destroy() {
    gtk_main_quit();
    return TRUE;
}

gboolean chat_show(gpointer m) {
    static int last_added_chat_index = -1;
    chat_show_info_s *chat_show_info = (chat_show_info_s *)m;
    char last_msg_time_buf[BUFFER_SZ];
    int new_chat_index = chat_show_info->counter;

    // printf("new_chat_index: %d\nlast_added_chat_index: %d\n", new_chat_index, last_added_chat_index);

    if (new_chat_index > last_added_chat_index) {
        //printf("adding new chat %d with index %d\n", chat_show_info->chat->chat_id, new_chat_index);
        if (chat_show_info->chat->last_msg_time != -1) {
            time_t time = (time_t)chat_show_info->chat->last_msg_time;
            struct tm *ptm = localtime(&time);
            if (ptm == NULL) {
                puts("The localtime() function failed");
                return FALSE;
            }

            snprintf(last_msg_time_buf, BUFFER_SZ, "%s  %02d:%02d unread_msg_id: %d", chat_show_info->chat->chat_name, ptm->tm_hour, ptm->tm_min, chat_show_info->chat->f_unread_msg_id);
        }
        else {
            snprintf(last_msg_time_buf, BUFFER_SZ, "%s", chat_show_info->chat->chat_name);
        }
        chat_show_info->client->m->chat[new_chat_index] = gtk_button_new_with_label(last_msg_time_buf);
        /* GtkWidget *new_msg_image = gtk_image_new_from_file ("client/resources/new_msg.png");
        if (chat_show_info->chat->f_unread_msg_id != -1) {
            gtk_button_set_image(GTK_BUTTON(chat_show_info->client->m->chat[new_chat_index]), new_msg_image);
            gtk_button_set_image_position(GTK_BUTTON(chat_show_info->client->m->chat[new_chat_index]), GTK_POS_RIGHT);
        } */
        gtk_container_add(GTK_CONTAINER(chat_show_info->client->m->box_chat_list), GTK_WIDGET(chat_show_info->client->m->chat[new_chat_index]));
        gtk_widget_show(GTK_WIDGET(chat_show_info->client->m->chat[new_chat_index]));
        get_messages_request_s *get_messages_request = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        get_messages_request->chat = chat_show_info->chat;
        get_messages_request->client = chat_show_info->client;
        // get_messages_request_s *get_msg_buf = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        get_messages_request_s *get_msg_buf = get_messages_request;


        g_signal_connect(chat_show_info->client->m->chat[new_chat_index], "clicked", G_CALLBACK(get_msg_request), (gpointer)get_msg_buf);
        last_added_chat_index = new_chat_index;
        bzero(last_msg_time_buf, BUFFER_SZ);
    }

    if (chat_show_info->client->exit == 1)
        return FALSE;
    return TRUE;
}
void add_mem_wind(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    gtk_widget_hide(chat_menu_wind);
    client_t *client = (client_t *)data;
    GtkEntry *entr;
    entr = GTK_ENTRY(gtk_builder_get_object(builder, "search_user"));
    gtk_widget_set_sensitive(GTK_WIDGET(entr), TRUE);
    add_memwind = GTK_WIDGET(gtk_builder_get_object(builder, "add_user_chat"));
    gtk_window_move(GTK_WINDOW(add_memwind), client->m->root_x, client->m->root_y);
    gtk_widget_show(add_memwind);
}
void clean_adduser() {
    gtk_entry_set_text(GTK_ENTRY(adduser_entry), "");
}
void cancel_d_f() {
    gtk_widget_hide(chat_menu_wind);
}
void cancel_n_f() {
    gtk_widget_hide(chat_name_d);
}
void cancel_u_f() {
    gtk_widget_hide(add_memwind);
}
