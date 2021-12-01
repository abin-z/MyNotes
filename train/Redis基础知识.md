# Redis基础知识

date: 2021-9-10 pm

学习目标: 掌握Redis相关专业和技能



**快速回顾关系型数据库相关理论**

* X_Y轴构建的二维表
* 满足笛卡尔积
* 满足一定的范式
* 数据结构合理
* 通过加密后的文件格式存储于磁盘中----IO瓶颈
* 事务机制, ACID特征(**数据库事务必须具备`ACID`特性，`ACID`分别是`Atomic`原子性，`Consistency`一致性，
  `Isolation`隔离性，`Durability`持久性。**)
* 支持通用的SQL(结构化查询语言)
* 常见的关系型数据库: MySQL, Oracle, IBM-DB2, IBM-informix, SQL server, access



关系型数据库的不足: 高并发,海量 不能满足企业级应用需求



### 初步了解非关系型数据库Redis

NoSQL, 泛指非关系型数据库. 

关系型数据库和非关系型数据库: https://www.jianshu.com/p/fd7b422d5f93

**Redis是非关系型数据库的一个主流代表**(面向高性能并发读写的Key-Value数据库)

* 是键值对(K-V)的数据结构
* 数据类型非常丰富
* 是一款内存数据库
* 提供将内存中的数据进行持久化
* 基于C语言开发的
* 单线程的内存数据库
* 非关系型数据库不支持事务,也不具备ACID特性

**常用的应用场景:** 

​	易于大型企业系统快速拓展 : 1.主从复制  2.哨兵机制

​	高性能的读写速度

​	使用C语言开发-----更加有利于硬件资源的管理

​	分布式集群

**快速了解16个逻辑数据库**



redis数据持久化, RDB与AOF

https://baijiahao.baidu.com/s?id=1654694618189745916&wfr=spider&for=pc





### Redis的安装

1. 可以单独安装在Windows系统. Linux系统下
2. 本次学习, 为了搭建环境, 在docker容器下安装
3. Redis的默认端口号: 6379

```bash
docker pull redis	#docker中拉取最新的Redis
docker run --name redis --restart always -p 6379:6379 -d redis		#创建容器并启动
docker ps -a 
docker logs redis
docker inspect redis
docker exec -it redis bash
```



```bash
#关注目录下的重要配置文件
cd /usr/local/bin/
```

![image-20210910152852542](https://gitee.com/abin_z/pic_bed/raw/master/img/202111181526483.png)

```bash
redis-cli				#Redis的客户端
redis-server			#Redis的服务器端
redis-check-aof			#AOF持久化
redis-check-rdb			#RDB持久化
redis-sentinel			#哨兵机制
gosu					#?
docker-entrypoint.sh	#新版本添加shell脚本
```

登录Redis客户端

```bash
redis-cli							#在docker容器中执行
docker exec -it redis redis-cli		#在物理机进入docker时候直接进入Redis客户端
```

使用第三方工具连接: Redis Desktop Manager





**客户端命令行执行常用Redis命令**

Redis的命令:  http://doc.redisfans.com/		掌握基础命令(至少要熟悉 key 和 string)

### key键

```bash
select index(0-15)  #进入相应的逻辑数据库,默认是0数据库
set KEY VALUE		#添加键值对数据(K-V)
get KEY				#获取键为KEY的值Value
keys * 				#获取当前数据库的所有key值
flushdb				#清除当前数据库的所有数据
flushall			#清除所有数据库的所有数据

del key[key...]		#删除给定的一个或多个key
exists key			#检查给定的key是否存在,存在返回1,不存在返回0;
key pattern			#查找所有符合给定模式pattern的key.  key * / key h?llo
move key db			#将当前数据库的key移动到给定数据库db中: move ename 2   #将ename移动到2
type key			#返回key所存储的值类型
expire key seconds	#为给定 key 设置生存时间，当 key 过期时(生存时间为 0 )，它会被自动删除。
persist	key			#移除给定 key 的生存时间，将这个 key 从『易失的』(带生存时间 key )转换成『持久的』(一个不带生存时间、永不过期的 key )。
ttl key				#以秒为单位,返回给定key的剩余生存时间
pttl key			#这个命令类似于 TTL 命令，但它以毫秒为单位返回 key 的剩余生存时间，而不是像 TTL 命令那样，以秒为单位
rename key newkey	#将key改名为newkey,newkey存在时将覆盖旧的值
renamenx key newkey	#当且仅当newkey不存在时候,将key改名为newkey
expireat key timestamp 	#EXPIREAT 的作用和 EXPIRE 类似，都用于为 key 设置生存时间。不同在于 EXPIREAT 命令接受的时间参数是 UNIX 时间戳(unix timestamp)。

pexpireat key milliseconds-timestamp	#这个命令和 EXPIREAT 命令类似，但它以毫秒为单位设置 key 的过期 unix 时间戳，而不是像 EXPIREAT 那样，以秒为单位。

randomkey			#从当前数据库中随机返回(不删除)一个 key 。
sort				#返回或保存给定列表、集合、有序集合 key 中经过排序的元素。
scan				#一个基于游标的迭代器（cursor based iterator）

```

### string字符串

```bash
append key value  	
	#如果 key 已经存在并且是一个字符串， APPEND 命令将 value 追加到 key 原来的值的末尾。
	#如果 key 不存在， APPEND 就简单地将给定 key 设为 value ，就像执行 SET key value 一样。

decr key		
	#将 key 中储存的数字值减一。如果 key 不存在，那么 key 的值会先被初始化为 0 ，然后再执行 DECR 操作。

decrby key decrement		
	#将 key 所储存的值减去减量 decrement 。如果 key 不存在，那么 key 的值会先被初始化为 0 ，然后再执行 DECRBY 操作。

incr key
	#将 key 中储存的数字值增一。
	#如果 key 不存在，那么 key 的值会先被初始化为 0 ，然后再执行 INCR 操作。

incrby key increment
	#将key多存储的值上增量increment
	#如果 key 不存在，那么 key 的值会先被初始化为 0 ，然后再执行 INCRBY 命令

incrbyfloat key increment
	#为 key 中所储存的值加上浮点数增量 increment 。

get key
    #返回 key 所关联的字符串值。
    #如果 key 不存在那么返回特殊值 nil 。
    #假如 key 储存的值不是字符串类型，返回一个错误，因为 GET 只能用于处理字符串值。

getrange key start end
    #返回 key 中字符串值的子字符串，字符串的截取范围由 start 和 end 两个偏移量决定(包括 start 和 end 在内)。
    #负数偏移量表示从字符串最后开始计数， -1 表示最后一个字符， -2 表示倒数第二个，以此类推。

getset key value
    #将给定 key 的值设为 value ，并返回 key 的旧值(old value)。
    #当 key 存在但不是字符串类型时，返回一个错误。
   
mget key[key...]
    #返回所有(一个或多个)给定 key 的值。
    #如果给定的 key 里面，有某个 key 不存在，那么这个 key 返回特殊值 nil 。因此，该命令永不失败。

mset key value[key value ...]
    #同时设置一个或多个 key-value 对。
    #如果某个给定 key 已经存在，那么 MSET 会用新值覆盖原来的旧值，如果这不是你所希望的效果，请考虑使用 MSETNX 命令：它只会在所有给定 key 都不存在的情况下进行设置操作。
    #MSET 是一个原子性(atomic)操作，所有给定 key 都会在同一时间内被设置，某些给定 key 被更新而另一些给定 key 没有改变的情况，不可能发生。

strlen key
	#返回 key 所储存的字符串值的长度。
	#当 key 储存的不是字符串值时，返回一个错误。
```



# docker容器中搭建Redis一主三从 + 哨兵机制

**架构示意图:**

![image-20210913170957940](https://gitee.com/abin_z/pic_bed/raw/master/img/202111181525188.png)

### Redis一主三从搭建

1. 分别构建四台Redis应用容器

```bash
docker run --name redis_s1 --restart always -p 6380:6379 -d redis
docker run --name redis_s2 --restart always -p 6381:6379 -d redis
docker run --name redis_s3 --restart always -p 6382:6379 -d redis

docker ps -a #查看是否为UP状态
```

2. 查看四台Redis容器的内部ip

```bash
docker inspect redis			#172.17.0.2
docker inspect redis_s1			#172.17.0.7
docker inspert redis_s2			#172.17.0.8
docker inspect redis_s3			#172.17.0.9
```

3. 分别登录相应的Redis容器

```bash
docker exec -it redis redis-cli
docker exec -it redis_s1 redis-cli
docker exec -it redis_s2 redis-cli
docker exec -it redis_s3 redis-cli

#####: 如果想在命令行中使用中文可以在进入容器的时候添加参数: --raw
docker exec -it redis redis-cli --raw



#分别查看当前Redis容器的所有信息
info
#分别查看当前Redis容器的主从复制的所有信息
info replication
```



正式搭建一主三从的架构

```bash
#分别在从机的docker容器中执行
slaveof 主机IP 对应的对外端口号

slaveof 172.17.0.2 6379
info 			#查看是否配置成功

slaveof no one	#将slave变为master

#在主机端查看确认是否配置成功
info replication
```

![image-20210913151939973](https://gitee.com/abin_z/pic_bed/raw/master/img/202111181526371.png)

```bash
#测试相应的主从复制过程
set ename "tom" 

#可以在从机中查看相应的值(数据同步)
#提示: 在Redis中主从复制的架构中, 从机的默认情况下是 只读 模式,从机上不能进行写操作
```



### 哨兵机制的搭建(如果master宕机,自动选举master)

**Redis的哨兵默认的端口为: 26379**

打开指定的文件目录:  /usr/local/bin

```bash
cd /usr/local/bin		#redis-sentinel 是一个哨兵服务.
```

![image-20210913154440874](https://gitee.com/abin_z/pic_bed/raw/master/img/202111181526413.png)

```bash
在宿主机中的 /root/redis/conf
vi sentinel.conf
#添加如下内容
port 26379
sentinel monitor 哨兵名称 主机IP 端口号6379 哨兵数量1

sentinel monitor mysentinel 172.17.0.2 6379 1

#################
#可以在哨兵配置文件中添加参数修改宕机检测周期：
sentinel down-after-milliseconds 哨兵名  毫秒

sentinel down-after-milliseconds mysentinel 10000 #宕机检测周期修改为10秒,10000毫秒, 默认是30秒
#################

#创建相应的哨兵redis容器
docker run --name sentinel --restart always -p 26379:26379 -v /root/redis/conf:/etc/redis/conf -d redis redis-sentinel /etc/redis/conf/sentinel.conf

docker ps -a

cat sentinel.conf
```

该哨兵配置文件会根据当前主机--从机状态动态添加相应的监控信息

![image-20210913162132148](https://gitee.com/abin_z/pic_bed/raw/master/img/202111181526183.png)

```bash
docker logs sentinel
```

<img src="https://gitee.com/abin_z/pic_bed/raw/master/img/202111181526369.png" alt="image-20210913164415552"  />



演示主从身份的切换

**如果当前的master 宕机后, 哨兵会从slave中选举(算法)出一个新的master, 并且其他slave也会自动连接到新的master中.**

**如果之前宕机的master恢复后, 不会再变为主机, 将作为slave从机**





### redis配置文件 redis.conf

Windows server2003

Linux --- 编译 --- gcc --- 安装后 --- 会有配置文件redis.conf

docker + redis 将不会有核心配置文件: 但是可以自行下载



redis.conf 配置信息是K----V形式

redis.conf 对格式要求比较高,建议修改前备份

```bash
	68行 ==========>bind 127.0.0.1 =======># bind 127.0.0.1
	87行 ==========>protected-mode yes =======>protected-mode no
	91行 port 6379  一般情况下不修改
	100行 tcp-backlog 511  
	112行 timeout 0
	129行 tcp-keepalive 300
	255行 loglevel notice 
	/data/dump.rdb
	342行 dbfilename dump.rdb
	395行 # masterauth 123456
	403 # masteruser <username>
	790行 requirepass root
	833行 # maxclients 10000
	1094行 appendonly no  
	1098行 appendfilename "appendonly.aof"
	1227行 # cluster-enabled yes
	1241行 # cluster-node-timeout 15000
	
	68行 ==========>bind 127.0.0.1 =======># bind 127.0.0.1      务必关注
	87行 ==========>protected-mode yes =======>protected-mode no 务必关注
	1094行 appendonly no  务必关注
```



### 搭建redis分布式集群

在VMware中搭建

* 直接复制系统镜像文件
* 通过虚拟机的克隆技术

上述的方式构建的Linux服务器: UUID会冲突 ,需要手动修改UUID

```bash
vim /etc/sysconfig/network-scripts/ifcfg-ens33 
#修改文件中的UUID ,原则: 不相同就可以
systemctl restart network			#重启网络
```



搭建四台Linux服务器和使用核心配置文件: redis.conf

redis.conf 

```bash
68行: # 172.0.0.1
87行 ==========>protected-mode yes =======>protected-mode no
1094行 appendonly yes
```

