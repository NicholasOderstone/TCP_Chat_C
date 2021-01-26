#ifndef INTERFACE_H
#define INTERFACE_H

// INCLUDES
    #include <gtk/gtk.h>
    #include <stdlib.h>
    #include <string.h>
    #include "header.h"
//////////////////////////

// DEFINES

//////////////////////////

// STRUCTURES
typedef struct message_struct
{
    GtkWidget *view ;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
} message_s;
//////////////////////////

// GLOBAL VARIABLES
    GtkBuilder      *builder;
    GtkWidget       *window;
    char username_str [32], passoword_str[32], message_str[2048], port_str[5],
                ipv_str[16], username_str_s[32], nick_str_s[32], pass_str_s[32],
                r_pass_str_s[32];
    int is_exit;
    GtkEntry *message_entry, *ipv_entry, *port_entry;
    GtkSpinner *connection_spin;
//////////////////////////

// FUNCTIONS
    gboolean destroy();
    void init_interface();
    void init_connect_page();
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void username_changed();
    void password_changed();
    void send_message();
    void message_clear();
    void message_send();
    void username_s_changed();
    void nick_s_changed();
    void pass_s_changed();
    void r_pass_s_changed();
//////////////////////////

#endif
