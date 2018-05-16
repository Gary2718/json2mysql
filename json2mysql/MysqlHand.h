#pragma once
#include<iostream>
#include<string>
#include<memory>
#include"stdafx.h"
#include"mysql.h"
#include "block_entry.h"


class MysqlHandSingleton
{
private:
    MysqlHandSingleton();
    static MysqlHandSingleton * _instance_ptr ; //�����ʼ��

    class Garbo//Ψһ�����þ��� delete ptr
    {
        ~Garbo();
    };
    static Garbo garbo;
public:

    static MysqlHandSingleton * get_instance();







    ~MysqlHandSingleton();
    bool connect_to_mysql();
    void free_connect();
    bool run_insert_sql(std::string&  sqlss);
    long max_block_num();
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

