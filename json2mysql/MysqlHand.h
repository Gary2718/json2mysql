#pragma once
#include<iostream>
#include<string>
#include<memory>
#include"stdafx.h"
#include"mysql.h"
#include "block_entry.h"


class MysqlHand
{
public:
    MysqlHand();
    ~MysqlHand();
    bool Connect_To_Mysql();
    void Free_Connect();
    bool Insert_To_Block_Entry(Block_Entry& block_Entry);
    bool Update_Block_Entry(Block_Entry& block_Entry);
    bool Query_Block_Entry(Block_Entry& block_Entry);
    bool Truncate_Block_Entry(Block_Entry& block_Entry);
    long Max_Block_Num();     //if reurn 0 , means empty;

private:

    const std::string mysql_user = "root";             //  username
    const std::string mysql_pswd = "password";         //  password
    const std::string mysql_host = "localhost";        //  or"127.0.0.1"
    const std::string mysql_database = "achaindb";     //  database
    unsigned int mysql_port = 3306;                    //  server port

    MYSQL myConnect;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
//    MYSQL_FIELD *fd;

};

