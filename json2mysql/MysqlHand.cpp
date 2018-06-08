#include "stdafx.h"
#include "MysqlHand.h"
#include <assert.h>
#include <sstream>
#include <thread>

std::vector<MysqlHand *> MysqlHand::_instance_ptr_vec(100, nullptr);
MysqlHand * MysqlHand::_instance_ptr = nullptr;
//私有静态成员变量在使用前必须初始化

MysqlHand::Garbo::~Garbo()
{
    {
        if (MysqlHand::_instance_ptr)
            delete MysqlHand::_instance_ptr;
        for (auto itr : _instance_ptr_vec)
        {
            if (itr)
            {
                delete itr;
            }
        }
    }
} 

MysqlHand::MysqlHand() :
mysql_user("root")
, mysql_pswd("password")
{
    if (!connect_to_mysql())
    {
        assert(false);
    }
}
MysqlHand::MysqlHand(int user_seq) :
 mysql_pswd("password")
{
    std::stringstream  userss;
    userss << "user_";
    userss << user_seq;
    mysql_user = userss.str();

    if (!connect_to_mysql())
    {
        assert(false);
    }
}

void MysqlHand::init_all_instance(int instance_num)
{
    for (int i = 0; i < instance_num; i++)
    {
        _instance_ptr_vec[i] = new MysqlHand(i + 1);
    }
}

MysqlHand * MysqlHand::get_instance()
{
    if (!_instance_ptr)
        _instance_ptr = new MysqlHand();
    return _instance_ptr;

}

MysqlHand * MysqlHand::get_instance(int seq)
{
//    std::cout << "get_instance:  " << seq << std::endl;

    assert(!_instance_ptr_vec[seq]);
    return _instance_ptr_vec[seq];

}

MysqlHand::~MysqlHand()
{
    free_connect();
}

bool MysqlHand::connect_to_mysql()
{
    std::lock_guard<std::mutex> lock(connect_mutex);

    mysql_init(&myConnect);
    if (mysql_real_connect(&myConnect, mysql_host.c_str(), mysql_user.c_str(), mysql_pswd.c_str(),
        mysql_database.c_str(), mysql_port, NULL, 0))
    {
        std::lock_guard<std::mutex> lock(connect_mutex1);
        std::cout << " thread id:  " << std::this_thread::get_id() << std::endl;
        std::cout << " user     :  " << mysql_user << std::endl;
        //std::cout << " host     :  " << mysql_host << std::endl;
        //std::cout << " port     :  " << mysql_port << std::endl;
        //std::cout << " database :  " << mysql_database << std::endl;
        std::cout << " Database connected successfully!" << std::endl;
    }
    else
    {
        std::lock_guard<std::mutex> lock(connect_mutex2);
        std::cout << "Database connect failure !" << mysql_error(&myConnect) << std::endl;
        std::cout << " thread id:  " << std::this_thread::get_id() << std::endl;
        std::cout << " user     :  " << mysql_user << std::endl;
    }

    //mysql_query(&myConnect, "set names gbk");
    //mysql_query(&myConnect, "select * from block_entry;");
    return true;
}

void MysqlHand::free_connect()
{
    if (result)
    {
        mysql_free_result(result);
    }
    if (&myConnect)
    {
        mysql_close(&myConnect);
    }
}

bool MysqlHand::run_insert_sql(std::string  sql_str)
{
    std::lock_guard<std::mutex> lock(insert_mutex);


    //std::cout << sql_str << std::endl;
    if (mysql_query(&myConnect, sql_str.c_str()))
    {
        std::cout << "Insert into mysql failed, " << mysql_error(&myConnect) << std::endl;
        if (sql_str.size() < 1000)
        {
            std::cout << "The sqlstr :  " << sql_str << std::endl;
        }
        //mysql_sqlstate(&myConnect);
        return false;

    }
    else
    {
//        std::cout << "The insert user :  " << mysql_user << std::endl;
        return true;
    }
} 

long MysqlHand::max_block_num()
{
    std::string querySqlStr;
    uint64_t maxBlockNum;
    querySqlStr = "SELECT MAX(block_num) FROM block_entry;";

    if (mysql_query(&myConnect, querySqlStr.c_str()))
    {
        std::cout << "Insert into block_entry failed, " << mysql_error(&myConnect) << std::endl;
        std::cout << "The sqlstr :  " << querySqlStr << std::endl;
        //mysql_sqlstate(&myConnect);
        return -1;
    }

    if (!(result = mysql_store_result(&myConnect)))
    {
        std::cout << "Couldn't get the query result, " << mysql_error(&myConnect) << std::endl;
        std::cout << "The sqlstr :  " << querySqlStr << std::endl;
        return -1;
    }

    if (sql_row = mysql_fetch_row(result))
    {
        std::istringstream iStream;
        iStream.str(sql_row[0]);

        if (!iStream)
        {
            maxBlockNum = 0;
        }
        else
        {
            iStream >> maxBlockNum;
        }
    }


    if (result)
    {
        mysql_free_result(result);
    }

    return maxBlockNum;
}