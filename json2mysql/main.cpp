// main.cpp : 

#include "stdafx.h"
#include <cstdio>
#include <assert.h>
#include <iostream>
#include "MysqlHand.h"
#include "JsonHand.h"



int _tmain(int argc, _TCHAR* argv[])
{

    std::shared_ptr<MysqlHand> sqlHand_sptr(new MysqlHand() );
    std::string path_str("./block_entry.json");
    std::shared_ptr<JsonHand>  jsonhand(new JsonHand( path_str, sqlHand_sptr));
    jsonhand->LoadData();
    system("pause");
    return 0;
}

