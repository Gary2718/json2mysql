create table block_entry
(
    block_num                 bigint(10)  UNSIGNED     NOT NULL   COMMENT '块号' ,
    block_id                  varchar(40)              NOT NULL   COMMENT '块ID' ,
    pre_block_id              varchar(40)                         COMMENT '上一个块ID',
    block_timestamp           datetime                            COMMENT '产块时间' ,
    num_trxs                  int(4)       UNSIGNED               COMMENT '块中交易数量' ,
    block_size                bigint(10)    UNSIGNED              COMMENT '块的大小' ,
    processing_time           bigint(20)     UNSIGNED             COMMENT '处理时间' ,
    sync_timestamp            datetime                            COMMENT '开始同步时间' ,
    last_update_timestamp     datetime                            COMMENT '最近一次更新的时间' ,
    PRIMARY KEY (block_num),
    KEY idx_block_num (block_num),
    KEY idx_block_id  (block_id)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='块表';

create table result_to_origin_trx_id
(
    result_trx_id             varchar(40)             NOT NULL   COMMENT '结果交易id' ,
    origin_trx_id             varchar(40)                        COMMENT '原始交易id',
    last_update_timestamp     datetime                           COMMENT '最近一次更新的时间',
    PRIMARY KEY (result_trx_id),
    KEY idx_result_trx_id (result_trx_id),
    KEY idx_origin_trx_id  (origin_trx_id)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='结果交易原始交易id对照表';

create table transaction_entry
(
    trx_id                 varchar(40)                         COMMENT '合约id',
    expiration                datetime                            COMMENT '到期时间' ,
    operations               varchar(256)                         COMMENT '交易中的所有操作',
    op_count                 int(4)         UNSIGNED               COMMENT '交易中操作的数量' ,
    result_trx_type           varchar(40)        NOT NULL         COMMENT '结果交易类型' ,
    contract_id                varchar(36)                         COMMENT '合约id',
    contract_method          varchar(40)                          COMMENT ' 合约方法',
    contract_arg            varchar(512)                           COMMENT ' 合约参数',
    block_num                 bigint(10)  UNSIGNED     NOT NULL   COMMENT '块号' ,
    last_update_timestamp     datetime                            COMMENT '最近一次更新的时间' ,
    PRIMARY KEY (trx_id),
    KEY idx_trx_id (trx_id),
    KEY idx_block_num  (block_num)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='交易表';

