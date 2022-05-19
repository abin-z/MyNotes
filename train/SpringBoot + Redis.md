# SpringBoot + Redis



### 1. 在docker容器中运行redis

```bash
docker run --name redistest --restart always -p 8899:6379 -d redis	
```



### 2. 在maven的pom.xml文件中添加redis依赖

```xml
 <!-- Redis依赖 -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-redis</artifactId>
        </dependency>
```

![image-20210922103559629](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210922103559629.png)



### 3. 配置application.properties或者application.yml文件

```xml
#=====================================================================
# 连接Redis数据库
#=====================================================================
spring.redis.password=				#没有密码可以不写
spring.redis.database=0
spring.redis.port=6379
spring.redis.host=192.168.1.131
#=====================================================================
```

![image-20210922104231102](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210922104231102.png)





### 4. 在测试类中演示

Jedis 项目中使用频率小

RedisTemplate: 查看相关源码: 接口, 类, 命名规范, 常量, 序列化等

