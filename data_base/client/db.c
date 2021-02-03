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

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("data_client.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
   
       
//CHATS
sql = "CREATE TABLE IF NOT EXISTS CHATS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "DESCRIPTION         TEXT);";
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
   

   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "All OK\n");
   }
   sqlite3_close(db);


   return 0;
}
