# STORE MANAGER

## Project description
STORE MANAGER is a product and sales management system that allows efficient control of inventory and completed sales.

:warning: The application operates entirely via the command-line interface (CLI), with no graphical interface, enabling fast and direct operations.  :warning:

It offers the following features:
  - Registration, updating, and removal of products.
  - Consultation of registered products.
  - Sales recording based on the product ID.
  - Generation of simple reports via the terminal.
    
In more detail, the system allows for quick and easy sales processing using the product ID, automatically updating the inventory. To facilitate business performance analysis, the system also includes a sales report feature, enabling users to view completed sales and revenue (gross income and net income) for a specific day.
With this approach, the system ensures efficient and organized management, providing greater control over products, sales, and inventory.



:rocket: The system was developed in C programming language and using MySQL database.

## How to use the program?
- *Necessary installations:*
  - Open the terminal
  - To use this program, you need to install the C programming language (if you use Windows). Check the official website for correct installation.
  - you need to install Mysql and MySQL client library (libmysqlclient), to do this do the following installations (for Linux):
    
    ``` bash
    sudo apt update
    
    sudo apt install mysql-server -y

    sudo apt-get install libmysqlclient-dev

  - Now with mysql installed, use this command to enter and set a password:
    
    ``` bash
    sudo mysql -u root -p
    
    alter user 'root'@'localhost' identified with mysql_native_password by 'your_password';

    flush privileges;

    exit
    
  - Clone the repository, using:
    
    ``` bash
    git clone https://github.com/PriscillaAlmeida07/StoreManager.git
    cd StoreManager

- *Open the program:*  
  - To run the program, use the code:
    
    ```bash
      ./main
    
- *In the STORE MANAGER program:*
  
  - 1: When running (using ./main) you will need to enter the password previously created in Mysql;
  - 2: The database will be configured by itself;
  - 3: You can now use the program by entering the number corresponding to the option you want to perform.
   

## Information about the project
This project was developed by:

:woman_technologist: Priscilla Almeida: Computer Engineering Student - Universidade Estadual de Campinas (Unicamp)
