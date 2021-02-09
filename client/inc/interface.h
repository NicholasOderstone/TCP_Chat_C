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
    GtkWidget       *window, *chat_name_d, *chat_menu_wind;
    char username_str [32], passoword_str[32], message_str[2048], port_str[5],
                ipv_str[16], username_str_s[32], nick_str_s[32], pass_str_s[32],
                r_pass_str_s[32], chatname_str[32];
    int is_exit;
    GtkEntry *message_entry, *ipv_entry, *port_entry, *chatname_entry;
    GtkSpinner *connection_spin;
    //GtkListBox *box_chat_list;
    // GtkWidget *chat[MAX_CHATS];
    GtkButton *ch_b, *chat_lbl, *edit_b;
    GtkLabel *chat_label;
//////////////////////////

// FUNCTIONS
    gboolean destroy();
    void init_interface();
    //void init_connect_page();
    void open_signup_page();
    void open_login_page();
    void open_main_page();
    void username_changed();
    void password_changed();
    //void show_my_msg();
    void message_clear();
    void message_send();
    void username_s_changed();
    void nick_s_changed();
    void pass_s_changed();
    void r_pass_s_changed();
    void del_message();
    gboolean message_show();
    gboolean chat_show();
    gboolean is_edit_delet();
    void message_delet();
    void message_edit();
    void cancel_ch();
    gboolean clean_listbox();
    void my_popup_handler();
    void new_chat();
    void chat_menu();
    void chatname_clear();
    void close_ch_dialog();
    //////////////////////////

#endif
