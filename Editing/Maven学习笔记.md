# Maven教程

## 一. Maven简介

Maven 翻译为"专家"、"内行"，是 Apache 下的一个纯 Java 开发的开源项目。基于项目对象模型（缩写：POM）概念，Maven利用一个中央信息片断能管理一个项目的构建、报告和文档等步骤。

Maven 是一个项目管理工具，可以对 Java 项目进行构建、依赖管理。

Maven 也可被用于构建和管理各种项目，例如 C#，Ruby，Scala 和其他语言编写的项目。Maven 曾是 Jakarta 项目的子项目，现为由 Apache 软件基金会主持的独立 Apache 项目。

### 1. Maven是什么

- Maven 的本质是一个项目管理工具，将项目开发和管理过程抽象成一个项目对象模型（POM）
- POM(Project Object Model)：项目对象模型

![image-20220613144535052](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613144535052.png)



### 2. Maven的作用

- 项目构建: 提供标准的, 跨平台的自动化的项目构建方式
- 依赖管理: 方便快捷的管理项目依赖的资源(jar包), 避免资源间的版本冲突问题
- 统一开发结构: 提供标准的, 统一的项目结构

Maven 提倡使用一个共同的标准目录结构，Maven 使用约定优于配置的原则，大家尽可能的遵守这样的目录结构。如下所示：

| 目录                               | 目的                                                         |
| :--------------------------------- | :----------------------------------------------------------- |
| ${basedir}                         | 存放pom.xml和所有的子目录                                    |
| ${basedir}/src/main/java           | 项目的java源代码                                             |
| ${basedir}/src/main/resources      | 项目的资源，比如说property文件，springmvc.xml                |
| ${basedir}/src/test/java           | 项目的测试类，比如说Junit代码                                |
| ${basedir}/src/test/resources      | 测试用的资源                                                 |
| ${basedir}/src/main/webapp/WEB-INF | web应用文件目录，web项目的信息，比如存放web.xml、本地图片、jsp视图页面 |
| ${basedir}/target                  | 打包输出目录                                                 |
| ${basedir}/target/classes          | 编译输出目录                                                 |
| ${basedir}/target/test-classes     | 测试编译输出目录                                             |
| Test.java                          | Maven只会自动运行符合该命名规则的测试类                      |
| ~/.m2/repository                   | Maven默认的本地仓库目录位置                                  |

![201808131239225](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/201808131239225.jpg)

### 3. Maven的下载与配置

下载与配置: https://zhuanlan.zhihu.com/p/350857381   (自行百度)

Maven是Java写的绿色软件不需要安装, 但是需要配置对应的系统环境变量, 下图是Maven的安装目录结构

![image-20220613160503645](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613160503645.png)



## 二. Maven基础概念

### 1. 仓库

- **仓库**: 仓库用于存储资源,包含各种jar包
- **仓库分类**:
  - ==本地仓库==: 自己电脑上存储资源的仓库, 连接远程仓库获取资源
  - ==远程仓库==: 非本地电脑上的仓库, 为本地仓库提供资源
    - 中央仓库: Maven团队维护, 存储所有开源资源的仓库
    - 私服: 部门/公司范围内存储资源的仓库, 从中央仓库获取资源
- **私服的作用**: 
  - 保存具有一定版权的资源, 包含购买或者自主研发的jar包
  - 一定范围内共享资源, 仅对内部开放, 不对外共享

![image-20220613152534465](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613152534465.png)



### 2. 坐标

- 坐标是什么:  
  - Maven中的坐标用于**描述仓库中的资源的位置**
- Maven坐标的主要组成部分:
  - **groupId**: 定义当前Maven项目隶属于组织名称(通常是域名反写, 例如: org.mybatis)
  - **artifactId**: 定义当前Maven的项目名称(通常是模块名称, 例如CRM, SMS)
  - **version**: 定义当前项目的版本号
- Maven坐标的作用:
  - 使用唯一标识, 唯一性定位资源位置, 通过该标识可以将资源的识别与下载工作交由机器完成



查询官方开源坐标:  https://mvnrepository.com/

![image-20220613154841209](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613154841209.png)



## 三. Maven仓库的配置

构建配置文件是一系列的配置项的值，可以用来设置或者覆盖 Maven 构建默认值。

构建配置文件大体上有三种类型:

| 类型                  | 在哪定义                                                     |
| :-------------------- | :----------------------------------------------------------- |
| 项目级（Per Project） | 定义在项目的POM文件pom.xml中                                 |
| 用户级 （Per User）   | 定义在Maven的设置xml文件中 (%USER_HOME%/.m2/settings.xml)    |
| 全局（Global）        | 定义在 Maven 全局的设置 xml 文件中 (%M2_HOME%/conf/settings.xml) |

在将 Maven 安装好之后，为了方便我们后面的使用，可以对 Maven 进行简单的配置。

### 1. 修改本地仓库位置

在 Maven 的使用过程中，会自动将项目依赖的 jar 包从中央仓库下载到本地仓库，默认本地仓库路径是`${user.home}/.m2/repository`，这样的话，会占用较多的 C 盘空间，因此，我们可以自定义该路径。

进入 Maven 路径下的 conf 目录，打开 setting.xml 文件。

![image-20220613161550302](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613161550302.png)



### 2. 修改中央仓库镜像位置

由于 Maven 中央仓库的服务器是架设在国外的，所以由于某种不可抗拒力量，国内用户如果直接使用中央仓库的话，下载速度会受很大的影响。如下图所示，个人用户可以使用阿里云镜像。这里阿里云仓库是作为中央仓库的一个镜像的，**镜像库会完全屏蔽被镜像库**。

![image-20220613161948541](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220613161948541.png)



















































