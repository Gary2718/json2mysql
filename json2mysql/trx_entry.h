
#pragma once
#include<string>
#include<iostream>
#include<stdint.h>

struct Trx_Entry
{

    void display()
    {
        std::cout << "trx_id: " << trx_id << std::endl;
        std::cout << "expiration: " << expiration << std::endl;
        std::cout << "operations: " << operations << std::endl;
        std::cout << "op_count: " << op_count << std::endl;
        std::cout << "result_trx_type: " << result_trx_type << std::endl;
        std::cout << "contract_id: " << contract_id << std::endl;
        std::cout << "contract_method: " << contract_method << std::endl;
        std::cout << "contract_arg: " << contract_arg << std::endl;
        std::cout << "block_num: " << block_num << std::endl;
    }

    std::string trx_id;                //
    std::string expiration;         // 
    std::string operations;         // 
    uint32_t    op_count;         // 
    std::string result_trx_type;         // 
    std::string contract_id;         // 
    std::string contract_method;         // 
    std::string contract_arg;         // 
    uint64_t    block_num;               //¿éºÅ
};
