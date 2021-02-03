#include "../inc/header.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   (void)(NotUsed);
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int initDB(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("data.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
   

//USERS
   sql = "CREATE TABLE IF NOT EXISTS USERS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "LOGIN          TEXT    NOT NULL," \
      "PASSWORD       TEXT    NOT NULL," \
      "NICK           TEXT    NOT NULL," \
      "STATUS         TEXT );";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      
  
//CHATS
sql = "CREATE TABLE IF NOT EXISTS CHATS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "DESCRIPTION         TEXT);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


//MESSAGES
  sql = "CREATE TABLE IF NOT EXISTS MESSAGES("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "CHAT_ID             INT     NOT NULL," \
      "USER_ID             INT     NOT NULL," \
      "MESSAGE             TEXT    NOT NULL," \
      "DATE                INT    NOT NULL," \
      "IS_READ             INT     NOT NULL );";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   
//BLOCK_LIST
  sql = "CREATE TABLE IF NOT EXISTS BLOCK_LIST("  \
      "USER_ID             INT     NOT NULL," \
      "BLOCK_USER_ID       INT     NOT NULL);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  
  
//USER_IN_CHAT
  sql = "CREATE TABLE IF NOT EXISTS USER_IN_CHAT("  \
      "USER_ID       INT     NOT NULL," \
      "LOGIN         TEXT    NOT NULL," \
      "CHAT_ID       INT     NOT NULL," \
      "NAME          TEXT    NOT NULL);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); 
   
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "All OK\n");
   }
   sqlite3_close(db);
   
   return 0;
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

// void insertUSER_TO_CHAT(char* user_id, char* chat_id){
//     char sql[500];
//     sqlite3 *db;
//     sqlite3_stmt *res;
//     char *err_msg = 0;
//     char login[200];
//     char name[200];
//     int rc = sqlite3_open("data.db", &db);
//     sprintf (sql,"select LOGIN from Users WHERE ID = '%d';",user_id);
//     rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
//     sqlite3_bind_text(res, 1, user_id);
//     rc = sqlite3_step(res);
//     sprintf(login, "%s\n", sqlite3_column_text(res, 0));
//     printf("%s", login);
//     sprintf (sql,"select NAME from Chats WHERE ID = '%d';",chat_id);
//     rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
//     sqlite3_bind_text(res, 1, user_id, strlen(user_id), NULL);
//     //sqlite3_bind_int(res, 1, user_id);
//     rc = sqlite3_step(res);
//     sprintf(name, "%s\n", sqlite3_column_text(res, 0));
//     sprintf (sql,"INSERT INTO USER_IN_CHAT (USER_ID, LOGIN, CHAT_ID, NAME) VALUES ('%s','%s','%s','%s');",user_id,login,chat_id,name);
//     printf("%s", sql);
//     //rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
//     sqlite3_finalize(res);
//     sqlite3_close(db);
//     return;
// }



int getLastId(int id){

    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open("data.db", &db);
    char sql[500];
    sprintf(sql, "SELECT MAX(ID) FROM MESSAGES WHERE CHAT_ID = '%d'", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);    
    rc = sqlite3_step(res);
    int rez = sqlite3_column_int(res, 0);

    sqlite3_finalize(res);
    sqlite3_close(db);

    return rez;
}

msg_t *packMsg(int id){
    char sql_req[500];
    char buffer[4096];
    msg_t *new_msg = (msg_t *)malloc(sizeof(msg_t));
    //sprintf (sql,"select group_concat(MyColumn, '') from (select id || ',' || CHAT_ID || ',' || USER_ID || ',' || MESSAGE || ',' || DATE || ';' as MyColumn from MESSAGES where CHAT_ID = %d and id between %d and %d);",id, from, from);
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

