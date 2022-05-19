# 问题记录



### 1. 问题描述:

==Navicat Premium 15 连接 Mycat 可以连接成功, 但是双击数据表不能打开数据表==

报错: Table 'TESTDB.emp' doesn't exist

![image-20210909210825777](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909210825777.png)





### 2.原因分析:

###### 排查过程

1. **在数据表右键可以查看数据表结构 (功能正常)**

![image-20210909211049098](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909211049098.png)

2. **新建查询 单独执行: select * from emp;  能够正常查询出结果(功能正常)** 

![image-20210909212209730](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909212209730.png)

根据上面功能正常初步判断 Navicat 是正常连接 Mycat 并可以正常访问, 仅仅是Navicat触发: 数据表双击事件(打开表) 后台执的SQL语句有问题(个人观点);



3. **结合给出的错误提示信息: Table 'TESTDB.emp' doesn't exist  思考**

提示说: TESTDB.emp 表不存在,  TESTDB 只是存在于Mycat的抽象数据库中, 在物理机的MySQL中没有 TESTDB .

**重现错误提示**:	在Navicat查询界面或者在Xshell界面中执行如下语句,将会重现该错误.

```SQL
select * from TESTDB.emp;		#(出现相同的错误信息)
```

![image-20210909215608939](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909215608939.png)

```sql
select * from empdb.emp;		#(查询成功)
```

![image-20210909215455598](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909215455598.png)

根据以上测试初步判断: Navicat数据库可视化工具打开表时后台执行的SQL语句可能为:

```SQL
select * from  TESTDB.emp;		#可能还有其他参数,但是可以确定是 from TESTDB.emp;
#Navicat可视化工具在打开表时: from 数据库名.表名  然而在物理机的MySQL中数据库名为empdb而非TESTDB;
```

###### 初步结论:

* **高版本的 Navicat 数据库可视化工具在打开表时, ==会自动加上数据库名==, 而抽象数据库名TESTDB与实际数据库名empdb不同导致出现错误;** 



### **3.解决方案**

##### 方案1: 

​			==跟换为低版本的 Navicat== (群里有提供): 低版本的Navicat在打开表时可能不会自动添加数据库名(个人观点)

##### 方案2:

​			==修改配置文件==:  使抽象数据库名和实际数据库名一致, 具体步骤如下.

第一步:修改 server.xml 文件

```bash
vim /usr/local/mycat/conf/server.xml
```

![image-20210909230318871](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909230318871.png)

![image-20210909225756543](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909225756543.png)

​			

第二步:修改 schema.xml 文件

```bash
vim /usr/local/mycat/conf/schema.xml
```

![image-20210909231025543](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909231025543.png)

![image-20210909230649808](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909230649808.png)



第三步: 重启Mycat

```bash
mycat restart			#重启mycat服务
mycat status			#查看mycat服务是启动成功
ss -lnt | grep 8066		#查看mycat端口是否在监听状态
```



第四步: Navicat 可视化工具重新连接 Mycat 即可

![image-20210909231639805](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909231639805.png)



**==温馨提示: 建议提前备份配置文件==**

