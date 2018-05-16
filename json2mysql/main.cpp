// main.cpp : 

#include "stdafx.h"
#include <cstdio>
#include <assert.h>
#include <iostream>
#include "MysqlHand.h"
#include "JsonHand.h"
#include "const_string.h"


bool json_to_mysql(std::string path_str)
{
    std::shared_ptr<JsonHand>  jsonhand(new JsonHand(path_str));
    if (!jsonhand->load_data())
    {
        return false;
    }
   return jsonhand->write_to_mysql();
}

int _tmain(int argc, _TCHAR* argv[])
{

    if (!json_to_mysql(json_file_directory_const+block_entry_file_name_const))
    {
        std::cout << block_entry_file_name_const << "    insert to mysql error" << std::endl;
    }
    if (!json_to_mysql(json_file_directory_const+trx_entry_file_name_const))
    {
        std::cout << trx_entry_file_name_const << "    export to mysql error" << std::endl;
    }
    //if (!json_to_mysql(result_origin_path_str))
    //{
    //    std::cout << result_origin_path_str << "    json to mysql errot" << std::endl;
    //}

    system("pause");


    return 0;
}

