// json2mysql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "block_entry.h"
#include <cstdio>
#include <assert.h>
#include <iostream>

static const char* kTypeNames[] =
{ "Null", "False", "True", "Object", "Array", "String", "Number" };

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace rapidjson;

    FILE* fp;

    auto status = fopen_s(&fp, "./block_entry.json", "rb");

    if (status==0)
    {
        std::cout << "block_entry.json  opened successfully!" << std::endl;
    }
    else
    {
        std::cout << "open failed" << std::endl;
    }
    std::cout << status << std::endl;


    Document document;
    char readBuffer[102400];
    document.ParseStream(FileReadStream(fp, readBuffer, sizeof(readBuffer)));


    std::cout << "document type: " << kTypeNames[document.GetType()] << "\t size: " << document.Size() << std::endl;
    if (document.IsArray())
    {
        for (auto& rec_v : document.GetArray())
        {
            std::cout << "record type: " << kTypeNames[rec_v.GetType()] << "\t size: " << rec_v.Size() << std::endl;
            if (rec_v.IsArray())
            {
                for (auto& kv_v : rec_v.GetArray()) 
                {
                    //std::cout << "kv_v type : " << kTypeNames[kv_v.GetType()] << "\t size: " << kv_v.Size() << std::endl;
                    if (kv_v.IsString())
                    {
                        std::cout << "block_id :" << kv_v.GetString() << "\t";
                    }
                    else if(kv_v.IsObject())
                    {
                        if (kv_v.HasMember("block_num"))
                        {
                            std::cout << "block_num:" << kv_v["block_num"].GetInt64() << std::endl;
                        }
                        if (kv_v.HasMember("user_transaction_ids"))
                        {
                            std::cout << "num_trx :" << kv_v["user_transaction_ids"].Size() << std::endl;
                        }
                    }
                }

            }
        }

    }

    //Connect_To_Mysql();

    //auto itr = document.MemberBegin();
    //std::cout << itr->name.GetString() << "  ---  " << kTypeNames[itr->value.GetType()] << std::endl;
    //if (itr->value.IsArray())
    //{
    //    std::cout << itr->value.Size() << std::endl;
    //    for (auto&v : itr->value.GetArray())
    //    {
    //        std::cout << kTypeNames[v.GetType()] << std::endl;
    //    }
    //}

    char exit;
    std::cin >> exit;
    return 0;
}

