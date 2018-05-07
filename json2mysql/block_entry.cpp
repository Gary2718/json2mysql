#include"stdafx.h"
#include"mysql.h"
#include "block_entry.h"
#include<iostream>
#include<string>

const char mysql_user[] = "root";         //username
const char mysql_pswd[] = "ouae9713";         //password
const char mysql_host[] = "localhost";    //or"127.0.0.1"
const char mysql_database[] = "achain";        //database
unsigned int mysql_port = 3306;           //server port      

MYSQL myCont;
MYSQL_RES *result;
MYSQL_ROW sql_row;
MYSQL_FIELD *fd;

bool Connect_To_Mysql(){

	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, mysql_host, mysql_user, mysql_pswd, mysql_database, mysql_port, NULL, 0))
	{
		std::cout << "user    :  " << mysql_user << std::endl;
		std::cout << "host    :  " << mysql_host << std::endl;
		std::cout << "port    :  " << mysql_port << std::endl;
		std::cout << "database:  " << mysql_database << std::endl;
		std::cout << "Database connected successfully!" << std::endl;
	}
	else
	{
		std::cout << "Database connect failure !"<< mysql_error(&myCont) << std::endl;
	}

	mysql_query(&myCont, "set names gbk");
	mysql_query(&myCont, "select * from block_entry;");

	return true;
}


Block_Entry::Block_Entry()
{
}

Block_Entry::~Block_Entry()
{
}