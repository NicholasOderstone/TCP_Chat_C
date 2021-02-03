#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#define BUFFER_SZ 2048

char* itoa(int num, char* buffer, int base) {
    int curr = 0;
 
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    int num_digits = 0;
 
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
            // Unsupported base. Return NULL
            return NULL;
    }
 
    num_digits += (int)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}


char* getAllUsers(char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || login || ',' || password || ',' || nick || ';' as MyColumn  from Users);", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
        //printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    

    return rez;
}

char* getAllChats(){
   char rez[10000];
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || name || ',' || g_chat || ';' as MyColumn  from CHATS);", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    

    return "rez";
}

char* getOneUser(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || login || ',' || password || ';' as MyColumn  from Users WHERE ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

char* getUserName(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select LOGIN from Users WHERE ID = ?;", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

char* getUserPassword(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select PASSWORD from Users WHERE ID = ?;", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

int getIdUserByUserName(char* login){
    sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return -1;
    }
    
    rc = sqlite3_prepare_v2(db, "select id from users where login = ?;", -1, &res, 0);    
    sqlite3_bind_text(res, 1, login, strlen(login), NULL);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return -1;
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
        //printf("%s\n", sqlite3_column_text(res, 0));
     }
     char rez[10000];
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return atoi(rez);
}

char* getIdUserByNick(char* nick, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select NICK || ','  as MyColumn  from Users WHERE NICK = ?);", -1, &res, 0);    
     sqlite3_bind_text(res, 1, nick, strlen(nick), NULL);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

int getIdChatByName(char* chat){
    sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return -1;
    }
    
    rc = sqlite3_prepare_v2(db, "select id from chats where name = ?;", -1, &res, 0);    
    sqlite3_bind_text(res, 1, chat, strlen(chat), NULL);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return -1;
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
        //printf("%s\n", sqlite3_column_text(res, 0));
     }
     char rez[10000];
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return atoi(rez);
}

char* getOneChats(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || name || ',' || DESCRIPTION || ';' as MyColumn  from CHATS WHERE ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

char* getChatName(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    rc = sqlite3_prepare_v2(db, "select NAME from CHATS WHERE ID = ?;", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

char* getOneMessage(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || chat_id || ',' || user_id || ',' || message || ',' || date || ',' || is_read || ';' as MyColumn  from MESSAGES WHERE ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

void updateNameUser(int id, char* name){
   char sql[500];
    sprintf (sql,"update USERS set LOGIN = '%s' where ID = '%d'", name, id);


    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    return;
}

void updatePasswordUser(int id, char* name){
   char sql[500];
    sprintf (sql,"update USERS set PASSWORD = '%s' where ID = '%d'", name, id);


    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    return;
}

void updateStatusUser(int id, char* Status){
   char sql[500];
    sprintf (sql,"update USERS set STATUS = '%s' where ID = '%d'", Status, id);


    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    return;
}

void updateTextMessage(int id, char* text){
   char sql[500];
    sprintf (sql,"update MESSAGES set MESSAGE = '%s' where ID = '%d'", text, id);


    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    return;
}

int insertUser(char* login, char* password, char* nick, char* status){
    char sql[500];
    sprintf (sql,"INSERT INTO USERS (LOGIN, PASSWORD, NICK, STATUS) VALUES ('%s','%s','%s','%s');",login,password,nick,status);
    
    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;

    int rc = sqlite3_open("data.db", &db);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    rc = sqlite3_prepare_v2(db, "select max(id) from USERS;", -1, &res, 0);    
    rc = sqlite3_step(res);

    
    int rez = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sqlite3_close(db);
    return rez;
}

int insertChat(char* name, char* description){
    char sql[500];
    sprintf (sql,"INSERT INTO CHATS (name, description) VALUES ('%s','%s');",name,description);


    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    rc = sqlite3_prepare_v2(db, "select max(id) from CHATS;", -1, &res, 0);    
    rc = sqlite3_step(res);


    int rez = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sqlite3_close(db);
    return rez;
}

int insertMessage(char* chat_id, char* user_id, char* message, int date, char* is_read){
    char sql[500];
    sprintf (sql,"INSERT INTO MESSAGES (chat_id, user_id, message, date, is_read) VALUES ('%s','%s','%s','%d','%s');",chat_id,user_id,message,date,is_read);
    
    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;
   
    int rc = sqlite3_open("data.db", &db);
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    
    rc = sqlite3_prepare_v2(db, "select max(id) from MESSAGES;", -1, &res, 0);    
    rc = sqlite3_step(res);

    int rez = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sqlite3_close(db);
    return rez;
}

void deleteUser(char* id){
    char sql[500];
    sprintf (sql,"delete from users where id = %s;",id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

void deleteChat(char* id){
    char sql[500];
    sprintf (sql,"delete from CHATS where id = %s;",id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

void deleteMessage(char* id){
    char sql[500];
    sprintf (sql,"delete from MESSAGES where id = %s;",id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

void insertInBlockList(int user_id, int block_user_id){
    char sql[500];
    sprintf (sql,"INSERT INTO BLOCK_LIST (USER_ID, BLOCK_USER_ID) VALUES ('%d','%d');",user_id, block_user_id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

void insertInUserInChats(int user_id, int chat_id){
    char sql[500];
    sprintf (sql,"INSERT INTO USER_IN_CHAT (USER_ID, CHAT_ID) VALUES ('%d','%d');",user_id, chat_id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

char* getUserChats(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select CHAT_ID || ',' as MyColumn  from USER_IN_CHAT WHERE USER_ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    
    rc = sqlite3_step(res);

    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

char* getBlockList(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select BLOCK_USER_ID || ',' as MyColumn  from BLOCK_LIST WHERE USER_ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }    
    
    rc = sqlite3_step(res);
    
     if (rc == SQLITE_ROW) {
       // printf("%s\n", sqlite3_column_text(res, 0));
     }
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

void deleteFromBlock(int user_id, int block_user_id){
    char sql[500];
    sprintf (sql,"delete from BLOCK_LIST where user_id = %d and block_user_id = %d;",user_id, block_user_id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

void deleteFromChat(int user_id, int chat_id){
    char sql[500];
    sprintf (sql,"delete from USER_IN_CHAT where user_id = %d and CHAT_ID = %d;",user_id, chat_id);


    sqlite3 *db;
    char *err_msg = 0;
   
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
   

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
    
    return;
}

char* getAllMesFromChat(int id, char* rez){
   sqlite3 *db;
    sqlite3_stmt *res;
    
    
    int rc = sqlite3_open("data.db", &db);

    // sprintf(sql, "SELECT Count(*) FROM MESSAGES WHERE ID = '%d",id);
    // rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    // sqlite3_bind_int(res, 1, id);
    // rc = sqlite3_step(res);
    // //sprintf(login, "%s\n", sqlite3_column_text(res, 0));
    // printf("%s", sqlite3_column_text(res, 0));
    
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || chat_id || ',' || user_id || ',' || message || ',' || date || ',' || is_read || ';' as MyColumn  from MESSAGES WHERE CHAT_ID = ?);", -1, &res, 0);    
    sqlite3_bind_int(res, 1, id);
    
    
    rc = sqlite3_step(res);
    
    sprintf(rez, "%s\n", sqlite3_column_text(res, 0));
    

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

void insertUSER_TO_CHAT(int user_id, int chat_id){
    char sql[500];
    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;

    char login[200];
    char name[200];

    int rc = sqlite3_open("data.db", &db);

    sprintf (sql, "select LOGIN from Users WHERE ID = '%d';", user_id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    sqlite3_bind_text(res, 1, login, strlen(login), NULL);
    rc = sqlite3_step(res);
    sprintf(login, "%s", sqlite3_column_text(res, 0));
    printf("%s", login);

    sprintf (sql, "select NAME from CHATS WHERE ID = '%d';", chat_id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    sqlite3_bind_text(res, 1, name, strlen(name), NULL);
    rc = sqlite3_step(res);
    sprintf(name, "%s", sqlite3_column_text(res, 0));
    printf("%s", name);

    sprintf (sql,"INSERT INTO USER_IN_CHAT (USER_ID, LOGIN, CHAT_ID, NAME) VALUES ('%d','%s','%d','%s');",user_id,login,chat_id,name);
    printf("%s", sql);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    sqlite3_finalize(res);
    sqlite3_close(db);
    return;
    //INSERT INTO USER_IN_CHAT (USER_ID, LOGIN, CHAT_ID, NAME) VALUES ('1','test1','1','chat1');
}

void insertUSER_TO_CHAT2(int user_id, char* login, int chat_id, char* name){
    char sql[500];
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("data.db", &db);
    sprintf (sql,"INSERT INTO USER_IN_CHAT (USER_ID, LOGIN, CHAT_ID, NAME) VALUES ('%d','%s','%d','%s');",user_id,login,chat_id,name);
    printf("%s", sql);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    sqlite3_close(db);
    return;
}


int getLastId(int id){

    sqlite3 *db;
    sqlite3_stmt *res;
    int rez;
    int rc = sqlite3_open("data.db", &db);
    char sql[500];
    sprintf(sql, "SELECT MAX(ID) FROM MESSAGES WHERE CHAT_ID = '%d'", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    rc = sqlite3_step(res);
    rez = sqlite3_column_int(res, 0);

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

typedef struct message_s {
        char chat_id[10];
        char msg_id[10];
        char sender[32];
        char text[BUFFER_SZ];
        char time[50];
    } msg_t;

msg_t *pack_msg_from_chat(int id){
    if (getLastId(id) == 0) return NULL;
    char sql_req[500];
    char buffer[4096];
    msg_t *new_msg = (msg_t *)malloc(sizeof(msg_t));
    int last_msg_from_chat_id = getLastId(id);
    static int from = 1;

    if (from == 0) {
        from = 1;
        return NULL;
    }

    sqlite3 *db;
    sqlite3_stmt *res;
   
    
    int rc = sqlite3_open("data.db", &db);
    
   
    while(1){
        sprintf (sql_req,"select group_concat(MyColumn, '') from (select id || ' , ' || CHAT_ID || ' , ' || USER_ID || ' , ' || DATE || ' , ' || MESSAGE || '\n' as MyColumn from MESSAGES where CHAT_ID = %d and id = %d);",id, from);
        rc = sqlite3_prepare_v2(db, sql_req, -1, &res, 0);    
        rc = sqlite3_step(res);
        if (sqlite3_column_text(res, 0) != NULL){
            if (sqlite3_column_int(res, 0) == last_msg_from_chat_id) {
                from = 0;
                sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
                sscanf(buffer, "%s , %s , %s , %s , %[^\n]", new_msg->msg_id, new_msg->chat_id, new_msg->sender, new_msg->time, new_msg->text);
                break;
            }
            from = sqlite3_column_int(res, 0) + 1;
            sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
            sscanf(buffer, "%s , %s , %s , %s , %[^\n]", new_msg->msg_id, new_msg->chat_id, new_msg->sender, new_msg->time, new_msg->text);
            break;
        }
        else {
            from++;
        }
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return new_msg;
}

typedef struct chat_s {
    char chat_id[10];
    char chat_name[32];
} chat_t;

chat_t *pack_user_chats(int id){
    
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open("data.db", &db);
    char sql[500];
    sprintf(sql, "SELECT MAX(ID) FROM USER_IN_CHAT WHERE USER_ID = '%d'", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    rc = sqlite3_step(res);

    if(sqlite3_column_int(res, 0) == 0){
        sqlite3_finalize(res);
        sqlite3_close(db);
        return NULL;
    }
    int last_chat_from_user_id = sqlite3_column_int(res, 0);
    // printf("last_chat_from_user_id: \"%d\"\n", last_chat_from_user_id);
    

    //char sql_req[500];
    char buffer[4096];
    chat_t *new_chat = (chat_t *)malloc(sizeof(chat_t));
    static int from = 1;

    if (from == 0) {
        from = 1;
        return NULL;
    }
    /* from = 5;
    sprintf (sql,"select group_concat(MyColumn, '') from (select CHAT_ID || ',' || NAME as MyColumn from USER_IN_CHAT where USER_ID = %d and id = %d);",id, from);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);  
    rc = sqlite3_step(res);
    printf("\"%s\"", sqlite3_column_text(res, 0));
    return NULL; */


    while(1){
        sprintf (sql,"select group_concat(MyColumn, '') from (select CHAT_ID || ' , ' || NAME as MyColumn from USER_IN_CHAT where USER_ID = %d and id = %d);",id, from);
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);  
        rc = sqlite3_step(res);
        if (sqlite3_column_text(res, 0) != NULL){
            // printf("\"%s || %d\n", sqlite3_column_text(res, 0), sqlite3_column_int(res, 0));
            if (from == last_chat_from_user_id) {
                // write(1,"8",1);
                from = 0;
                sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
                sscanf(buffer, "%s , %s", new_chat->chat_id, new_chat->chat_name);
                
                break;
            }
            from++;
            sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
            sscanf(buffer, "%s , %s", new_chat->chat_id, new_chat->chat_name);
            break;
        }
        else {
            from++;
        }
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return new_chat;
}

    typedef struct user_s {
        char user_id[10];
        char user_name[32];
    } user_t;

user_t *pack_chat_members(int id){
    
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open("data.db", &db);
    char sql[500];
    sprintf(sql, "SELECT MAX(ID) FROM USER_IN_CHAT WHERE CHAT_ID = '%d'", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    rc = sqlite3_step(res);

    if(sqlite3_column_int(res, 0) == 0){
        sqlite3_finalize(res);
        sqlite3_close(db);
        return NULL;
    }
    int last_user_from_chat_id = sqlite3_column_int(res, 0);
    // printf("last_chat_from_user_id: \"%d\"\n", last_chat_from_user_id);
    

    //char sql_req[500];
    char buffer[4096];
    user_t *new_user = (user_t *)malloc(sizeof(user_t));
    static int from = 1;

    if (from == 0) {
        from = 1;
        return NULL;
    }

    while(1){
        sprintf (sql,"select group_concat(MyColumn, '') from (select USER_ID || ' , ' || LOGIN as MyColumn from USER_IN_CHAT where CHAT_ID = %d and id = %d);",id, from);
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);  
        rc = sqlite3_step(res);
        if (sqlite3_column_text(res, 0) != NULL){
            // printf("\"%s || %d\n", sqlite3_column_text(res, 0), sqlite3_column_int(res, 0));
            if (from == last_user_from_chat_id) {
                // write(1,"8",1);
                from = 0;
                sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
                sscanf(buffer, "%s , %s", new_user->user_id, new_user->user_name);
                
                break;
            }
            from++;
            sprintf(buffer, "%s\n", sqlite3_column_text(res, 0));
            sscanf(buffer, "%s , %s", new_user->user_id, new_user->user_name);
            break;
        }
        else {
            from++;
        }
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return new_user;
}



int main() {
    //  char rez[10000];


    //GET

    //getAllUsers(&rez);  //work
    //getOneUser(1, &rez);//work
    //getOneChats(2, &rez); // work
    //getOneMessage(1, &rez);//work
    //getChatName(1, &rez);
    //getUserChats(1, &rez);//work
    //getBlockList(1, &rez);//work
    //getAllMesFromChat(1, &rez);//work
        //printf("%d", getIdUserByUserName("THEBESTUSER"));//work
        //printf("%d", getIdChatByName("New chat"));//work
        //printf("%d", getIdUserByUserName("AAA"));
    //getUserName(1, rez);//work
    //getUserPassword(1, rez);//work
    //getIdUserByNick("3", rez);
//printf("%d", );
//getLastId(1);


    //INSERT

    insertUser("test1", "pass1", "3", "4");//work
    insertUser("test2", "pass2", "3", "4");
    insertUser("test3", "pass3", "3", "4");
    insertUser("test4", "pass4", "3", "4");
    insertUser("test5", "pass5", "3", "4");

    insertChat("chat1", "des0");
    insertChat("chat2", "des0");
    insertChat("chat3", "des0");
    insertChat("chat4", "des0");
    insertChat("chat5", "des0");


    //insertChat("New chat", "des0");//work
    /* insertMessage("3","2","something tam", (int)time(NULL), "0");
    insertMessage("2","2","something tam", (int)time(NULL), "0");
    insertMessage("3","2","something tam", (int)time(NULL), "0");
    insertMessage("3","2","something tam", (int)time(NULL), "0");
    insertMessage("1","2","something tam", (int)time(NULL), "0");
    insertMessage("2","2","something tam", (int)time(NULL), "0");
    
    insertMessage("3","2","something tam", (int)time(NULL), "0");
    insertMessage("2","5","something tam", (int)time(NULL), "0");
    insertMessage("1","4","something tam", (int)time(NULL), "0");
    insertMessage("2","3","something tam", (int)time(NULL), "0");
    insertMessage("3","3","something tam", (int)time(NULL), "0"); */
    //work
        //printf("%d", insertUser("AAA", "2", "3", "4"));
        //printf("%d", insertChat("New chat", "des0"));
        //printf("%d", insertMessage("1","2","something tam", "2010 02 13:11:00", "0"));
    //insertInBlockList(1, 3);//work
    //insertInUserInChats(1, 3);//work
        

    //insertUSER_TO_CHAT(1,  1);//допиши - дописал
    // insertUSER_TO_CHAT2(1, "test1", 1, "chat1");
    // insertUSER_TO_CHAT2(2, "test2", 1, "chat1");
    // insertUSER_TO_CHAT2(3, "test3", 1, "chat1");
    // insertUSER_TO_CHAT2(4, "test4", 1, "chat1");
    // insertUSER_TO_CHAT2(5, "test5", 1, "chat1");

    // insertUSER_TO_CHAT2(1, "test1", 2, "chat2");
    // insertUSER_TO_CHAT2(2, "test2", 2, "chat2");
    // insertUSER_TO_CHAT2(3, "test3", 2, "chat2");
    // insertUSER_TO_CHAT2(4, "test4", 2, "chat2");

    // insertUSER_TO_CHAT2(5, "test5", 3, "chat3");
    // insertUSER_TO_CHAT2(1, "test1", 3, "chat3");
    // insertUSER_TO_CHAT2(2, "test2", 3, "chat3");
    // insertUSER_TO_CHAT2(3, "test3", 3, "chat3");


    //DELETE

    //deleteUser("7"); //work
    //deleteChat("7");//work
    //deleteMessage("4");//work
    //deleteFromBlock(1,3);//work
    //deleteFromChat(1,3);//work


    //UPDATE

    //updateNameUser(1, "WOOOOORK");//work
    //updatePasswordUser(1, "NEW Pawssword");//work
    //updateStatusUser(1, "mew se");
    //updateTextMessage(1, "new mess");





//     msg_t *new_msg = NULL;
//     int chat_id = 3;
//     new_msg = pack_msg_from_chat(chat_id);
//     while (new_msg != NULL) {
//         printf("\n\t\t\tMSG from CHAT %d: chat_id: %s, msg_id: %s, sender: %s, text: \"%s\", time: %s;\n", chat_id, new_msg->chat_id, new_msg->msg_id, new_msg->sender, new_msg->text, new_msg->time);
//         new_msg = pack_msg_from_chat(chat_id);
//     }

//     chat_t *new_chat = NULL;
//     int user_id = 3;
//     new_chat = pack_user_chats(user_id);
//     while (new_chat != NULL) {
//         printf("\n\t\t\tCHAT of USER %d: chat_id: %s, chat_name: %s;\n", user_id, new_chat->chat_id, new_chat->chat_name);
//         new_chat = pack_user_chats(user_id);
//     }


//   user_t *new_user = NULL;
//     chat_id = 3;
//     new_user = pack_chat_members(chat_id);
//     while (new_user != NULL) {
//         printf("\n\t\t\tUSER in CHAT %d: user_id: %s, user_name: %s;\n", chat_id, new_user->user_id, new_user->user_name);
//         new_user = pack_chat_members(chat_id);
//     }

// printf("%s", rez);
}
