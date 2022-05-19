# springboot项目

## 一. 基于maven的springboot项目快速开始!

### 第一步: 创建一个maven项目

![image-20211119100009747](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191000827.png)

### 第二部: 添加springboot的相关依赖

```xml
  <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>1.5.9.RELEASE</version>
    </parent>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
```

### 第三步: 创建一个主程序

```Java
package com.abin;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * @SpringBootApplication 来标注一个主程序类, 说明这是一个springboot应用
 */
@SpringBootApplication
public class Demo {
    public static void main(String[] args) {
        SpringApplication.run(Demo.class,args);//这里传入的.class类对象一定是有@SpringBootApplication注解的, args是main方法的参数
    }
}
```

### 第四步: 编写相应的controller, service

```Java
package com.abin.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * @Project_Name: SpringBoot-mvn-study
 * @Package_Name: com.abin.controller
 * @Class_Name: HelloController
 * @Description: TODO
 * @Author: Abin
 * @Date: 2021/11/19 9:51
 * @Day_Name_Full: 星期五
 * @Version 1.0
 **/
@Controller             //@Controller表示能够处理请求
public class HelloController {
    @ResponseBody                          //将返回的结果响应给浏览器
    @RequestMapping("/hello")           //处理浏览器发出的 /hello 请求
    public String hello(){
        return "hello world!";
    }
}
```

### 第五步: 测试

* 直接启动main方法

![image-20211119101428706](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191014777.png)

* 在浏览器中进行验证

  ![image-20211119101552562](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191015607.png)

* 注意: 其中的目录层级

  ![image-20211119101740826](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191017870.png)



### 第六步: 简化部署

* 首先添加maven打包依赖: 一定需要这个依赖, 不然打包后的jar包不能直接运行

```xml
    <!--该插件可以将一个应用打包成可运行的jar包-->
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
```

* 然后在maven的lifecycle中双击package进行打包, 打完包后会在target文件夹中存在提个jar包
* 可以直接运行该jar包, 就启动了相应的服务
* jar包中自带tomcat等相关依赖

通过一下的命令直接运行jar包:

```bash
java -jar SpringBoot-mvn-study-1.0-SNAPSHOT.jar
```

![image-20211119104247723](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191042765.png)

* 然后在浏览器就可以直接访问`http://localhost:8080/hello`



## 二. 使用idea的提供的模板进行快速开发

![image-20211119133716481](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111191337673.png)

### 然后勾选要用到的相应的模块

* 自带properties配置文件(后面可以是用yml配置文件代替)
* 在pom.xml文件中有着相应的依赖文件(包括必要的以及自己勾选的模块)







