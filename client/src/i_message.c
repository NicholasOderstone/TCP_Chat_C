#include "../inc/interface.h"

void message_delet(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    gint index;
    client_t *client = (client_t *)data;
    index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row (client->m->box_message));

    msg_id_q *current = client->msg_id_q_head;

    while (index) {
        current = current->next;
        index--;
    }
    printf("deleted: msd_id -- %d\n", current->msg_id);
    del_msg_request_s *delete_msg = (del_msg_request_s *)malloc(sizeof(del_msg_request_s));
    delete_msg->msg_id = current->msg_id;
    delete_msg->client = client;
    delete_msg_request(delete_msg);
    //display_msg_id_q(&client->msg_id_q_head);

    client->m->row_num_list_gtk--;
}

void message_edit(GtkWidget *widget, gpointer data){
    UNUSED(widget);
    gint index;
    client_t *client = (client_t *)data;
    GTK_WIDGET(gtk_list_box_get_selected_row (client->m->box_message));
    index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row (client->m->box_message));

    msg_id_q *current = client->msg_id_q_head;

    while (index) {
        current = current->next;
        index--;
    }
    printf("edited: msd_id -- %d\n", current->msg_id);
    edit_msg_request_s *edit_msg = (edit_msg_request_s *)malloc(sizeof(edit_msg_request_s));
    edit_msg->msg_id = current->msg_id;
    edit_msg->new_text = strdup("edited_text");
    edit_msg->client = client;
    edit_msg_request(edit_msg);
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
        gtk_text_buffer_insert_interactive (buffer, &end, itoa(received_mess->msg_id, 10), -1, TRUE );
        snprintf(time_buf, BUFFER_SZ, "  --  %02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        gtk_text_buffer_insert_interactive (buffer, &end, time_buf, -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, "   ", -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, received_mess->sender_name, -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, ": ", -1, TRUE );
        gtk_text_buffer_insert_interactive (buffer, &end, received_mess->message, -1, TRUE );
        bzero(time_buf, BUFFER_SZ);
        gtk_container_add (GTK_CONTAINER(received_mess->client->m->box_message), GTK_WIDGET(view));
        received_mess->client->m->row_num_list_gtk++;
        to_msg_id_q(received_mess->msg_id, &received_mess->client->msg_id_q_head);
        gtk_widget_show (GTK_WIDGET(view));
        gtk_container_set_focus_child(GTK_CONTAINER(received_mess->client->m->box_message),
            GTK_WIDGET(gtk_list_box_get_row_at_index (received_mess->client->m->box_message, received_mess->client->m->row_num_list_gtk)));
        //gtk_widget_grab_focus (GTK_WIDGET(gtk_list_box_get_row_at_index (received_mess->client->m->box_message, received_mess->client->m->row_num_list_gtk)));
        memset(received_mess->message, 0, sizeof(received_mess->message));
        memset(received_mess->sender_name, 0, sizeof(received_mess->sender_name));
    }
    
    if (received_mess->client->exit == 1)
        return FALSE;
    return TRUE;
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

void del_message(GtkTextBuffer *m){
    GtkTextMark * del_mark;
    GtkTextBuffer *mess = (GtkTextBuffer *)m;
    del_mark = gtk_text_buffer_get_selection_bound (mess);
    gtk_text_buffer_delete_mark(mess, del_mark);
    printf("%s\n", "work");
}
