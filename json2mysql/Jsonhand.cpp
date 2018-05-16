#include "stdafx.h"
#include <sstream>
#include <stdint.h>
#include "Jsonhand.h"
#include "MysqlHand.h"
#include "trx_entry.h"
#include "const_string.h"

using namespace rapidjson;
static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

JsonHand::JsonHand(std::string jsonfile) :json_file_path(jsonfile)
{
    std::cout << "josn file: " << json_file_path.string() << std::endl;
    std::cout << "josn file name : " << json_file_path.filename() << std::endl;
    std::cout << "josn file directory : " << json_file_path.directory_string() << std::endl;
}

JsonHand::~JsonHand()
{
}


bool JsonHand::load_data()
{
    FILE* fp;
    auto status = fopen_s(&fp, json_file_path.string().c_str(), "rb");

    if (status == 0)
    {
        std::cout << json_file_path.string() << "  opened successfully !" << std::endl;
    }
    else
    {
        std::cout << json_file_path.string() << "  open failed !!!" << std::endl;
        assert(false);
        return false;
    }
    std::cout << json_file_path.filename() <<"  Loading data......" << std::endl;
    char readBuffer[10240];
    json_document.ParseStream(FileReadStream(fp, readBuffer, sizeof(readBuffer)));
    std::cout << "Loading completed !!!" << std::endl;

    fclose(fp);
    return true;

}

uint64_t JsonHand::get_json_size()
{
    return json_document.Size();
}

bool JsonHand::write_to_mysql()
{
    
    if (json_document.Empty())
    {
        std::cout << "json document is empty !" << std::endl;
        return false;
    }
    if (json_document.IsArray())
    {
        if (json_document.Size() < 1)
        {
            std::cout << "document type: " << kTypeNames[json_document.GetType()] << "\t size: " << json_document.Size() << std::endl;
            return true;
        }

        std::stringstream sqlss;
        sqlss << insert_sqlstr_beginning();
        uint64_t rec_cnt = 0;
        uint64_t not_empty_rec_cnt = 0;
        for (auto& rec_v : json_document.GetArray())
        {
            if ( !rec_v.IsArray() && rec_v.Size()==2 )
            {

                std::cout << "record type: " << kTypeNames[rec_v.GetType()] << "\t"
                    << "record size: " << rec_v.Size() << ", "
                    << " is not the type as expected" << std::endl;
                return false;
            }
            std::string sql_str("");
            if (!json_rec2insert_value(rec_v, sql_str))
            {
                std::cout << "ParseBlockEntry error" << std::endl;
                return false;
            }

            rec_cnt++;

            if (sql_str.size() > 1)
            {
                not_empty_rec_cnt++;
                sqlss << sql_str;
            }

            if ((not_empty_rec_cnt % 5000 == 0 && sql_str.size() > 1 ) || rec_cnt >= json_document.Size())  //
            {
                sqlss << insert_sqlstr_ending();
                if (!MysqlHandSingleton::get_instance()->run_insert_sql(sqlss.str()))
                {
                    return false;
                }
                //std::cout << sqlss.str() << std::endl;
                sqlss.str("");
                sqlss << insert_sqlstr_beginning();

                std::cout << rec_cnt << "  records handled  " << std::endl;
                std::cout << not_empty_rec_cnt << " not empty  records inserted  " << std::endl;
                std::cout << json_document.Size() << " in total  " << std::endl << std::endl;

                continue;
            }
            if (sql_str.size() > 1)
            {
                sqlss << ",";
                //std::cout << sqlss.str() << std::endl;
            }
        }

    }
    else
    {
        std::cout << "record type: " << kTypeNames[json_document.GetType()] << " is not the type as expected" << std::endl;
        return false;
    }
    return true;
}


std::string JsonHand::insert_sqlstr_beginning()
{
    std::string block_entry_sqlstr = "INSERT INTO block_entry ( block_num, block_id, pre_block_id, block_timestamp, num_trxs, block_size, processing_time, sync_timestamp, last_update_timestamp ) VALUES ";
    std::string transaction_entry_sqlstr = "INSERT INTO transaction_entry ( trx_id,expiration,operations,op_count,result_trx_type,contract_id,contract_method,contract_arg,block_num,last_update_timestamp ) VALUES ";
    std::string result_origin_sqlstr = "INSERT INTO result_to_origin_trx_id ( result_trx_id,origin_trx_id,last_update_timestamp ) VALUES ";

    if (get_file_name() == block_entry_file_name_const)
    {
        return block_entry_sqlstr;
    }
    else if (get_file_name() == trx_entry_file_name_const)
    {
        return transaction_entry_sqlstr;
    }
    else if (get_file_name() == result_origin_file_name_const)
    {
        return result_origin_sqlstr;
    }
    else
    {
        std::cout << "No such file : "<< get_file_name() << std::endl;
    }
}
std::string JsonHand::insert_sqlstr_ending()
{
    //std::string sqlstr_ending(";");
    //return sqlstr_ending;

    //if (!on_duplicate_update)
    //{
    //    return sqlstr_ending;
    //}

    std::string block_entry_sqlstr = " on duplicate key update  processing_time = values(processing_time), sync_timestamp =values(sync_timestamp), last_update_timestamp=values(last_update_timestamp) ; ";
    std::string transaction_entry_sqlstr = "; ";
    std::string result_origin_sqlstr = ";";


    if (get_file_name() == block_entry_file_name_const)
    {
        return block_entry_sqlstr;
    }
    else if (get_file_name() == trx_entry_file_name_const)
    {
        return transaction_entry_sqlstr;
    }
    else if (get_file_name() == result_origin_file_name_const)
    {
        return result_origin_sqlstr;
    }
    else
    {
        std::cout << "No such file : " << get_file_name() << std::endl;
    }

    //insert into test_tbl(id, dr) values(1, '2'), (2, '3'), ...(x, 'y') on duplicate key update dr = values(dr);
}
bool JsonHand::json_rec2insert_value(KV_REC& kv_rec, std::string& sql_str)
{
    if (get_file_name() == block_entry_file_name_const)
    {
        return parse_block_entry_values(kv_rec, sql_str);
    }
    else if (get_file_name() == trx_entry_file_name_const )
    {
        return parse_transaction_entry_values(kv_rec, sql_str);
    }
    else if (get_file_name() == result_origin_file_name_const )
    {
        return false;
    }
    else
    {
        std::cout << "No such file : " << get_file_name() << std::endl;
    }
}



std::string  JsonHand::get_file_name()
{
    return json_file_path.filename();
}

bool JsonHand::parse_block_entry_values(KV_REC& kv_rec, std::string& sql_str)
{
    
    Block_Entry block_entry;
    std::stringstream sqlss;
    for (auto& kv_v : kv_rec.GetArray())
    {
        if (kv_v.IsString())
        {
            block_entry.block_id = kv_v.GetString();
        }
        else if (kv_v.IsObject())
        {
            block_entry.block_num = kv_v["block_num"].GetUint64();
            block_entry.pre_block_id = kv_v["previous"].GetString();
            block_entry.block_timestamp = kv_v["timestamp"].GetString();
            block_entry.num_trxs = kv_v["user_transaction_ids"].Size();
            block_entry.block_size = kv_v["block_size"].GetUint64();
            block_entry.processing_time = kv_v["processing_time"].GetUint64();

            if (kv_v["latency"].IsString())
            {
                std::stringstream tmpss;
                std::string tmpstr = kv_v["latency"].GetString();
                if (tmpstr.size() < 6)
                {
                    tmpss << tmpstr;
                }
                tmpss << tmpstr.substr(0, tmpstr.size() - 6); //microseconds to seconds
                tmpss >> block_entry.latencey;

            }
            else
            {
                block_entry.latencey = 0;
            }

        }
        else
        {
            return false;
        }
    }
    if (block_entry.num_trxs < 1)// 
    {
        sql_str.clear();
        return true;
    }
    sqlss << "(";
    sqlss << block_entry.block_num;
    sqlss << ",'";
    sqlss << block_entry.block_id << "','";
    sqlss << block_entry.pre_block_id << "',";
    sqlss << "STR_TO_DATE('" << block_entry.block_timestamp << "','%Y-%m-%d T %H:%i:%s'),";

    sqlss << block_entry.num_trxs << ",";
    sqlss << block_entry.block_size << ",";
    sqlss << block_entry.processing_time << ",";

    sqlss << "TIMESTAMPADD(SECOND," << block_entry.latencey;
    sqlss << ",STR_TO_DATE('" + block_entry.block_timestamp << "','%Y-%m-%d T %H:%i:%s')),";
    sqlss << "now())";

    sql_str = sqlss.str();
    //std::cout << " Insert Value :  " << sql_str << std::endl;

    return true;
}

bool JsonHand::parse_transaction_entry_values(KV_REC& kv_rec, std::string& sql_str)
{
    Trx_Entry trx_entry;
    std::stringstream sqlss;
    for (auto& kv_v : kv_rec.GetArray())
    {

        if ( !( kv_v.IsString() || kv_v.IsObject() ) )
        {
            std::cout << "trx rec type : " << kTypeNames[kv_v.GetType()] 
                <<"  is not as expected ! "<< std::endl;
        }

        if (kv_v.IsString())
        {
            trx_entry.trx_id = kv_v.GetString();
        }
        if (kv_v.IsObject())
        {
            //kTypeNames[kv_v["trx"].GetType()] == object

            trx_entry.expiration = kv_v["trx"]["expiration"].GetString();
            trx_entry.result_trx_type = kv_v["trx"]["result_trx_type"].GetString();

            //kTypeNames[kv_v["chain_location"].GetType()] == object
            trx_entry.block_num = kv_v["chain_location"]["block_num"].GetUint64();

            //kTypeNames[kv_v["trx"]["operations"].GetType() == array
            trx_entry.op_count = kv_v["trx"]["operations"].Size();

            bool is_contract_result_trx = false;
            for (auto& op_v : kv_v["trx"]["operations"].GetArray())
            {
                //kTypeNames[op_v["type"].GetType()] == string
                trx_entry.operations += op_v["type"].GetString();
                trx_entry.operations += ",";


                if (op_v["type"].GetString() == "transaction_op_type")
                {
                    is_contract_result_trx = true;
                }
                if (is_contract_result_trx)
                {



                }

                //kTypeNames[op_v["data"].GetType()] == object

                //std::cout << "type    opv   opv        :     " << kTypeNames[op_v.GetType()] << std::endl;
                //std::cout << "type    opv   type        :     " << kTypeNames[op_v["type"].GetType()] << std::endl;
                //std::cout << "type    opv   data        :     " << kTypeNames[op_v["data"].GetType()] << std::endl;

            }
            trx_entry.operations.substr(0, trx_entry.operations.size() - 1);  //remove the trail comma

            trx_entry.contract_id = "";
            trx_entry.contract_method = "";
            trx_entry.contract_arg = "";
            //auto trx_obj = kv_v["trx"]["expiration"].GetType();
        }

        trx_entry.display();


    sqlss << "('";
    sqlss << trx_entry.trx_id;
    sqlss << "',";
    sqlss << "STR_TO_DATE('" << trx_entry.expiration<< "','%Y-%m-%d T %H:%i:%s'),'";
    sqlss << trx_entry.operations << "',";
    sqlss << trx_entry.op_count << ",'";

    sqlss << trx_entry.result_trx_type << "',";
    sqlss << "null,";
    sqlss << "null,";
    sqlss << "null,";
    sqlss << trx_entry.block_num << ",";
    sqlss << "now())";

    sql_str=sqlss.str();
    std::cout << " Insert Value :  " << sql_str << std::endl;

    return true;
}
