# 一. MySQL数据库概述

CRUD是指 create增加, retrieve检索, update更新, delete删除

### 1. 关系型数据库特点:

* X_Y轴构建的二维表

* 满足笛卡尔积

* 满足一定的范式

* 数据结构合理

* 通过加密后的文件格式存储于磁盘中----IO瓶颈

* 事务机制, ACID特征(**数据库事务必须具备`ACID`特性，`ACID`分别是`Atomic`原子性，`Consistency`一致性，
  `Isolation`隔离性，`Durability`持久性。**)

* 支持通用的SQL(结构化查询语言)

* 常见的关系型数据库: MySQL, Oracle, IBM-DB2, IBM-informix, SQL server, access

  

### 2. 数据库的设计

**需求分析**-------概要分析（E-R数据库模型）三大范式理解------详细设计

​						但是不盲目追寻范式，需要找到一个平衡点。

设计合理的数据库需要考虑哪些要素？

1. 考虑范式
2. 表的依赖关系
3. 表的对应关系 ： 一对一，一对多
4. 字段命名规范
5. 字段的长度
6. 是否可以为null
7. 是否有默认值
8. 那个字段为主键？
9. 那个字段为外键?



### 3. 数据库管理系统（DBMS）

**SQL**语言    结构化查询语言

SQL 语句分类：

DQL： 数据查询语言： select			#查询语句不会修改数据库中的数据，只适用于显示。

DML： 数据操作语言： insert / delete / update

DDL :   数据库定义语言： create / drop / alter

TCL  :   事务控制语言： 	commit / rollback



### 4. 数据库三范式:

**第一范式(1NF):	必须有主键, 字段不能再分**

​		要求有主键，数据库中不能出现重复记录，每一个字段是原子性不能再分



# 二. MySQL基础





**第二范式(2NF):	非主键字段完全依赖主键**

​		第二范式在第一范式的基础上，要求数据库中所有非主键字段完全依赖主键（严格意义上说，尽量不要使用联合主键）



**第三范式(3NF):  建立在第二范式基础上，要求非主键字段不能产生传递依赖与主键字段**



### 1. **导入数据库脚本：**

进入数据库： `use db_name;`

导入sql文件：` source 文件路径`

查看当前数据库版本:   `select version() from dual;`     企业在用的mysql数据库版本一般是5.7

```sql
mysql> select version() from dual;
+-----------+
| version() |
+-----------+
| 8.0.26    |
+-----------+
1 row in set (0.02 sec)
```



创建数据库和数据表；

```sql
create database db_name;

use db_name;

desc emp;		#查看表结构

select empno,ename,job,mgr,hiredate,sal,comm,deptno from emp;

select * from emp;			#使用*（不建议）：效率比前一个方法要低，因为要把*转成所有具体字段，而且语义不明确
```



### 2. MySQL中的常用数据类型

| 类型         | 大小           | 描述                                                         |
| ------------ | -------------- | ------------------------------------------------------------ |
| char         | 0-255 bytes    | 定长字符串                                                   |
| varchar      | 0-65535 bytes  | 变长字符串（节约存储空间）                                   |
| int          | 4 bytes        | 整型                                                         |
| double       | 8 bytes        | 双精度浮点型                                                 |
| decimal(m,d) | 依赖于M和D的值 | m总个数， d小数位数。                                        |
| date         | 3 bytes        | YYYY-MM-DD 日期值                                            |
| time         | 3 bytes        | HH:MM:SS 时间值                                              |
| DATETIME     | 8 bytes        | YYYY-MM-DD HH:MM:SS 混合日期和时间值                         |
| BLOB         |                | Binary Large Object(二进制大对象) 视频图像等，开发中基本不用，只需要存文件地址 |
| CLOB         |                | Character Large Object(字符串大对象)开发中很少用，最大存4G+的字符串 |

**VARCHAR和CHAR对比**

1、 都是字符串

2、 VARCHAR可以==根据实际数据长度分配空间==，需要进行长度判断，因此执行效率比较低

3、 CHAR不需要动态分配空间，==执行效率高==，可能会导致空间浪费

4、 字段中数据==不具备伸缩性==的时候，采用CHAR存储，比如（状态值）性别MALE和FEMALE，其他就是用VARCHAR，比如姓名等



date时间格式控制符

| 格式符   | 功能                       |      | 格式符 | 功能                    |
| -------- | -------------------------- | ---- | ------ | ----------------------- |
| %Y       | 代表四位的年份             |      | %y     | 代表两位的年份          |
| %m       | 代表月,格式(01,02....12)   |      | %c     | 代表月, 格式(1,2....12) |
| %d       | 代表日                     |      |        |                         |
| %H       | 代表24小时制               |      | %h     | 代表12小时制            |
| %i       | 代表分钟,格式(00,01....59) |      |        |                         |
| %S或者%s | 代表秒, 格式(00,01....59)  |      |        |                         |



### 3. MySQL中的运算符：

```sql
=			#等于  注意：null字段不能使用 = ， 需要用 is null 或者 is not null
<>或!=		#不等于
< 			#小于
<=			#小于等于
> 			#大于
>=			#大于等于
between ... and ...			#两个值之间，相当于>= and <=
is null		#为null（is not null 不为空）
and			#并且
or			#或者
in			#包含，相当于多个or（not in 不在这个范围中）或的关系
not			#not可以取非，用于is和in中
like		#like为模糊查询，支持%或者下划线_匹配
#			%匹配任意个字符
#			下划线_只匹配一个字符
```

注意：==null不是数字，是空值，不能进行数学计算，因此不能用 = 号 用 is null 或者 is not null==

   		null不能进行数学计算，如果进行计算的话，结果都为null，可以使用 ifnull（comm，0）函数



### 4. 数据处理函数

#### 单行处理函数 			

一对一， 一行一行数据进行转换。数据处理函数是mysql数据本身特有的，有些函数可能在其他数据库不起作用

```sql
lower(字段名)			#转换小写
		select lower(ename) aslowername from emp;
upper(字段名)				#转换大写
		select upper(ename) asuppername from emp;
substr(...)				#截取子串（substr(被截取的字符串，起始下标，截取的长度）
		select substr(ename,1,1)as firstchar from emp;  #起始下标是从1开始的！
length				#取长度
		select length(ename) asenameLength from emp;
trim				#去除字符串前后空格
		select * from emp where ename=trim('  king    ');
str_to_date			#将字符串转换成日期(插入的时候用的多)
		select ename,hiredate from emp where hiredate > str_to_date('01-01-1998','%m-%d-%Y');
date_format			#格式化日期，将date类型数据转化为字符串(查询的时候用)
		select ename,date_format(hiredate,'%m/%d/%Y')as newhiredate from emp;
Format				#设置千分位
Round				#四舍五入
		select round(123.56,1);#结果为123.6
		select round(123.56,-1);#结果为120
Rand()				#生成随机数
		select rand();#输出0-1闭区间的随机数
		
ifnull				#可以把null转换成一个具体值
		select sum(ifnull(comm,0)) as sumcomm from emp;
```



#### 多行处理函数/聚合函数/分组函数

多对一，多行数据输入只输出一行，group by 后面可用

注意：

* ==分组函数会自动忽略 null 值，不需要手动增加where条件排除null==
* ==分组函数不能直接使用在where 关键字后面（可用间接使用）==

```sql
sum			#求和
		select sum(sal+ifnull(comm,0)) as sumsal from emp;
		select sum(ifnull(comm,0)) as sumcomm from emp;
			或者
		select sum(comm) assumcomm from emp;#空值无需做处理，但是还是建议加上ifnull
avg			#平均
		select avg(sal+ifnull(comm,0)) as avgsal from emp;
max			#最大值
		select max(sal) as maxsalfrom emp;
min			#最小值
		select min(sal) as minsalfrom emp;
count		#记录数
		count(*)  	# 表示多行记录, 会包含null的行
		count(1) 	# 和count(*)几乎没有区别
		如果写成：
		select count(comm) from emp where comm is null;
		#结果为0，因为count(字段)会全表扫描自动忽略 字段 = null 的值
		
distinct	#将查询结果中的某一个字段的重复记录去除
			#distinct A 区处于字段名A相同的记录
            #distinct A,B 去除与字段名A和字段名B相同的记录
            #注意：DISTINCT只能出现在所有字段的最前面，后面接多个字段为多字段联合去重
        select distinct job fromemp;
		select count(distinct job) from emp;
		select distinct deptno,job from emp;
```

1、COUNT(expr) ，返回SELECT语句检索的行中expr的值不为NULL的数量。结果是一个BIGINT值。

2、如果查询结果没有命中任何记录，则返回0

3、但是，值得注意的是，`COUNT(*)` 的统计结果中，会包含值为NULL的行数。

**所以，** **`COUNT(常量)` 和 `COUNT(*)`表示的是直接查询符合条件的数据库表的行数。而`COUNT(列名)`表示的是查询符合条件的列的值不为NULL的行数**



### 5. 起别名 as

```sql
select ename,sal*12 as yearsal from emp;	#as 起别名
或者：
select ename,sal*12 yearsal from emp;		#不建议省略as
```



# 三. 查询select

## 1. 简单查询

### 1. 条件查询 where

注意:  ==where 后面不能直接使用分组函数(多行处理函数)==

```sql
select 字段 from 表名 where 条件;

select * from emp where sal >= avg(sal);	#错误的写法,where后面不能直接使用分组函数

#但是可以间接使用(子查询)
select
	*
from
	emp
where
	sal >= (select avg(sal) from emp);
```



### 2. 排序：order by

​			默认是升序： asc

​			降序是：  	desc

​			有条件查询的时候需要放在where的后面；

单一字段排序

```sql
select ename,sal from emp order by sal asc;
select ename,sal from emp order by sal desc;
select ename,sal,hiredate from emp order by hiredate desc;
```

多个字段排序的时候，**首先按照第一个字段排序，如果第一个字段相同，那么按照第二个字段再进行排序**

```sql
select job,ename,sal from emp order by ename asc,sal desc;
#字段下标从1开始，这里的下标指的是你查询显示的列的下边，比如job,ename,sal，那么job就是1，sal是3
select job,ename,sal fromemp where job=’MANAGER’ order by 3 asc;
```



### 3. 分组：group by

语句格式：

	select
		字段
	from
		表名
	group by
		字段;

分组后显示的结果有两类: ==分组的字段==和==分组函数(多行处理函数)==, 如果显示其他字段没有意义.在ORACLE中会直接报错

```sql
#查找每个职业中，最高的薪水
select job,max(sal) as maxsal from emp group by job;
#查找每个部门的最高薪水
select deptno,avg(sal) as avgsal from emp group by deptno order by deptno;
#计算不同部门不同岗位的最高薪水
select deptno,job,max(sal) as maxsal from emp group by deptno,job order by deptno;
#找出每个工作岗位的最高薪水,除了manager之外
select job,max(sal) as maxsal from emp where job <> 'MANAGER' group by job;
```

**group by子句在数据库底层执行时会先排序，再分组。**



### 4. 数据过滤条件 having

注意： ==having 必须和 group  by搭配使用，分组后再筛选==

where 和having 都是数据过滤条件,  但是where是用在group by 之前, having是用在group by之后.

```sql
#找出每个工作岗位的平均薪水,要求只显示平均薪水大于2000的
#having 是对分组后的数据仍然不满意的情况下使用
select
	job, avg(sal) as avgsal
from
	emp
group by
	job
having
	avgsal > 2000
order by
	avgsal;
```



### 5. limit 

作用: 获取一表的前几行和中间某几行的数据（**只在mysql中有用**）

```sql
#例子：取得前5个员工信息
select * from emp limit 0, 5;
#或者
select * from emp limit 5;

limit m,n		#m 为起始下标(默认是0开始的), n表示长度

select * from emp;				#全部员工信息
select * from emp limit 0,5;	#求得前五个员工信息：

select ename,sal from emp order by sal desc limit 0,3;	#截取薪水的前三名

limit #实现分页		数据的下标是从0开始的		
				页码：pageNo        		pageSize：5
				第一页：1,2,3,4,5			limit 0,5
				第二页：6,7,8,9,10			limit 5,5
				第三页：11,12,13,14,15		limit 10,5
										   limit (pageNo-1)*pageSize,pageSize
```



### 6. 基础select 查询语句总结

**一个完整的查询select SQL语句如下:** 

```sql
#以下顺序不能变,严格遵守
select				
	xxx		#显示,操作,函数等		
from				
	xxx		#数据表		
where				
	xxx		#分组前的过滤条件		
group by			
	xxx		#分组字段
having
	xxx		#分组后的过滤条件
order by
	xxx		#排序规则
limit m,n;	#分页

# 1. from 将硬盘上的表文件加载到内存
# 2. where 将符合条件的数据行摘取出来，生成一张临时表
# 3. group by 根据列中的数据种类，将当前临时表划分成若干个新的临时表
# 4. having 可以过滤掉group by生成的不符合条件的临时表
# 5. select 对当前表进行整列读取
# 6. order by 对select生成的临时表，进行重新排序，生成新的临时表
# 7. limit 对最终生成的临时表的数据行进行截取
```





## 2. 跨表查询,联表查询

查询次数:	跨表查询的查询次数, 如果没有加条件限制为多张表的笛卡尔积(乘积)	建议:**==联表查询最多不能超过三张表==**

**Mysql多表连接查询的执行细节**: https://blog.csdn.net/qq_27529917/article/details/87904179

按照年代分类

```sql 
# SQL92:
	select ename,dname from emp as e, dept as d where e.deptno = d.deptno;
	
# SQL99:
	select
		e.ename, d.dname
	from 
		emp as e
	join
		dept as d
	on
		e.deptno = d.deptno
	where
		#数据过滤条件;
```



按照链接方式分类:

### **1. 内连接**:  	

![image-20211007202741920](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211007202741920.png)



#### ① 等值连接

```sql
#查询员工所对应的部门名称
select
	e.ename, d.dname			#要显示的字段
from
	emp as e					# as 可以省略
inner join						#连接表, inner可以省略
	dept as d
on
	e.deptno = d.deptno;		#等值连接方式
```

#### ② 非等值连接

```sql
#查询出员工薪水对应的薪水等级
select
	e.ename, e.sal, s.grade
from
	emp as e
inner join									#inner可以省略
	salgrade as s
on
	e.sal between s.losal and s.hisal		#非等值连接方式
order by
	s.grade, e.sal;							#先按照等级排序,在按照薪水排序
```

#### ③ 自连接

```sql
#把一张表看成两张表使用,自己连接自己
#查询出员工所对应的领导名称:显示员工的名称和领导名称
select
	a.ename, b.ename as leadername
from	
	emp as a
inner join							#inner可以省略
	emp as b
on
	a.mgr = b.empno;				#自连接方式,连接的是同一张表的不同临时表
```



### **2. 外连接**:

​			概念: A表和B表能够完全匹配的记录查询出来之外，**将其中一张表的记录无条件的完全查询出来，对方表没有匹配的记录时，会自动模拟出null值与之匹配**

​			外连接的查询结果条数 >= 内连接查询条数

#### ① 左外连接/左连接  

左外连接: 	包含左边表的全部行(不管右边是否存在与它们匹配的行),以及右边表中全部匹配的行

![image-20211007202823961](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211007202823961.png)

```sql
#员工的领导名称,并且显示所有的员工
select
	a.ename, b.ename as leadername
from
	emp as a
left outer join				#显示所有的员工, outer可以省略
	emp as b
on
	a.mgr = b.empno;
```



#### ② 右外连接/右连接

右外连接: 	包含右边表的全部行（不管左边表是否存在与它们匹配的行），以及左边表中全部匹配的行

![image-20211007202837996](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211007202837996.png)

```sql
#要求显示员工的部门名称,并且显示所有的部门名称
select
	e.ename, d.dname
from
	emp as e
right outer join				#让右边表的全部行全部显示(显示所有部门)  outer可以省略
	dept as d
on
	e.deptno = d.deptno
order by
	d.deptno;
```

左右外连接可以互换的(表的位置互换和left和right互换)

==只能通过 right 或者 left 区分内连接和外连接==

多表查询(join最好不要超过三个表)

```sql
#查询员工的部门名称,员工的领导名称和薪水等级
#需要查询三张表
#ename -> emp
#dname -> dept
#grade -> salgrade
select
	d.dname,
    e.ename, 
    m.ename as leadername,
    s.grade
from
	emp as e
join						#所有的join都是和emp表建立的连接
	dept as d
on
	e.deptno = d.deptno
join						#所有的join都是和emp表建立的连接
	emp as m
on
	e.mgr = m.empno
join						#所有的join都是和emp表建立的连接
	salgrade as s
on
	e.sal between s.losal and s.hisal
order by
	d.dname,
	s.grade desc;
```



## 3. 子查询

定义: select语句嵌套select语句

注意：select子句可以出现在select/from/where关键字后面，例如

select... (select) ... [很少时候用，了解即可]

from ...(select) ...

where ...(select) ...



### where后面的子查询

```SQL
#找出薪水比公司平均薪水高的员工,要求显示员工名和薪水
select ename, sal from emp where sal > avg(sal);#错误:分组函数不能直接使用在where后面
#ERROR 1111 (HY000): Invalid use of group function

#正确语句
select ename, sal from emp where sal > (select avg(sal) as avgsal from emp); 
```



### from后面的子查询

```sql
#找出每个部门的平均薪水，并且要求显示部门编号和名称以及平均薪水和薪水等级
#首先找出每个部门的部门信息和平均薪水
	select
		e.deptno as dno, d.dname as dnm, avg(e.sal) as avgsal
	from
		emp as e
	join
		dept as d
	on
		e.deptno = d.deptno
	group by
		e.deptno;

#然后将子查询的结果作为临时表替换

select
	t.dno, t.dnm, t.avgsal, s.grade
from
	(
    	select
            e.deptno as dno, d.dname as dnm, avg(e.sal) as avgsal
        from
            emp as e
        join
            dept as d
        on
            e.deptno = d.deptno
        group by
            e.deptno
    ) as t
join
	salgrade as s
on
	t.avgsal between s.losal and s.hisal
order by
	t.dno;
```



## 4. union 合并(相加)集合

注意: ==两个查询子句的字段的个数和类型要一样，ename / job==

```sql
#查询出工作岗位是manager和salesman的员工
select ename,job from emp where job = 'MANAGER' or job = 'SALESMAN';
select ename,job from emp where job in ('MANAGER','SALESMAN'); #或的关系
#如果是 	not in('MANAGER','SALESMAN') 括号里面是and的关系

#使用union
select ename,job from emp where job = 'MANAGER'
union
select ename,job from emp where job = 'SALESMAN';

#注意:如果第二个ename改成empno 输出结果为一串数字,没有意义
```

**UNION 语句**：用于将不同表中相同列中查询的数据展示出来；（不包括重复数据）

**UNION ALL 语句**：用于将不同表中相同列中查询的数据展示出来；（包括重复数据）

```sql
SELECT 列名称 FROM 表名称 UNION SELECT 列名称 FROM 表名称 ORDER BY 列名称；
SELECT 列名称 FROM 表名称 UNION ALL SELECT 列名称 FROM 表名称 ORDER BY 列名称；
```



# 四. 数据表table

表的定义 :==数据库基本组成单元，行和列组成，行是记录，列是字段==，字段包括：字段名称，类型，长度，约束。

## DDL语句

- **DDL :   数据库定义语言**： create / drop / alter

### **1. 创建表语法: **

```sql
create table t_表名(
	字段1 字段类型(长度) 字段约束,
	字段2 字段类型(长度) 字段约束,
	字段3 字段类型(长度) 字段约束,
	...
	字段N 字段类型(长度) 字段约束,
);
```

创建学生表:

```sql
create table t_student(
    no int(4) not null,
    name varchar(32) not null,
    gender char(1) not null,
    birth date,
    email varchar(128)
);
```

mysql中判断表是否存在，**若不存在就创建，存在就跳过**创建操作的方法：

```sql
CREATE TABLE IF NOT EXISTS `student` (    #判断这张表是否存在，若存在，则跳过创建表操作，
 `s_id` varchar(40) NOT NULL, 
`s_name` varchar(255) default NULL, 
`s_age` varchar(255) default NULL, 
`s_msg` varchar(255) default NULL, 
PRIMARY KEY (`s_id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO `student` VALUES ('7', '重阳节', '33', '登高赏菊'); # 插入数据

# 仅仅复制表结构, 会判断表是否存在, 若存在，则跳过创建表操作，
CREATE TABLE IF NOT EXISTS user_basics_deleted LIKE user_basics;
```

根据现有表快速复制一张表:

```sql
CREATE TABLE T_NEW SELECT * FROM T_OLD WHERE 1=2  # -----只复制表结构到新表
create table emp_bak as select * from emp;	#对一张表做备份:emp_bak和emp表没有任何关联
```

### **2. 查看表的建表语句:**

```sql
show create table t_student;
```

### **3.删除表语法:**

```SQL
drop table 表名;
drop table if exists 表名;

drop table t_student;			#如果表不存在的时候就会报错
drop table if exists t_student;	#如果表不存在则不会报错, MySQL特有的
```

### **4. 快速复制一张表**

```sql
create table emp_bak as select * from emp;	#对一张表做备份:emp_bak和emp表没有任何关联
show create table emp_bak;					#查看表的结构
```

### **5. 修改表的结构:**

```sql
1、新增：ALTER TABLE 表名 ADD 字段名 字段类型(长度);
alter table t_student add email varchar(128);	#新增email字段

2、修改：ALTER TABLE 表名 MODIFY 字段名 字段类型(长度);
alter table t_student modify no int(8);			#修改no字段长度为8

3、删除：ALTER TABLE 表名 DROP 字段名;
alter table t_student drop email;				#删除email字段

不常用的修改字段名称方法：
alter table 表名 change 原字段名称 新字段名称 字段类型(长度);
alter table t_student change name username varchar(32);
```

## DML语句

**DML语句, 数据库管理语言:** insert / update / delete

### **1. insert语句**: 

向表中添加数据

```sql
insert into 表名(字段1，字段2，...，字段N) values (字段1的值，字段2 的值，...，字段N的值);

insert into t_student(no, name, gender, birth, email) values(1001,'zhangsan','1',str_to_date('1998-10-01','%Y-%m-%d'),'163@163.com');

#mysql默认的日期格式为 年月日 当日期格式本来就是年月日的时候可以不使用str_to_date()函数
insert into t_student(no, name, gender, birth, email) values(1002,'lisi','1','1998-11-01','126@163.com');

#给指定字段添加值: 未添加的字段默认填充 null
insert into t_student(no, name, gender) values(1003,'wangwu','0');

#当给每个字段都添加值的时候可以用不写字段名,顺序必须一一对应, 但是不推荐
insert into t_student values(1005, 'tom', '1', '1998-12-12','tom@163.com');
```

快速向表中插入数据

```sql
insert into emp_bak select * from emp where job = 'MANAGER';
#注意：快速插入保证字段类型和数量一致
select count(*) from emp_bak;		#查看表的数量
```



### **2. update语句:**

修改表中已经存在的记录

```sql
update 表名 set 字段名称1 = 字段1值，字段名称2 = 字段2值 where 限制条件;

update t_student set birth = str_to_date('1951-10-10','%Y-%m-%d'), email = '192@126.com' where name ='tom';
###必须加限制条件！！否则就是全表修改
```

### **3. delete语句**:

 删除表中的数据

```sql
delete from t_student;  #删除表中的所有数据

delete from t_student where no = 1001; #添加限制条件

#注意：这属于物理删除，无法恢复
```

------

### 4. default

**设置表中字段的默认值: default**

```sql
drop table if exists t_student;		#删除相应的表

create table t_student(
    no int(4) not null,
    name varchar(32) not null,
    gender char(1) default '1',		#给性别默认值为男 '1'
    birth date,
    email varchar(128)
);
```

查看MySQL字符集相关配置

```sql
show variables like '%char%';
```

![image-20210924220157118](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210924220157118.png)

修改相应的变量信息:

```sql
set 变量名 = 字符集名称;
set character_set_results = gbk;
set character_set_results = utf8mb4;

show variables like '%char%';
```

# 五. 约束constraint

约束的概念: 对表中数据的限制条件

目的：保证表中数据的完整和有效

### 1. 非空约束: not null

表明字段必须有具体数据，不能为NULL

```sql
create table t_student(
    no int(10),
    name varchar(32) not null,	#非空约束not null
    email varchar(128)
);
```



### 2. 唯一性约束: unique

表明字段必须不能重复，保持唯一,  但是添加数据时null 可以重复   

唯一键约束添加后，实际上建立了一个索引，将该索引删除后，就等于删除了联合唯一约束。

**列级写法**: 写在字段后面

```sql
#列级约束：写在字段后面，保证邮箱唯一性
create table t_student(
no int(10),
name varchar(32) not null,
email varchar(128) unique		#列级约束
);
```

**表级写法:** 表级写法支持多个字段联合约束()

```sql
create table t_student(
no int(10),
name varchar(32) not null,
email varchar(128),
unique(email)						#表级写法,多个字段的时候是联合约束
);
```

联合唯一性约束:只有当name和email都一样的时候，才是重复值，只要有一个值不一样，就认为不是重复记录

```sql
drop table if exists t_student;		#删除相应的表
create table t_student(
no int(10),
name varchar(32) not null,
email varchar(128),
unique(email,name)	
 		#表级写法,多个字段的时候是联合约束,只有当email和name都相同时候才是重复的,与去重
);
```

**约束起别名：**

```sql
create table t_user(
    no int(10),
    name varchar(32) not null,
    email varchar(128),
    constraint t_user_name_email_unique unique(name,email)	
    #上面的语句表示给 unique(name,email) 起别名:t_user_name_email_unique
);
```

查看相应表的约束:

```sql
use  information_schema;
select CONSTRAINT_NAME from TABLE_CONSTRAINTS where TABLE_NAME = "t_user";
```

![image-20210928235406912](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210928235406912.png)

给已有的表添加唯一性约束(唯一性索引): ==注意:在原有表上添加唯一性约束要保证原有字段的数据的唯一性, 否则添加约束失败==(添加索引时null也不能重复)

```sql
ALTER TABLE `库名`.`表名` 
ADD UNIQUE INDEX `索引名称`(`字段名`) USING BTREE COMMENT '机构代码code 唯一性索引';
```

查询user表中，user_name字段值重复的数据及重复次数

```sql
select user_name,count(*) as count from user group by user_name having count>1;
```

**约束_非空约束(notnull)与唯一性约束(unique)联合使用** 可以达到主键唯一性的效果



### 3. 主键约束: primary key

primary key 简称 PK

主键约束、主键字段、主键值:

表中某个字段添加主键约束之后，该字段成为主键字段，主键字段中出现的每一个数据都成为主键值。

1、添加了主键 primary key的字段“==**既不能重复也不能为空**==”; 效果与 not null unique 效果相同，但是==本质是不同的,**primary key会自动添加“主键索引-index”**==，提高检索效率。

2、**一张表必须有主键**，否则这张表就是无效的（数据库设计第一范式），主键值是当行数据的唯一标识，就是表中两行数据完全相同，但是由于主键不同，也可以认为是两行完全不同的数据。



**primary key主键**分为**单一主键**和**复合主键**

#### ==单一主键==:给一个字段添加主键约束；

```sql
drop table if exists t_user;
create table t_user(
	id int(4) primary key,			#单一主键:列级写法
    name varchar(32) not null
);

#或者使用以下的表级写法:
drop table if exists t_user;
create table t_user(
	id int(4),			#单一主键
    name varchar(32) not null,
    primary key(id)					#只用一个字段的时候就是单一主键: 表级写法
);
```



#### ==复合主键==:**将主键约束作用在多个字段上**

```sql
drop table if exists t_user;
create table t_user(
	id int(4),			
    name varchar(32) not null,
    primary key(id,name)				#多个字段的时候就是复合主键: 表级写法
);
#只有当id和name都一致的时候，才认为是重复的数据

drop table if exists t_user;
create table t_user(
	id int(4),			
    name varchar(32) not null,
    constraint t_user_id_name_pk primary key(id,name) 	#给复合主键起别名
);
```

无论是单一主键还是复合主键，==**一张表中有且只能有一个主键约束**==

#### 主键按照业务性质分类:自然主键和业务主键

**自然主键**：主键值是一个自然数，与业务没有任何关系(==推荐使用int类型且自增的自然主键==)

**业务主键**：主键值和表中业务紧密相关，如果业务发生变化，则主键也会受到影响，所以业务主键使用较少，大多数情况下使用自然主键，比如身份证号位数扩展



#### 主键自增:auto_increment

自增数字auto_increment，用来自动生成主键值，是MySQL独有的函数，默认从1开始，步进1递增

使用insert的时候就不需要填写主键primary key的值了(mysql 特有的)

**auto_increment只能用来修饰主键primary key**

```sql
drop table if exists t_user;
create table t_user(
	id int(4) primary key auto_increment,			#主键自增
    name varchar(32) not null
);

```

```sql
CREATE TABLE `t_user` (
  `uid` int NOT NULL AUTO_INCREMENT COMMENT '用户ID',
  `uname` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户名',
  `telphone` char(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '电话号码',
  `phone` char(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '固定电话',
  `email` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '邮箱',
  `sum_points` int NOT NULL DEFAULT '0' COMMENT '累计积分',
  `points` int NOT NULL DEFAULT '0' COMMENT '可用积分',
  `address` varchar(254) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '默认收货地址',
  `post_code` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '邮编',
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=600 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
#可以设置主键自增的起始值: AUTO_INCREMENT=600
#CHARSET=utf8mb4  表示采用的字符集
# COLLATE=utf8mb4_0900_ai_ci 表示mysql采用哪种排序规则, MySQL8.0默认的排序规则是utf8mb4_0900_ai_ci   MySQL5.7不支持
```



### 4. 外键约束: foreign key

**在关系为一对多的情况下，最好给多的一方添加外键**(在单机模式时使用, 在分布式系统中不建议使用外键)

foreign key简称FK

外键约束，外键字段，外键值

给某个字段添加外键约束之后，这个字段就是外键字段，字段中的数据就是外键值。



单一外键：给一个字段添加外键约束

复合外键：给多个字段联合添加外键

==**同一张表中可以有多个外键存在**==

需求分析:

```markdown
学生表t_student包含：sno,sname,classno,cname
学生和班级的关系，一个班级有多个学生，一个学生只能属于一个班级，属于一对多关系

第一种解决方案：
把学生和班级信息都存储到一张表中
问题：高三一班重复出现，数据冗余

第二种解决方案：
创建1张学生表，1张班级表

为了保证t_student表中的cno字段的数据必须来之t_class中的cno，
需要给t_student的cno字段添加外键约束，
cno成为外键字段，100、200、300就是外键值，cno此处为单一外键
```

班级表: t_class:

```sql
drop table if exists t_class;
create table t_class(
	cno int(4) primary key,			#业务主键
    cname varchar(32) not null
);
```

学生表: t_student:

```sql
drop table if exists t_student;
create table t_student(
	id int(4) primary key auto_increment,		#自然主键
    sno int(4) not null unique,
    sname varchar(32) not null,
    classno int(4),
    constraint t_student_classno_fk foreign key(classno) references t_class(cno)
    #外键约束: t_student_classno_fk 本表中的classno 必须引用于 t_class中的cno字段
);
```

注意：

1、  外键字段可以为NULL，空外键值为孤儿数据

2、  ==被引用的字段必须unique约束==（一般就是父表的主键）

3、  外键引用之后，就可以区分父表和子表，t_class为父表，t_student为子表

4、  ==先创建父表，再创建子表，先在父表插入数据，再在子表中插入数据==



#### 级联更新和级联删除

==级联更新和级联删除只能使用在外键约束后面==

注意：级联更新与极限删除操作==**谨慎使用**==，因为级联操作会导致数据改变或者删除

##### 级联更新：on update cascade 

**效果是更新主表(父表)的信息的时候，同时更新已经引用外键的相同的从表(子表)信息**

先删除外键约束：

```sql
ALTER TABLE 表名 DROP FOREIGN KEY 外键字段;
alter table t_student drop foreign key t_student_classno_fk;	#删除外键
```

添加外键约束：

```sql
alter table t_student add constraint t_student_classno_fk foreign key(classno) references t_class(cno) on update cascade;	
#添加外键
```

##### 级联删除：on delete cascade 

**效果是删除主表(父表)的信息的时候，同时删除已经引用外键的相同的从表(子表)信息**

先删除外键约束：

```sql
ALTER TABLE 表名 DROP FOREIGN KEY 外键字段;
alter table t_student drop foreign key t_student_classno_fk;
```

添加外键约束：

```sql
alter table t_student add constraint t_student_classno_fk foreign key(classno) references t_class(cno) on delete cascade;
```



# 六. 索引 index(重点)

相当于一本字典目录，**提高程序的检索/查询效率**，表中的每一个字段都可以添加索引

==**主键自动添加索引**==，能通过主键查询的尽量通过主键查询，效率较高

==**unique唯一性约束也会自动创建唯一性索引**==, 唯一性约束会依赖于唯一性索引

**索引是表的一部分**，因此也存放在硬盘文件中, 只不过可能会提前加载到内存中,加快检索速度



索引分单列索引和组合索引。

**单列索引**，即一个索引只包含单个列，**一个表可以有多个单列索引，但这不是组合索引。**

**组合索引**，即一个索引包含多个列。创建索引时，你需要确**保该索引是应用在 SQL 查询语句的条件**(一般作为 WHERE 子句的条件)。==最左前缀原则==



实际上，索引也是一张表，该表保存了主键与索引字段，并指向实体表的记录。上面都在说使用索引的好处，但过多的使用索引将会造成滥用。

因此索引也会有它的缺点：**==虽然索引大大提高了查询速度，同时却会降低更新表的速度==，如对表进行INSERT、UPDATE和DELETE。**

因为更新表时，MySQL不仅要保存数据，还要保存一下索引文件。建立索引会占用磁盘空间的索引文件。



**MySQL数据库有2中检索方式：**

1、 全表扫描（效率较低）

例子：查询ename=’KING’

```sql
select * from emp where ename=’KING’;
```

如果ename没有添加索引，那么通过ename过滤数据的时候，ename字段会全表扫描

2、 通过索引检索（提高查询效率）

**创建索引时,MySQL会去生成一个==B+tree==数据结构**, 用于检索的效率

**创建索引的情况：**

1.  该字段的数据量庞大,且数据的唯一性较强的字段

2.  该字段很少使用DML操作（**索引需要维护**，DML操作太多的时候，影响DML的效率）

3.  该字段经常出现在筛选条件where中



### 1. 索引的种类:

**普通索引**(index)：仅加速查询

**唯一索引**(unique index)：加速查询 + 列值唯一（可以有null）

**主键索引**( primary key)：加速查询 + 列值唯一（不可以有null）+ 表中只有一个组合索引：多列值组成一个索引，专门用于组合搜索，其效率大于索引合并

**全文索引**(fulltext)：对文本的内容进行分词，进行搜索,  其中，全文索引存储引擎必须是 MyISAM，line 字段必须为空间数据类型，而且是非空的。

**ps.**

**索引合并，使用多个单列索引组合搜索(各走各的索引)**

覆盖索引，select的数据列只用从索引中就能够取得，不必读取数据行，换句话说查询列要被所建的索引覆盖

### 2. 创建index索引:

```sql
create index 索引名 on 表名(字段名);				#创建普通索引
CREATE INDEX t_student_sname_index ON t_student(sname);

create unique index 索引名 on 表名(字段名);		#创建唯一性索引
create unique index t_student_sno_unique_index on t_student(sno);

show index from 表名;
show index from t_student;					#查看表的索引

drop index 索引名 on 表名; 
drop index t_student_sname_index on t_student; #删除索引

#在创建表的时候就添加索引
CREATE TABLE table_name (
    ID INT NOT NULL,
	col_name VARCHAR (16) NOT NULL,
	INDEX index_name (col_name)
);
```

上面的索引知识仅仅是基础, 索引优化还需要参考更多相关资料

[Mysql目前主要的几种索引类型](https://zhuanlan.zhihu.com/p/111362942)

[MySQL索引类型详解](http://c.biancheng.net/view/7897.html)



那些操作会让索引失效?

[导致索引失效的几种常见方法](https://zhuanlan.zhihu.com/p/220028437)



### 3. MYSQL中唯一约束和唯一索引的区别

1、唯一约束和唯一索引，都可以实现列数据的唯一，列值可以有null。
2、创建唯一约束，==会自动创建一个同名的唯一索引==，该索引不能单独删除，删除约束会自动删除索引。==唯一约束是通过唯一索引来实现数据的唯一==。
3、创建一个唯一索引，这个索引就是独立，可以单独删除。
4、如果一个列上想有约束和索引，且两者可以单独的删除。可以先建唯一索引，再建同名的唯一约束。
5、如果表的一个字段，要作为另外一个表的外键，这个字段必须有唯一约束（或是主键），如果只是有唯一索引，就会报错。

------

　　==约束是业务检查==,比方说非空约束,check约束,那是检查字段非空,是否符合check。而==索引是一种数据结构==, rowid与字段值的键值对. 两个东西的效果是一样。但:在建立唯一约束时,会自动创建一个唯一索引.并且,失效该约束时,索引自动删除.而创建唯一索引则不会自动创建唯一约束.因此在建表时,如果要创建唯一索引,最好先建唯一索引再创建唯一约束.这样的话,在进行大批量数据插入时,可以先失效约束,插入完成后再进行索引重建.
　　除了引文中提到的，要被外键引用必须有唯一约束，还有这个区别：索引的键不一定要和唯一约束完全匹配，唯一约束可以只用索引的前导列。



# 七. 视图view

### 1. 视图原理

视图在数据库管理系统中也是一个对象，以文件形式存在.  视图底也是表

视图也对应了一个查询结果，只是从不同的角度查看数据

视图的相关的语法:

```sql
create view 视图名称 as 查询语句;
create view myview as select * from emp; 	#创建视图
show tables;			#查看表的时候可以查看到创建的视图myview

show create view myview;		#查看视图的创建语句
```

![image-20210929234457936](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20210929234457936.png)

**==创建视图的语句是一个查询语句, 并不是建表语句.==**  **视图和原表的数据是同步的**

原表中的数据改变, 视图的数据也会改变. 数据是同步的

视图中的数据改变, 原表的数据也会跟着改变. 数据是同步的

```sql
drop view myview;		#删除视图
```

### 2. 视图的作用

* **隐藏表的实现细节**

```sql
create view myview as select empno as a, enameas b from emp;
select * from myview;
#DBA管理员可以给相应的权限使普通用户不能执行以下语句
show show create view myview;		#查看视图的创建语句, 将不会看到相应的表的具体信息
```

* **提高检索效率**(多用与联表查询)

```sql
#比如经常使用一个联表查询, 可以将该查询作为一个视图提升检索效率
select 
	e.ename,
	d.dname 
from 
	emp as e 
join 
	dept as d 
on 
	e.deptno = d.deptno;
	
#将以上的联表查询作为一个视图,提升检索效率
create view myview2 as 
(select 
	e.ename,
	d.dname 
from 
	emp as e 
join 
	dept as d 
on 
	e.deptno = d.deptno);
```

# 八. MySQL存储引擎

**存储引擎是MySQL特有**，其他数据库没有

查看MySQL所有的存储引擎:

```sql
show engines\G;
```

**MySQL默认的存储引擎为: InnoDB**

1、创建表时，可以使用ENGINES=InnoDB指定引擎类型

```sql
create table table_name(
	no int(2)
)engine =InnoDB;
```

2、如果创建表时没有指定存储引擎，会使用默认的存储引擎

3、默认的存储引擎可以在安装目录的my.ini中配置`default-storage-engin`指定

4、修改表的存储引擎：

```sql
alter table table_name engine = new_engine_name;
```

5、查看表使用的存储引擎

```sql
show create table emp\G;		#查看建表语句
```



### 1. 常用的存储引擎_MyISAM

1、**是MySQL数据库最常用的**,**但不是默认的**

2、管理的表具备以下特性(使用三个文件来表示每一个表):

​	a) ==格式文件.frm==   **存储表的结构**    mytable.frm

​	b) ==数据文件.MYD== **存储表的数据**   mytable.MYD

​	c) ==索引文件.MYI== **存储表的索引**     mytable.MYI

![](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211001214450243.png)

3、**可压缩为只读表**，**只读表用来节省空间**

frm和MYI可以存放在不同的目录下。MYI文件用来存储索引，但仅保存记录所在页的指针，索引的结构是B+树结构。下面这张图就是MYI文件保存的机制：

![image-20211001211009697](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211001211009697.png)



### 2. 常用的存储引擎_InnoDB

1、**是MySQL默认的存储引擎**

* InnoDB使用两个文件来管理一张表:

  ​	a) ==格式文件.frm==:  **用来存储表的结构**						test_innodb.frm

  ​	b) ==索引+数据 .ibd== : **存储索引和数据(聚集索引)**		test_innodb.ibd

![image-20211001214342274](F:\Images\image-20211001214342274.png)

2、管理的表具备以下特性

​	（1）**可以通过自动增长列**，方法是auto_increment。

​	（2）==支持事务==。默认的事务隔离级别为==可重复读==，通过MVCC（并发版本控制）来实现的。

​	（3）**使用的锁粒度为==行级锁==**，可以支持更高的并发；

​	（4）==支持外键约束==；外键约束其实降低了表的查询速度，但是增加了表之间的耦合度。

​	（5）配合一些热备工具可以支持在线热备份；

​	（6）**在InnoDB中存在着缓冲管理**，通过缓冲池，将索引和数据全部缓存起来，加快查询的速度；

​	（7）对于InnoDB类型的表，其数据的物理组织形式是聚簇表。所有的数据按照主键来组织。==数据和索引放在一块，都位于B+tree的叶子节点上==；

![image-20211001213607305](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211001213607305.png)

### 3. 常用的存储引擎_MEMORY

1、 ==数据存储在内存中==，且行的长度固定，因此非常快

2、 管理的表具备以下特性：

​	a)在数据库目录中，每个表以.frm格式文件表示

​	b) 表数据及索引被存储在内存中

​	c) 表级锁机制

​	d) 字段属性不能包含TEXT或者BLOB字段

​	e) 默认使用**hash索引**

3、 旧名HEAP引擎



### 4. 如何选择合适的存储引擎

1、使用场景是否需要事务支持；
2、是否需要支持高并发，InnoDB的并发度远高于MyISAM；
3、是否需要支持外键；
4、是否需要支持在线热备；
5、高效缓冲数据，InnoDB对数据和索引都做了缓冲，而MyISAM只缓冲了索引；
6、索引，不同存储引擎的索引并不太一样；MyISAM为非聚簇索引, InnoDB为聚簇索引



* MyISAM表适合于**大量数据读而少量数据更新**的混合操作。MyISAM表的另一种适用情形是**使用压缩的只读表**

* 如果查询中包含较多的数据更新操作，应该使用InnoDB，其**行级锁机制**和多版本的支持为数据读取和更新的混合提供了良好的并发机制（由事务控制）**支持事务**

* 使用MEMORY存储引擎存储**非永久需要的数据**，或者是能够从基于磁盘的表中重新生成测数据。





# 九. 事务 Transaction

### 1. 什么是事务?

1.    **一个最小的不可再分的工作单元**

2.    **通常一个事务对应一个完整的业务（如：银行转账业务）**

3.    **一个完整的业务需要批量的DML(insert, update, delete)语句共同完成**

4.    **事务只和DML语句有关系,或者说只有DML才有事务机制**

5.    **以上所描述的额批量DML语句，数量和业务逻辑相关**



* **示例: 转账**

(转出账号的余额减少, 转入账户的余额增加)  至少有两条update语句DML语句

分析:

1. **上面两条DML语句必须==要么都执行成功，要么就不执行==**

2. **第一条DML执行成功之后，不能修改数据库，而只是记录操作，这个记录是在内存中完成的**

3. **第二条DML也成功之后提交事务，底层数据库文件的数据此时完成同步**

4. **如果第二条执行失败，会清空所有的历史操作记录，数据库不变**

   

### 2. 事务的四个特征ACID:

* **原子性（atomicity）**，事务是最小单位，==不可再分==

* **一致性（consistency）**，所有DML语句操作，==必须保证全部成功或者全部失败==

- **隔离性（isolation）**，一个事务==不会影响其他事务==

- **持久性（durability）**，事务完成之后，对数据库做的修改==会持久的保存在数据库中==，不会被回滚



### 3. 事务控制语言(TCL)

开启事务：**start**  transaction

结束事务：**end**  transaction

提交事务：**commit**  transaction

回滚事务：**rollback**  transaction



**MySQL默认是自动提交的**

```sql
show variables like '%commit%';
```

![image-20211001220652660](https://gitee.com/abin_z/pic_bed/raw/master/img/image-20211001220652660.png)

**手动开始事务**

```sql
start transaction;

多条DML语句

commit;
```

**设置不要自动提交：**

```sql
set autocommit = OFF;
```





### 4. 事务的隔离级别概述



#### 1. read uncommitted 读未提交(级别最低)

**事务A和事务B，==事务A未提交的数据，事务B可以读取(脏读)==**

这里读取到的数据可以叫做脏数据，或者，脏读 Dirty Read

这种级别一般只是理论上存在，数据库默认的隔离级别都高于这个

 

#### 2. read committed 读已提交

**==事务A每一次提交，事务B读取到的数据库都会变化(不可重复读)==**  

会导致：B一直都在读取变化的数据库(不满足ACID的隔离性)

Oracle数据库管理系统的默认隔离级别为可重复读

 

#### 3. repeatable read 可重复读（==MySQL的默认级别==）

**==事务A每次提交都不影响事务B读取的数据库内容，也就是事务B读取到的数据库一直都不变化(幻象读)==**

会导致：B感知不到数据库变化

 

#### 4. serializable 串行化

**==事务排队，一个事务完成后才能继续下一个事务==**

同一个时刻只能有一个事务执行(单线程)

这种级别很少使用，吞吐量小，用户体验不好



**查看当前会话级隔离级别**

```sql
select @@tx_isolation;
select @@session.tx_isolation;
```

**查看全局隔离级别**

```sql
select @@global.tx_isolation;
```



#### 5. 设置服务器缺省隔离级别

第一种方法：修改my.ini配置文件

第二种方法，通过命令方式设置事务隔离级别

```sql
set transaction isolation level isolation-level;		#isolation-level可选4种隔离级别
set global transaction isolation level READ COMMITED;	#全局范围
set session transaction isolation level READ COMMITED;	#会话范围
```





# 十. 存储过程 procedure

在mysql中，==存储过程是一组为了完成特定功能的SQL语句集合==。一个存储过程是一个可编程的函数，它在数据库中创建并保存，一般由SQL语句和一些特殊的控制结构组成。使用存储过程不仅可以提高数据库的访问效率，同时也可以提高数据库使用的安全性。

存储过程链接:	https://www.runoob.com/w3cnote/mysql-stored-procedure.html

### 优点

- 存储过程可封装，并隐藏复杂的商业逻辑。
- 存储过程可以回传值，并可以接受参数。
- 存储过程无法使用 SELECT 指令来运行，因为它是子程序，与查看表，数据表或用户定义函数不同。
- 存储过程可以用在数据检验，强制实行商业逻辑等。

### 缺点

- 存储过程，往往定制化于特定的数据库上，因为支持的编程语言不同。当切换到其他厂商的数据库系统时，需要重写原有的存储过程。
- 存储过程的性能调校与撰写，受限于各种数据库系统。



### 1、存储过程的创建和调用

- **MYSQL 存储过程中的关键语法**

声明语句结束符，可以自定义:

```sql
DELIMITER $$
或
DELIMITER //
```

声明存储过程:

```sql
CREATE PROCEDURE demo_in_parameter(IN p_in int)       
```

存储过程开始和结束符号:

```sql
BEGIN .... END    
```

变量赋值:

```sql
SET @p_in=1  
```

变量定义:

```sql
DECLARE l_int int unsigned default 4000000; 
```

创建mysql存储过程、存储函数:

```sql
create procedure 存储过程名(参数)
```

存储过程体:

```sql
create function 存储函数名(参数)
```

调用存储过程：

```sql
call sp_name[(传参)];
```



### 2、存储过程的参数

MySQL存储过程的参数用在存储过程的定义，共有三种参数类型,IN,OUT,INOUT,形式如：

```sql
CREATE PROCEDURE 存储过程名([[IN |OUT |INOUT ] 参数名 数据类形...])
```

- IN 输入参数：表示调用者向过程传入值（传入值可以是字面量或变量）			
- OUT 输出参数：表示过程向调用者传出值(可以返回多个值)（传出值只能是变量）   
- INOUT 输入输出参数：既表示调用者向过程传入值，又表示过程向调用者传出值（值只能是变量）            

**注意：**

1、如果过程没有参数，也必须在过程名后面写上小括号例：

```sql
CREATE PROCEDURE sp_name ([proc_parameter[,...]]) ……
```

2、确保参数的名字不等于列的名字，否则在过程体中，参数名被当做列名来处理

**建议：**

- 输入值使用in参数。
- 返回值使用out参数。
- inout参数就尽量的少用。



```sql
delimiter //
create procedure get_chargeInfo(in YF varchar(16))
begin
select 
	month as 月份,
	sum(shouldCharge) as 应收费用合计,
	sum(realCharge) as 实收费用合计 
from 
	charge_t 
where 
	month=YF;
end //
delimiter ;

delimiter //
create procedure get_userChargeInfo(in YF varchar(16))
begin
select 
	c.month as 月份,
	u.userName as 用户名,
	c.shouldCharge as 应收费用,
	c.tollSign as 收费标志,
	u.phoneNum as 电话号码,
	u.address as 家庭住址
from 
	charge_t c
join 
	users_t u
on 
	c.userNo=u.userNo
where
	c.month = YF 
and
	c.tollSign = '未收费';
end //
delimiter ;
```



# 十一. 触发器 trigger

### **1、什么是触发器**

**监视某种情况，并触发执行某种操作。**触发器是==在表中数据发生更改时自动触发执行的==，它是与表事件相关的特殊的存储过程，它的执行不是由程序调用，也不是手工启动，而是由事件来触发，例如当对一个表进行操作（insert，delete， update）时就会激活它执行。也就是说触发器**只执行DML事件**(insert、update和delete)	

触发器只能创建在永久表上, 不能对临时表创建触发器

### 2、**触发器的作用**

**1.**安全性。可以基于数据库的值使用户具有操作数据库的某种权利。

**2.**审计。可以**跟踪用户对数据库的操作**。

**3.**实现复杂的数据完整性规则

**4.**实现复杂的非标准的数据库相关完整性规则。**触发器可以对数据库中相关的表进行连环更新**。



   触发器经常用于加强数据的完整性约束和业务规则等。 触发器创建语法四要素：
    **1.监视地点(table)**
    **2.监视事件(insert/update/delete)** 
    **3.触发时间(after/before)** 
    **4.触发事件(insert/update/delete)**



### 3. 基本语法:

```sql
CREATE TRIGGER <触发器名称>
{ BEFORE | AFTER }
{ INSERT | UPDATE | DELETE } 
ON <表名称>
FOR EACH ROW
BEGIN
 <触发的SQL语句>
END;
```

语法说明如下。

##### 1) 触发器名

触发器的名称，触发器在当前数据库中必须具有唯一的名称。如果要在某个特定数据库中创建，名称前面应该加上数据库的名称。

##### 2) INSERT | UPDATE | DELETE

触发事件，用于指定激活触发器的语句的种类。

注意：三种触发器的执行时间如下。

- INSERT：将新行插入表时激活触发器。例如，INSERT 的 BEFORE 触发器不仅能被 MySQL 的 INSERT 语句激活，也能被 LOAD DATA 语句激活。
- DELETE： 从表中删除某一行数据时激活触发器，例如 DELETE 和 REPLACE 语句。
- UPDATE：更改表中某一行数据时激活触发器，例如 UPDATE 语句。

##### 3) BEFORE | AFTER

BEFORE 和 AFTER，触发器被触发的时刻，表示触发器是在激活它的语句之前或之后触发。若希望验证新数据是否满足条件，则使用 BEFORE 选项；若希望在激活触发器的语句执行之后完成几个或更多的改变，则通常使用 AFTER 选项。

##### 4) 表名

与触发器相关联的表名，此表必须是永久性表，不能将触发器与临时表或视图关联起来。在该表上触发事件发生时才会激活触发器。同一个表不能拥有两个具有相同触发时刻和事件的触发器。例如，对于一张数据表，不能同时有两个 BEFORE UPDATE 触发器，但可以有一个 BEFORE UPDATE 触发器和一个 BEFORE INSERT 触发器，或一个 BEFORE UPDATE 触发器和一个 AFTER UPDATE 触发器。

##### 5) 触发器主体

触发器动作主体，包含触发器激活时将要执行的 MySQL 语句。如果要执行多个语句，可使用 BEGIN…END 复合语句结构。

##### 6) FOR EACH ROW

一般是指行级触发，对于受触发事件影响的每一行都要激活触发器的动作。例如，使用 INSERT 语句向某个表中插入多行数据时，触发器会对每一行数据的插入都执行相应的触发器动作。

> 注意：每个表都支持 INSERT、UPDATE 和 DELETE 的 BEFORE 与 AFTER，因此每个表最多支持 6 个触发器。每个表的每个事件每次只允许有一个触发器。单一触发器不能与多个事件或多个表关联。

### 4. **NEW与OLD关键字详解**

MySQL 中定义了 NEW 和 OLD，用来表示触发器的所在表中，触发了触发器的那一行数据，来引用触发器中发生变化的记录内容，具体地：

① 在INSERT型触发器中，NEW用来表示将要（BEFORE）或已经（AFTER）插入的新数据；

② 在UPDATE型触发器中，OLD用来表示将要或已经被修改的原数据，NEW用来表示将要或已经修改为的新数据；

③ 在DELETE型触发器中，OLD用来表示将要或已经被删除的原数据；



### 5. 示例:

```sql
#要求：创建一个触发器trigg_course_teacher_score,当在 course表上删除一门课程后，将score和teach_course表中该门课程相关的信息同步删除。
delimiter //
create trigger trigg_course_teacher_score after delete
on course for each row
begin
delete from teach_course where course = old.courseno;
delete from score where course = old.courseno;
end //
```

```sql
#创建触发器,当更新charge_t前 将相应的字段更改为'已收费'
delimiter //
create trigger trigg_charge_t_change01 before update
on charge_t for each row
begin
declare tollSign_01 varchar(32);
set tollSign_01 = '已收费' ;
set new.tollSign = tollSign_01;
end //
```

```sql
#数据库自动更新余额
delimiter //
create trigger trigg_charge_t_change02 before update
on charge_t for each row
begin
declare balance_01 decimal(10,1);
set balance_01 = old.shouldCharge - new.realCharge;
set new.balance = balance_01;
end //
```



# 十二. 游标  cursor	(了解即可)

### 1. 概念

游标(Cursor)它使用户可逐行访问由SQL Server返回的结果集。 
使用游标(cursor)的一个主要的原因就是==把集合操作转换成单个记录处理方式==。

用SQL语言从数据库中检索数据后，结果放在内存的一块区域中，且结果往往是一个含有多个记录的集合。

游标机制允许用户在SQL server内逐行地访问这些记录，按照用户自己的意愿来显示和处理这些记录。

### 2. 优点

1、允许程序对由查询语句select返回的行集合中的每一行执行相同或不同的操作，而不是对整个行集合执行同一个操作。

2、提供对基于游标位置的表中的行进行删除和更新的能力。

3、游标实际上作为面向集合的数据库管理系统（RDBMS）和面向行的程序设计之间的桥梁，使这两种处理方式通过游标沟通起来。

### 3. 原理

**游标就是把数据按照指定要求提取出相应的数据集，然后逐条进行数据处理。**

**使用游标的顺序**

 声名游标、打开游标、读取数据、关闭游标、删除游标。

### 4. 使用游标(cursor)

1.声明游标
DECLARE cursor_name CURSOR FOR select_statement
这个语句声明一个游标。也可以在子程序中定义多个游标，但是一个块中的每一个游标必须有唯一的名字。声明游标后也是单条操作的，但是不能用SELECT语句不能有INTO子句。

2. 游标OPEN语句
OPEN cursor_name       这个语句打开先前声明的游标。

3. 游标FETCH语句
FETCH cursor_name INTO var_name [, var_name] ...这个语句用指定的打开游标读取下一行（如果有下一行的话），并且前进游标指针。

4. 游标CLOSE语句
CLOSE cursor_name  这个语句关闭先前打开的游标。

### 5. 特性

1,只读的，不能更新的。
2,不滚动的
3,不敏感的，不敏感意为服务器可以活不可以复制它的结果表

 

游标(cursor)必须在声明处理程序之前被声明，并且变量和条件必须在声明游标或处理程序之前被声明。

```sql
delimiter $$
create procedure pa(out sum bigint)
  begin

declare iii int;

declare done int default 0;
# 1、游标的定义
declare c_person cursor for select id from randtable;
# 捕获系统抛出的 not found 错误，如果捕获到，将 done 设置为 1  相当于try异常
declare continue handler for not found set done=1;
set sum=0;
# 2、打开游标
open c_person;

www:loop
  # 3、使用游标
  fetch c_person into iii;
  # 如果发生异常
    if done = 1 then

      leave www;
    end if ;

  set sum = sum +iii ;
end loop ;
# 4、关闭游标
close c_person;
end $$
delimiter  ;
```





# 十三. MySQL拓展

### MySQL的COLLATE是什么?

https://www.cnblogs.com/qcloud1001/p/10033364.html

所谓`utf8_unicode_ci`，其实是==**用来排序的规则**==。对于mysql中那些字符类型的列，如`VARCHAR`，`CHAR`，`TEXT`类型的列，都需要有一个`COLLATE`类型来告知mysql如何对该列进行排序和比较。简而言之，**COLLATE会影响到ORDER BY语句的顺序，会影响到WHERE条件中大于小于号筛选出来的结果，会影响**`DISTINCT`**、**`GROUP BY`**、**`HAVING`**语句的查询结果**。另外，mysql建索引的时候，如果索引列是字符类型，也**会影响索引创建**，只不过这种影响我们感知不到。总之，**凡是涉及到字符类型比较或排序的地方，都会和COLLATE有关**。



MySQL常用的排序规则COLLATE :  **utf8mb4_general_ci		/ 	utf8mb4_unicode_ci**

MySQL8.0默认的COLLATE = **utf8mb4_0900_ai_ci**			MySQL5.7不支持**utf8mb4_0900_ai_ci**			



### MySQL中的字符集最好使用  utf8mb4

mysql中有`utf8`和`utf8mb4`两种编码，==**在mysql中请大家忘记**`utf8`**，永远使用**`utf8mb4`==。这是mysql的一个遗留问题，mysql中的`utf8`最多只能支持3bytes长度的字符编码，对于一些需要占据4bytes的文字，mysql的`utf8`就不支持了，要使用`utf8mb4`才行。



### MySQL配置文件  my.ini

```sql
[mysqld]
# 设置3306端口
port=3306
# 设置mysql的安装目录
basedir=D:/MySQL/mysql-8.0.26-winx64/						#最好使用 / 代替 \ 
# 设置mysql数据库的数据的存放目录
datadir=D:/MySQL/mysql-8.0.26-winx64/data/
# 允许最大连接数
max_connections=200
# 允许连接失败的次数。这是为了防止有人从该主机试图攻击数据库系统
max_connect_errors=10
# 服务端使用的字符集默认为utf8mb4
character-set-server=utf8mb4
# 创建新表时将使用的默认存储引擎
default-storage-engine=INNODB
# 默认使用“mysql_native_password”插件认证
default_authentication_plugin=mysql_native_password

[mysql]
# 设置mysql客户端默认字符集
default-character-set=utf8mb4
[client]
# 设置mysql客户端连接服务端时默认使用的端口
port=3306
default-character-set=utf8mb4
```



### 逻辑删除

**在企业级开发中数据库数据的删除都不是物理删除,均为逻辑删除**

**物理删除:** `dorp table t_name;	`或者`delete from t_name;`

​			需求: 将表的数据大量删除?------不推荐使用delete进行清空(因为涉及事务提交, 存在缓存)

​														  -------推荐使用:  ==truncate  table  t_name;==  不涉及事务

**逻辑删除:**	

​			用一个字段来表示 这条信息是否已经不能再使用了；

（1）给students表添加一个 is_delete 字段 bit 类型 默认为0

```sql
alter table students add is_delete bit default 0;
```

（2）is_delete = 1 逻辑删除: 将删除操作改为更新操作,数据依然在数据库中

```sql
update students set is_delete=1 where id=6;
```



### MySQL局域网连接解决方案

* 首先确保MySQL相应的端口对外开发, 不开放在防火墙里修改:	https://blog.csdn.net/weixin_39895486/article/details/113949186
* 让MySQL服务运行远程连接:     https://www.cnblogs.com/zhuoweihuang/p/9291560.html
* 给相应的用户授权:     https://www.cnblogs.com/liangmingshen/p/11340526.html





