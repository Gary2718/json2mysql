
#pragma once
#include<string>
#include<iostream>
#include"mysql.h"
#include<stdint.h>

class Block_Entry
{
public:
    Block_Entry(){}
    ~Block_Entry(){};
    void Display()
    {
        std::cout << "block_num: " << block_num << std::endl;
        std::cout << "block_id: " << block_id << std::endl;
        std::cout << "pre_block_id: " << pre_block_id << std::endl;
        std::cout << "block_timestamp: " << block_timestamp << std::endl;
        std::cout << "block_delegate: " << block_delegate << std::endl;
        std::cout << "num_trxs: " << num_trxs << std::endl;
        std::cout << "block_size: " << block_size << std::endl;
        std::cout << "processing_time: " << processing_time << std::endl;
        std::cout << "latencey: " << latencey << std::endl;
    }

public:
    uint64_t    block_num;               //块号
    std::string block_id;                //块ID
    std::string pre_block_id;            //上一个块ID
    std::string block_timestamp;         //产块时间
    std::string block_delegate;          //产块代理
    uint32_t num_trxs;                   //块中交易数量
    uint64_t block_size;                 //块的大小
    uint64_t processing_time;            //处理时间 
//    std::string sync_timestamp;        //开始同步时间,
    uint64_t latencey;                   //延迟，用于计算同步时间(seconds)
    std::string ins_mysql_timestamp;     //开始同步时间
};
