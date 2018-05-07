#include "stdafx.h"
#include "Jsonhand.h"
#include "block_entry.h"

using namespace rapidjson;

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

JsonHand::JsonHand()
{
}

JsonHand::~JsonHand()
{
}


bool JsonHand::LoadData()
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

    char readBuffer[10240];
    json_document.ParseStream(FileReadStream(fp, readBuffer, sizeof(readBuffer)));

    fclose(fp);
    return true;

}
bool JsonHand::ParsetoRec()
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

        for (auto& rec_v : json_document.GetArray())
        {
            std::cout << "record type: " << kTypeNames[rec_v.GetType()] << "\t size: " << rec_v.Size() << std::endl;
            if ( rec_v.IsArray() && rec_v.Size()==2 )
            {

              return  ParseBlockEntry( rec_v );

            }
            else
            {
                std::cout << "record type: " << kTypeNames[rec_v.GetType()] << "\t"
                    << "record size: " << rec_v.Size() << ", "
                    << " is not the type as expected" << std::endl;
                return false;

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

bool JsonHand::ParseBlockEntry( KV_REC& kv_rec )
{
    Block_Entry block_entry;
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
            block_entry.block_delegate = kv_v["delegate_signature"].GetString();
            block_entry.num_trxs = kv_v["user_transaction_ids"].Size();
            block_entry.block_size = kv_v["block_size"].GetUint64();
            block_entry.processing_time = kv_v["processing_time"].GetUint64();
            //block_entry.sync_timestamp = kv_v["user_transaction_ids"].Size();
            //block_entry.ins_mysql_timestamp = kv_v[""].Size();
        }
    }

    block_entry.Display();

    return true;
}