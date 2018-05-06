// json2mysql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "block_entry.h"
#include <cstdio>
#include <assert.h>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
    using namespace rapidjson;

    FILE* fp;

    auto status = fopen_s(&fp, "./property_id_to_entry.json", "rb");

    if (fp)
    {
        std::cout << "property_id_to_entry.json  opened" << std::endl;
    }
    else
    {
        std::cout << "file not opened" << std::endl;
    }
    std::cout << status << std::endl;

    char readBuffer[102400];

//    assert(!fp);
	static const char* kTypeNames[] =
	{ "Null", "False", "True", "Object", "Array", "String", "Number" };
    FileReadStream fis(fp, readBuffer, sizeof(readBuffer) );
    Document d;
    d.ParseStream(fis);
	std::cout <<d.GetString() << "  ---  " << kTypeNames[d.GetType()] << std::endl;
	auto itr = d.MemberBegin();
	std::cout << itr->name.GetString() << "  ---  " << kTypeNames[itr->value.GetType()] << std::endl;
	if (itr->value.IsArray())
	{
		std::cout << itr->value.Size() << std::endl;
		for (auto&v : itr->value.GetArray())
		{
			std::cout << kTypeNames[v.GetType()] << std::endl;
		}
	}
	Connect_To_Mysql();
	char exit;
	std::cin >> exit;
    return 0;
}

