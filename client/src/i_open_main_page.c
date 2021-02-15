#include "../inc/interface.h"

void open_main_page(GtkWidget *widget, gpointer gp_client)
{
    UNUSED(widget);


    client_t *client = (client_t *)gp_client;
    GtkLabel *user_name;
    //GtkListBox *box;
    GtkImage *avatar;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    //client->m = (gtk_utils_t *)malloc(sizeof(gtk_utils_t));
    //client->m = message_s;

    GtkWidget *send_b_image = gtk_image_new_from_file ("client/resources/send_b_img.png");
    GtkWidget *edit_b_image = gtk_image_new_from_file ("client/resources/edit.png");
    GtkWidget *add_chat_b_image = gtk_image_new_from_file ("client/resources/add_chat.png");
    GtkButton *add_chat;

    gtk_css_provider_load_from_path(cssProvider, "client/resources/gtk.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_get_position (GTK_WINDOW(window), &client->m->root_x, &client->m->root_y);
    gtk_widget_hide(window);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "client/resources/messanger.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_set_title (GTK_WINDOW(window), "PLACE");
    gtk_window_move(GTK_WINDOW(window), client->m->root_x, client->m->root_y);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    //ПЕРЕДЕЛАЙ ОКНА В ОКНА А НЕ ВИДЖЕТЫ
    connection_spin = GTK_SPINNER(gtk_builder_get_object(builder, "connection_spinner"));
    edit_b = GTK_BUTTON(gtk_builder_get_object (builder, "edit_b"));
    add_user = GTK_BUTTON(gtk_builder_get_object (builder, "add_member"));
    gtk_button_set_image (edit_b, edit_b_image);
    gtk_widget_hide(GTK_WIDGET(edit_b));
    chat_label  = GTK_LABEL(gtk_builder_get_object(builder, "name_chat"));
    gtk_widget_set_name(GTK_WIDGET(chat_label), "name_chat1");
    user_name  = GTK_LABEL(gtk_builder_get_object(builder, "name_user"));
    no_chat  = GTK_LABEL(gtk_builder_get_object(builder, "not_chat"));
    gtk_widget_show(GTK_WIDGET(no_chat));
    gtk_label_set_text(user_name, client->login);
    add_chat = GTK_BUTTON(gtk_builder_get_object(builder, "add_chat"));
    gtk_button_set_image(add_chat, add_chat_b_image);
    cancel_n  = GTK_BUTTON(gtk_builder_get_object(builder, "cancel_n"));
    cancel_u  = GTK_BUTTON(gtk_builder_get_object(builder, "cancel_u"));
    avatar = GTK_IMAGE(gtk_builder_get_object(builder, "avatar"));
    gtk_image_set_from_file(avatar, "client/resources/avatar.jpg");
    //chat_lbl = GTK_BUTTON(gtk_builder_get_object (builder, "chat_label"));
    //gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), FALSE);
    //gtk_button_set_label(chat_lbl, "");
    send_b = gtk_builder_get_object (builder, "send_buttom");
    gtk_button_set_image (GTK_BUTTON (send_b), send_b_image);
    client->m->box_message = GTK_LIST_BOX(gtk_builder_get_object(builder, "message_list"));
    client->m->box_chat_list = GTK_LIST_BOX(gtk_builder_get_object(builder, "chat_list"));
    //gtk_text_buffer_create_tag(message_s->buffer, "gray_bg", "background","gray", NULL);
    //gtk_text_buffer_insert_with_tags_by_name (message_s->buffer, &message_s->end, "name", -1, "gray_bg", NULL);
    message_entry = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
    gtk_widget_hide(GTK_WIDGET(message_entry));
    gtk_widget_hide(GTK_WIDGET(client->m->box_message));
    gtk_widget_hide(GTK_WIDGET(send_b));
    adduser_entry = GTK_ENTRY(gtk_builder_get_object(builder, "search_user"));
    gtk_widget_show(GTK_WIDGET(user_name));
    //g_signal_connect(send_b, "clicked", G_CALLBACK(show_my_msg), (gpointer)message_s);
    //gtk_binding_entry_add_signall()
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_send), gp_client);
    g_signal_connect(send_b, "clicked", G_CALLBACK(message_clear), NULL);
    gtk_list_box_set_selection_mode(client->m->box_message, GTK_SELECTION_SINGLE);
    gtk_list_box_set_activate_on_single_click (client->m->box_message, FALSE);
    //gdk_threads_add_idle(is_edit_delet, (gpointer)client);
    g_signal_connect(client->m->box_message, "selected-rows-changed", G_CALLBACK(is_edit_delet),gp_client);
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
    g_signal_connect(edit_b, "clicked", G_CALLBACK(edit_msg_request), gp_client);


    new_chat_request_s *new_chat_r = (new_chat_request_s *)malloc(sizeof(new_chat_r));
    new_chat_r->client = client;
    del_chat_request_s *leave_chat_r = (del_chat_request_s *)malloc(sizeof(del_chat_request_s));
    leave_chat_r->chat_id = client->active_chat_id;
    leave_chat_r->client = client;
    ch_b = GTK_BUTTON(gtk_builder_get_object(builder, "confirm"));
    add_mem = GTK_BUTTON(gtk_builder_get_object(builder, "add_user"));
    leave_chat = GTK_BUTTON(gtk_builder_get_object(builder, "delete_chat"));
    gtk_widget_set_sensitive(GTK_WIDGET(add_user), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(leave_chat), FALSE);
    g_signal_connect(message_entry, "activate", G_CALLBACK(message_send), gp_client);
    g_signal_connect(message_entry, "activate", G_CALLBACK(message_clear), NULL);
    g_signal_connect(add_user, "clicked", G_CALLBACK(add_mem_wind), gp_client);
    g_signal_connect(add_user, "clicked", G_CALLBACK(clean_adduser), NULL);
    g_signal_connect(add_mem, "clicked", G_CALLBACK(add_user_to_chat_request), gp_client);
    g_signal_connect(leave_chat, "clicked", G_CALLBACK(leave_chat_request), leave_chat_r);
    g_signal_connect(ch_b, "clicked", G_CALLBACK(new_chat_request), (gpointer)new_chat_r);
    g_signal_connect(ch_b, "clicked", G_CALLBACK(chatname_clear), NULL);
    //g_signal_connect(chat_lbl, "clicked", G_CALLBACK(chat_menu), gp_client);
    g_signal_connect(add_chat, "clicked", G_CALLBACK(new_chat), gp_client);
    g_signal_connect(cancel_n, "clicked", G_CALLBACK(cancel_n_f),  NULL);
    g_signal_connect(cancel_u, "clicked", G_CALLBACK(cancel_u_f),  NULL);
}
