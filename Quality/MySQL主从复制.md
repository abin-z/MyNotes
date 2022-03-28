# MySQL一主三从复制配置

date： 2021-09-07 pm

### 1、数据库主从复制的应用场景

* **数据的备份----提高数据的安全性**
* **在复杂业务的情况下,sql操作可能会锁表:防止影响其他业务**
* **减轻主数据库的压力,实现读写分离: 主写从读**



### **2、为什么需要主从复制？**

1、在业务复杂的系统中，有这么一个情景，有一句sql语句需要锁表，导致暂时不能使用读的服务，那么就很影响运行中的业务，使用主从复制，让主库负责写，从库负责读，这样，即使主库出现了锁表的情景，通过读从库也可以保证业务的正常运作。

2、做数据的热备份

3、架构的扩展。业务量越来越大，I/O访问频率过高，单机无法满足，此时做多库的存储，降低磁盘I/O访问的频率，提高单个机器的I/O性能。

### **3、什么是mysql的主从复制？**

MySQL 主从复制是指数据可以从一个MySQL数据库服务器主节点复制到一个或多个从节点。MySQL 默认采用异步复制方式，这样从节点不用一直访问主服务器来更新自己的数据，数据的更新可以在远程连接上进行，从节点可以复制主数据库中的所有数据库或者特定的数据库，或者特定的表。

### **4、mysql复制原理**

[**MySQL主从复制的原理**](https://zhuanlan.zhihu.com/p/96212530)

#### **原理：**

（1）master服务器将数据的改变记录二进制binlog日志，当master上的数据发生改变时，则将其改变写入二进制日志中；

（2）slave服务器会在一定时间间隔内对master二进制日志进行探测其是否发生改变，如果发生改变，则开始一个I/OThread请求master二进制事件

（3）同时主节点为每个I/O线程启动一个dump线程，用于向其发送二进制事件，并保存至从节点本地的中继日志中，从节点将启动SQL线程从中继日志中读取二进制日志，在本地重放，使得其数据和主节点的保持一致，最后I/OThread和SQLThread将进入睡眠状态，等待下一次被唤醒。

![image-20210930165409110](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210930165409110.png)

#### **总结：**

- 从库会生成两个线程,一个I/O线程,一个SQL线程;
- I/O线程会去请求主库的binlog,并将得到的binlog写到本地的relay-log(中继日志)文件中;
- 主库会生成一个log dump线程,用来给从库I/O线程传binlog;
- SQL线程,会读取relay log文件中的日志,并解析成sql语句逐一执行;



## 一主三从技术架构:

![image-20210908161300971](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210908161300971.png)

**配置master主库:配置文件**

```sql
server-id = 4			#指定的主机ID--可以自定义
binlog-do-db = empdb	#指定的业务数据库名称--可以自定义
binlog-format = mixed	#主从复制的格式:混合模式
log-bin = mysql-bin		#记录复制过程的日志文件名--可以自定义
```

```bash
binlog-format = row		#主从复制的模式, 也可以是行模式: row , SQL模式: statement
```



**配置salve从机:配置文件**

```sql
server-id = 1			#从机的ID不能重复
#super-read-only = 1	#设置从机的超级只读模式
```



### **1.首先在docker中添加MySQL容器**

```bash
#主机master
docker run --name master --restart always -p 3306:3306 -v /root/mysql/data:/mysql -e MYSQL_ROOT_PASSWORD=root -d mysql:5.7

#从机slave
docker run --name slave1 --restart always -p 3307:3306 -v /root/mysql/data:/mysql -e MYSQL_ROOT_PASSWORD=abin -d mysql:5.7
docker run --name slave2 --restart always -p 3308:3306 -v /root/mysql/data:/mysql -e MYSQL_ROOT_PASSWORD=abin -d mysql:5.7
docker run --name slave3 --restart always -p 3309:3306 -v /root/mysql/data:/mysql -e MYSQL_ROOT_PASSWORD=abin -d mysql:5.7

```

### **2.复制相应的配置文件到 	/etc/mysql/my.cnf 	(也可以修改配置文件)**

```bash
#复制master的配置文件
docker cp ./my.cnf master:/etc/mysql/my.cnf

#复制slave的配置文件
docker cp ./my.cnf slave1:/etc/mysql/my.cnf
docker cp ./my.cnf slave2:/etc/mysql/my.cnf
docker cp ./my.cnf slave3:/etc/mysql/my.cnf
#注意,主机和从机的配置文件都是不相同的,根据情况来操作
```



### **3.重启MySQL容器**

```bash
docker restart master
docker restart slave1
docker restart slave2
docker restart slave3
docker ps -a				#重启之后需要验证容器是否启动成功 UP状态

cat /etc/mysql/my.cnf		#进入到相应的容器中查看确认MySQL的配置文件已经修改了
```



### **4.主机的操作**

```bash
#登录到MySQL中
mysql -u root -p 

#查看master的状态(记录相应的参数,后面有用)
show master status;

mysql> show master status;
+------------------+----------+--------------+------------------+-------------------+
| File             | Position | Binlog_Do_DB | Binlog_Ignore_DB | Executed_Gtid_Set |
+------------------+----------+--------------+------------------+-------------------+
| mysql-bin.000005 |      154 | empdb        |                  |                   |
+------------------+----------+--------------+------------------+-------------------+
1 row in set (0.00 sec)

#PS: 日志文件的目录: /var/lib/mysql
#PS: 重新初始化从机命令	
reset master		#注意,每次执行重置主机后,需要重新配置从机的通信方式
```

![](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210908160250909.png)





### **5.从机的操作**

```bash
#确认从机已经启动;
docker ps -a

#登录到MySQL中
mysql -u root -p
```

修改从机与主机的通信语句:

```sql
	change master to
	master_host='192.168.220.128',		#主机master的IP地址
	master_port=3306,					#主机master的MySQL的对外的端口号
	master_user='root',					#用户名
	master_password='root',				#密码
	master_log_file='mysql-bin.000001',	#日志文件名称		需要严格根据master的参数写入
	master_log_pos=154;					#日志文件的Position偏移量
```

```sql
#开启slave服务:
start salve;
#确定主从状态是否OK?
show slave status \G;

#若一下两个变量为yes 则说明配置成功
         	Slave_IO_Running: Yes
            Slave_SQL_Running: Yes
  
#PS:如果配置不成功:都不为yes的方式
#登录slave从机执行如下命令:
stop slave;
reset slave all;
show slave status \G;
```

可以在主机上对MySQL操作来验证主从复制的功能...

如果出现一下情况参考下面链接: 注意防火墙是否关闭

            Slave_IO_Running: Connecting
            Slave_SQL_Running: Yes

https://blog.csdn.net/mbytes/article/details/86711508





### 本方式一主三从的方式

如果数据库的CRUD在主机master上操作,会同步到从机中,

如果数据库的CRUD在从机slave上操作,不会同步到主机master中, 但是在本从机中可以查看相应的修改



如果想让从机只能读取数据,不能修改数据,则修改从机的my.cnf配置文件

```sql
super-read-only = 1	#设置从机的超级只读模式	
```



#### 思考:

​	验证大批量数据在主机master中导入时, 与主机的延迟问题, 如何解决?
