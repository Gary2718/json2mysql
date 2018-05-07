drop table block_entry;

create table block_entry(

block_num             bigint(10)  UNSIGNED     NOT NULL   COMMENT '块号' ,
block_id              varchar(40)     NOT NULL   COMMENT '块ID' ,
pre_block_id          varchar(40)                COMMENT '上一个块ID',
block_timestamp       datetime                   COMMENT '产块时间' ,
block_delegate        varchar(40)                COMMENT '产块代理' ,
num_trxs              int(4)       UNSIGNED              COMMENT '块中交易数量' ,
block_size            bigint(10)       UNSIGNED          COMMENT '块的大小' ,
processing_time       bigint(20)     UNSIGNED            COMMENT '处理时间' ,
sync_timestamp        datetime                   COMMENT '开始同步时间' ,
ins_mysql_timestamp   datetime                   COMMENT '写入MySQL的时间' ,

PRIMARY KEY (block_num),
KEY idx_block_num (block_num),
KEY idx_block_id  (block_id)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='块表';


SELECT * from block_entry  ;
