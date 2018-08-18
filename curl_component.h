#ifndef CURL_COMPONENT_H_
#define CURL_COMPONENT_H_
#include <mysql/mysql.h>
#include <gumbo.h>

#define PERMISSION_WRITE "写入权限" 
#define MODE S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH

void print_intosql(GumboNode *node,GumboAttribute *attr, MYSQL *conn_prt);
 
void get_content(GumboNode *node, MYSQL *conn_prt);

char *file_pt(char *url, char *fname);

#endif