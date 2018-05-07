#include <filesystem>
#include <iostream>
#include <string>

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include "mysql.h"



typedef rapidjson::GenericArray <false, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ValueType>::ValueType KV_REC;
using namespace std::tr2::sys;

class JsonHand
{
public:
    JsonHand();
    ~JsonHand();
    bool LoadData();
    bool ParsetoRec();

    
    bool ParseBlockEntry(KV_REC& kv_rec);
    void ParseTransactionEntry(rapidjson::Value kv_rec);


private:
    path                     json_file_path;
    rapidjson::Document      json_document;

};

