#ifndef HEADER_H
#define HEADER_H

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
    gboolean destroy (GtkWidget *widget);
    GtkWidget       *window;
    char username_str [32], passoword_str[32];

//////////////////////////

// FUNCTIONS
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void login_changed();
    void password_changed();

//////////////////////////

#endif
