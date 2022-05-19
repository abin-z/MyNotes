# **Docker容器技术**

docker是基于Go语言开发的, 

Docker 是一个开源的应用容器引擎，让开发者可以打包他们的应用以及依赖包到一个可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化。容器是完全使用沙箱机制，相互之间不会有任何接口（类似 iPhone 的 app）。几乎没有性能开销,可以很容易地在机器和数据中心中运行。

## 一. Linux系统的结构

**内核**:  Linux内核直接与计算机硬件进行交互, 比如调用CPU, 调用I/O,操作内存等, 但是这些调用硬件的指令都非常复杂,不方便人们记忆, 于是出现了系统应用.

**系统应用**: 系统应用主要是将硬件指令进行了封装, 方便普通应用的调用, Linux的发行版就行相当于是不同的系统应用 

![](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261427457.png)



Linux的发行版都是基于Linux内核的, 只是系统应用的不同, 提供的函数库有差异

![image-20211126143754964](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261437163.png)

![image-20220519152837079](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220519152837079.png)

## 二. Docker原理

docker 是将程序需要运行的依赖和第三方库, 以及**将要调用系统(比如centos)的函数库**也一起打包, ==打包后的容器直接与Linux内核进行交互,不经过系统应用==,因此打包后的容器可以直接运行在基于Linux内核的机器上, 而不用考虑系统应用的环境

![image-20211126145424368](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261454536.png)



1. Docker如何解决大型项目依赖关系复杂，不同组件依赖的兼容性问题？

   - Docker允许开发中将**应用、依赖、函数库、配置**一起打包，形成可移植==镜像==

   - Docker应用运行在容器中，使用**沙箱机制，相互隔离**

1. Docker如何解决开发、测试、生产环境有差异的问题?
   - Docker镜像中包含完整运行环境，包括系统函数库，仅依赖系统的Linux内核，因此可以在任意Linux操作系统上运行



docker详解: https://zhuanlan.zhihu.com/p/25179221

[Docker容器中应避免的10件事](https://cloud.51cto.com/art/202003/612095.htm)



## 三.  Docker与VM

### 1. 虚拟机技术:

**虚拟机架构:**	通过软件模拟具有完整硬件系统功能的、运行在一个完全隔离环境中的完整计算机系统，能提供物理计算机的功能

​						虚拟机提供了==物理机硬件级别的操作系统隔离==，这让不同虚拟机之间的==隔离很彻底==，但也需要消耗更多资源.

![image-20210910111736464](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261542814.png)

### 2. 容器技术:

**容器架构:**	容器可以提供==操作系统级别的进程隔离==，以 Docker 为例，当我们运行 Docker 容器时，此时**容器本身只是操作系统中的一个进程**，只是利用操作系统					提供的各种功能实现了进程间网络、空间、权限等隔离，让多个 Docker 容器进程相互不知道彼此的存在

![image-20210910111937416](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261542411.png)



虚拟机技术与容器技术的最大区别在于：==**多个虚拟机使用多个操作系统内核，而多个容器共享宿主机操作系统内核。**==

![image-20211126154118016](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261546285.png)

## 四. Docker中的镜像. 容器. 仓库

**镜像（lmage）**：Docker将应用程序及其所需的依赖、函数库、环境、配置等文件打包在一起，称为镜像

**容器（Container）**：镜像中的应用程序运行后形成的进程就是容器，只是Docker会给容器做隔离，对外不可见, 容器与容器之间没有任何接口。

![image-20211126162651482](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261626566.png)



#### 1. 镜像(image)

```text
docker镜像从概念上讲类似于vm里面的iso文件，就是一个只读的模板。一个镜像可以包含一个Linux操作系统，里面安装了一系列的软件。镜像可以拷到任何装了docker的机器上运行。
```

#### 2. 仓库(registry)

```text
存储docker镜像的地方就是镜像仓库, 全球最大的docker镜像仓库是docker.io, 里面有大量官方和民间的优秀镜像可以直接拿过来使用，如mysql, centos等等。阿里也有自己的docker仓库: docker.alibaba-inc.com
```

#### 3. 容器(container)

```text
容器与镜像的关系有点像进程与程序的关系，运行中的镜像就叫容器。 从原理上讲，容器事实上是镜像上面加了一层读写
```

docker中镜像类似于Java中的类class,  容器则类似于Java中的一个实例instance

**三者之间的关系:**

![image-20210910112829061](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261622767.png)

## 五. Docker 和 DockerHub

* **DockerHub:** DockerHub是一个Docker镜像的托管平台, 这样的平台称为Docker Registry

* 国内也有很多类似于DockerHub的公开服务, 比如 网易云镜像服务, 阿里云镜像服务等
* 除此之外还可以搭建自己的Docker本地仓库
* DockerHub官网地址:  https://hub.docker.com/

![image-20211126163238040](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261632160.png)



## 六. Docker架构

docker是一个CS架构的程序, 由两部分组成: 

- **服务端(server):** Docker守护进程, 负责处理Docker指令, 管理镜像, 容器等 

- **客户端(client):** 通过命令或RestAPI向Docker服务端发送指令, 可以在本地或远程向服务端发送指令



![image-20211126163743131](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261637248.png)





## 七. Docker常用命令

```bash
docker --help    #可以查看所有的docker命令
docker images --help  #查看images命令的详细信息, 包括参数
```

**安装docker:**

安装docker前可以先配置一下国内镜像源, 默认是在国外的服务器去下载速度比较慢(百度)

```bash
yum install -y docker-ce	#下载docker
systemctl start docker      #启动docker
systemctl daemon-reload   	#重新加载配置文件
systemctl enable docker		#设置开机自启动
```

![image-20210906090329980](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261427569.png)

Docker应用需要用到各种端口，逐一去修改防火墙设置。非常麻烦，因此建议大家直接关闭防火墙！(在企业开发中不这样使用)

```bash
docker images				#查看本地的镜像
```

![image-20210906092724633](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261438826.png)

在docker安装好后docker官方的镜像源拉取速度很慢, **最好配置一下拉取镜像的镜像加速(百度)**

**docker==镜像==相关操作:**

![image-20211126170204515](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261702612.png)

**docker==容器==相关操作:**

![image-20211126172803473](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261728568.png)



```bash
docker pull mysql:5.7 		#远程拉取MySQL5.7镜像
```

**创建容器**

```bash
docker run --name mysql --restart always -p 3306:3306 -e MYSQL_ROOT_PASSWORD=root -d mysql:5.7			#运行相应的容器, 如果不存在则先创建, -d表示后台运行
```

![image-20211126174710271](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261747388.png)

**查看容器的状态**

```bash
docker ps -a		#查看相关信息 status: UP为启动状态
```

![image-20210906092954552](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261542072.png)

```bash
docker exec -it mysql bash		#登录到容器中,进入到指定容器打开虚拟终端
```

```bash
mysql -u root -p -h ip地址		#登录到指定IP的MySQL中
```

**常用命令(熟悉)**

如果相关的组件命令不熟悉可以参考DockerHub官网: https://hub.docker.com/   直接搜索相应的组件名称即可

```bash
 #===========================镜像相关命令====================================
 docker pull 镜像版本					#拉取镜像
 docker images							#查看镜像
 docker rmi 镜像id或者REPOSITORY:TAG  		#删除镜像
 docker save -o nginx.tar nginx:latest	#将nginx:latest这个镜像压缩成一个nginx.tar的文件, 用于拷贝
 
 #===========================容器相关命令====================================
 docker run ........					#运行容器,如果不存在就先创建
 docker ps -a							#查看容器运行状态
 docker exec -it 容器名称或ID bash		#进入到相应的容器,也可以不使用bash, 也可以直接进入容器中相应的命令终端等
 docker logs 容器名称或ID		#查看容器的运行日志
 docker restart 容器名称或ID    #重启
 docker start 容器名称或ID        #启动
 docker stop 容器名称或ID		#停止容器
 docker pause 容器名或者ID 		#暂停一个或多个容器
 docker unpause 容器名或者ID		#恢复一个容器 
 docker kill 容器名称或ID		#强制杀掉容器
 docker rm 容器名称或ID         #只能删除没有运行的容器
 docker rm -f 容器名称或ID      #强制删除相应的容器
 docker rename 旧名称 新名称		#重命名容器
 docker inspect 容器名称或者ID    #查看容器相关信息，包括容器的IP地址等相关信息

 1删除多个容器:  docker rm -f 多个容器名称或ID
 2删除多个容器:  docker rm -f `docker ps -a -p`
 3删除多个容器:  docker rm -f $(docker ps -a -p)
```

**将一个镜像保存为一个压缩文件**:    `docker save -o ***.tar REPOSITORY:TAG  `	-o表示的是output输出

<img src="https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261715975.png" alt="image-20211126171528887">

**将一个镜像的压缩包加载到docker中**    `docker load -i ***.tar`

![image-20211126171735906](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111261717981.png)

**查看容器详细信息(日志)**

```bash
docker inspect 容器名称或者ID    #查看容器相关信息，包括容器的IP地址等相关信息
```



## 八. Docker数据卷

如何解决容器与数据耦合的问题：

- **容器不便于修改**：当我们需要修改容器中的文件内容时，需要进入容器，并且没有高级的编辑器。
- **数据不可复用**：容器内的修改对外是不可见的，所有修改对新建的容器是不可复用的。
- **升级维护困难**： 数据在容器内部，如果升级容器必然要删除旧容器，那么旧容器中的数据也跟着被删除了



### 1. 数据卷

**数据卷（volume）是一个虚拟目录**，指向宿主机文件系统的某个目录

![image-20211128104052496](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281040680.png)



操作数据卷基本语法：

![image-20211128105818034](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281058089.png)

```bash
docker volume [command]			#docker数据卷操作是一个二级指令
#docker volume 命令表示操作数据卷, 根据后面的[command]来确定对数据卷的操作

docker volume create html		#创建一个名为html的数据卷
docker volume rm html			#删除html的数据卷
docker volume ls				#查看所有的数据卷
docker volume inspect html		#查看某个数据卷的详细信息
docker volume prune				#删除当前所有未使用的数据卷
```

- create 				**创建**一个volume
- ls					      **列出**所有的volume
- rm						**删除一个或多个指定的**volume
- prune				  **删除==当前所有未使用==**的volume
- inspect			    显示一个或多个volume的**信息**

![image-20211128105412178](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281054225.png)

![image-20211128105527113](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281055154.png)

数据卷的作用

- ==将容器与数据分离, 解耦合, 方便操作容器内数据, 保证数据的安全性==
- ==即使删除了容器,数据卷的内容也会保留在宿主机中,除非手动删除数据卷==



### 2. 挂载数据卷

在创建(run)容器的同时可以使用  **-v**  参数将数据卷挂载到某个容器的目录中

```bash
-v  [数据卷名称]:[容器内的目录]   #如果数据卷不存在则直接创建数据卷
```

![image-20211128110849850](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281108950.png)

```bash
docker run --name nginx --restart always -p 80:80 -v html:/usr/share/nginx/html -d nginx			#创建一个Nginx的容器,并使用html数据卷挂载(如果数据卷不存在则直接创建)
```

当我们修改宿主机中相应的数据卷的时候,与之挂载的容器中的数据也会跟着改变



### 3.挂载宿主机目录

使用挂载宿主机目录(宿主机----容器直接文件或目录的映射):外挂

```bash
#目录挂载和数据卷挂载的语法很类似,使用在run阶段
	-v [宿主机目录]:[容器内目录]
	-v [宿主机文件]:[容器内文件]
```



在run的时候使用参数:   -v 宿主机的目录或者文件:容器中的目录或文件

```bash
docker run --name mysql_name --restart always -p 3309:3306 -v /root/mysql/data:/abin -e MYSQL_ROOT_PASSWORD=root -d mysql:5.7
#上面是创建mysql的容器, 并设置默认密码为 root

docker run \
	--name redis \
	--restart always \
	-p 6379:6379 \
	-d redis redis-server \
	--save 60 1 \
	--loglevel warning
#上面是创建redis容器, 并设置持久化, 以及设置打印日志的级别,  \  表示换行拼接

source sql文件路径  	#MySQL导入sql文件
```



### 4.宿主机与容器间文件目录相互复制

将==宿主机中得文件复制到容器==中:**在宿主机操作**

```bash
docker cp  宿主机文件路径 容器的名称或ID:容器中的目录		#均在宿主机中操作,注意顺序
```

将==容器中的文件复制到宿主机==中:**也是在宿主机上操作**

```bash
docker cp 容器名称或ID:容器中文件的目录 宿主机文件路径		#均在宿主机中操作,注意顺序
```



### 5. 挂载方式对比

![image-20211128114227947](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281142130.png)

![image-20211128114429095](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281144189.png)





2021/9/6  pm

**MySQL配置文件**

登录MySQL容器后:  `/etc/mysql/my.cnf #配置文件目录`

**提高效率,定义常用的别名**

增加别名:   	`alias cmd_name='docker exec -it mysql bash'`

永久生效需要修改配置文件: /etc/profile		也可以修改/etc/bashrc   	在后面追加



## 九. 卸载docker

```bash
#1.停止docker服务
systemctl stop docker

#2.查看安装的相关程序包
yum list installed
yum list installed | grep docker
yum list installed | grep container

#分别卸载上述的安装包
yum -y remove 安装包名称

#再次确认是否卸载成功
yum list installed | grep docker
yum list installed | grep container

#删除相关的目录
cd /etc
rm -rf docker

cd /var/lib
rm -rf docker docker-engine
#更多的细节可以去百度
```

**大批量导入sql数据**

```bash
#首先登录MySQL
mysql -u root -p root --local_infile=1

#登录后 ,查看是否支持大批量导入数据
show global variables like 'local_infile';
```

![image-20210906154333577](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210906154333577.png)

```bash
#如果不为ON,则修改为ON
set global local_infile=true;

#执行数据库脚本文件
source /mysql/empdb.sql

#执行如下命令,大批量导入数据
load data local infile '/mysql/emp_50w.dat' into table empdb.emp;
```

![image-20210906160424448](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210906160424448.png)



## 十. Dockerfile自定义镜像

**镜像是分层结构**,每一层称为一个Layer

- BaseImage层: 包含基本的系统函数库\环境变量\文件系统等
- Entrypoint层: 镜像运行的入口, 是镜像启动的命令
- 其他: 在BaseImage基础上添加依赖\安装程序\完成整个应用的安装和配置

![image-20211128142551865](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281425123.png)

### 1.Dockerfile定义

Dockerfile是一个文本文件,其中包含一个个的指令(instruction), 用指令来说明要执行什么操作来构建镜像.

每一个指令都会形成一层Layer

![image-20211128143811190](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281438382.png)

Dockerfile的基本写法:

![image-20211128144150210](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281441328.png)



```bash
docker build -t REPOSITORY:TAG    #基于dockerfile进行构建项目
#需要注意相应的jar包和dockerfile需要在同一级目录
```

![image-20211128144515537](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281445626.png)

刚才构建的镜像:

![image-20211128145052424](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281450532.png)



可以基于java:8-alpine镜像简化Dockerfile构建过程:

![image-20211128145302681](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281453802.png)

原理: java:8-alpine镜像将通用的过程给封装好, 不需要我们构建每一层,简化开发

![image-20211128145222859](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281452936.png)

### 总结:

1. Dockerfile的本质就是一个文件, 通过指令描述镜像的构建过程
2. Dockerfile的第一行必须是FROM, 可以从一个基础镜像来构建
3. 基础镜像可以是基本的操作系统,比如Ubuntu, 也可以是第三方制作好的镜像, 比如: java:8-alpine 





## 十一. 根据现有的容器制作镜像

**docker commit :**从容器创建一个新的镜像。

**语法**

```
docker commit [OPTIONS] CONTAINER [REPOSITORY[:TAG]]
```

OPTIONS说明：

- **-a :**提交的镜像作者；
- **-c :**使用Dockerfile指令来创建镜像；
- **-m :**提交时的说明文字；
- **-p :**在commit时，将容器暂停。

```bash
docker commit 容器ID  自定义的镜像名:版本号

docker commit 5836a9f2c051 mytomcat:10
```

![image-20210924144108237](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281503502.png)



### 1. 将制作的镜像打包

```bash
docker save -o 包名.tar 镜像名:版本号
docker save -o mytomcat10.tar mytomcat:10			#打包自己的镜像

gzip mytomcat10.tar
```

![image-20210924144914098](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281503514.png)

此时就可以将该镜像的压缩文件拷贝走



### 2. 将镜像文件的压缩文件加载到docker镜像中.

```bash
gunzip mytomcat10.tar.gz			#解压docker镜像包,产生一个mytomcat10.tar

docker load -i mytomcat10.tar		#将镜像文件包添加到镜像中
```

![image-20210924150639116](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281503253.png)

![image-20210924150710168](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281503935.png)

已经恢复到本地镜像中了

```bash
#创建自定义镜像的docker容器
docker run --name mytomcat --restart always -p 8060:8080 -d mytomcat:10
```

在8060端口进行验证:

![image-20210924151413212](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281503390.png)



## 十二. DockerCompose

什么是DockerCompose?

- **Docker Compose可以基于Compose文件帮我们快速的部署分布式应用**，而无需手动一个个创建和运行容器！		

- Compose文件是一个yaml文本文件，**通过指令定义集群中的每个容器如何运行**。
- 可以协助我们部署微服务集群, 类似于多个容器的run命令,但是格式上有不同之处

![image-20211128155139282](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111281551535.png)

DockerCompose的详细细节参考官网:    https://docs.docker.com/compose/compose-file/

DockerCompose需要自行下载, 更多细节需要自行百度



## Docker镜像仓库

视频地址:   https://www.bilibili.com/video/BV1LQ4y127n4?p=60&spm_id_from=pageDriver
