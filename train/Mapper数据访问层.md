# Mapper数据访问层(springboot + mybatis)

2021-09.16  pm

首先是基本环境的搭建(idea中)

## 1. 在maven的pom.xml 加载MySQL驱动

![image-20210916144227354](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916144227354.png)

## 2. 单独使用MyBatis: 添加相应的GAV坐标

![image-20210916144617443](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916144617443.png)

提示: 如果使用的是MyBatis-plus依赖, 就不用添加MyBatis和MyBatis-spring, 防止冲突

本次实训就直接使用的是MyBatis-Plus依赖:

![image-20210920233400669](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920233400669.png)



## 3. 添加核心配置文件application.yml或者application.properties

**添加数据库连接:**

* 可以直接连接MySQL数据库(可以参考其他相关的权威资料)
  1. 使用SpringBoot默认的数据源

![image-20210920233614153](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920233614153.png)

		2. 推荐使用阿里的Druid数据源(可以参考其他相关的权威资料)

![image-20210920233925819](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920233925819.png)

* 可以通过数据库中间件MyCat连接数据库(可以参考其他相关的权威资料)

![image-20210920234238397](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920234238397.png)

**数据源:**

1. 可以使用SpringBoot默认的数据源

2. 也可以使用阿里巴巴开源的Druid(德鲁伊)数据源



## 4. 构建SQL语句有两种方式(①.使用注解②.使用ORM的.xml映射文件)



### **方式1: 使用ORM映射文件:**

**使用.xml映射文件背景:** 

1. 业务SQL与Java代码分离
2. 分工明确、提高团队人力资源的使用率
3. 软件的可读性、可维护性好

    		1. 一般情况下接口名和.xml文件名应该一致

#### 需要在核心配置文件application.yml或者application.properties中添加映射文件位置

![image-20210916151140822](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916151140822.png)

开发、测试过程中添加SQL语句的调试属性(该属性在正式上线前要关闭)

![image-20210920234933045](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920234933045.png)



#### 初步熟悉ORM映射文件:	EmpMapper.xml

了解：DOCTYPE

**文档类型定义（DTD）可定义合法的XML文档构建模块。它使用一系列合法的元素来定义文档的结构。**

**DTD 可被成行地声明于 XML 文档中，也可作为一个外部引用。**

```
<!DOCTYPE 根元素 [元素声明]>
```

![image-20210920235947594](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920235947594.png)



了解命名空间：

![image-20210921000350347](F:\Images\image-20210921000350347.png)



**CRUD操作**

**id:** 与Mapper接口内的方法名保持一致

![image-20210921000631424](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921000631424.png)



**parameterType:**参数类型	(可以写全路径,也可以定义别名,定义别名后则可以直接写: **小写的类名**)

![image-20210921001132860](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921001132860.png)

![image-20210921001157664](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921001157664.png)

insert----update----delete  默认返回的是受影响的行数

#### 动态 SQL

动态 SQL 是 MyBatis 的强大特性之一。如果你使用过 JDBC 或其它类似的框架，你应该能理解根据不同条件拼接 SQL 语句有多痛苦，例如拼接时要确保不能忘记添加必要的空格，还要注意去掉列表最后一个列名的逗号。利用动态 SQL，可以彻底摆脱这种痛苦。

使用动态 SQL 并非一件易事，但借助可用于任何 SQL 映射语句中的强大的动态 SQL 语言，MyBatis 显著地提升了这一特性的易用性。

如果你之前用过 JSTL 或任何基于类 XML 语言的文本处理器，你对动态 SQL 元素可能会感觉似曾相识。在 MyBatis 之前的版本中，需要花时间了解大量的元素。借助功能强大的基于 OGNL 的表达式，MyBatis 3 替换了之前的大部分元素，大大精简了元素种类，现在要学习的元素种类比原来的一半还要少。

- if
- choose (when, otherwise)
- trim (where, set)
- foreach

https://mybatis.org/mybatis-3/zh/dynamic-sql.html



![image-20210921002531595](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921002531595.png)

循环迭代删除, 理解每个参数的含义

![image-20210921002703878](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921002703878.png)

使用转义字符: ` <![CDATA[    SQL语句    ]]>`

![image-20210921002946601](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921002946601.png)

参考权威资料: https://mybatis.org/mybatis-3/zh/dynamic-sql.html





### 方式2: 使用注解开发

如果不使用ORM映射文件开发, 而使用注解开发, 则可以不加载或者不配置.xml文件

在实际开发中复杂的,动态的查询在ORM映射文件中配置, 简单的查询就使用注解



了解当前框架的注解种类:

![image-20210921003255359](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210921003255359.png)



