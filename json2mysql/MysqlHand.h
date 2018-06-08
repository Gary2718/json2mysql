#pragma once
#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include <mutex>
#include"stdafx.h"
#include"mysql.h"
#include "block_entry.h"


class MysqlHand
{
private:
    MysqlHand();
    MysqlHand(int user_seq);
    static MysqlHand * _instance_ptr; //必须初始化
    static std::vector<MysqlHand *> _instance_ptr_vec; //必须初始化
    class Garbo//唯一的作用就是 delete ptr
    {
        ~Garbo();
    };
    static Garbo garbo;
public:

    static void init_all_instance(int instance_num);
    static MysqlHand * get_instance();
    static MysqlHand * get_instance(int seq);







    ~MysqlHand();
    bool connect_to_mysql();
    void free_connect();
    bool run_insert_sql(std::string  sqlss);
    long max_block_num();
private:
    std::string mysql_user ;                   //  username
    std::string mysql_pswd ;                   //  password
    const std::string mysql_host = "localhost";        //  or"127.0.0.1"
    const std::string mysql_database = "achaindb";     //  database
    unsigned int mysql_port = 3306;                    //  server port

    MYSQL myConnect;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    
    std::mutex connect_mutex;
    std::mutex connect_mutex1;
    std::mutex connect_mutex2;
    std::mutex insert_mutex;

//    MYSQL_FIELD *fd;

};

