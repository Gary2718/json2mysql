#include<iostream>
#include<string>
#include"stdafx.h"
#include"mysql.h"
#include "block_entry.h"


class MysqlHand
{
public:
    MysqlHand();
    ~MysqlHand();
    bool Connect_To_Mysql();
    bool Insert_To_Block_Entry();
    long Max_Block_Num();

private:

    const std::string mysql_user = "root";         //username
    const std::string mysql_pswd = "password";         //password
    const std::string mysql_host = "localhost";      //or"127.0.0.1"
    const std::string mysql_database = "achaindb";        //database
    unsigned int mysql_port = 3306;           //server port      

    MYSQL myConnect;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD *fd;

};

