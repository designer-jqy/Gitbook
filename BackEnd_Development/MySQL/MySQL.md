# MySQL

## 四种隔离级别
未提交读

提交读

可重复读

串行化


多版本并发控制(MVCC)

慢查询




性能剖析SQL指令
```sql
-- 查看profiling变量的配置情况
SHOW VARIABLES LIKE 'profiling%';
-- 如果profiling值为off，通过如下指令设置profiling
SET profiling = 1;
-- 查看最近几条SQL语句的查询情况
SHOW profiles;
-- 查询特定的SQL语句
SHOW profile FOR QUERY 10;
-- 对特定查询的耗时进行排序
SELECT STATUS, SUM(DURATION) AS Total_time, COUNT(*) AS Calls FROM INFORMATION_SCHEMA.PROFILING WHERE QUERY_ID = 1 GROUP BY STATE ORDER BY Total_time DESC;
```
根据计数器剖析某个SQL指令
```sql
-- 先清空计数器
FLUSH STATUS;
-- 查询执行SQL语句后特定的计数器数量，结果中的Created_tmp_disk_tables表示创建磁盘表的次数，Handler_read_rnd表示查询无索引的次数
SHOW STATUS WHERE Variable_name LIKE 'Handler%' OR Variable_name LIKE 'Created%';
```

```sql
-- 查询当前服务器的连接情况
SHOW processlist;
SELECT * FROM INFORMATION_SCHEMA.PROCESSLIST WHERE DB='test';

SELECT event_name, count_star, sum_timer_wait FROM performance_schema.events_waits_summary_global_by_event_name ORDER BY sum_timer_wait DESC LIMIT 5;
```


悲观锁、乐观锁、多版本并发控制
https://juejin.cn/post/6961938483837403150

外键约束: foreign_key_checks

修改表的字符编码
```sql
alter table <table_name> default charset=<new_charset>;
```

在已有表上创建索引
```sql
-- 普通索引
create index <index_name> on <table_name>(`<table_item_name>`);
-- 唯一索引
create unique index <index_name> on <table_name>(`<table_item_name>`);
-- 复合索引
create index <index_name_long> on <table_name>(`<table_item_name_1>`, `<table_item_name_2>`);
```

索引下推
```sql
select * from table_1 where a > 1 and b = 2;
```

覆盖索引
```sql
select b from table_1 where a > 1;
```

UTF8编码中一个汉字（包括数字）占用3个字节

GBK编码中一个汉字（包括数字）占用2个字节

4.0版本以下，varchar(100)，指的是100字节，如果存放UTF8汉字时，只能存33个（每个汉字3字节）

5.0版本以上，varchar(100)，指的是100字符，无论存放的是数字、字母还是UTF8汉字（每个汉字3字节），都可以存放100个。最大大小是 65532字节

varchar括号里面的数字表示的是字符还是字节:

[MySQL VARCHAR Lengths and UTF-8](https://stackoverflow.com/questions/1997540/mysql-varchar-lengths-and-utf-8)

[Mysql: String Type Overview](https://web.archive.org/web/20160425203826/https://dev.mysql.com/doc/refman/5.0/en/string-type-overview.html)