#ifndef INTERFACE_H
#define INTERFACE_H

// INCLUDES
    #include <gtk/gtk.h>
    #include <stdlib.h>
    #include <string.h>

//////////////////////////

// DEFINES

//////////////////////////

// STRUCTURES

//////////////////////////

// GLOBAL VARIABLES
    GtkBuilder      *builder;
    gboolean destroy ();
    GtkWidget       *window;
    char username_str [32], passoword_str[32], message_str[2048], port_str[5],
                ipv_str[13];

//////////////////////////

// FUNCTIONS
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void username_changed();
    void password_changed();
    void send_message(GtkTextBuffer *buffer);
//////////////////////////

#endif
