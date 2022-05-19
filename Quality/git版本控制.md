# Git分布式版本控制系统

[**git原理图解**](https://www.cnblogs.com/cb0327/p/5066685.html)

git是一个分布式版本控制系统, **版本控制**是一种记录一个或若干文件内容变化，以便将来查阅特定版本修订情况的系统。

在本书所展示的例子中，我们对保存着软件源代码的文件作版本控制，但实际上，**可以对任何类型的文件进行版本控制**。

快速上手: https://www.yiibai.com/git/git_basic_concepts.html

# Git使用铁令

- ### ==切换分支前先提交本地的修改==

- ### ==代码及时提交, 只要提交过了就不会丢==

- ### 切勿删除 .git 目录



# 一.  版本控制分类

### 1. 本地版本控制

---

许多人习惯用复制整个项目目录的方式来保存不同的版本，或许还会改名加上备份时间以示区别。 这么做唯一的好处就是简单，但是特别容易犯错。 有时候会混淆所在的工作目录，一不小心会写错文件或者覆盖意想外的文件。

为了解决这个问题，人们很久以前就开发了许多种本地版本控制系统，大多都是采用某种简单的数据库来记录文件的历次更新差异。

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290025006.png)

其中最流行的一种叫做 *RCS*，现今许多计算机系统上都还看得到它的踪影。 甚至在流行的 Mac OS X 系统上安装了开发者工具包之后，也可以使用 `rcs` 命令。 它的工作原理是在硬盘上保存补丁集(补丁是指文件修订前后的变化)；通过应用所有的补丁，可以重新计算出各个版本的文件内容。



### 2. 集中化的版本控制系统

---

**代表作: SVN**

接下来人们又遇到一个问题，如何让在不同系统上的开发者协同工作？ 于是，集中化的版本控制系统(Centralized Version Control Systems，简称 *CVCS*)应运而生。 这类系统，诸如 *CVS*、*Subversion(SVN)* 以及 *Perforce* 等，都有一个单一的集中管理的服务器，保存所有文件的修订版本，而协同工作的人们都通过客户端连到这台服务器，取出最新的文件或者提交更新。多年以来，这已成为版本控制系统的标准做法。

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290026057.png)

这种做法带来了许多好处，特别是相较于老式的本地 *VCS* 来说。 现在，每个人都可以在一定程度上看到项目中的其他人正在做些什么。 而管理员也可以轻松掌控每个开发者的权限，并且管理一个 *CVCS* 要远比在各个客户端上维护本地数据库来得轻松容易。

事分两面，有好有坏。 这么做最显而易见的**缺点是中央服务器的单点故障**。 如果宕机一小时，那么在这一小时内，谁都无法提交更新，也就无法协同工作。 如果中心数据库所在的磁盘发生损坏，又没有做恰当备份，毫无疑问您将丢失所有数据——包括项目的整个变更历史，只剩下人们在各自机器上保留的单独快照。本地版本控制系统也存在类似问题，只要整个项目的历史记录被保存在单一位置，就有丢失所有历史更新记录的风险。



### 3. 分布式版本控制系统

---

**代表作是git**

于是分布式版本控制系统(Distributed Version Control System，简称 *DVCS*)面世了。 在这类系统中，像 *Git*、*Mercurial*、*Bazaar* 以及 *Darcs* 等，客户端并不只提取最新版本的文件快照，而是把代码仓库完整地镜像下来。 这么一来，任何一处协同工作用的服务器发生故障，事后都可以用任何一个镜像出来的本地仓库恢复。 因为每一次的克隆操作，实际上都是一次对代码仓库的完整备份。如下图所示 -

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290026467.png)

更进一步，许多这类系统都可以指定和若干不同的远端代码仓库进行交互。藉此，你就可以在同一个项目中，分别和不同工作小组的人相互协作。可以根据需要设定不同的协作流程，比如层次模型式的工作流，而这在以前的集中式系统中是无法实现的。



**分布式相比于集中式的最大区别在于开发者可以提交到本地，每个开发者通过克隆（git clone），在本地机器上拷贝一个完整的Git仓库。**





# 二. git的下载安装与基本配置:

git安装配置: https://www.yiibai.com/git/git_environment.html



### 1. git使用前的配置

Git 自带一个 `git config` 的工具来帮助设置控制 Git 外观和行为的配置变量。 这些变量存储在三个不同的位置：

`/etc/gitconfig` 文件: 包含**系统上每一个用户及他们仓库的通用配置**。 如果使用带有 `--system` 选项的 `git config` 时，它会从此文件读写配置变量。

`~/.gitconfig` 或 `~/.config/git/config` 文件：**只针对当前用户。 可以传递`--global` 选项让 Git 读写此文件。**

**当前使用仓库的 Git 目录中的 `config` 文件(就是 `.git/config`)：针对该仓库。**

每一个级别覆盖上一级别的配置，所以 `.git/config` 的配置变量会覆盖 `/etc/gitconfig` 中的配置变量。

在 Windows 系统中，Git 会查找 `$HOME` 目录下(一般情况下是 `C:\Users\$USER`)的 `.gitconfig` 文件。 Git 同样也会寻找 `/etc/gitconfig` 文件，但只限于 MSys 的根目录下，即安装 Git 时所选的目标位置。

### 2. 用户信息

当安装完 Git 应该做的第一件事就是设置用户名称与邮件地址。这样做很重要，因为每一个 Git 的提交都会使用这些信息，并且它会写入到每一次提交中，不可更改：(这个可以是不存在的邮箱，但是就是必须要有)

```shell
$ git config --global user.name "abin"
$ git config --global user.email abin_z@163.com
```

再次强调，如果使用了 `--global` 选项，那么该命令只需要运行一次，因为之后无论你在该系统上做任何事情， Git 都会使用这些信息。 当你想针对特定项目使用不同的用户名称与邮件地址时，可以在那个项目目录下运行不使用 `--global` 选项的命令来配置。

![image-20211129005231063](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290052111.png)

修改后可以在文件中查看配置: `C:\Users\Abin\.gitconfig`  (windows下)

![image-20211129005355014](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290053054.png)



### 3. 检查配置信息

如果想要检查你的配置，可以使用 `git config --list` 命令来列出所有 Git 当时能找到的配置。

或者是使用`git config -l` 查看当前配置

```shell
yiibai@ubuntu:~$ git config --list
user.name=maxsu
user.email=maxsu@yiibai.com
color.status=auto
color.branch=auto
color.interactive=auto
color.diff=auto
...
```

![image-20211129005854658](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111290058764.png)



上面的输出结果中，可能会看到重复的变量名，因为 Git 会从不同的文件中读取同一个配置(例如：`/etc/gitconfig` 与 `~/.gitconfig`)。 这种情况下，Git 会使用它找到的每一个变量的最后一个配置。

可以通过输入 `git config <key>：` 来检查 Git 的某一项配置。

```shell
yiibai@ubuntu:~$ git config user.name
maxsu
yiibai@ubuntu:~$ git config user.email
maxsu@yiibai.com
yiibai@ubuntu:~$
Shell
```

### 4. 获取帮助

若在使用 Git 时需要获取帮助，有三种方法可以找到 Git 命令的使用手册：

```shell
$ git help <verb>
$ git <verb> --help
$ man git-<verb>
Shell
```

例如，要想获得 `config` 命令的手册，执行

```shell
$ git help config
Shell
```

这些命令很棒，因为随时随地可以使用而无需联网。如果你觉得手册或者本书的内容还不够用，你可以尝试在 Freenode IRC 服务器( `irc.freenode.net` )的 `#git` 或 `#github` 频道寻求帮助。这些频道经常有上百人在线，他们都精通 Git 并且乐于助人。



### 5. 为常用指令设置别名（可选项）

有些常用的指令参数非常多，每次都要输入好多参数，我们可以使用别名。
1. 打开用户目录，创建 .bashrc 文件
部分windows系统不允许用户创建点号开头的文件，可以打开gitbash,执行 touch ~/.bashrc   在文件中添加一下信息:

```sh
#用于输出git提交日志
alias git-log='git log --pretty=online --all --graph --abbrev-commit'

#用于输出当前目录所有文件的基本信息
alias ll='ls -al'
```

### 6. 解决gitbash中文乱码的问题

1. 打开gitbash执行以下的命令:

   ```sh
   git config --global core.quotepath false
   ```

2. ${git_home}/etc/bash.bashrc 文件最后添加如下内容:

   ```sh
   export LANG="zh_CN.UTF-8"
   export LC_ALL="zh_CN.UTF-8"
   ```

   

# 三. Git 工作流程图

**说明：**

- workspace：工作区
- staging area：暂存区/缓存区
- local repository：版本库或本地仓库
- remote repository：远程仓库

![image-20211130215157473](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111302151592.png)

```sh
clone   	#克隆： 从远程仓库中克隆代码到本地仓库
checkout	#检出:  从本地仓库中检出一个仓库分支然后进行修订
add			#添加:  在提交代码前先将代码添加到暂存区
commit		#提交:  提交到本地仓库. 本地仓库中保存了修改的历史版本
fetch		#抓取:  从远程仓库抓取到本地仓库,不进行任何的合并操作,使用频率不高
pull		#拉取:  从远程仓库中拉取代码到本地仓库,并自动进行合并(merge),然后放到工作区
push		#推送:  修改完成后,需要和团队成员共享代码时,将代码推送到远程仓库
log			#日志:  查看历史提交记录
config		#配置:  可以配置和查看相应的git配置信息
status		#状态:  查看当前状态
switch		#切换:  切换分支
```



一个简单的操作步骤：

```sh
$ git init    		#初始化仓库。
$ git add .    		#添加文件到暂存区。
$ git commit  		#将暂存区内容添加到本地仓库中。
```

### 1. 创建仓库命令

下表列出了 git 创建仓库的命令：

| 命令        | 说明                                           |
| :---------- | :--------------------------------------------- |
| `git init`  | 初始化仓库, 文件夹中会出现一个  .git  的文件夹 |
| `git clone` | 拷贝一份远程仓库，也就是下载一个项目。         |

------

### 2. 提交与修改

Git 的工作就是创建和保存你的项目的快照及与之后的快照进行对比。

下表列出了有关创建与提交你的项目的快照的命令：

| 命令         | 说明                                     |
| :----------- | :--------------------------------------- |
| `git add`    | 添加文件到仓库                           |
| `git status` | 查看仓库当前的状态，显示有变更的文件。   |
| `git diff`   | 比较文件的不同，即暂存区和工作区的差异。 |
| `git commit` | 提交暂存区到本地仓库。                   |
| `git reset`  | 回退版本。                               |
| `git rm`     | 删除工作区文件。                         |
| `git mv`     | 移动或重命名工作区文件。                 |

### 3. 查看提交日志

| 命令               | 说明                                 |
| :----------------- | :----------------------------------- |
| `git log`          | 查看历史提交记录                     |
| `git blame <file>` | 以列表形式查看指定文件的历史修改记录 |

### 4. 远程操作

| 命令         | 说明               |
| :----------- | :----------------- |
| `git remote` | 远程仓库操作       |
| `git fetch`  | 从远程获取代码库   |
| `git pull`   | 下载远程代码并合并 |
| `git push`   | 上传远程代码并合并 |

### 5. 版本回退

- 作用: 不同提交版本之间的切换

```sh
git reset --hard [commitID]    # --hard 表示强制回退
```

- commitID 可以使用 `git log` 或者是`git-log` 查看

- 如何查看已经所有已提交的记录?

  ```sh
  git reflog			#这个指令可以看到已经删除的提交记录
  ```

  

### 6. git基础操作指令

Git工作目录下对于文件的修改(增加、删除、更新)会存在几个状态，这些修改的状态会随着我们执行Git的命令而
发生变化。

![image-20211130230947835](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111302309959.png)

## 7. 基础指令练习

- 首先准备一个空文件夹

![image-20211203204629981](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032046041.png)

- **初始化本地仓库**

```sh
git init
```

![image-20211203204852351](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032048431.png)

- 创建一个file01.txt文件(这个文件怎么创建都可以,可以在Windows下创建)

```sh
touch file01.txt
```

![image-20211203205219873](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032052949.png)

- **查看当前工作区的文件状态**

```sh
git status
```

![image-20211203205513508](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032055595.png)

- **将工作区中的文件添加到暂存区**

```sh
git add .			#注意其中的 . 表示当前文件夹的所有文件   也可以单独指定某个文件
```

![image-20211203205745442](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032057525.png)

- **提交暂存区文件到本地仓库**

```sh
git commit -m 'add file01'				#-m 表示提交的说明信息/一般为功能描述
```

![image-20211203210129081](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032101165.png)

- **查看提交的文件的目的地**(所在分支)

```sh
git log			#查看文历史提交日志
```

![image-20211203210524203](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032105299.png)

- 现在修改工作区中的文件

```sh
vim file01.txt
```

![image-20211203211023883](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032110976.png)

- **查看此时文件的状态**: 此时的状态为未暂存

```sh
git status
```

![image-20211203211214866](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032112956.png)

- **添加文件到暂存区**

![image-20211203211313170](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032113250.png)

- 提交本次修改

```sh
 git commit -m 'update file01'
```

![image-20211203211542496](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032115580.png)

- **查看此时的提交日志**

```sh
git log
```

![image-20211203211836792](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032118889.png)

![image-20211203211917423](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032119482.png)

- **演示版本回退功能**

再次提交一次修改, 并且添加一个文件 file02.txt 文件

![image-20211203212457649](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032124748.png)

提交本次版本

![image-20211203212658577](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032126669.png)

![image-20211203212730426](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032127478.png)

- 版本回退 可以跳转到任何提交的版本

```sh
git reset --hard [commitID]			#commitID 表示要回退的版本
```

![image-20211203213301918](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032133014.png)

-  查看历史提交版本记录 , 还是可以回到之前的版本的, 可以通过以下命令来查看历史提交版本

```sh
git reflog
```

![image-20211203213746416](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032137507.png)

# 四. 添加忽略列表(.gitignore文件) 

一般我们总会有些文件无需纳入Git 的管理，也不希望它们总出现在未跟踪文件列表。 通常都是些自动生成的文件，比如日志文件，或者编译过程中创建的临时文件等。 在这种情况下，我们可以在工作目录中创建一个名为.gitignore 的文件（文件名称固定），列出要忽略的文件模式。下面是一个示例:

```sh
touch .gitignore
vim .gitignore
```

![image-20211203215253728](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032152845.png)

## 1. 常用忽略规则

/abc/：忽略根目录下的abc文件夹以及abc文件夹下的所有子文件夹和文件
bcd/：忽略根目录下或者根目录下任意子目录下的bcd文件夹以及bcd文件夹下的所有子文件夹和文件
/mmm.txt：忽略根目录下的mmm.txt文件
nnn.txt：忽略根目录下或者根目录下任意子目录下的nnn.txt文件

根目录：即工作区目录。工作区、暂存区、版本库概念

## 2. 忽略已被跟踪的文件

**忽略规则只针对还没有被git跟踪的文件及文件夹有效。**若需要忽略规则对已被跟踪的文件及文件夹有效，则需要取消对文件或文件夹的跟踪

```sh
git rm -r --cached <dir>：取消对文件夹及文件夹下的所有子文件夹、文件的跟踪，文件夹及文件夹下的所有子文件夹、文件的状态将从跟踪状态变为未跟踪状态
git rm --cached <file>：取消对文件的跟踪，文件的跟踪状态将变为未跟踪状态
git restore --staged <file> 将指定文件移除跟踪
```

取消对文件或文件夹的跟踪之后，.gitignore文件中的忽略规则将会对取消了跟踪状态的文件或文件夹生效



# 五. Git 分支管理

几乎每一种版本控制系统都以某种形式支持分支。使用分支意味着你可以从开发主线上分离开来，然后在不影响主线的同时继续工作。

有人把 Git 的分支模型称为**必杀技特性**，而正是因为它，将 **Git** 从版本控制系统家族里区分出来。

**Git分支命令git branch、git switch、git checkout的区别**: https://blog.csdn.net/wpw2000/article/details/115895848

### 1. **列出分支命令：**

```sh
git branch		#查看本地分支，当前分支前面会标一个*号。
git branch -r 	#查看远程分支。
git branch -a	#查看本地分支和远程分支，远程分支会用红色表示出来（如果你开了颜色支持的话）。
git branch -vv 	#查看本地分支对应的远程分支。		出现ahead表示本地分支领先远端分支
```

![image-20211203215918148](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032159218.png)

```sh
git branch -vv				#说明
```

![image-20211222174854629](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112221748743.png)



### 2. **创建分支命令：**

```sh
git branch [branchname]		#创建分支,但是没有切换过去, 还停留在当前分支

----------------------------------------------------------------------------------
git checkout -b <name>
#创建一个叫name的分支，然后切换到该分支。
#相当于两条命令：git branch <name>，git checkout <name>

git switch -c <name>
#创建一个叫name的分支,并切换过去
#相当于两条命令：git branch <name>，git switch <name>

----------------------------------------------------------------------------------
git branch -m oldName newName		#重命名分支
```

![image-20211203220451565](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032204670.png)

现在在master主分支上新建文件master.txt并提交

![image-20211203221032117](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032210214.png)

### 3. **切换分支命令:**

就简单的切换分支，推荐使用switch命令，不推荐使用checkout

`git checkout`命令用于切换分支或恢复工作树文件。`git checkout`是git最常用的命令之一，同时也是一个很危险的命令，**因为这条命令会重写工作区**。

```sh
git checkout [branchname]		#切换分支
git switch	[branchname]		#切换分支, 推荐使用 switch 切换分支
#-------------------------- checkout 和 switch 在分支操作方面的用处完全一样, 那么在分支操作上尽量使用: git branch 和 git switch
#-------------------------- 因为 git checkout 除了可以操作分支, 它还可以操作文件, 这个命令可以重写工作区, 是一个很危险的命令

================================================================
git checkout -b [branchname]	#直接创建分支并且切换到当前分支,若分支存在则直接切换到该分支		
```

当你切换分支的时候，Git 会用该分支的最后提交的快照替换你的工作目录的内容， 所以多个分支不需要多个目录。

![image-20211203221335336](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032213433.png)

现在在develop分支上新建文件develop.txt并提交

![image-20211203222004772](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032220874.png)

现在切换回master分支上, ==不会出现develop分支上提交的develop.txt文件==

![image-20211203222325558](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032223664.png)



### 4. **合并分支命令:**

```sh
git merge [branchname]			# 将branchname的分支合并到当前分支
```

合作开发时,基本都是在develop分支上进行开发的, 需要保证master分支的稳定性

协同开发就会出现分支, 下图是在develop分支上开发的情况

![image-20211203223453387](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032234475.png)

下图是在master分支上开发的情况

![image-20211203223736044](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032237133.png)

**合并分支操作(没有冲突的时候):**

```sh
git merge [branchname]
```

![image-20211203224609911](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032246014.png)

填写合并分支的说明信息(一般为实现了什么功能)

![image-20211203224246123](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032242213.png)

### 5. **删除分支命令：**

- 删除分支的时候是==不能删除当前所在的分支的==

```sh
git branch -d [branchname]	#需要做检查,未合并分支的时候会提示

git branch -D [branchname]	#不需要做检查,直接删除
```

![image-20211203225018394](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032250483.png)



### 6. 合并分支冲突

当两个分支都修改**同一个文件的同一部分**(比如同一行)就会产生冲突,这时候git==需要开发人员决定==要保留哪一部分

- 创建一个文件(common.txt)模拟冲突

原始数据如下

![image-20211203230842897](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032308977.png)

master分支中提交的数据

![image-20211203231039516](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032310593.png)

dev分支中提交的数据

![image-20211203231245257](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032312329.png)

目前分支情况:

![image-20211203231515953](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032315019.png)

**执行合并分支操作**:

![image-20211203231809897](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032318976.png)

可以通过查看文件详情了解那些文件冲突

```sh
git status 	#查看那些文件存在冲突
```

此时的冲突文件common.txt内容为:

![image-20211203232400116](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032324195.png)

根据实际情况来修改冲突的文件

![image-20211203232643827](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032326904.png)

修改完冲突文件后, 后面进行add , commit 指定解决冲突信息

![image-20211203233009675](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032330750.png)

![image-20211203233322495](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112032333575.png)

### 7. Git合并的快进模式

![image-20211204003003676](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112040030764.png)

在master执行合并操作,就会执行快进模式(**效果是一样的**)

![image-20211204003304032](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112040033117.png)



# 六. 开发中分支使用原则与流程

几乎所有的版本控制系统都以某种形式支持分支。

使用分支意味着你可以把你的工作从开发主线上分离开来进行. 

重大的Bug修改、开发新的功能，以免影响开发主线。



在开发中，一般有如下分支使用原则与流程：

### **1. master分支(生产环境)**

- 线上分支，主分支，中小规模项目作为线上运行的应用对应的分支;
- 需要确保master分支的稳定性, 一般不会再master分支上直接进行开发.
- 一般不会删除master主分支



### 2. develop分支(开发环境)

- 是从master创建的分支，一般作为开发部门的主要开发分支.
- 开发新功能一般都在develop分支上开发
- 如果没有其他并行开发不同期上线要求，都可以在此版本进行开发，阶段开发完成后，需要是合并到master分支,准备上线。
- 一般也不会删除develop分支



### 3. feature(特征分支)

- 从develop创建的分支, 为了完成不同的开发需求
- 一般是同期并行开发，但不同期上线时创建的分支
- 分支上的研发任务完成后合并到develop分支。
- 测试通过后,合并到develop分支后, 可以删除该分支



### 4. hotfix(BUG修复分支)

- 从master派生的分支，一般作为线上bug修复使用
- ==修复完成后需要合并到master、test、develop分支==。
- BUG修复完成并合并完成后可以删除该分支

### 5. test分支(测试分支)等其他分支

- test主要是用于测试
- 可以删除



### 6. 分支示意图

![image-20211204001011707](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112040010926.png)





git使用**远端仓库强制覆盖本地仓库**

```sh
git fetch --all   	#将远端仓库的所有抓取下来
git reset --hard origin/[分支名称]		#版本回退
git pull 			#重新拉取并合并
```

git**本地强制覆盖远程** 说明分支情况

```sh
git push origin [分支名称] --force		#强制推送到分支
```



# 七. Git远程仓库

## 常见的代码托管服务

**GitHub**（ 地址：https://github.com/ ）是一个面向开源及私有软件项目的托管平台，因为只支持Git 作为唯一
的版本库格式进行托管，故名GitHub
**Gitee**（地址： https://gitee.com/ ）是国内的一个代码托管平台，由于服务器在国内，所以相比于GitHub，码云
速度会更快
**GitLab** （地址： https://about.gitlab.com/ ）是一个用于仓库管理系统的开源项目，使用Git作为代码管理工
具，并在此基础上搭建起来的web服务，一般用于在企业、学校等内部网络搭建git私服。



企业中开发一般使用的是GitLab, 可以使用自己的机房来搭建,自己的代码自己来托管

github一般是很多的开源项目的服务托管平台(国内一般使用的是Gitee)



## Git远程仓库的SSH配置

### 1.创建远程仓库![image-20211205220452846](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052204953.png)

### 2.配置SSH公钥

- 生成SSH公钥

  ```sh
  ssh-keygen -t rsa			#使用rsa方式生成非对称秘钥
  ```

  ![image-20211205221247500](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052212598.png)

注意: 如果公钥已经存在,则自动覆盖

在用户目录下的 .ssh 目录下会生成相应的公钥`id_rsa.pub`

![image-20211205221733108](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052217194.png)

将生成的公钥`id_rsa.pub`内容复制到代码托管平台上

![image-20211205222230854](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052222965.png)



点击确定后输入密码后就配置号了公钥,  可以在gitbash中测试是否配置成功

```sh
ssh -T git@gitee.com			#需要输入 yes
```

![image-20211205222636401](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052226470.png)



## 操作远程仓库

### 1.添加远程仓库

![image-20211205224018132](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052240185.png)

```sh
git remote add [远端仓库名] [ssh远程仓库地址]		#一般远端仓库名都为 origin
```

```sh
git remote add origin git@gitee.com:abin_z/git-demo.git		#origin仅仅是远端仓库名, 还没有远端分支名
```

![image-20211205224848724](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052248800.png)

### 2.查看远程仓库

```sh
git remote 				#查看远程仓库
```

### 3.推送到远程仓库

在推送(`push`)操作之前，如想要检查文件代码变化，可使用`git show [commitID]`  命令指定提交ID来查看具体的变化。

```sh
git push [-f] [--set-upstream] [远端分支名 [本地分支名]:[远端分支名]]	
```

-    -f    表示强制推送

- 如果远程分支名和本地分支名一致,则可以只写本地分支名

  - ```sh
    git push origin master
    ```

- --set-upstream 表示在推送到远端的同时并==建立起本地分支和远端分支==的追踪关系

  - ```sh
    git push --set-upstream origin master
    ```

- **如果当前分支已经和远端分支关联,则可以省略分支名和远端名**

  - ```sh
    git push		#将master分支推送到远端的master分支
    ```

```sh
git push --set-upstream origin master
```

![image-20211205230106636](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052301705.png)

![image-20211205230241823](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052302919.png)

### 4.关联远程分支

```sh
## 建立当前分支与指定远程分支的追踪关系，但不会拉取代码。参数"-u"和"--set-upstream-to"同样的意思。
$ git branch -u <远程主机名>/<远程分支名>
$ git branch --set-upstream-to <远程主机名>/<远程分支名>


git branch -vv 				#用于查看本地分支与远端分支的绑定情况
git push --set-upstream origin master:master	#推送的同时建立追踪关系
```

![image-20211205230835220](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052308298.png)

* #### 创建本地分支来跟踪并拉取远程分支

git switch -c、git checkout -b、git branch --track

```sh
## 该命令创建本地分支跟踪分支<本地分支名>，并从远程分支<远程主机名>/<远程分支名>拉取代码。
git switch -c <本地分支名> <远程主机名>/<远程分支名>
git checkout -b <本地分支名> <远程主机名>/<远程分支名>
git branch --track <本地分支名> <远程主机名>/<远程分支名>
```



### 5.从远程仓库克隆

```sh
git clone [远端地址]
```

![image-20211205231402105](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052314159.png)

克隆成功! 克隆后的目录和远端是一样的(一般克隆操作只需要使用一次就可以)

![image-20211205231438643](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052314708.png)

### 6.从远程仓库抓取和拉取

- ==**fetch抓取**, 将仓库里的更新都抓取到本地,**但是不进行合并**==
  - 如果不指定远端名称和分支, 则抓取所有分支修改

```sh
git fetch [remote name] [branch name]
```

- ==**pull拉取**, 将远程仓库的修改拉取到本地并**自动进行合并**,类似于: **pull = fetch + merge**==
  - 如果不指定远端名称和分支, 则抓取所有分支修改并自动合并

```sh
git pull 				#抓取并自动合并
```

![image-20211205233037566](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052330736.png)

![image-20211205233320577](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052333667.png)

### 7.解决合并冲突

发送冲突的情况:

​		在一段时间，A、B用户修改了同一个文件，且修改了同一行位置的代码，此时会发生合并冲突。A用户在本地修改代码后优先推送到远程仓库，此时B用户在本地修订代码，提交到本地仓库后，==也需要推送到远程仓库，此时B用户晚于A用户，**故需要先拉取远程仓库的提交，经过合并后才能推送到远端分支**==,如下图所示。

![image-20211205233613742](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052336876.png)

在B用户拉取代码时，因为A、B用户同一段时间修改了同一个文件的相同位置代码，故会发生合并冲突。
**远程分支也是分支，所以合并时冲突的解决方式也和解决本地分支冲突相同相同**，但是解决冲突时需要在本地解决

![image-20211205234559783](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052345871.png)

此时需要先pull然后在push

![image-20211205234655331](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052346395.png)

![image-20211205234817228](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052348286.png)

![image-20211205235018313](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052350400.png)

----





# 八. Git其他操作

## 1. 恢复==暂存区==的指定文件到==工作区==：git checkout 

```sh
## 恢复暂存区的指定文件到工作区
$ git checkout -- [file]
$ git checkout [file]

# 恢复暂存区的所有文件到工作区
$ git checkout .

# 恢复某个commit的指定文件到暂存区和工作区
$ git checkout [commit] [file]

## 注意：git add然后git commit后，认为暂存区和本地仓库一致。克隆文件下来时，认为暂存区和远程仓库一致
```

![image-20211222211955883](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222119018.png)

```sh
git checkout -- [filename]		#将filename文件从暂存区恢复到工作区.会导致工作区修改丢失, 使用时慎重
git checkout [filename]			#将filename文件从暂存区恢复到工作区.会导致工作区修改丢失, 使用时慎重
git checkout .					#将暂存区的所有文件恢复到工作区,会导致工作区修改丢失, 使用时慎重
```

![image-20211222212856703](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222128810.png)

![image-20211222213537134](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222135221.png)

![image-20211222213715025](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222137094.png)



## 2. 在远程仓库新建分支

git是无法直接在远程仓库直接新建分支的, 

但是可以通过**新建本地分支+推送本地分支**到远程达到新建远程分支目的

**git branch     +     git push**

- 在本地创建develop分支

  ```sh
  $ git branch develop
  ```

- 将创建的develop分支推送到远端仓库: 远程没有develop分支,但是将本地的develop分支推送到远端仓库, 就会在远程仓库中新建一个develop分支

  ```sh
  $ git push origin develop 		#将本地的提交到远程仓库，如果远程没有相依的分支则创建
  ```

![image-20211222223012599](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222230741.png)

## 3.删除远程仓库的分支

**git push origin --delete  [name]**

仅仅删除==远程仓库==的叫[name]的分支,  ==同名的本地分支不会被删除==, 要删除本地同名的本地分支还需要单独删除

```sh
$ git push origin --delete test
```

事先已经创建好了远程分支: test,  feature

![image-20211222225403709](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222254823.png)

## 4.用本地分支追踪远程仓库分支(建立追踪关系)

 建立当前分支与指定远程分支的追踪关系，但不会拉取代码。

**git branch --set-upstream-to <远程主机名>/<远程分支名>**

```sh
## 建立当前分支与指定远程分支的追踪关系，但不会拉取代码。参数"-u"和"--set-upstream-to"同样的意思。
$ git branch -u <远程主机名>/<远程分支名>
$ git branch --set-upstream-to <远程主机名>/<远程分支名>

==================================================
$ git push --set-upstream <远程主机名> <远程分支名>   #在push的同时也建立当前分支与的远端分支的追踪关系（会新建远程分支）
```

![image-20211222231139016](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222311166.png)



## 5.删除 git branch -r 列表中的追踪分支

**git branch -dr  <origin>/<branch-name>**  ==没有删除远程分支，只是删除 git branch -r 列表中的追踪分支。==

```sh
git branch -dr origin/feature	#并不是删除远程分支, 仅仅是删除git branch -r中的追踪分支
```

![image-20211222233617863](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222336014.png)

## 6.把远程分支的最新情况拉取到本地

**git fetch -p**

```sh
$ git fetch -p
```

![image-20211222234602222](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112222346324.png)

## 7.创建本地分支来跟踪并拉取远程分支

```sh
## 该命令创建本地分支跟踪分支<本地分支名>，并从远程分支<远程主机名>/<远程分支名>拉取代码。
git switch -c <本地分支名> <远程主机名>/<远程分支名>
git checkout -b <本地分支名> <远程主机名>/<远程分支名>
git branch --track <本地分支名> <远程主机名>/<远程分支名>
```

![image-20211223000106431](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112230001575.png)



更多更详细教程参考易百教程： https://www.yiibai.com/git

