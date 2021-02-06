#include "../inc/interface.h"

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    UNUSED(widget);

    GObject *send_b;
    client_t *client = (client_t *)gp_client;
    GtkButton *menu_b, *add_user_b;
    GtkMenu *menu;
    GtkWidget *menu_new_chat, *menu_join_chat;
    //GtkListBox *box;

    //GtkCssProvider *cssProvider = gtk_css_provider_new();


    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    GtkWidget *menu_b_image = gtk_image_new_from_file ("client/resources/menu.png");
    GtkWidget *add_user_b_image = gtk_image_new_from_file ("client/resources/add_user.png");


    //gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    //gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
    //                           GTK_STYLE_PROVIDER(cssProvider),
    //                           GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));

    menu_b = GTK_BUTTON(gtk_builder_get_object (builder, "main_menu"));
    add_user_b = GTK_BUTTON(gtk_builder_get_object (builder, "add_user"));
    add_user_b = GTK_BUTTON(gtk_builder_get_object (builder, "add_user"));

    gtk_button_set_image (menu_b, menu_b_image);
    gtk_button_set_image (add_user_b, add_user_b_image);
    menu_new_chat = gtk_menu_item_new_with_label ("Add Chat");
    menu_join_chat = gtk_menu_item_new_with_label ("Join Chat");
    menu = GTK_MENU(gtk_builder_get_object (builder, "menu"));
    gtk_menu_button_set_popup (GTK_MENU_BUTTON(menu_b), GTK_WIDGET(menu));


    gtk_menu_attach (menu, menu_new_chat, 0, 1, 0, 1);
    gtk_menu_attach (menu, menu_join_chat, 0, 1, 1, 2);
    gtk_widget_show_all(GTK_WIDGET(menu));

    box_chat_list = GTK_LIST_BOX(gtk_builder_get_object(builder, "chat_list"));
    //get_messages_request_s *get_messages_request = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
    /*chat[0] = gtk_button_new_with_label("name");
    gtk_container_add(GTK_CONTAINER(box_chat_list), GTK_WIDGET(chat[0]));
    gtk_widget_show(GTK_WIDGET(chat[0]));
    //gtk_widget_show(GTK_WIDGET(box_chat_list));
    get_messages_request->chat = current;
    get_messages_request->client = client;
    get_messages_request_s *get_msg_buf = get_messages_request;
    g_signal_connect(chat[i], "clicked", G_CALLBACK(get_msg_request), (gpointer)get_msg_buf);*/


    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);

    client->m->box_message = GTK_LIST_BOX(gtk_builder_get_object(builder, "message_list"));
    //gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    //gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->end, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
    
    //g_signal_connect(send_b, "clicked", G_CALLBACK(show_my_msg), (gpointer)message_s);
    //gtk_binding_entry_add_signall()
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    gtk_list_box_set_selection_mode(client->m->box_message, GTK_SELECTION_SINGLE);
    gtk_list_box_set_activate_on_single_click (client->m->box_message, FALSE);
    gdk_threads_add_idle(is_edit_delet, (gpointer)client);
    client->m->cancel_b = GTK_WIDGET(gtk_builder_get_object (builder, "cancel_b"));
    client->m->edit_b = GTK_WIDGET(gtk_builder_get_object (builder, "ed_b"));
    client->m->delet_b = GTK_WIDGET(gtk_builder_get_object (builder, "del_b"));
    client->m->b_box = GTK_BUTTON_BOX(gtk_builder_get_object(builder, "ed_del_box"));
    gtk_widget_hide(GTK_WIDGET(client->m->b_box));
    gtk_widget_hide(client->m->cancel_b);
    gtk_widget_hide(client->m->edit_b);
    gtk_widget_hide(client->m->delet_b);
    g_signal_connect(client->m->delet_b, "clicked", G_CALLBACK(message_delet),gp_client);
    g_signal_connect(client->m->edit_b, "clicked", G_CALLBACK(message_edit),gp_client);
    g_signal_connect(client->m->cancel_b, "clicked", G_CALLBACK(cancel_ch),gp_client);


    new_chat_request_s *new_chat_r = (new_chat_request_s *)malloc(sizeof(new_chat_r));
    new_chat_r->client = client;
    ch_b = GTK_BUTTON(gtk_builder_get_object(builder, "confirm"));
    g_signal_connect(ch_b, "clicked", G_CALLBACK(new_chat_request), (gpointer)new_chat_r);
    g_signal_connect(ch_b, "clicked", G_CALLBACK(chatname_clear), NULL);
    g_signal_connect(menu_new_chat, "activate", G_CALLBACK(new_chat), gp_client);

    //g_signal_connect(message_s->view, "move-cursor", G_CALLBACK(del_message), (gpointer)message_s->buffer);

}
