
#pragma once
#include <filesystem>
#include <iostream>
#include <string>

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include "stdint.h"
#include "mysql.h"
#include "MysqlHand.h"



typedef rapidjson::GenericArray <false, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ValueType>::ValueType KV_REC;
using namespace std::tr2::sys;



class JsonHand
{
public:
    JsonHand(std::string jsonfile );
    ~JsonHand();
    bool          load_data();
    bool          write_to_mysql();

    uint64_t     get_json_size();
    std::string  get_file_name();

    std::string insert_sqlstr_beginning();
    std::string insert_sqlstr_ending();
    bool json_rec2insert_value(KV_REC& kv_rec, std::string& sql_str);



    bool parse_block_entry_values(KV_REC& kv_rec, std::string& sqlstr);
    bool parse_transaction_entry_values(KV_REC& kv_rec, std::string& sql_str);


private:
    path                     json_file_path;
    rapidjson::Document      json_document;
    int                      mysql_instance_num;
    bool                     sigleton;
};

