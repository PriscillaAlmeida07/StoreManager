#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <time.h>
#include "config_db.h"
#include "send_message.h"


void insert_db(MYSQL *connection){
    printf("\nLet's register a new product!\n\n");
    char name[100];
    float purchase_price;
    float sale_price;
    char brand[100];
    int quantity;

    printf("Type the product name: \n");
    scanf("%99s", name);  
    printf("Type the product purchase price: \n");
    scanf("%f", &purchase_price);
    printf("Type the product sale price: \n");
    scanf("%f", &sale_price); 
    printf("Type the product brand: \n");
    scanf("%99s", brand); 
    printf("Type the product quantity: \n");
    scanf("%d", &quantity);

    char query[500];
    snprintf(query, sizeof(query), 
        "INSERT INTO Products(name, sale_price, brand, purchase_price, quantity) VALUES ('%s', %f, '%s', %f, %d)", 
        name, sale_price, brand, purchase_price, quantity);

    if (mysql_query(connection, query)) {
        printf("\nProduct not registered.\n");
        return;
    }
    printf("\nSucess! Product registered.\n");
}

int exist_ID(MYSQL *connection, int id_product) {
    char query[500];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Products WHERE id_Product = %d", id_product);
    
    if (mysql_query(connection, query)) {
        printf("Error: %s\n", mysql_error(connection));
        return -1;  
    }
    MYSQL_RES *res = mysql_store_result(connection);
    if (!res)
        return -1;  

    MYSQL_ROW row = mysql_fetch_row(res);
    int exists = 0;
    if (row && row[0])
        exists = atoi(row[0]) > 0 ? 1 : 0;

    mysql_free_result(res);
    return exists;
}

void general_update(MYSQL *connection, int id_product, const char *command, float number, char value[100],int integer, int current_case){
    char query[500];
    if(exist_ID(connection, id_product)){
        // If float, sale_price or purchase_price:
        if(current_case == 1){
            snprintf(query, sizeof(query), 
            "UPDATE Products SET %s= %f WHERE id_Product = %d ", command, number, id_product);
            if (mysql_query(connection, query)) {
                printf("\nProduct not update\n");
                return;
            }
            printf("\nSucess! Product %s update\n", command);   
        }
        // If string, name or brand:
        else if(current_case == 2){
            snprintf(query, sizeof(query), 
            "UPDATE Products SET %s= '%s' WHERE id_Product = %d ",command, value, id_product);
            if (mysql_query(connection, query)) {
                printf("Product not update");
                return;
            }
            printf("\nSucess! Product %s update\n", command);    
        }
        // If int, quantity:
        else if(current_case == 3){
            snprintf(query, sizeof(query), 
            "UPDATE Products SET %s= %d WHERE id_Product = %d ",command, integer, id_product);
            if (mysql_query(connection, query)) {
                printf("Product not update");
                return;
            }
            printf("\nSucess! Product %s update\n", command);    
        }
    }
    else
        printf("The product ID doesn't exist!\n");
}

void update_db(MYSQL *connection){
    printf("\nLet's update a product! \nAttention: You need to know the product ID\n\n");
    int proceed = 1;
    int command;
    int id_product;
    char aux[100] = "0";

    while (proceed){
        printf("\n  [1] - Update the product name:");
        printf("\n  [2] - Update the product purchase price:");
        printf("\n  [3] - Update the product sale price:");
        printf("\n  [4] - Update the product brand:");
        printf("\n  [5] - Update the product quantity:");
        printf("\n  [0] - Type zero to go back :\n");
        
        scanf(" %d", &command);
        switch (command){
            case 1 :
                char name[100];
                printf("Insert new product name:\n");
                scanf("%99s", name);
                printf("Type the product ID:\n");
                scanf("%d", &id_product);
                general_update(connection, id_product, "name", 0, name, 0, 2);
                break;
            
            case 2 :
                float purchase_price;
                printf("Insert new product purchase price:\n");
                scanf("%f", &purchase_price);
                printf("Type the product ID:\n");
                scanf("%d", &id_product);
                general_update(connection, id_product, "purchase_price", purchase_price, aux, 0, 1);
                break;

            case 3 :
                float sale_price;
                printf("Insert new product sale price:\n");
                scanf("%f", &sale_price);
                printf("Type the product ID:\n");
                scanf("%d", &id_product);
                general_update(connection, id_product, "sale_price", sale_price, aux, 0, 1);
                break;

            case 4 :
                char brand[100];
                printf("Insert new product brand:\n");
                scanf("%99s", brand);
                printf("Type the product ID:\n");
                scanf("%d", &id_product);
                general_update(connection, id_product, "brand", 0, brand, 0, 2);
                break;

            case 5 :
                int quantity;
                printf("Insert new product quantity:\n");
                scanf("%d", &quantity);
                printf("Type the product ID:\n");
                scanf("%d", &id_product);
                general_update(connection, id_product, "quantity", 0, aux, quantity, 3);
                break;
            
            case 0 :
                proceed = 0;
                break;

            default :
                printf ("Invalid value!\n");
                break;
        }   
    } 
}

void general_search(MYSQL *connection, int current_case){
    char query[500];
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    
    if(current_case == 1){
        if (mysql_query(connection, "SELECT * FROM Products ORDER BY name")) {
            printf("\nFailure in selection \n");
            return;
        }
        res = mysql_store_result(connection);
        int num_columns = mysql_num_fields(res);
        int num_rows = mysql_num_rows(res);
        
        if(num_rows == 0){
            printf("No product registration yet\n");
            mysql_free_result(res);
            return;
        }
        printf("\n");
        for (int i = 0; i < num_columns; i++) {
            field = mysql_fetch_field_direct(res, i);
            printf("%-*s", 20, field->name);  // Column name
        }
        printf("\n");

        while ((row = mysql_fetch_row(res))) {
            for (int i = 0; i < num_columns; i++)
                printf("%-*s", 20, row[i] ? row[i] : "NULL");
            printf("\n");
        }
        printf("\nSucess! selection made\n");  
        mysql_free_result(res); 
        return;
    }
    else if(current_case == 2){
        char name[100];
        printf("Type the product name to search: \n");
        scanf("%99s", name);  

        printf("\n");
        snprintf(query, sizeof(query), "SELECT * FROM Products WHERE name LIKE '%%%s%%'", name);
        execute_query(connection, query);

        res = mysql_store_result(connection);
        int num_rows = mysql_num_rows(res);
        
        if(num_rows == 0){
            printf("Product not found\n");
            mysql_free_result(res);
            return;
        }
        else{
            int num_columns = mysql_num_fields(res);
            for (int i = 0; i < num_columns; i++) {
                field = mysql_fetch_field_direct(res, i);
                printf("%-*s", 20, field->name);  // Nome da coluna
            }
            printf("\n");
            while ((row = mysql_fetch_row(res))) {
                for (int i = 0; i < num_columns; i++) {
                    printf("%-*s", 20, row[i] ? row[i] : "NULL");
                }
                printf("\n");
            }
            printf("\nSucess! selection made\n"); 
        }
        mysql_free_result(res);
        return;
    }
}

void read_db(MYSQL *connection){
    printf("\nLet's search! \n");
    int proceed = 1;
    int command;

    while (proceed){
        printf("\n  [1] - List all products registered");
        printf("\n  [2] - Find specific product");
        printf("\n  [0] - Type zero to go back :\n");
        
        scanf(" %d", &command);
        switch (command){
            case 1 :
                general_search(connection, 1);
                break;
            
            case 2 :
                general_search(connection, 2);
                break;
            
            case 0 :
                proceed = 0;
                break;

            default :
                printf ("Invalid value!\n");
                break;
        }
    }
}

void delete_db(MYSQL *connection){
    int id_product;
    printf("\nLet's delete a product!\nAttention: You need to know the product ID\n\n");
    printf("\nInsert product ID:\n");
    scanf("%d", &id_product);

    if(exist_ID(connection, id_product)){
        char query[500];
        snprintf(query, sizeof(query), "DELETE FROM Products WHERE id_Product= %d", id_product);
        if (mysql_query(connection, query)) {
            printf("Error deleting product: %s\n", mysql_error(connection));
            return;
        }
        
        printf("Success! Product deleted\n");
    }
    else
        printf("The product ID doesn't exist\n\n");
}

void find_name(MYSQL *connection, int id_product) {
    char query[500];
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(query, sizeof(query), "SELECT name FROM Products WHERE id_Product = %d", id_product);
    execute_query(connection, query);

    res = mysql_store_result(connection);
    if (!res) {
        printf("Error getting result \n");
        return;
    }

    row = mysql_fetch_row(res);
    if (row && row[0])
        printf("%-10s %-*s"," ", 20, row[0]);
    else 
        printf("Product not found!\n");

    mysql_free_result(res);  
}

void find_quant(MYSQL *connection, int quant, int id_product, float *total) {
    char query[500];
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(query, sizeof(query), "SELECT sale_price FROM Products WHERE id_Product = %d", id_product);
    execute_query(connection, query);

    res = mysql_store_result(connection);
    if (!res) {
        printf("Error getting result\n");
        return;
    }

    printf("%-*d", 20, quant);
    row = mysql_fetch_row(res);
    if (row && row[0]) {
        float price = atof(row[0]);  // Converts the value to float
        *total += (price * quant);  
        printf("%-*.*f", 20, 2, price);
        printf("%-*.*f", 20, 2, (price * quant));
    } 
    else 
        printf("Product not found!\n");
    mysql_free_result(res);
}


void receipt(MYSQL *connection, int sale_id) {
    char query[500];
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(query, sizeof(query), "SELECT id_Product_aux, quantity FROM Sale_products WHERE id_Sale_aux = %d", sale_id);
    execute_query(connection, query);

    res = mysql_store_result(connection);
    if (!res) {
        printf("Error getting result\n");
        return;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0) {
        printf("No products found for this sale\n");
        mysql_free_result(res);
        return;
    }

    float total = 0.00;
    printf("%75s\n", "----------------------------------------------------------------");
    printf("%55s\n\n", "STORE MANAGER RECEIPT");
    printf("%-10s %-20s%-20s%-20s%-20s\n", " ", "Product Name", "Quantity", "Unit Price", "Total");

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && row[1]) {  
            int id_product = atoi(row[0]);
            int quant = atoi(row[1]);
            find_name(connection, id_product); 
            find_quant(connection, quant, id_product, &total);
        }
        printf("\n");
    }
    printf("\n %68s %-10.2f\n", "The total:", total);
    mysql_free_result(res);

    time_t current_time;
    struct tm *tm_info;
    time(&current_time);
    tm_info = localtime(&current_time);
    printf("\n%65s %02d/%02d/%04d", "Date:",
        tm_info->tm_mday,     
        tm_info->tm_mon + 1, 
        tm_info->tm_year + 1900);

    printf("\n%65s %02d:%02d:%02d\n", "Time:",
        tm_info->tm_hour, 
        tm_info->tm_min,    
        tm_info->tm_sec);

    printf("%75s\n\n", "----------------------------------------------------------------");
}


int update_qnt_stock(MYSQL *connection, int id_product, int quantity){
    MYSQL_ROW row;
    MYSQL_RES *res;
    char query[500];
    int number;
    int new_quant;  

    snprintf(query, sizeof(query), "SELECT Products.quantity FROM Products WHERE Products.id_Product = %d", id_product);
    if (mysql_query(connection, query)) {
        printf("\nFailure in selection\n");
        return -1;
    }

    res = mysql_store_result(connection);
    row = mysql_fetch_row(res);
    if (row) {
        number = atoi(row[0]);  
        new_quant = number - quantity; 
    }
    mysql_free_result(res);
    if(new_quant < 0){
        printf("\nIt is not possible to register this sale as there is not enough product in stock\n");
        return 0;
    }
    snprintf(query, sizeof(query), 
    "UPDATE Products SET quantity= %d WHERE id_Product = %d ", new_quant, id_product);
    if (mysql_query(connection, query)) {
        printf("\nProduct not update\n");
        return -1;
    }
    else if(new_quant == 0){
        printf("\nWith this sale, this product is out of stock!\n");
        return 1;
    }
    return 1;
    
}

void sale_db(MYSQL *connection){
    char query[500];
    int sale_id;
    int id_product;
    int quantity;
    int count = 1;
    printf("\nLet's a new sale!\n\n");
    mysql_query(connection, "INSERT INTO Sale () VALUES ()");
    sale_id = mysql_insert_id(connection);

    while(1){
        printf("Type the ID of the %dº product or zero to finish sale! \n", count);
        scanf("%d", &id_product);
        if(exist_ID(connection, id_product) || id_product == 0){
            if(id_product == 0 ){
                char query[500];
                snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Sale_products WHERE id_Sale_aux = %d", sale_id);
                execute_query(connection, query);

                MYSQL_RES *res = mysql_store_result(connection);
                if (!res)
                    return;  
            
                MYSQL_ROW row = mysql_fetch_row(res);
                int exists = 0;
                if (row && row[0])
                    exists = atoi(row[0]) > 0 ? 1 : 0;
            
                mysql_free_result(res);
                if(!exists){
                    snprintf(query, sizeof(query), "DELETE FROM Sale WHERE id_Sale= %d", sale_id);
                    if (mysql_query(connection, query)) {
                        printf("Error deleting product: %s\n", mysql_error(connection));
                        return;
                    }
                    printf("Sale not made!\n");
                }
                else{
                    printf("\nSucess! Sale registered\n");
                    receipt(connection, sale_id);
                }
                return;
            }  
            else{
                printf("Type the quantity of the %dº product \n", count);
                scanf("%d", &quantity);

                if(update_qnt_stock(connection, id_product, quantity)){
                    snprintf(query, sizeof(query), 
                    "INSERT INTO Sale_products(id_Sale_aux, id_Product_aux, quantity) VALUES (%d, %d, %d)", 
                    sale_id, id_product, quantity);

                    if (mysql_query(connection, query)) {
                        printf("\nSale not registered %s\n",mysql_error(connection));
                        return;
                    }
                    count++;
                }
            }
        }
        else
            printf("Product ID not found\n\n");
    }       
}

void report_aux(MYSQL *connection, int id_sale, float *end_total){
    char query[500];
    float total;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(query, sizeof(query), "SELECT id_Product_aux, quantity FROM Sale_products WHERE id_Sale_aux = %d", id_sale);
    execute_query(connection, query);

    res = mysql_store_result(connection);
    if (!res) {
        printf("Error getting result\n");
        return;
    }
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && row[1]) {  
            int id_product = atoi(row[0]);
            int quant = atoi(row[1]);
            find_name(connection, id_product); 
            find_quant(connection, quant, id_product, &total);
        }
        printf("\n");
    }
    *end_total += total;
    printf("\n %68s %-10.2f\n\n", "The total:", total);
    mysql_free_result(res);
}

void report_db(MYSQL *connection){
    char query[500];
    MYSQL_RES *res;
    MYSQL_ROW row;
    char date[12];
    printf("\nType the date to view sales made on that day!\n"
        "\nEnter the date in mm-dd-yyyy or dd-mm-yyyy format. \n");
    scanf("%s", date);

    snprintf(query, sizeof(query),
    "SELECT id_Sale, date_time FROM Sale WHERE DATE(date_time) = STR_TO_DATE('%s', '%%d-%%m-%%Y') "
    "OR DATE(date_time) = STR_TO_DATE('%s', '%%m-%%d-%%Y')", date, date);
    execute_query(connection, query);

    res = mysql_store_result(connection);
    if (!res) {
        printf("Error getting result\n");
        return;
    }

    float end_total = 0.00;
    printf("%75s\n", "----------------------------------------------------------------");

    printf("%55s\n\n", "STORE MANAGER REPORT");

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0) {
        printf("\n%62s\n\n","There were no sales that day!");
        printf("%75s\n\n", "----------------------------------------------------------------");
        mysql_free_result(res);
        return;
    }

    int count = 1;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && row[1]) {  
            int id_sale= atoi(row[0]);
            char date_time[22];
            strcpy(date_time, row[1]);
            printf("\n%10d° sale of the day", count);
            printf("%52s \n", date_time);
            printf("\n%-10s %-20s%-20s%-20s%-20s\n", " ", "Product Name", "Quantity", "Unit Price", "Total");
            report_aux(connection, id_sale, &end_total);
            count++;
        }
        printf("\n");
    }
    printf("\n %68s %-10.2f\n", "The final total:", end_total);
    mysql_free_result(res);  

    time_t current_time;
    struct tm *tm_info;
    time(&current_time);
    tm_info = localtime(&current_time);
    printf("\n%65s %02d/%02d/%04d", "Date:",
        tm_info->tm_mday,     
        tm_info->tm_mon + 1, 
        tm_info->tm_year + 1900);

    printf("\n%65s %02d:%02d:%02d\n", "Time:",
        tm_info->tm_hour, 
        tm_info->tm_min,    
        tm_info->tm_sec);

    printf("%75s\n\n", "----------------------------------------------------------------");
}

int main(){
    MYSQL *connection = connect_to_database();
    int proceed=1;
    int comando;

    while (proceed){
        printf("\n ----------------------------- STORE_MANAGER -----------------------------\n");
        printf("\n  [1] - Register a new product");
        printf("\n  [2] - Update a product");
        printf("\n  [3] - Find product");
        printf("\n  [4] - Delete product");
        printf("\n  [5] - Make a Sale");
        printf("\n  [6] - Display the report of sales made in one day");
        printf("\n  [0] - Finalize \n"); 

        scanf(" %d", &comando);
        switch (comando){
            case 1 :
                insert_db(connection);
                break;
            
            case 2 :
                update_db(connection);
                break;
            
            case 3 :
                read_db(connection);
                break;
            
            case 4 :
                delete_db(connection);
                break;
            
            case 5 :
                sale_db(connection);
                break;

            case 6 :
                report_db(connection);
                break;

            case 0 :
                proceed = 0;
                break;
            
            default :
                printf ("Invalid value!\n");
                break;
        }
    }
    mysql_close(connection);
    printf("Connection closed\n");
    return 0;
}