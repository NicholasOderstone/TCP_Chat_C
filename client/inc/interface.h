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

//////////////////////////

// GLOBAL VARIABLES
    GtkBuilder      *builder;
    GtkWidget       *window;
    char username_str [32], passoword_str[32], message_str[2048], port_str[5],
                ipv_str[16];
    int is_exit;

//////////////////////////

// FUNCTIONS
    gboolean destroy();
    void init_interface(GtkBuilder **p_builder, GtkWidget **p_window);
    void init_connect_page(GObject **p_connect_b,GtkBuilder **p_builder, gpointer gp_client);
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void username_changed();
    void password_changed();
    void send_message(GtkTextBuffer *buffer);
//////////////////////////

#endif