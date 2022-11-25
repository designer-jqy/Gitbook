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