#include "../inc/interface.h"

void username_changed(GtkEntry *e){
    sprintf(username_str,"%s", gtk_entry_get_text(e));
}
void chatname_changed(GtkEntry *e){
    sprintf(chatname_str,"%s", gtk_entry_get_text(e));
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

void message_changed(GtkEntry *e){
    sprintf(message_str, "%s", gtk_entry_get_text(e));
}
void user_searh_changed(GtkEntry *e) {
    sprintf(user_searh_str, "%s", gtk_entry_get_text(e));
}
