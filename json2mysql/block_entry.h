#include<string>
#include"mysql.h"


bool Connect_To_Mysql();
class Block_Entry
{
public:
	Block_Entry();
	~Block_Entry();

public:
	long int    block_num;               //���
	std::string block_id;                //��ID
	std::string pre_block_id;            //��һ����ID
	std::string block_timestamp;           //����ʱ��
	std::string signature_delegate;       //�������
	int num_trxs;                         //���н�������
	long int block_size;                 //��Ĵ�С
	std::string sync_timestamp;             //��ʼͬ��ʱ��
	long int processing_time;              //����ʱ�� s
};
