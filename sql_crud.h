#ifndef SQL_CRUD_H_
#define SQL_CRUD_H_

#include <mysql/mysql.h>

void sql_init();
void sql_connect();
void insert_msg(char *table_name, char *field, char *msg ,int in_len, MYSQL *conn_prt);
void sql_close();

#endif
