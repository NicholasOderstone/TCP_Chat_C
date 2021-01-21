#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
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
   
 
  
   sql = "INSERT INTO USERS (LOGIN,PASSWORD,NICK,STATUS)" \
         "VALUES ('THEBESTUSER', 'AWD', 'ST_FATHER ', ':)' );";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sql = "INSERT INTO USERS (LOGIN,PASSWORD,NICK,STATUS)" \
         "VALUES ('fuckeddata_base', 'superPass', 'redMan ', ':(' );";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   

   sql = "SELECT * from USERS";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      
  
   
   
//CHATS
fprintf(stdout, "----------------CHATS----------------\n");
sql = "CREATE TABLE IF NOT EXISTS CHATS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "DESCRIPTION         TEXT);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  
  sql = "INSERT INTO CHATS (NAME,G_CHAT)" \
        "VALUES ('NAMECHAT', 0);";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   sql = "SELECT * from CHATS";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


   
//MESSAGES
  fprintf(stdout, "----------------MESSAGES----------------\n");
  sql = "CREATE TABLE IF NOT EXISTS MESSAGES("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "CHAT_ID             INT     NOT NULL," \
      "USER_ID             INT     NOT NULL," \
      "MESSAGE             TEXT    NOT NULL," \
      "DATE                TEXT    NOT NULL," \
      "IS_READ             INT     NOT NULL );";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  
  sql = "INSERT INTO MESSAGES (CHAT_ID,USER_ID,MESSAGE,DATE,IS_READ)" \
        "VALUES (1, 1, 'MESSAGE', '2020 12 30 13:28:40', 0);";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   sql = "SELECT * from MESSAGES";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   
   
//BLOCK_LIST
  sql = "CREATE TABLE IF NOT EXISTS BLOCK_LIST("  \
      "USER_ID             INT     NOT NULL," \
      "BLOCK_USER_ID       INT     NOT NULL);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  
  
  
//USER_IN_CHAT
  sql = "CREATE TABLE IF NOT EXISTS USER_IN_CHAT("  \
      "USER_ID       INT     NOT NULL," \
      "CHAT_ID       INT     NOT NULL);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); 
   
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "All OK\n");
   }
   sqlite3_close(db);
};

int main(int argc, char* argv[]) {
   
   initDB();

   return 0;
}
