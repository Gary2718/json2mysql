#include "stdafx.h"
#include "MysqlHand.h"
#include <assert.h>
#include <sstream>



MysqlHand::MysqlHand()
{
    if (!Connect_To_Mysql())
    {
        assert(false);
    }
}

MysqlHand::~MysqlHand()
{
    Free_Connect();
}

bool MysqlHand::Connect_To_Mysql()
{
    mysql_init(&myConnect);
    if (mysql_real_connect(&myConnect, mysql_host.c_str(), mysql_user.c_str(), mysql_pswd.c_str(),
        mysql_database.c_str(), mysql_port, NULL, 0))
    {
        std::cout << " user     :  " << mysql_user << std::endl;
        std::cout << " host     :  " << mysql_host << std::endl;
        std::cout << " port     :  " << mysql_port << std::endl;
        std::cout << " database :  " << mysql_database << std::endl;
        std::cout << " Database connected successfully!" << std::endl;
    }
    else
    {
        std::cout << "Database connect failure !" << mysql_error(&myConnect) << std::endl;
    }

    //mysql_query(&myConnect, "set names gbk");
    //mysql_query(&myConnect, "select * from block_entry;");
    return true;
}

void MysqlHand::Free_Connect()
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

bool MysqlHand::Insert_To_Block_Entry( Block_Entry& block_Entry )
{
    std::string insertSqlStr;
    insertSqlStr += "INSERT INTO block_entry ( block_num, block_id, pre_block_id, block_timestamp, block_delegate, num_trxs, block_size, processing_time, sync_timestamp, ins_mysql_timestamp ) ";
    insertSqlStr += "VALUES ( ";
    insertSqlStr += block_Entry.block_num;


    //insertSqlStr += "'";
    //insertSqlStr += block_Entry.block_id;
    //insertSqlStr += "'";
    //insertSqlStr += ",";
    insertSqlStr += ",'";
    insertSqlStr += block_Entry.block_id + "','";
    insertSqlStr += block_Entry.pre_block_id + "',";
    insertSqlStr += "STR_TO_DATE('" +  block_Entry.block_timestamp + "','%Y-%m-%d T %H:%i:%s'),'";

    insertSqlStr += block_Entry.block_delegate + "',";
    insertSqlStr += block_Entry.num_trxs + ",";
    insertSqlStr += block_Entry.block_size + ",";
    insertSqlStr += block_Entry.processing_time + ",";

    insertSqlStr += "TIMESTAMPADD(SECOND," + block_Entry.latencey;
    insertSqlStr += ",STR_TO_DATE('" + block_Entry.block_timestamp + "','%Y-%m-%d T %H:%i:%s')),";
    insertSqlStr += "now();";

    std::cout << insertSqlStr << std::endl;

    if ( mysql_query( &myConnect, insertSqlStr.c_str() ) )
    {
        std::cout << "Insert into block_entry failed, " << mysql_error(&myConnect) << std::endl;
        std::cout << "The sqlstr :  " << insertSqlStr << std::endl;


        //mysql_sqlstate(&myConnect);

        return false;

    }
    else
    {
        return true;
    }
} 

bool MysqlHand::Update_Block_Entry(Block_Entry& block_Entry)
{
    return true;
}
bool MysqlHand::Query_Block_Entry(Block_Entry& block_Entry)
{
    return true;
}
bool MysqlHand::Truncate_Block_Entry(Block_Entry& block_Entry)
{
    return true;
}
long MysqlHand::Max_Block_Num()
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