#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "config_db.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_NAME "DB_STORE_MANAGER"

void execute_query(MYSQL *connection, const char *query) {
    if (mysql_query(connection, query))
        fprintf(stderr, "Error when executing query: %s\n", mysql_error(connection));
}

int bank_exists(MYSQL *connection) {
    MYSQL_RES *res;
    char query[256];
    snprintf(query, sizeof(query), "SHOW DATABASES LIKE '%s'", DB_NAME);

    if (mysql_query(connection, query)) {
        fprintf(stderr, "Error checking database: %s\n", mysql_error(connection));
        return 0;
    }

    res = mysql_store_result(connection);
    int exists = (mysql_num_rows(res) > 0);
    mysql_free_result(res);
    return exists;
}

void create_db(MYSQL *connection) {
    char query[500];
    snprintf(query, sizeof(query), "CREATE DATABASE %s", DB_NAME);
    execute_query(connection, query);

    snprintf(query, sizeof(query), "USE %s", DB_NAME);
    execute_query(connection, query);

    snprintf(query, sizeof(query),
        "CREATE TABLE IF NOT EXISTS Products ("
        "id_Product INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
        "name VARCHAR(100), "
        "sale_price FLOAT, "
        "brand VARCHAR(100), "
        "purchase_price FLOAT, "
        "quantity INT)"
    );
    execute_query(connection, query);

    snprintf(query, sizeof(query),
        "CREATE TABLE IF NOT EXISTS Sale ("
        "id_Sale INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
        "date_hora DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP, "
        "total FLOAT)"
    );
    execute_query(connection, query);

    snprintf(query, sizeof(query),
        "CREATE TABLE IF NOT EXISTS Sale_products ("
        "id_Sale_products INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
        "id_Sale_aux INT, "
        "id_Product_aux INT, "
        "quantity INT, "
        "CONSTRAINT fk_Sale FOREIGN KEY (id_Sale_aux) REFERENCES Sale(id_Sale), "
        "CONSTRAINT fk_Product FOREIGN KEY (id_Product_aux) REFERENCES Products(id_Product))"
    );
    execute_query(connection, query);

    printf("Database created and tables configured successfully!\n");
}

MYSQL* connect_to_database() {
    char password[50];
    printf("Enter the MySQL password to connect: ");
    scanf("%s", password);

    MYSQL *connection = mysql_init(NULL);
    if (connection == NULL) {
        fprintf(stderr, "Error initializing connection: %s\n", mysql_error(connection));
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(connection, DB_HOST, DB_USER, password, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to MySQL: %s\n", mysql_error(connection));
        mysql_close(connection);
        exit(EXIT_FAILURE);
    }

    // Check if the bank exists
    if (bank_exists(connection)) {
        printf("The '%s' Database already exists!\n", DB_NAME);
    } else {
        printf("Database '%s' does NOT exist. Creating now...\n", DB_NAME);
        create_db(connection);
    }

    // Connecting to the created bank
    if (mysql_select_db(connection, DB_NAME) != 0) {
        fprintf(stderr, "Error selecting database: %s\n", mysql_error(connection));
        mysql_close(connection);
        exit(EXIT_FAILURE);
    }

    printf("Database connected successfully!\n");
    return connection;
}
