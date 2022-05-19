# Linux下安装Mycat

什么是Linux: 是一个用于服务器的OS, 是多用户,多进程, 多任务,支持多CPU的安全可靠的服务器操作系统



## Linux安装Java

执行解压Java安装包

```bash
tar -zxvf jdk-8u261-linux-x64.tar.gz -C /usr/local/
```



然后配置环境变量

```bash
#首先复制一下配置文件,防止发生错误
cp -p /etc/profile /etc/profile_bak

vim /etc/profile
#在文件末尾追加如下内容
#添加Java环境变量
#-------------------------------
export JAVA_HOME=cd /usr/local/jdk1.8.0_261
export PATH=$PATH:$JAVA_HOME/bin
#-------------------------------

source /etc/profile
#验证: 在任意路径下都可以使用Java 或者 Java -version 查看Java的相关信息
```



查看Linux的环境变量: 	env

查看Windows的环境变量:	set



## Linux安装数据库中间件mycat

**传统的应用程序系统架构**如下图:

![](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210909133453341.png)



数据库中间件的定义:	

​		**处于底层数据库和用户应用系统之间，主要用于屏蔽异构数据库的底层细节的中间件。是客户端与后台的数据库之间进行通信的桥梁。**



Mycat是一个彻底开源的，面向企业应用开发的大数据库集群(中间件), 其核心是分库分表

遵守Mysql原生协议，跨语言，跨平台，跨数据库的通用中间件代理

基于心跳的自动故障切换，支持读写分离，支持MySQL主从，以及galera cluster集群。

基于Nio实现，有效管理线程，解决高并发问题。

支持分布式事务

集群基于ZooKeeper管理，在线升级，扩容，智能优化，大数据处理

**详细参考:**

 https://www.cnblogs.com/kevingrace/p/9365840.html

https://www.cnblogs.com/joylee/p/7513038.html



**Mycat 和 MySQL主从模式基本架构**

![image-20210909103719092](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210909103719092.png)



###  安装mycat

mycat是基于Java开发的, 开源的数据库中间件

```bash
# 打开相应的目录
cd /root/mycat

#解压安装包 解压到/usr/local/目录下
tar -zxvf Mycat-server-1.6.7.3-linux.tar.gz -C /usr/local/

#进入到mycat的文件夹确认是否解压成功
/usr/local/mycat

#目录解析
bin		#二进制文件(包含可执行文件)
conf	#存放核心配置文件
lib		#依赖包,依赖库
logs	#mycat产生的日志文件

#配置环境变量
#打开 /etc/profile 在文件末尾追加
vim /etc/profile

#add macat path
#------------------------------
export MYCAT_HOME=/usr/local/mycat
export PATH=$PATH:$MYCAT_HOME/bin
#------------------------------

source /etc/profile

#也可以是使用在/sbin目录下创建软连接
ln -s /usr/local/mycat/bin/mycat  /sbin/mycat
```

conf中的配置文件

![image-20210909094522410](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210909094522410.png)

==mycat 的默认端口是8066==

查看相应的端口: `ss -lnt | grep 8066`  如果8066端口启动则说明启动成功



启动, 停止, 重启, 查看mycat

```bash
mycat start
mycat restart
mycat stop
mycat status

#出现问题时, 首先查看日志文件
cd /usr/local/mycat/logs/
cat mycat.log	或者
cat wrapper.log
```

设置mycat服务开机自启动

```bash
#打开 /etc/rc.d 文件夹
cd /etc/rc.d

#里面有一个rc.local文件, 将该文件打开并在末尾追加如下代码:
vim rc.local

# set mycat auto start 
#---------------------------------
source /etc/profile
/usr/local/mycat/bin/mycat start
#---------------------------------
```



在docker MySQL容器中登录Mycat

```bash
docker exec -it master bash							#进入到docker容器中
mysql -uroot -p -P8066 -h192.168.220.128			#mycat的默认端口号8066 -h主机IP
#默认的密码是:123456		可在server.xml配置文件中修改

#注意这里登录的是mycat不是MySQL,并且此时的mycat是独立的 还没有与MySQL进行关联
```

![image-20210909124338305](https://gitee.com/abin_z/pic_bed/raw/master/img/NDTBmfRsuFU6tOL.png)

此时的mycat是独立的,还没有与MySQL关联(想要关联需要修改配置文件,并重启mycat)

![image-20210909125122779](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210909125122779.png)



### 关联Mycat与MySQL

将默认的抽象数据库与实际业务数据库进行关联( 修改配置文件 schema.xml )

```bash
#以下内容为schema.xml的信息 需要根据自己的情况修改
<?xml version="1.0"?>
<!DOCTYPE mycat:schema SYSTEM "schema.dtd">
<mycat:schema xmlns:mycat="http://io.mycat/">

        <schema name="TESTDB" checkSQLschema="false" sqlMaxLimit="100" dataNode="dn01" >
        
        </schema>
        <dataNode name="dn01" dataHost="dh01" database="empdb" />

        <dataHost name="dh01" maxCon="1000" minCon="10" balance="1" writeType="0" dbType="mysql" dbDriver="native" switchType="1" slaveThreshold="100">
                <heartbeat>select user()</heartbeat>
                <writeHost        host="master1"   url="192.168.220.128:3306" user="root" password="root">
                        <readHost host="M1_slave1" url="192.168.220.128:3307" user="root" password="abin" />
                        <readHost host="M1_slave2" url="192.168.220.128:3308" user="root" password="abin" />
                        <readHost host="M1_slave3" url="192.168.220.128:3309" user="root" password="abin" />
                </writeHost>
        </dataHost>
</mycat:schema>

```



```bash
cp /root/mycat/conf/schema.xml /usr/local/mycat/conf/schema.xml 
cp：是否覆盖"/usr/local/mycat/conf/schema.xml"？ y					#直接覆盖原来的schema.xml

#重启mycat
mycat restart
mycat status
ss -lnt | grep 8066
```

验证是否关联成功

```bash
docker exec -it master bash							#进入到docker容器中
mysql -uroot -p -P8066 -h192.168.220.128			#mycat的默认端口号8066 -h主机IP
show databases;
use TESTDB;
show tables;
select * from emp;
```

![image-20210909132931082](https://gitee.com/abin_z/pic_bed/raw/master/img/hRb6NEsf9pOaPrc.png)



实现读写分离: 主写从读

重点关注: schema.xml 配置文件

![image-20210910131543655](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210910131543655.png)

```bash
balance="0"		#不开启读写分离-----所有的操作都发送到: writeHost 上

balance="1"		#如果从机存在,读取功能有从机slave负责,写只能在主机master上
				#从机全部宕机后,此时读写功能都由主机master负责
				
balance="2"		#随机在从机与主机之间随机提供读功能,写只能在主机master上
```

