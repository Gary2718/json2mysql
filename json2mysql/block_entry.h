
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
    uint64_t    block_num;               //���
    std::string block_id;                //��ID
    std::string pre_block_id;            //��һ����ID
    std::string block_timestamp;         //����ʱ��
    std::string block_delegate;          //�������
    uint32_t num_trxs;                   //���н�������
    uint64_t block_size;                 //��Ĵ�С
    uint64_t processing_time;            //����ʱ�� 
//    std::string sync_timestamp;        //��ʼͬ��ʱ��,
    uint64_t latencey;                   //�ӳ٣����ڼ���ͬ��ʱ��(seconds)
    std::string ins_mysql_timestamp;     //��ʼͬ��ʱ��
};
