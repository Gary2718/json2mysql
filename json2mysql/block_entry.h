#include<string>
#include"mysql.h"


bool Connect_To_Mysql();
class Block_Entry
{
public:
	Block_Entry();
	~Block_Entry();

public:
	long int    block_num;               //块号
	std::string block_id;                //块ID
	std::string pre_block_id;            //上一个块ID
	std::string block_timestamp;           //产块时间
	std::string signature_delegate;       //产块代理
	int num_trxs;                         //块中交易数量
	long int block_size;                 //块的大小
	std::string sync_timestamp;             //开始同步时间
	long int processing_time;              //处理时间 s
};
