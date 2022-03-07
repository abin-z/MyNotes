# **MySQL进阶**

[**MySQL 5.1中文文档**](https://www.mysqlzh.com/)

[MySQL官方文档](https://dev.mysql.com/doc/)

[#数据库](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=MzI4NjY4MTU5Nw==&action=getalbum&album_id=1500546306904260609&scene=173&from_msgid=2247485306&from_itemidx=1&count=3&nolastread=1#wechat_redirect)

[深入理解 MySQL ——锁、事务与并发控制](https://mp.weixin.qq.com/s?__biz=MzI4NjY4MTU5Nw==&mid=2247485306&idx=1&sn=eca2fd59c65ef4579de248e4fa36baf2&chksm=ebd877e8dcaffefec64ea929a3bd360cec403d83b54a4aeaf9dfe535119cf85cfcaffe31e5ed&scene=178&cur_album_id=1500546306904260609#rd)



# 一. MySQL的执行原理

## 1. MySQL架构图

当我们对网站或者App做出操作去访问数据时，其实归根到底是一条SQL语句的执行，那么一条SQL语句到底是怎么执行的呢？

![preview](https://pic4.zhimg.com/v2-8a773bde2b5ec56bead25ad57dc76d1f_r.jpg)

MySQL官方提供的MySQL架构图，我们可以清楚的看到一个连接是要经过很多个步骤最后才获得结果的。

博客园中找到一张较为清楚的图片:

![v2-df7af3acb9b9e050348bc6f00163a7a5_r](https://gitee.com/abin_z/pic_bed/raw/master/v2-df7af3acb9b9e050348bc6f00163a7a5_r.jpg)



## 2. MySQL架构解析

**MySQL主要分为==Server层== 和 ==存储引擎层==**

- **server层:**

​		主要包括**连接器、查询缓存（MySQL8.0移除）、分析器、优化器、执行器**等，

​		所有的跨存储引擎的功能都在这一层实现，比**如存储过程、触发器、视图、函数**等，还有一个**通用的日志模块binglog**

- **存储引擎层:**

​		**主要负责数据的存储和读取**，采用可以替换的插件式架构，支持InnoDB、MyISAM、Memory等多个存储引擎，

​		存储引擎层和server层是可分离的，插件式的，默认的是InnoDB

​		其中InnnoDB有属于自己的日志模块（下文会介绍到）。**「现在最常用的存储引擎是InnoDB，它从MySQL5.5.5版本开始被当做默认的存储引擎了。」**



更加简显易懂的体系结构图: 

![v2-760f1324c080d37a8590b45316827b04_r](https://gitee.com/abin_z/pic_bed/raw/master/v2-760f1324c080d37a8590b45316827b04_r.jpg)

## 3.**组件的详细介绍**

#### 1.连接器 (验证身份+权限判定)

**主要负责用户登录数据库，进行用户的身份认证，包括校验账户密码，权限等操作**，如果用户账户密码已通过，连接器会到权限表中查询该用户的所有权限，之后在这个连接里的权限逻辑判断都是会依赖此时读取到的权限数据，也就是说，后续只要这个连接不断开，即使管理员修改了该用户的权限，该用户也是不受影响的。

> 连接器主要和身份认证和权限相关的功能相关，就好比一个级别很高的门卫一样。



#### 2.查询缓存 (8.0后被移除)

**连接建立后，执行查询语句的时候，会先查询缓存**，MySQL 会先校验这个 sql 语句是否执行过，以 Key-Value 的形式缓存在内存中，Key 是查询语句，Value 是结果集。如果缓存 key 被命中，就会直接返回给客户端，如果没有命中，就会执行后续的操作，完成后也会把结果缓存起来，方便下一次调用。当然在真正执行缓存查询的时候还是会校验用户的权限，是否有该表的查询条件。

**MySQL 8.0 版本后删除了缓存的功能**，官方也是认为该功能在实际的应用场景比较少，所以干脆直接删掉了。

> 为什么8.0过后要移除缓存?
>
> 因为查询缓存失效在实际业务场景中可能会非常频繁，假如你对一个表更新的话，这个表上的所有的查询缓存都会被清空。对于不经常更新的数据来说，使用缓存还是可以的。所以，一般在大多数情况下我们都是不推荐去使用查询缓存的。



#### 3.分析器（词法分析+语法分析）

MySQL 没有命中缓存，那么就会进入分析器，**分析器主要是用来分析 SQL 语句是来干嘛的**，分析器也会分为几步：

分析器，词法分析，语法分析，语义分析，在这里会返回You have an error in your SQL的错误消息，这里会检查表信息，会抛出表字段不存在等错误消息

- 第一步，**词法分析**

  一条 SQL 语句有多个字符串组成，首先要提取关键字，比如 select，提出查询的表，提出字段名，提出查询条件等等。做完这些操作后，就会进入第二步。

- 第二步，**语法分析**

  主要就是判断你输入的 sql 是否正确，是否符合 MySQL 的语法。

完成这 2 步之后，MySQL 就准备开始执行了，但是如何执行，怎么执行是最好的结果呢？这个时候就需要优化器上场了。



#### 4.优化器（选取MySQL认为最优的方案执行）

**优化器的作用就是它认为的`'最优的执行方案'`去执行（有时候可能也不是最优）**，比如多个索引的时候该如何选择索引，多表查询的时候如何选择关联顺序等。

可以说，经过了优化器之后可以说这个语句具体该如何执行就已经定下来。



#### 5.执行器 (选择对应的存储引擎开始执行) 

当选择了执行方案后，MySQL 就准备开始执行了，首先执行前会校验该用户有没有权限，如果没有权限，就会返回错误信息，如果有权限，**就会去调用引擎的接口，返回接口执行的结果。**



> 来张图了解整个过程

![v2-38ce979bcec53ad082d2e15cb330b0c3_r](https://gitee.com/abin_z/pic_bed/raw/master/v2-38ce979bcec53ad082d2e15cb330b0c3_r.jpg)

### 4.语句分析

究竟一条sql语句是怎么执行的呢？其实sql语句大致上可以分为两种，一种是查询语句，一种是更新语句（增加、更新、删除）。

#### 4.1 查询语句

- 查询语句:

```sql
select * from tb_student  A where A.age='18' and A.name=' 张三 ';
```

分析一下这条语句的具体执行流程：

1. 先检查该语句是否有权限，如果没有权限，直接返回错误信息，如果有权限，在 MySQL8.0 版本以前，会先查询缓存，以这条 sql 语句为 key 在内存中查询是否有结果，如果有直接缓存，如果没有，执行下一步。

2. 通过分析器进行词法分析，提取 sql 语句的关键元素，比如提取上面这个语句是查询 select，提取需要查询的表名为 tb_student,需要查询所有的列。然后判断这个 sql 语句是否有语法错误，比如关键词是否正确等等，如果检查没问题就执行下一步。

3. 接下来就是优化器进行确定执行方案，上面的 sql 语句，可以有两种执行方案：

   > 方案a.先查询学生表中姓名为“张三”的学生，然后判断是否年龄是 18

   > 方案b.先找出学生中年龄 18 岁的学生，然后再查询姓名为“张三”的学生。

​		那么优化器根据自己的优化算法进行选择执行效率最好的一个方案（**优化器认为，有时候不一定最好**）。那么确认了执行计划后就准备开始执行了。

4. 进行权限校验，如果没有权限就会返回错误信息，如果有权限就会调用数据库引擎接口，返回引擎的执行结果。



#### 4.2 日志

由于更新语句设计到日志操作，所以先介绍一下日志log。

- ### **binlog 归档日志**

`binlog`（归档日志）是MySQL的Server层有的。 逻辑日志

**主要记录用户对数据库操作的SQL语句**

> binlog 属于逻辑日志，是以二进制的形式记录的是这个语句的原始逻辑，依靠 binlog 是没有 crash-safe 能力的。
> binlog 有两种模式，statement 格式的话是记 sql 语句，row 格式会记录行的内容，记两条，更新前和更新后都有。
> sync_binlog 这个参数设置成 1 的时候，表示每次事务的 binlog 都持久化到磁盘。这个参数也建议设置成 1，这样可以保证 MySQL 异常重启之后 binlog 不丢失。

正是由于binlog有归档的作用，**所以binlog主要用作主从同步和数据库基于时间点的还原**。在mysql数据库主从复制中有用到binlog

`tips：`crash-safe 指MySQL服务器宕机重启后，能够保证：

 		所有已经提交的事务的数据仍然存在。

​		 所有没有提交的事务的数据自动回滚。



- ### **undo log 归档日志**

`undo log`（回滚日志）

**undo log顾名思义，主要就是提供了回滚的作用，但其还有另一个主要作用，就是多个行版本控制(MVCC)，保证事务的原子性**。==在数据修改的流程中，**会记录一条与当前操作相反的逻辑日志**到undo log中==(可以认为当delete一条记录时，undo log中会记录一条对应的insert记录，反之亦然，当update一条记录时，它记录一条对应相反的update记录) 如果因为某些原因导致事务异常失败了，可以借助该undo log进行回滚，保证事务的完整性，**所以undo log也必不可少。**



- ### **redo log (重做日志)**

`redo log` （重做日志）**是 ==InnoDB 引擎特有的日志==。物理日志**

**记录的是数据库中每个页的修改，可以用来恢复提交后的物理数据页**（恢复数据页，且**只能恢复到最后一次提交的位置**，因为修改会覆盖之前的）。

> 在 MySQL 中，如果每一次的更新操作都需要写进磁盘，然后磁盘也要找到对应的那条记录，然后再更新，整个过程 IO 成本、查找成本都很高。为了解决这个问题，MySQL 的设计者就采用了日志（redo log）来提升更新效率。
> 而日志和磁盘配合的整个过程，其实就是 MySQL 里的 WAL 技术，WAL 的全称是 Write-Ahead Logging，它的关键点就是**先写日志，再写磁盘**。
> 具体来说，当有一条记录需要更新的时候，InnoDB 引擎就会先把记录写到 redo log（redolog buffer）里面，并更新内存（buffer pool），这个时候更新就算完成了。同时，InnoDB 引擎会在适当的时候（如系统空闲时），将这个操作记录更新到磁盘里面（刷脏页）。

**redo log 是 InnoDB 存储引擎层的日志，又称重做日志文件，==redo log 是顺序循环写的==**，相比于更新数据文件的随机写，日志的写入开销更小，能显著提升语句的执行性能，提高并发量。

> 在redo log满了到擦除旧记录腾出新空间这段期间，是不能再接收新的更新请求，所以有可能会导致MySQL卡顿。（所以针对并发量大的系统，适当设置redo log的文件大小非常重要）

redo log 是固定大小的，比如可以配置为一组 4 个文件，每个文件的大小是 1GB，那么日志总共就可以记录 4GB 的操作。从头开始写，写到末尾就又回到开头循环写。



- **redo log 和 binlog 区别：**
  1. **redo log 是 InnoDB 引擎特有的；binlog 是 MySQL 的 Server 层实现的，所有引擎都可以使用。**
  2. **redo log 是物理日志，记录的是在某个数据页上做了什么修改，记录了数据；binlog 是逻辑日志，记录的是这个语句的原始逻辑。**
  3. **redo log 是循环写的，空间固定会用完；binlog 是可以追加写入的。追加写是指 binlog 文件写到一定大小后会切换到下一个，并不会覆盖以前的日志。**
  3. **redo log影响主库的数据，binlog影响从库的数据，所以redo log和binlog必须保持一致才能保证主从数据一致，这是前提。**



#### 4.3 更新语句

说完日志，我们再来看一下更新语句，我们看下面这条语句：

```text
UPDATE` ``test` ``SET` ``c` = `c` + 1 ``WHERE` ``id` = 1;
```

语句的意思是找到id为1的那条数据，将c这列的值+1。

这条语句的操作顺序是怎么样的呢？

**操作顺序**

1. 「**查找记录」**: 执行器先找引擎取id=1这一行。ID是主键，引擎直接用树搜索找到这一行。如果id=1这一行所在的数据页本来就在内存中，就直接返回给执行器；否则，需要先从磁盘读入内存，然后再返回；
2. **「执行器」**拿到引擎返回的行数据，把c+1，得到新的一行数据，再调用引擎接口写入这行新数据；
3.  引擎将这行新数据更新到**「内存」**中，同时**「将这个更新之后的数据记录到redo log里面」**，此时redo log处于**「prepare」**状态；
4. 引擎告知执行器，我执行完成了，你随时可以调我的接口提交事务了；
5. 执行器生成这个操作的binlog，并把**「binlog」**写入磁盘。
6. 执行器调用引擎的提交事务接口, **「引擎把刚刚写入的redo log改成」**提交commit状态，更新完成。

思路图:

![v2-829f090ec9c882505262d0e0330cc03e_1440w](https://gitee.com/abin_z/pic_bed/raw/master/v2-829f090ec9c882505262d0e0330cc03e_1440w.jpg)



> 那么**为什么redo log要分两步写，中间再穿插写binlog呢？**

在上图中我们可以看到redolog分为两个阶段，那为什么要这样呢？如果不这样会发生什么问题？下面我们用反证法进行论述：

- **「先写redolog并提交，然后再写binlog」**，假设redolog写完后，机器宕机了，这个时候binlog没有写入，机器重新启动之后，由于redo log已经写完了，系统重启后会通过redo log将数据恢复回来，但是由于binlog没写完就crash了，这时候binlog里面就没有记录这个语句，如果需要用这个binlog来恢复临时库的话，由于这个语句的binlog丢失，这个临时库就会少了这一次更新，恢复出来的数据与原库的值不同。造成了主从不一致
- **「先写 binlog，然后写 redo log」**，如果在binlog写完之后crash，由于redo log还没写，崩溃恢复以后这个事务无效，所以没有记录到redolog。但是binlog里面已经记录了日志。所以，在之后用binlog来恢复的时候，恢复出来的临时库中的数据就与原库的值不同。





### 5.MySQL执行原理脑图

![v2-1b4b32eb5da73b6aefd81e541feaecbf_r](https://gitee.com/abin_z/pic_bed/raw/master/v2-1b4b32eb5da73b6aefd81e541feaecbf_r.jpg)





相关文档:

[全面了解MySQL的执行原理](https://zhuanlan.zhihu.com/p/352436463)





# 二.MySQL 的 crash-safe 

MySQL作为当下最流行的开源关系型数据库，有一个很关键和基本的能力，就是必须能够保证数据不会丢。那么在这个能力背后，MySQL是如何设计才能保证不管在什么时间崩溃，恢复后都能保证数据不会丢呢？有哪些关键技术支撑了这个能力？

相关文档： [MySQL 的 crash-safe 原理解析](https://zhuanlan.zhihu.com/p/142491549)

## 1、前言

MySQL 保证数据不会丢的能力主要体现在两方面：

1. **能够恢复到任何时间点的状态；**    依赖**binlog**
2. **能够保证MySQL在任何时间段突然奔溃，重启后之前提交的记录都不会丢失；**       依赖**InnoDB的redo log和undo log**

对于第一点的能力,   将MySQL恢复到任何时间点的状态，相信很多人都知道，只要保留有足够的**binlog**，就能通过重跑binlog来实现。

对于第二点的能力，也就是本文标题所讲的**crash-safe**。即在 InnoDB 存储引擎中，事务提交过程中任何阶段，MySQL突然奔溃，重启后都能保证事务的完整性，已提交的数据不会丢失，未提交完整的数据会自动进行回滚。这个能力依赖的就是**redo log和unod log**两个日志。



因为crash-safe主要体现在事务执行过程中突然奔溃，重启后能保证事务完整性，所以在讲解具体原理之前，先了解下MySQL事务执行有哪些关键阶段，后面才能依据这几个阶段来进行解析。下面以一条更新语句的执行流程为例，话不多说，直接上图：

![image-20220307235519366](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307235519366.png)

从上图可以清晰地看出一条更新语句在MySQL中是怎么执行的，简单进行总结一下：

1. > 从内存中找出这条数据记录，对其进行更新；

2. > 将对数据页的更改记录到redo log中；

3. > 将逻辑操作记录到binlog中；

4. > 对于内存中的数据和日志，都是由后台线程，当触发到落盘规则后再异步进行刷盘；



## 2、WAL机制

**问题：为什么不直接更改磁盘中的数据，而要在内存中更改，然后还需要写日志，最后再落盘这么复杂？**

这个问题相信很多同学都能猜出来，MySQL更改数据的时候，之所以不直接写磁盘文件中的数据**，最主要就是性能问题。因为直接写磁盘文件是随机写，开销大性能低，没办法满足MySQL的性能要求**。所以才会设计成先在内存中对数据进行更改，再异步落盘。但是内存总是不可靠，万一断电重启，还没来得及落盘的内存数据就会丢失，所以还需要加上写日志这个步骤，万一断电重启，还能通过日志中的记录进行恢复。

**写日志虽然也是写磁盘，但是它是顺序写，相比随机写开销更小**，能提升语句执行的性能（针对顺序写为什么比随机写更快，可以比喻为你有一个本子，按照顺序一页一页写肯定比写一个字都要找到对应页写快得多）。

这个技术就是大多数存储系统基本都会用的**WAL(Write Ahead Log)技术，也称为日志先行的技术，指的是对数据文件进行修改前，必须将修改先记录日志。保证了数据一致性和持久性，并且提升语句执行性能。**



## 3、核心日志模块

**问题：更新SQL语句执行流程中，总共需要写3个日志，这3个是不是都需要，能不能进行简化？**

更新SQL执行过程中，总共涉及**MySQL日志模块其中的三个核心日志，分别是redo log（重做日志）、undo log（回滚日志）、binlog（归档日志）。**这里提前预告，crash-safe的能力主要依赖的就是这三大日志。



### **1、重做日志 redo log**

**redo log也称为事务日志，由InnoDB存储引擎层产生。记录的是数据库中每个页的修改，而不是某一行或某几行修改成怎样，可以用来恢复提交后的物理数据页**（恢复数据页，且只能恢复到最后一次提交的位置，因为修改会覆盖之前的）。

​		前面提到的WAL技术，redo log就是WAL的典型应用，==**MySQL在有事务提交对数据进行更改时，只会在内存中修改对应的数据页和记录redo log日志，完成后即表示事务提交成功，至于磁盘数据文件的更新则由后台线程异步处理**==。由于redo log的加入，保证了MySQL数据一致性和持久性（即使数据刷盘之前MySQL奔溃了，重启后仍然能通过redo log里的更改记录进行重放，重新刷盘），此外还能提升语句的执行性能（**写redo log是顺序写**，相比于更新数据文件的随机写，日志的写入开销更小，能显著提升语句的执行性能，提高并发量），由此可见redo log是必不可少的。

​		**==redo log是固定大小的，所以只能循环写==，从头开始写，写到末尾就又回到开头，相当于一个环形**。当日志写满了，就需要对旧的记录进行擦除，但在擦除之前，需要确保这些要被擦除记录对应在内存中的数据页都已经刷到磁盘中了。**在redo log满了到擦除旧记录腾出新空间这段期间，是不能再接收新的更新请求，所以有可能会导致MySQL卡顿。**（==所以针对并发量大的系统，适当设置redo log的文件大小非常重要！！！==）



### **2、回滚日志 undo log**

undo log顾名思义，**主要就是提供了回滚的作用**，但其还有另一个主要作用，就是**多个行版本控制(MVCC)，保证事务的原子性**。在数据修改的流程中，==**会记录一条与当前操作相反的逻辑日志到undo log中**==（可以认为当delete一条记录时，undo log中会记录一条对应的insert记录，反之亦然，当update一条记录时，它记录一条对应相反的update记录），如果因为某些原因导致事务异常失败了，可以借助该undo log进行回滚，保证事务的完整性，所以undo log也必不可少。

### **3、归档日志 binlog**

**binlog在MySQL的server层产生，不属于任何引擎，主要记录用户对数据库操作的SQL语句（除了查询语句）**。之所以将binlog称为归档日志，是因为binlog不会像redo log一样擦掉之前的记录循环写，而是一直记录（超过有效期才会被清理），如果超过单日志的最大值（默认1G，可以通过变量 max_binlog_size 设置），则会新起一个文件继续记录。但由于日志可能是基于事务来记录的(如InnoDB表类型)，而事务是绝对不可能也不应该跨文件记录的，如果正好binlog日志文件达到了最大值但事务还没有提交则不会切换新的文件记录，而是继续增大日志，所以 **max_binlog_size 指定的值和实际的binlog日志大小不一定相等**。

正是由于binlog有归档的作用，所以binlog主要用作主从同步和数据库基于时间点的还原。

那么回到刚才的问题，binlog可以简化掉吗？这里需要分场景来看：

1. **如果是主从模式下，binlog是必须的，因为从库的数据同步依赖的就是binlog；**
2. 如果是单机模式，并且不考虑数据库基于时间点的还原，binlog就不是必须，因为有redo log就可以保证crash-safe能力了；但如果万一需要回滚到某个时间点的状态，这时候就无能为力，所以建议binlog还是一直开启；

根据上面对三个日志的详解，我们可以对这个问题进行解答：在主从模式下，三个日志都是必须的；在单机模式下，binlog可以视情况而定，保险起见最好开启。







# 三. 执行计划 Explain详解

explain 命令获取 select 语句的执行计划

```sql
explain [select语句]

mysql> EXPLAIN SELECT * FROM one o,two t, three r WHERE o.two_id = t.two_id AND t.three_id = r.three_id;
```

通过 explain 命令获取 select 语句的执行计划，通过 explain 可以知道 select 语句以下信息：

- 表的加载顺序
- sql 的查询类型
- 可能用到哪些索引，实际上用到哪些索引
- 表与表之间的引用关系
- 一个表中有多少行被优化器查询 
- ...



**explain 执行计划包含字段信息如下：分别是 `id`、`select_type`、`table`、`partitions`、`type`、`possible_keys`、`key`、`key_len`、`ref`、`rows`、`filtered`、`Extra` 12个字段。**

![image-20220307135105084](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307135105084.png)

## 1. id

`id：` ：表示查询中执行select子句或者操作表的顺序，**`id`的值越大，代表优先级越高，越先执行**。一般会出现3种情况:

创建三张表 `one`、`two`、`three`，表之间的关系 `one.two_id = two.two_id AND two.three_id = three.three_id`。

#### 1.1 id相同

具有同样的优先级，执行顺序由上而下，具体顺序由优化器决定。

```sql
EXPLAIN SELECT * FROM one o,two t, three r WHERE o.two_id = t.two_id AND t.three_id = r.three_id;
```

```sql
mysql> EXPLAIN SELECT * FROM one o,two t, three r WHERE o.two_id = t.two_id AND t.three_id = r.three_id;
+----+-------------+-------+------------+--------+---------------+---------+---------+----------------------+------+----------+----------------------------------------------------+
| id | select_type | table | partitions | type   | possible_keys | key     | key_len | ref                  | rows | filtered | Extra                                              |
+----+-------------+-------+------------+--------+---------------+---------+---------+----------------------+------+----------+----------------------------------------------------+
|  1 | SIMPLE      | o     | NULL       | ALL    | NULL          | NULL    | NULL    | NULL                 |    2 |      100 | NULL                                               |
|  1 | SIMPLE      | t     | NULL       | ALL    | PRIMARY       | NULL    | NULL    | NULL                 |    2 |       50 | Using where; Using join buffer (Block Nested Loop) |
|  1 | SIMPLE      | r     | NULL       | eq_ref | PRIMARY       | PRIMARY | 4       | xin-slave.t.three_id |    1 |      100 | NULL                                               |
+----+-------------+-------+------------+--------+---------------+---------+---------+----------------------+------+----------+----------------------------------------------------+
```

![image-20220307140007231](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307140007231.png)

可以看到三条记录的id都相同, 都是1, 可以理解成这三个表为一组，具有同样的优先级，执行顺序由上而下，具体顺序由优化器决定。



#### 1.2 id不同

如果我们的 `SQL` 中存在子查询，那么 `id`的序号会递增，`id`值越大优先级越高，越先被执行 。当三个表依次嵌套，发现最里层的子查询 `id`最大，最先执行。

```sql
EXPLAIN select * from one o where o.two_id = (select t.two_id from two t where t.three_id = (select r.three_id  from three r where r.three_name='我是第三表2'));
```

```sql
mysql> EXPLAIN select * from one o where o.two_id = (select t.two_id from two t where t.three_id = (select r.three_id  from three r where r.three_name='我是第三表2'));
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | PRIMARY     | o     | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    2 |       50 | Using where |
|  2 | SUBQUERY    | t     | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    2 |       50 | Using where |
|  3 | SUBQUERY    | r     | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    2 |       50 | Using where |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
```

![image-20220307140852891](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307140852891.png)

如果我们的 `SQL` 中存在子查询，那么 `id`的序号会递增，`id`值越大优先级越高，越先被执行 。当三个表依次嵌套，发现最里层的子查询 `id`最大，最先执行。

#### 1.3 相同和不相同的id均存在

将上边的 `SQL` 稍微修改一下，增加一个子查询，发现 `id`的以上两种同时存在。相同`id`划分为一组，这样就有三个组，同组的从上往下顺序执行，不同组 `id`值越大，优先级越高，越先执行。

```sql
EXPLAIN select * from one o where o.two_id = (select t.two_id from two t where t.three_id = (select r.three_id  from three r where r.three_name='我是第三表2')) AND o.one_id in(select one_id from one where o.one_name="我是第一表2");
```

```sql
mysql>  EXPLAIN select * from one o where o.two_id = (select t.two_id from two t where t.three_id = (select r.three_id  from three r where r.three_name='我是第三表2')) AND o.one_id in(select one_id from one where o.one_name="我是第一表2");
+----+-------------+-------+------------+--------+---------------+---------+---------+--------------------+------+----------+-------------+
| id | select_type | table | partitions | type   | possible_keys | key     | key_len | ref                | rows | filtered | Extra       |
+----+-------------+-------+------------+--------+---------------+---------+---------+--------------------+------+----------+-------------+
|  1 | PRIMARY     | o     | NULL       | ALL    | PRIMARY       | NULL    | NULL    | NULL               |    2 |       50 | Using where |
|  1 | PRIMARY     | one   | NULL       | eq_ref | PRIMARY       | PRIMARY | 4       | xin-slave.o.one_id |    1 |      100 | Using index |
|  2 | SUBQUERY    | t     | NULL       | ALL    | NULL          | NULL    | NULL    | NULL               |    2 |       50 | Using where |
|  3 | SUBQUERY    | r     | NULL       | ALL    | NULL          | NULL    | NULL    | NULL               |    2 |       50 | Using where |
+----+-------------+-------+------------+--------+---------------+---------+---------+--------------------+------+----------+-------------+

```

![image-20220307141231588](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307141231588.png)

将上边的 `SQL` 稍微修改一下，增加一个子查询，发现 `id`的以上两种同时存在。相同`id`划分为一组，这样就有三个组，同组的从上往下顺序执行，不同组 `id`值越大，优先级越高，越先执行。

## 2. select_type

**`select_type`：表示 `select` 查询的类型**，主要是用于区分各种复杂的查询，例如：`普通查询`、`联合查询`、`子查询`等。

1.  SIMPLE(简单SELECT,不使用UNION或子查询等)
2.  PRIMARY(查询中若包含任何复杂的子部分,最外层的select被标记为PRIMARY)
3.  UNION(UNION中的第二个或后面的SELECT语句)
4.  DEPENDENT UNION(UNION中的第二个或后面的SELECT语句，取决于外面的查询)
5.  UNION RESULT(UNION的结果)
6.  SUBQUERY(子查询中的第一个SELECT)
7.  DEPENDENT SUBQUERY(子查询中的第一个SELECT，取决于外面的查询)
8.  DERIVED(派生表的SELECT, FROM子句的子查询)
9.  UNCACHEABLE SUBQUERY(一个子查询的结果不能被缓存，必须重新评估外链接的第一行)



#### 2.1 SIMPLE

`SIMPLE`：表示最简单的 select 查询语句，也就是在查询中不包含子查询或者 `union`交并差集等操作。

#### 2.2 PRIMARY

`PRIMARY`：当查询语句中包含任何复杂的子部分，**最外层查询**则被标记为`PRIMARY`。

#### 2.3 SUBQUERY

`SUBQUERY`：当 `select` 或 `where` 列表中包含了子查询，该**子查询**被标记为：`SUBQUERY` 。

#### 2.4 DERIVED

`DERIVED`：表示包含在`from`子句中的子查询的select，**在我们的 `from` 列表中包含的子查询会被标记为`derived` 。**

#### 2.5 UNION

`UNION`：如果`union`后边又出现的`select` 语句，则会被标记为`union`；若 `union` 包含在 `from` 子句的子查询中，外层 `select` 将被标记为 `derived`。

#### 2.6 UNION RESULT

`UNION RESULT`：代表从`union`的临时表中读取数据，而`table`列的`<union1,4>`表示用第一个和第四个`select`的结果进行`union`操作。

```sql
mysql> EXPLAIN select t.two_name, ( select one.one_id from one) o from (select two_id,two_name from two where two_name ='') t  union (select r.three_name,r.three_id from three r);
```

```sql
mysql> EXPLAIN select t.two_name, ( select one.one_id from one) o from (select two_id,two_name from two where two_name ='') t  union (select r.three_name,r.three_id from three r);

+------+--------------+------------+------------+-------+---------------+---------+---------+------+------+----------+-----------------+
| id   | select_type  | table      | partitions | type  | possible_keys | key     | key_len | ref  | rows | filtered | Extra           |
+------+--------------+------------+------------+-------+---------------+---------+---------+------+------+----------+-----------------+
|    1 | PRIMARY      | two        | NULL       | ALL   | NULL          | NULL    | NULL    | NULL |    2 |       50 | Using where     |
|    2 | SUBQUERY     | one        | NULL       | index | NULL          | PRIMARY | 4       | NULL |    2 |      100 | Using index     |
|    4 | UNION        | r          | NULL       | ALL   | NULL          | NULL    | NULL    | NULL |    2 |      100 | NULL            |
| NULL | UNION RESULT | <union1,4> | NULL       | ALL   | NULL          | NULL    | NULL    | NULL | NULL | NULL     | Using temporary |
+------+--------------+------------+------------+-------+---------------+---------+---------+------+------+----------+-----------------+

```

![image-20220307142255463](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307142255463.png)

## 3.table

查询的表名，并不一定是真实存在的表，有别名显示别名，也可能为临时表，例如上边的`DERIVED`、 `<union1,4>`等。



## 4.partitions

查询时匹配到的分区信息，对于非分区表值为`NULL`，当查询的是分区表时，`partitions`显示分区表命中的分区情况。

![image-20220307142736760](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307142736760.png)

```sql
+----+-------------+----------------+---------------------------------+-------+---------------+---------+---------+------+------+----------+-------------+
| id | select_type | table          | partitions                      | type  | possible_keys | key     | key_len | ref  | rows | filtered | Extra       |
+----+-------------+----------------+---------------------------------+-------+---------------+---------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | one            | p201801,p201802,p201803,p300012 | index | NULL          | PRIMARY | 9       | NULL |    3 |      100 | Using index |
+----+-------------+----------------+---------------------------------+-------+---------------+---------+---------+------+------+----------+-------------+
```



## 5.type *

**type：查询使用了何种类型，它在 `SQL`优化中是一个非常重要的指标**，以下性能从好到坏依次是：

`system`  > `const` > `eq_ref` > `ref`  > `ref_or_null` > `index_merge` > `unique_subquery` > `index_subquery` > `range` > `index` > `ALL`

ALL：Full Table Scan， MySQL将遍历全表以找到匹配的行

index: Full Index Scan，index与ALL区别为index类型只遍历索引树

range:只检索给定范围的行，使用一个索引来选择行

ref: 表示上述表的连接匹配条件，即哪些列或常量被用于查找索引列上的值

eq_ref: 类似ref，区别就在使用的索引是唯一索引，对于每个索引键值，表中只有一条记录匹配，简单来说，就是多表连接中使用primary key或者 unique key作为关联条件

const、system: 当MySQL对查询某部分进行优化，并转换为一个常量时，使用这些类型访问。如将主键置于where列表中，MySQL就能将该查询转换为一个常量,system是const类型的特例，当查询的表只有一行的情况下，使用system



#### 5.1 system

`system`： 当表仅有一行记录时(系统表)，数据量很少，往往不需要进行磁盘IO，速度非常快。比如，Mysql系统表proxies_priv在Mysql服务启动时候已经加载在内存中，对这个表进行查询不需要进行磁盘 IO。

![preview](https://gitee.com/abin_z/pic_bed/raw/master/v2-48b919d21ca0271e1bfc61cb40b31c02_r.jpg)



#### 5.2const

`const`：表示查询时命中 `primary key` 主键或者 `unique` 唯一索引，或者被连接的部分是一个常量(`const`)值。这类扫描效率极高，返回数据量少，速度非常快。

```sql
EXPLAIN SELECT * from three where three_id=1;
```

![image-20220307144059666](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144059666.png)

```sql
mysql> EXPLAIN SELECT * from three where three_id=1;
+----+-------------+-------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table | partitions | type  | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+-------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | three | NULL       | const | PRIMARY       | PRIMARY | 4       | const |    1 |      100 | NULL  |
+----+-------------+-------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
```



#### 5.3 eq_ref

`eq_ref`：**多表关联**查询的时候，**==主键和唯一索引==作为关联条件。查询时命中主键`primary key` 或者 `unique key`索引**， `type` 就是 `eq_ref`。对于user表（外循环）的每一行，user_role表（内循环）只有一行满足join条件，只要查找到这行记录，就会跳出内循环，继续外循环的下一轮查询。

![preview](https://pic3.zhimg.com/v2-eb83ba64a69c5f79306bb96bf78db7c6_r.jpg)

```sql
EXPLAIN select o.one_name from one o ,two t where o.one_id = t.two_id ; 
```

![image-20220307144034496](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144034496.png)

```sql
mysql> EXPLAIN select o.one_name from one o ,two t where o.one_id = t.two_id ; 
+----+-------------+-------+------------+--------+---------------+----------+---------+--------------------+------+----------+-------------+
| id | select_type | table | partitions | type   | possible_keys | key      | key_len | ref                | rows | filtered | Extra       |
+----+-------------+-------+------------+--------+---------------+----------+---------+--------------------+------+----------+-------------+
|  1 | SIMPLE      | o     | NULL       | index  | PRIMARY       | idx_name | 768     | NULL               |    2 |      100 | Using index |
|  1 | SIMPLE      | t     | NULL       | eq_ref | PRIMARY       | PRIMARY  | 4       | xin-slave.o.one_id |    1 |      100 | Using index |
+----+-------------+-------+------------+--------+---------------+----------+---------+--------------------+------+----------+-------------+

```



#### 5.4 ref

`ref`：区别于`eq_ref` ，`ref`表示使用非唯一性索引，会找到很多个符合条件的行。

查找条件列**==使用了索引而且不为主键和唯一索引==**。虽然使用了索引，但该索引列的值并不唯一，这样**即使使用索引查找到了第一条数据，仍然不能停止，要在目标值附近进行小范围扫描。**但它的好处是不需要扫全表，因为索引是有序的，即便有重复值，也是在一个非常小的范围内做扫描。

![image-20220307144002845](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144002845.png)

```sql
mysql> select o.one_id from one o where o.one_name = "xin" ; 
+--------+
| one_id |
+--------+
|      1 |
|      3 |
+--------+
```

```sql
mysql> EXPLAIN select o.one_id from one o where o.one_name = "xin" ; 
+----+-------------+-------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
| id | select_type | table | partitions | type | possible_keys | key      | key_len | ref   | rows | filtered | Extra       |
+----+-------------+-------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
|  1 | SIMPLE      | o     | NULL       | ref  | idx_name      | idx_name | 768     | const |    1 |      100 | Using index |
+----+-------------+-------+------------+------+---------------+----------+---------+-------+------+----------+-------------+
```



#### 5.5 ref_or_null

`ref_or_null`：这种连接类型类似于 ref，**区别在于 `MySQL`会额外搜索包含`NULL`值的行。**

![image-20220307143918591](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307143918591.png)

```sql
mysql> EXPLAIN select o.one_id from one o where o.one_name = "xin" OR o.one_name IS NULL; 
+----+-------------+-------+------------+-------------+---------------+----------+---------+-------+------+----------+--------------------------+
| id | select_type | table | partitions | type        | possible_keys | key      | key_len | ref   | rows | filtered | Extra                    |
+----+-------------+-------+------------+-------------+---------------+----------+---------+-------+------+----------+--------------------------+
|  1 | SIMPLE      | o     | NULL       | ref_or_null | idx_name      | idx_name | 768     | const |    3 |      100 | Using where; Using index |
+----+-------------+-------+------------+-------------+---------------+----------+---------+-------+------+----------+--------------------------+

```



#### 5.6 index_merge

`index_merge`：**使用了索引合并优化方法，查询使用了两个以上的索引。**

下边示例中同时使用到主键`one_id` 和 字段`one_name`的`idx_name` 索引 。

![image-20220307144239929](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144239929.png)

```sql
mysql> EXPLAIN select * from one o where o.one_id >1 and o.one_name ='xin'; 
+----+-------------+-------+------------+-------------+------------------+------------------+---------+------+------+----------+------------------------------------------------+
| id | select_type | table | partitions | type        | possible_keys    | key              | key_len | ref  | rows | filtered | Extra                                          |
+----+-------------+-------+------------+-------------+------------------+------------------+---------+------+------+----------+------------------------------------------------+
|  1 | SIMPLE      | o     | NULL       | index_merge | PRIMARY,idx_name | idx_name,PRIMARY | 772,4   | NULL |    1 |      100 | Using intersect(idx_name,PRIMARY); Using where |
+----+-------------+-------+------------+-------------+------------------+------------------+---------+------+------+----------+------------------------------------------------+
```



#### 5.7 unique_subquery

`unique_subquery`：替换下面的 `IN`子查询，子查询返回不重复的集合。

```sql
value IN (SELECT primary_key FROM single_table WHERE some_expr)
```

#### 5.8 index_subquery

`index_subquery`：区别于`unique_subquery`，用于非唯一索引，可以返回重复值。

```sql
value IN (SELECT key_column FROM single_table WHERE some_expr)
```



#### 5.9 range

`range`：==使用索引选择行，仅检索给定范围内的行==。简单点说就是针对一个**有索引的字段**，给定范围检索数据。在`where`语句中使用 `bettween...and`、`<`、`>`、`<=`、`in` 等条件查询 `type` 都是 `range`。

举个栗子：`three`表中`three_id`为唯一主键，`user_id`普通字段未建索引。

```sql
mysql> EXPLAIN SELECT * from three where three_id BETWEEN 2 AND 3;
```

![image-20220307144634908](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144634908.png)

```sql
mysql> EXPLAIN SELECT * from three where three_id BETWEEN 2 AND 3;
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type  | possible_keys | key     | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | three | NULL       | range | PRIMARY       | PRIMARY | 4       | NULL |    1 |      100 | Using where |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
```



user_id 字段没有索引， 所以type不是 range ，而是全文检索 ALL 

所以**只有对设置了索引的字段，做范围检索 `type` 才是 `range`。**

```sql
mysql> EXPLAIN SELECT * from three where user_id BETWEEN 2 AND 3;
```

![image-20220307144907440](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307144907440.png)

```sql
mysql> EXPLAIN SELECT * from three where user_id BETWEEN 2 AND 3;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | three | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |    33.33 | Using where |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
```



#### 5.10 index

**index包括select索引列，order by主键两种情况。**

order by主键。这种情况会按照索引顺序全表扫描数据，拿到的数据是按照主键排好序的，不需要额外进行排序。

![preview](https://pic1.zhimg.com/v2-ccc6410ca9edbda2eb84144125d4e17c_r.jpg)

select索引列。type为index，而且extra字段为using index，也称这种情况为**索引覆盖**。所需要取的数据都在索引列，无需回表查询。

![preview](https://gitee.com/abin_z/pic_bed/raw/master/v2-ac2d258067814b0fe68a819839773ca7_r.jpg)



`index`：`Index` 与`ALL` 其实都是读全表，区别在于`index`是遍历索引树读取，而`ALL`是从硬盘中读取。

下边示例：`three_id` 为主键，不带 `where` 条件全表查询 ，`type`结果为`index` 。

```sql
mysql> EXPLAIN SELECT three_id from three ;
```

![image-20220307145656193](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307145656193.png)

```sql
mysql> EXPLAIN SELECT three_id from three ;
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type  | possible_keys | key     | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | three | NULL       | index | NULL          | PRIMARY | 4       | NULL |    1 |      100 | Using index |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
```



#### 5.11 ALL

`ALL`：将遍历全表以找到匹配的行，性能最差。

```sql
mysql> EXPLAIN SELECT * from two ;
```

![image-20220307145810003](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307145810003.png)

```sql
mysql> EXPLAIN SELECT * from two ;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
|  1 | SIMPLE      | two   | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    2 |      100 | NULL  |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
```



## 6.possible_keys

`possible_keys`：表示在`MySQL`中可能通过哪些索引，能让我们在表中找到想要的记录，一旦查询涉及到的某个字段上存在索引，则索引将被列出，**但这个索引并不定一会是最终查询数据时所被用到的索引**。具体请参考上边的例子。



## 7.key

`key`：区别于`possible_keys`，key是**查询中实际使用到的索引**，若没有使用索引，显示为`NULL`。具体请参考上边的例子。

当 `type` 为 `index_merge` 时，可能会显示多个索引。



## 8.key_len

`key_len`：表示查询用到的索引长度（字节数），不损失精确性的情况下，长度越短越好  。

- 单列索引，那么需要将整个索引长度算进去；
- 多列索引/复合索引，不是所有列都能用到，需要计算查询中实际用到的列。

注意：`key_len`只计算`where`条件中用到的索引长度，而排序和分组即便是用到了索引，也不会计算到`key_len`中。



## 9.ref

`ref`：常见的有：`const`，`func`，`null`，字段名。

- 当使用常量等值查询，显示`const`，
- 当关联查询时，会显示相应关联表的`关联字段`
- 如果查询条件使用了`表达式`、`函数`，或者条件列发生内部隐式转换，可能显示为`func`
- 其他情况`null`



## 10.rows

`rows`：以表的统计信息和索引使用情况，估算要找到我们所需的记录，需要读取的行数。

这是评估`SQL` 性能的一个比较重要的数据，**`mysql`需要扫描的行数，很直观的显示 `SQL` 性能的好坏**，一般情况下 `rows` 值越小越好。说

```sql
mysql> EXPLAIN SELECT * from three;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
|  1 | SIMPLE      | three | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |      100 | NULL  |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
```



## 11.filtered

`filtered` 这个是一个百分比的值，表里符合条件的记录数的百分比。简单点说，**这个字段表示存储引擎返回的数据在经过过滤后，剩下满足条件的记录数量的比例。** 100% 则说明存储引擎返回的数据全部符合要求, 效果最好.

```sql
在MySQL.5.7版本以前想要显示filtered需要使用explain extended命令。MySQL.5.7后，默认explain直接显示partitions和filtered的信息。
```



## 12.Extra

`Extra` ：不适合在其他列中显示的信息，`Explain` 中的很多额外的信息会在 `Extra` 字段显示。

#### 12.1 Using index

`Using index`：我们在相应的 `select` 操作中使用了覆盖索引，通俗一点讲就是查询的列被索引覆盖，使用到覆盖索引查询速度会非常快，`SQl`优化中理想的状态。

覆盖索引:   一条 `SQL`只需要通过索引就可以返回，我们所需要查询的数据（一个或几个字段），而不必通过二级索引

案例: `one_id`表为主键

```sql
mysql> EXPLAIN SELECT one_id from one ;			# 使用了索引覆盖 Extra = Using index
+----+-------------+-------+------------+-------+---------------+------------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type  | possible_keys | key        | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+-------+---------------+------------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | one   | NULL       | index | NULL          | idx_two_id | 5       | NULL |    3 |      100 | Using index |
+----+-------------+-------+------------+-------+---------------+------------+---------+------+------+----------+-------------+
```

**注意**：想要使用到覆盖索引，我们在 `select` 时只取出需要的字段，不可`select *`，而且该字段建了索引。

```sql
mysql> EXPLAIN SELECT * from one ;		# 没有用到索引覆盖 Extra = NULL
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
|  1 | SIMPLE      | one   | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |      100 | NULL  |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------+
```



#### 12.2 Using where

`Using where`：查询时未找到可用的索引，进而通过`where`条件过滤获取所需数据，但要注意的是并不是所有带`where`语句的查询都会显示`Using where`。

下边示例`create_time` 并未用到索引，`type` 为 `ALL`，即`MySQL`通过全表扫描后再按`where`条件筛选数据。

```sql
mysql> EXPLAIN SELECT one_name from one where create_time ='2020-05-18';
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | one   | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |    33.33 | Using where |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
```



#### 12.3 Using temporary

`Using temporary`：表示查询后结果需要使用临时表来存储，一般在排序或者分组查询时用到。常见于 order by 和 group by 中。典型的，当group by和order by同时存在，且作用于不同的字段时，就会建立临时表，以便计算出最终的结果集。

![image-20220307152822337](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307152822337.png)

```sql
mysql> EXPLAIN SELECT one_name from one where one_id in (1,2) group by one_name;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | one   | NULL       | range| NULL          | NULL | NULL    | NULL |    3 |    33.33 | Using where; Using temporary; Using filesort |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+-------------+
```



#### 12.4 Using filesort

`Using filesort`：表示无法利用索引完成的排序操作，也就是`ORDER BY`的字段没有索引，通常这样的SQL都是需要优化的。

文件排序。表示无法利用索引完成排序操作，以下情况会导致filesort：

- order by 的字段不是索引字段
- select 查询字段不全是索引字段
- select 查询字段都是索引字段，但是 order by 字段和索引字段的顺序不一致

```sql
mysql> EXPLAIN SELECT one_id from one  ORDER BY create_time;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra          |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
|  1 | SIMPLE      | one   | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |      100 | Using filesort |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
```

如果`ORDER BY`字段有索引就会用到覆盖索引，相比执行速度快很多。

```sql
mysql> EXPLAIN SELECT one_id from one  ORDER BY one_id;				# 使用到了索引覆盖 Extra =  Using index 
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
| id | select_type | table | partitions | type  | possible_keys | key     | key_len | ref  | rows | filtered | Extra       |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | one   | NULL       | index | NULL          | PRIMARY | 4       | NULL |    3 |      100 | Using index |
+----+-------------+-------+------------+-------+---------------+---------+---------+------+------+----------+-------------+
```



#### 12.5 Using join buffer

`Using join buffer`：在我们联表查询的时候，如果表的连接条件没有用到索引，需要有一个连接缓冲区来存储中间结果。

Block Nested Loop，**需要进行嵌套循环计算。**两个关联表join，关联字段均未建立索引，就会出现这种情况。比如内层和外层的type均为ALL，rows均为4，需要循环进行4*4次计算。常见的优化方案是，在关联字段上添加索引，避免每次嵌套循环计算。

**先看一下有索引的情况**：连接条件 `one_name` 、`two_name` 都用到索引。

```sql
mysql> EXPLAIN SELECT one_name from one o,two t where o.one_name = t.two_name;
```

![image-20220307153416368](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307153416368.png)

```sql
mysql> EXPLAIN SELECT one_name from one o,two t where o.one_name = t.two_name;
+----+-------------+-------+------------+-------+---------------+----------+---------+----------------------+------+----------+--------------------------+
| id | select_type | table | partitions | type  | possible_keys | key      | key_len | ref                  | rows | filtered | Extra                    |
+----+-------------+-------+------------+-------+---------------+----------+---------+----------------------+------+----------+--------------------------+
|  1 | SIMPLE      | o     | NULL       | index | idx_name      | idx_name | 768     | NULL                 |    3 |      100 | Using where; Using index |
|  1 | SIMPLE      | t     | NULL       | ref   | idx_name      | idx_name | 768     | xin-slave.o.one_name |    1 |      100 | Using index              |
+----+-------------+-------+------------+-------+---------------+----------+---------+----------------------+------+----------+--------------------------+

```

接下来删掉 连接条件 `one_name` 、`two_name` 的字段索引。发现`Extra` 列变成 `Using join buffer`，`type`均为全表扫描，这也是`SQL`优化中需要注意的地方。

![image-20220307153546201](https://gitee.com/abin_z/pic_bed/raw/master/image-20220307153546201.png)

```sql
mysql> EXPLAIN SELECT one_name from one o,two t where o.one_name = t.two_name;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------------------------------------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra                                              |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------------------------------------------+
|  1 | SIMPLE      | t     | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    2 |      100 | NULL                                               |
|  1 | SIMPLE      | o     | NULL       | ALL  | NULL          | NULL | NULL    | NULL |    3 |    33.33 | Using where; Using join buffer (Block Nested Loop) |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------------------------------------------+

```

#### 12.6 Impossible where

`Impossible where`：表示在我们用不太正确的`where`语句，导致没有符合条件的行。

```sql
mysql> EXPLAIN SELECT one_name from one WHERE 1=2;
```

```sql
mysql> EXPLAIN SELECT one_name from one WHERE 1=2;
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+------------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra            |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+------------------+
|  1 | SIMPLE      | NULL  | NULL       | NULL | NULL          | NULL | NULL    | NULL | NULL | NULL     | Impossible WHERE |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+------------------+
```



#### 12.7 No tables used

`No tables used`：我们的查询语句中没有`FROM`子句，或者有 `FROM DUAL`子句。

```sql
mysql> EXPLAIN select now();
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
| id | select_type | table | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra          |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
|  1 | SIMPLE      | NULL  | NULL       | NULL | NULL          | NULL | NULL    | NULL | NULL | NULL     | No tables used |
+----+-------------+-------+------------+------+---------------+------+---------+------+------+----------+----------------+
```

`Extra`列的信息非常非常多，详见 `MySQL`官方文档 ： https://dev.mysql.com/doc/refman/5.7/en/explain-output.html#jointype_index_merge

相关博客: https://juejin.cn/post/6844904163969630221#heading-7       

​				 https://zhuanlan.zhihu.com/p/396114960

















