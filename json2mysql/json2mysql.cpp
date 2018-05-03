// json2mysql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
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

    FileReadStream fis(fp, readBuffer, sizeof(readBuffer) );
    Document d;
    //d.ParseStream(fis);
    return 0;
}

