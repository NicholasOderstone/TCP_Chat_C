#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 


char* getAllUsers(char* rez){
   //char rez[10000];
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
 
    //printf("%s", rez);
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    
    //write(1, rez, strlen(rez));

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
    

    return rez;
}

//думаю вам не нужны возращать все сообщения сразу;

char* oneLineUsers(int id){
   char rez[10000];
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

char* oneLineChats(int id){
   char rez[10000];
   sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return "-1";
    }
    
    rc = sqlite3_prepare_v2(db, "select group_concat(MyColumn, '') from (select id || ',' || name || ',' || g_chat || ';' as MyColumn  from Chats WHERE ID = ?);", -1, &res, 0);    
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

char* oneLineMessages(int id){
   char rez[10000];
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

void insertUser(char* login, char* password, char* nick, char* status){
    char sql[500];
    sprintf (sql,"INSERT INTO USERS (LOGIN, PASSWORD, NICK, STATUS) VALUES ('%s','%s','%s','%s');",login,password,nick,status);


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

void insertChat(char* name, char* g_chat){
    char sql[500];
    sprintf (sql,"INSERT INTO CHATS (name, g_chat) VALUES ('%s','%s');",name,g_chat);


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

void insertMessage(char* chat_id, char* user_id, char* message, char* date, char* is_read){
    char sql[500];
    sprintf (sql,"INSERT INTO MESSAGES (chat_id, user_id, message, date, is_read) VALUES ('%s','%s','%s','%s','%s');",chat_id,user_id,message,date,is_read);
    

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


/*void updateUser(char* id, char* login, char* password, char* nick, char* status){
    char sql[500];
    sprintf (sql,"update users set login, set password, set nick, set status where id=? ('%s','%s','%s','%s');",login,password,nick,status);


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
}*/


int main(int argc, char* argv[]) {
char rez[10000];
    printf("%s", getAllUsers(&rez));
    //getAllUsers();
    //printf("%s", rez2);
    
    //printf("%s", getAllChats());


   //printf("%s", oneLineUsers(1));
   //printf("%s", oneLineChats(1));
   //printf("%s", oneLineMessages(1));


   //insertUser("rdhjbhjrd", "dawdawd", "dgbdrhbguerg", "AAA");
   //insertChat("New chat", "0");
   //insertMessage("1","2","something tam", "2010 02 13:11:00", "0");
   
   
   //deleteUser("2"); //
   //updateUser("1", "awd", "AWD", "awd", "awd", "ad"); not working yet:(
}
