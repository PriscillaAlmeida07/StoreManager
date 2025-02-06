#ifndef CONFIG_DB_H
#define CONFIG_DB_H
#include <mysql/mysql.h>

struct MYSQL* connect_to_database();
void execute_query(MYSQL *connection, const char *query);
#endif