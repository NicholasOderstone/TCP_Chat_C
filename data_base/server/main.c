#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

int getLastId(){

    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open("data.db", &db);
    rc = sqlite3_prepare_v2(db, "select max(id) from CHATS;", -1, &res, 0);    
    rc = sqlite3_step(res);
    int rez = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
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

int insertMessage(char* chat_id, char* user_id, char* message, char* date, char* is_read){
    char sql[500];
    sprintf (sql,"INSERT INTO MESSAGES (chat_id, user_id, message, date, is_read) VALUES ('%s','%s','%s','%s','%s');",chat_id,user_id,message,date,is_read);
    
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
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select CHAT_ID || ',' as MyColumn  from USER_IN_CHAT WHERE USER_ID = ?);", -1, &res, 0);    
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
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || chat_id || ',' || user_id || ',' || message || ',' || date || ',' || is_read || ';' as MyColumn  from MESSAGES WHERE CHAT_ID = ?);", -1, &res, 0);    
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



int main(int argc, char* argv[]) {
    char rez[10000];

    //getAllUsers(&rez);  //work

    //getOneUser(1, &rez);//work
   //printf("%s", rez);

    //getOneChats(2, &rez); // work
    //getOneMessage(1, &rez);//work
    //printf("%s", rez);

   //insertUser("AAA", "2", "3", "4");//work
  //insertChat("New chat", "des0");//work
   //insertMessage("1","2","something tam", "2010 02 13:11:00", "0");//work
   
       //printf("%d", insertUser("AAA", "2", "3", "4"));
       //printf("%d", insertChat("New chat", "des0"));
        //printf("%d", insertMessage("1","2","something tam", "2010 02 13:11:00", "0"));


   
   //deleteUser("7"); //work
   //deleteChat("7");//work
   //deleteMessage("4");//work

    //insertInBlockList(1, 3);//work

    //insertInUserInChats(1, 3);//work

    //getUserChats(1, &rez);//work
    //getBlockList(1, &rez);//work

    //deleteFromBlock(1,3);//work
    //deleteFromChat(1,3);//work
    //getAllMesFromChat(1, &rez);//work
    //printf("%d", getIdUserByUserName("THEBESTUSER"));//work
    //printf("%d", getIdChatByName("New chat"));//work
    //getUserName(1, rez);//work
    //getUserPassword(1, rez);//work
    //updateNameUser(1, "WOOOOORK");//work
    //updatePasswordUser(1, "NEW Pawssword");//work
    //updateStatusUser(1, "mew se");
    //updateTextMessage(1, "new mess");

    //printf("%d", getIdUserByUserName("AAA"));
    //getIdUserByNick("3", rez);

//printf("%s", rez);

}
