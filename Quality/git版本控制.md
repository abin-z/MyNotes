# git分布式版本控制系统

[**git原理图解**](https://www.cnblogs.com/cb0327/p/5066685.html)

git是一个分布式版本控制系统, **版本控制**是一种记录一个或若干文件内容变化，以便将来查阅特定版本修订情况的系统。

在本书所展示的例子中，我们对保存着软件源代码的文件作版本控制，但实际上，**可以对任何类型的文件进行版本控制**。

快速上手: https://www.yiibai.com/git/git_basic_concepts.html



## 版本控制分类

### 1. 本地版本控制

---

许多人习惯用复制整个项目目录的方式来保存不同的版本，或许还会改名加上备份时间以示区别。 这么做唯一的好处就是简单，但是特别容易犯错。 有时候会混淆所在的工作目录，一不小心会写错文件或者覆盖意想外的文件。

为了解决这个问题，人们很久以前就开发了许多种本地版本控制系统，大多都是采用某种简单的数据库来记录文件的历次更新差异。

![img](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290025006.png)

其中最流行的一种叫做 *RCS*，现今许多计算机系统上都还看得到它的踪影。 甚至在流行的 Mac OS X 系统上安装了开发者工具包之后，也可以使用 `rcs` 命令。 它的工作原理是在硬盘上保存补丁集(补丁是指文件修订前后的变化)；通过应用所有的补丁，可以重新计算出各个版本的文件内容。



### 2. 集中化的版本控制系统

---

**代表作: SVN**

接下来人们又遇到一个问题，如何让在不同系统上的开发者协同工作？ 于是，集中化的版本控制系统(Centralized Version Control Systems，简称 *CVCS*)应运而生。 这类系统，诸如 *CVS*、*Subversion(SVN)* 以及 *Perforce* 等，都有一个单一的集中管理的服务器，保存所有文件的修订版本，而协同工作的人们都通过客户端连到这台服务器，取出最新的文件或者提交更新。多年以来，这已成为版本控制系统的标准做法。

![img](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290026057.png)

这种做法带来了许多好处，特别是相较于老式的本地 *VCS* 来说。 现在，每个人都可以在一定程度上看到项目中的其他人正在做些什么。 而管理员也可以轻松掌控每个开发者的权限，并且管理一个 *CVCS* 要远比在各个客户端上维护本地数据库来得轻松容易。

事分两面，有好有坏。 这么做最显而易见的**缺点是中央服务器的单点故障**。 如果宕机一小时，那么在这一小时内，谁都无法提交更新，也就无法协同工作。 如果中心数据库所在的磁盘发生损坏，又没有做恰当备份，毫无疑问您将丢失所有数据——包括项目的整个变更历史，只剩下人们在各自机器上保留的单独快照。本地版本控制系统也存在类似问题，只要整个项目的历史记录被保存在单一位置，就有丢失所有历史更新记录的风险。



### 3. 分布式版本控制系统

---

**代表作是git**

于是分布式版本控制系统(Distributed Version Control System，简称 *DVCS*)面世了。 在这类系统中，像 *Git*、*Mercurial*、*Bazaar* 以及 *Darcs* 等，客户端并不只提取最新版本的文件快照，而是把代码仓库完整地镜像下来。 这么一来，任何一处协同工作用的服务器发生故障，事后都可以用任何一个镜像出来的本地仓库恢复。 因为每一次的克隆操作，实际上都是一次对代码仓库的完整备份。如下图所示 -

![img](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290026467.png)

更进一步，许多这类系统都可以指定和若干不同的远端代码仓库进行交互。藉此，你就可以在同一个项目中，分别和不同工作小组的人相互协作。可以根据需要设定不同的协作流程，比如层次模型式的工作流，而这在以前的集中式系统中是无法实现的。



**分布式相比于集中式的最大区别在于开发者可以提交到本地，每个开发者通过克隆（git clone），在本地机器上拷贝一个完整的Git仓库。**





# git的下载安装:

git安装配置: https://www.yiibai.com/git/git_environment.html



### git使用前的配置

Git 自带一个 `git config` 的工具来帮助设置控制 Git 外观和行为的配置变量。 这些变量存储在三个不同的位置：

`/etc/gitconfig` 文件: 包含**系统上每一个用户及他们仓库的通用配置**。 如果使用带有 `--system` 选项的 `git config` 时，它会从此文件读写配置变量。

`~/.gitconfig` 或 `~/.config/git/config` 文件：**只针对当前用户。 可以传递`--global` 选项让 Git 读写此文件。**

**当前使用仓库的 Git 目录中的 `config` 文件(就是 `.git/config`)：针对该仓库。**

每一个级别覆盖上一级别的配置，所以 `.git/config` 的配置变量会覆盖 `/etc/gitconfig` 中的配置变量。

在 Windows 系统中，Git 会查找 `$HOME` 目录下(一般情况下是 `C:\Users\$USER`)的 `.gitconfig` 文件。 Git 同样也会寻找 `/etc/gitconfig` 文件，但只限于 MSys 的根目录下，即安装 Git 时所选的目标位置。

### 用户信息

当安装完 Git 应该做的第一件事就是设置用户名称与邮件地址。这样做很重要，因为每一个 Git 的提交都会使用这些信息，并且它会写入到每一次提交中，不可更改：

```shell
$ git config --global user.name "abin"
$ git config --global user.email abin_z@163.com
```

再次强调，如果使用了 `--global` 选项，那么该命令只需要运行一次，因为之后无论你在该系统上做任何事情， Git 都会使用这些信息。 当你想针对特定项目使用不同的用户名称与邮件地址时，可以在那个项目目录下运行不使用 `--global` 选项的命令来配置。

![image-20211129005231063](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290052111.png)

修改后可以在文件中查看配置: `C:\Users\Abin\.gitconfig`  (windows下)

![image-20211129005355014](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290053054.png)



### 检查配置信息

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

![image-20211129005854658](https://gitee.com/abin_z/pic_bed/raw/master/img/202111290058764.png)



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

### 获取帮助

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







# Git 工作流程图

**说明：**

- workspace：工作区
- staging area：暂存区/缓存区
- local repository：版本库或本地仓库
- remote repository：远程仓库

![image-20211130215157473](https://gitee.com/abin_z/pic_bed/raw/master/img/202111302151592.png)

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
```



一个简单的操作步骤：

```sh
$ git init    		#初始化仓库。
$ git add .    		#添加文件到暂存区。
$ git commit  		#将暂存区内容添加到本地仓库中。
```

### 创建仓库命令

下表列出了 git 创建仓库的命令：

| 命令        | 说明                                           |
| :---------- | :--------------------------------------------- |
| `git init`  | 初始化仓库, 文件夹中会出现一个  .git  的文件夹 |
| `git clone` | 拷贝一份远程仓库，也就是下载一个项目。         |

------

### 提交与修改

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

### 提交日志

| 命令               | 说明                                 |
| :----------------- | :----------------------------------- |
| `git log`          | 查看历史提交记录                     |
| `git blame <file>` | 以列表形式查看指定文件的历史修改记录 |

### 远程操作

| 命令         | 说明               |
| :----------- | :----------------- |
| `git remote` | 远程仓库操作       |
| `git fetch`  | 从远程获取代码库   |
| `git pull`   | 下载远程代码并合并 |
| `git push`   | 上传远程代码并合并 |



### git基础操作指令

Git工作目录下对于文件的修改(增加、删除、更新)会存在几个状态，这些修改的状态会随着我们执行Git的命令而
发生变化。

![image-20211130230947835](https://gitee.com/abin_z/pic_bed/raw/master/img/202111302309959.png)







# Git 分支管理

几乎每一种版本控制系统都以某种形式支持分支。使用分支意味着你可以从开发主线上分离开来，然后在不影响主线的同时继续工作。

有人把 Git 的分支模型称为**必杀技特性**，而正是因为它，将 **Git** 从版本控制系统家族里区分出来。

**列出分支基本命令：**

```
git branch
```

**创建分支命令：**

```
git branch (branchname)
```

**切换分支命令:**

```
git checkout (branchname)
```

当你切换分支的时候，Git 会用该分支的最后提交的快照替换你的工作目录的内容， 所以多个分支不需要多个目录。

**合并分支命令:**

```
git merge 
```

**删除分支命令：**

```
git branch -d (branchname)
```





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



