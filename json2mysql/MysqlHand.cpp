#include "stdafx.h"
#include "MysqlHand.h"



MysqlHand::MysqlHand()
{
}

MysqlHand::~MysqlHand()
{
}

bool MysqlHand::Connect_To_Mysql()
{
    mysql_init(&myConnect);
    if (mysql_real_connect(&myConnect, mysql_host.c_str(), mysql_user.c_str(), mysql_pswd.c_str(),
        mysql_database.c_str(), mysql_port, NULL, 0))
    {
        std::cout << "user     :  " << mysql_user << std::endl;
        std::cout << "host     :  " << mysql_host << std::endl;
        std::cout << "port     :  " << mysql_port << std::endl;
        std::cout << "database :  " << mysql_database << std::endl;
        std::cout << "Database connected successfully!" << std::endl;
    }
    else
    {
        std::cout << "Database connect failure !" << mysql_error(&myConnect) << std::endl;
    }

    mysql_query(&myConnect, "set names gbk");
    mysql_query(&myConnect, "select * from block_entry;");

    return true;
}
bool MysqlHand::Insert_To_Block_Entry()
{
    return true;
}

