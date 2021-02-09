#include "../inc/interface.h"

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
