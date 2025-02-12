# STORE MANAGER

## Project description
O STORE MANAGER  é um sistema de gerenciamento de produtos e vendas, que permite o controle eficiente do estoque e das vendas efetuadas. 

:warning: A aplicação funciona totalmente via linha de comando (CLI), sem interface gráfica, permitindo operações rápidas e diretas. :warning:

Ele oferece as seguintes funcionalidades:
  - Cadastro, atualização e remoção de produtos.
  - Consulta de produtos cadastrados.
  - Registro de vendas com base no ID do produto.
  - Geração de relatórios simples via terminal.
    
Com mais detalhes, o sistema permite realizar vendas de forma simples e rápida, utilizando o ID do produto e atualizando automaticamente o estoque. Para facilitar a análise do desempenho comercial, o sistema também conta com a funcionalidade de relatórios de vendas, permitindo a visualização das vendas realizadas e seu faturamento em um determinado dia.
Com essa abordagem, o sistema garante um gerenciamento eficiente e organizado, proporcionando maior controle sobre produtos, vendas e estoque.



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
