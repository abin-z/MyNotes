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

# 不使用 --global 参数就是设置当前项目的git配置
$ git config user.name "abin"
$ git config user.email abin_z@163.com
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
alias git-log='git log --pretty=oneline --all --graph --abbrev-commit'

#用于输出当前目录所有文件的基本信息
alias ll='ls -al'
```

### 6. 解决gitbash中文乱码问题

1. 打开gitbash执行以下的命令:

   ```sh
   git config --global core.quotepath false
   ```

2. ${git_home}/etc/bash.bashrc 文件最后添加如下内容:

   ```sh
   export LANG="zh_CN.UTF-8"
   export LC_ALL="zh_CN.UTF-8"
   ```


### 7. 解决gitk中文乱码问题

1. 打开gitbash执行一下的命令

   ```sh
   git config --global gui.encoding utf-8
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
| `git show`   | 显示各种类型的对象, 常用于查看提交差异   |
| `git commit` | 提交暂存区到本地仓库。                   |
| `git reset`  | 回退版本。                               |
| `git rm`     | 删除工作区文件。                         |
| `git mv`     | 移动或重命名工作区文件。                 |
| `git tag`    | 对版本库做标记, 它是指向某个commit的指针 |

#### git log   #日志

git log 命令是 Git 中用于查看提交历史的命令

```sh
git log		#可以按键盘空格/字母b键将信息向下/向上翻页，也可以按键盘向上/向下箭头向上/向下按行滚动

git log –p	#输出每一个commit之间的差异信息

git log --stat	#输出每一个commit之间的差异统计信息

git log--oneline	#输出历史commit的简短信息

git log：显示当前分支（HEAD）的全部提交记录，按照时间倒序排列。
git log <commit>：从指定的提交记录开始显示，按照时间倒序排列。
git log --follow <file>：显示指定文件的提交历史，并显示该文件的移动或重命名记录。
git log --pretty=<format>：使用指定的格式输出提交信息。常用的格式有 %H（提交哈希值）、%h（简短的提交哈希值）、%an（作者名）、%ae（作者邮箱）、%cn（提交者名）、%ce（提交者邮箱）、%s（提交说明）等。
git log --grep=<pattern>：仅显示包含指定模式的提交记录，模式可以是正则表达式。
git log --author=<name>：仅显示指定作者的提交记录。
git log --oneline：将每个提交记录压缩为一行，只显示提交哈希值和提交说明。
git log --graph：在提交记录前面绘制 ASCII 图形表示提交记录之间的关系。
git log --since=<date>：仅显示指定日期之后的提交记录，日期的格式可以是 “YYYY-MM-DD” 或 “<n> days ago” 等。
```

![image-20240523221717862](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523221717862.png)

![image-20240523221807259](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523221807259.png)



#### git diff  #差异

- 当合并分支时, 如果出现了冲突, 也可以使用`git diff`查看是那些地方出现了冲突
- 查看当前分支修改了那些内容`git diff`

```sh
git diff			#显示工作区与暂存区的差异

git diff --cached	#显示暂存区与历史版本库的差异

git diff HEAD~2		#显示工作区与最新提交第二父提交的差异

git diff HEAD~2 --a.txt		#显示工作区与最新提交第二父提交中a.txt文件差异

git diff –cachedHEAD~1		#显示暂存区与历史版本库最新提交第一父提交的差异

git diff HEAD HEAD~2		#显示HEAD指向的历史提交和其第二父提交之间的差异

git diff HEAD HEAD~2-- a.txt	#显示HEAD指向的历史提交和其第二父提交中a.txt之间的差异
```

![image-20240523212427403](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523212427403.png)

#### git show #显示

显示一个或多个对象（blob、树、标签和提交）。

- 对于提交，它显示日志消息和文本差异。它还以 git diff-tree --cc 生成的特殊格式呈现合并提交。
- 对于标签，它显示标签消息和引用的对象。
- 对于树，它显示名称（相当于带有 --name-only 的 git ls-tree）。
- 对于纯 blob，它显示纯内容。

```sh
git show [commit_id]   	#查看某次历史提交信息的完整信息

git show HEAD			#查看HEAD标签当前指向的提交的完整信息

git show master 		#查看master分支最新一次提交的完整信息

git show master^或git show master~  #查看master分支最新一次提交的父提交的完整信息

git show master^2		#查看master分支最新一次提交的第二个父提交（也就是父提交的父提交）的完整信息
```

![image-20240523220652903](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523220652903.png)

### 3. 查看提交日志

| 命令               | 说明                                 |
| :----------------- | :----------------------------------- |
| `git log`          | 查看历史提交记录                     |
| `git blame <file>` | 以列表形式查看指定文件的历史修改记录 |

![image-20240523222812592](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523222812592.png)

### 4. 远程操作

| 命令         | 说明               |
| :----------- | :----------------- |
| `git remote` | 远程仓库操作       |
| `git fetch`  | 从远程获取代码库   |
| `git pull`   | 下载远程代码并合并 |
| `git push`   | 上传远程代码并合并 |

### 5. reset版本回退

git reset 命令用于`回退版本`，可以指定退回某一次提交的版本。

要想用好reset命令，必须深入理解它的三个参数:  `--soft`，`--mixed（默认）`，`--hard`

#### git reset --soft

如下图，soft参数是指将本地仓回滚到Y版本，但是暂存区和工作区保持不变。此时本地仓回滚到Y版本号commit完成的那一刻。

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/v2-e5d1963d5c4e164f433178ff79bc5c2a_r.jpg)

#### git reset --mixed 

```text
git reset --mixed  或者  git reset
```

这是默认参数。如下图 --mixed 表示本地仓和暂存区，都回滚到Y版本号。工作区代码不受影响。

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/v2-813f0be2f7143336fd194cd7d6244e11_r.jpg)

#### git reset --hard

本地仓库、暂存区、工作区，三区都回滚。

![img](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/v2-e9e0f4dd96f095a4290daa3f83a2abf1_r.jpg)

作用: 不同提交版本之间的切换

```sh
git reset [--soft | --mixed | --hard] [HEAD]
# --soft 回退到某个版本 。是指将本地仓回滚到指定版本，但是暂存区和工作区保持不变
git reset --soft <commitID> 

# --mixed 为默认，可以不用带该参数，用于重置暂存区的文件与上一次的提交(commit)保持一致，工作区文件内容保持不变。
git reset --mixed <commitID> 	

# --hard 参数撤销工作区中所有未提交的修改内容，将暂存区与工作区都回到上一次版本，并删除之前的所有信息提交：
git reset --hard <commitID>    	
```

```sh
# 回退所有内容到上一个版本
git reset HEAD^

# 回退test.txt这个文件的版本到上一个版本
git reset HEAD^ test.txt

# 向前回退到第3个版本
git reset  HEAD~3

# 回退到某个版本51363e6
git reset 51363e6
```

- commitID 可以使用 `git log` 或者是`git-log` 查看

- 如何查看已经所有已提交的记录?  


```sh
git reflog			#这个指令可以看到已经删除的提交记录, 包括 git reset --hard
```



### 6. tag标签 

- git仓库的tag是给仓库历史中的某一个提交打上标签，以示重要, 它指向某个commit id标记的快照记录指针.
- tag主要用于发布版本的管理，一个版本发布之后，我们可以为git打上 v.1.0.1 v.1.0.2 …这样的标签。
- tag 对应某次commit, 是一个点，是不可移动的。
- 创建 tag 是基于本地分支的 commit，而且与分支的推送是两回事，就是说分支已经推送到远程了，但是你的 tag 并没有，如果想把 tag 推送到远程分支上，需要另外执行 tag 的推送命令。

**tag 常用命令:**

1. #### **创建tag标签**

   Git 支持两种标签：==轻量标签（lightweight)==与==附注标签（annotated)==。

   轻量标签很像一个不会改变的分支——它只是某个特定提交的引用。

   而附注标签是存储在 Git 数据库中的一个完整对象， 它们是可以被校验的，其中包含打标签者的名字、电子邮件地址、日期时间， 此外还有一个标签信息，并且可以使用 GNU Privacy Guard （GPG）签名并验证。 通常会建议创建附注标签，这样你可以拥有以上所有信息。但是如果你只是想用一个临时的标签， 或者因为某些原因不想要保存这些信息，那么也可以用轻量标签。

   - #### 附注标签

     在 Git 中创建附注标签十分简单。 最简单的方式是当你在运行 `tag` 命令时指定 `-a` 选项：

   ```sh
   git tag -a <tagname> -m <comment>	# 创建本地附注tag, -a 指定标签名, -m 指定说明信息
   ```

   `-m` 选项指定了一条将会存储在标签中的信息。 如果没有为附注标签指定一条信息，Git 会启动编辑器要求你输入信息。

   ```sh
   git show <tagname>	 	# show命令可以看到标签信息和与之对应的提交信息
   ```

   通过使用 `git show <tagname>` 会输出显示了打标签者的信息、打标签的日期时间、附注信息，然后显示具体的提交信息:

   ```sh
   Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
   $ git tag -l
   v0.11
   v1.12
   
   Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
   $ git show v1.12
   tag v1.12
   Tagger: abin <abin_z@163.com>
   Date:   Thu Aug 10 22:43:19 2023 +0800
   
   标注tag说明, 版本号v1.12, 测试tag指令
   
   commit 1e1f9aecb47dd0671a64bd84138172b96869e45a (HEAD -> master, tag: v1.12)
   Author: abin <abin_z@163.com>
   Date:   Thu Aug 10 22:42:36 2023 +0800
   
       修改testFile.txt文件
   ```

   - #### 轻量标签

     另一种给提交打标签的方式是使用轻量标签。 轻量标签本质上是将提交校验和存储到一个文件中——没有保存任何其他信息。 创建轻量标签，不需要使用 `-a`、`-s` 或 `-m` 选项，只需要提供标签名字：

     ```sh
     git tag <tagname>			# 创建轻量级标签，不用-a，-m等参数
     ```

     这时，如果在标签上运行 `git show <tagname>` ，你不会看到额外的标签信息。 命令只会显示出提交信息：

     ```sh
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git tag v1.13_lw
     
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git tag
     v0.11
     v1.12
     v1.13_lw
     
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git show v1.13_lw
     commit ced5c08e34686bf2ddc6b9c7711b79bacf8fce8d (HEAD -> master, tag: v1.13_lw)
     Author: abin <abin_z@163.com>
     Date:   Thu Aug 10 22:57:14 2023 +0800
     
         修改testFile.txt文件
     ```

   - #### 给指定的commit打Tag

     你也可以对过去的提交打标签。打Tag不必要在head之上，**也可在之前的版本上打**，这需要你知道某个提交对象的校验和（通过git log获取）。

     ```sh
     git tag -a <tagname> <commitID>		# 给指定的commitID打tag
     ```

     ```sh
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git tag -a v0.1 766f0ae
     
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git tag
     v0.1
     v0.11
     v1.12
     v1.13_lw
     
     Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
     $ git show v0.1
     tag v0.1
     Tagger: abin <abin_z@163.com>
     Date:   Thu Aug 10 23:15:47 2023 +0800
     
     测试在指定commitID上添加tag标签
     
     commit 766f0ae17925916f572745c13136234cee7e3298 (tag: v0.1)
     Author: zhangbin <abin_z@163.com>
     Date:   Wed Dec 22 16:29:26 2021 +0800
     
         abc.txt
     ```

 2. ### 列出标签

- 在 Git 中列出已有的标签非常简单，只需要输入 `git tag` （可带上可选的 `-l` 选项 `--list`）：

  ```sh
  git tag 			# 查看本地所有tag列表
  git tag --list 		# 查看本地所有tag列表
  git tag -l 			# 同理查看本地所有tag列表
  ```

  这个命令以字母顺序列出标签，但是它们显示的顺序并不重要。

  你也可以按照特定的模式查找标签。 例如，Git 自身的源代码仓库包含标签的数量超过 500 个。 如果只对 1.8.5 系列感兴趣，可以运行：

  ```sh
  $ git tag -l "v1.8.5*"			# 只查看v1.8.5开头的tag标签, *号为通配符
  v1.8.5
  v1.8.5-rc0
  v1.8.5-rc1
  v1.8.5-rc2
  v1.8.5-rc3
  v1.8.5.1
  v1.8.5.2
  v1.8.5.3
  v1.8.5.4
  v1.8.5.5
  ```

  

3. ### 共享标签

- 默认情况下，`git push` 命令**并不会**传送标签到远程仓库服务器上。 在创建完标签后你**必须显式地推送标签到共享服务器上**。 这个过程就像共享远程分支一样——你可以运行 `git push origin <tagname>`。

  ```sh
  git push origin <tagname>			# 推送一个本地标签到远程仓库origin
  ```

  ```sh
  Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
  $ git tag -l "v1*"
  v1.12
  v1.13_lw
  
  Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
  $ git push origin v1.12
  Enumerating objects: 6, done.
  Counting objects: 100% (6/6), done.
  Delta compression using up to 6 threads
  Compressing objects: 100% (3/3), done.
  Writing objects: 100% (4/4), 470 bytes | 156.00 KiB/s, done.
  Total 4 (delta 1), reused 0 (delta 0), pack-reused 0
  remote: Powered by GITEE.COM [GNK-6.4]
  To gitee.com:abin_z/git-demo.git
   * [new tag]         v1.12 -> v1.12
  
  #效果如下图:
  ```

  ![image-20230810233137483](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20230810233137483.png)

- 如果想要一次性推送很多标签，也可以使用带有 `--tags` 选项的 `git push` 命令。 这将会把所有不在远程仓库服务器上的标签全部传送到那里。

  ```sh
  git push <remote> --tags			# 推送全部未推送过的本地标签(包括轻量标签),到远程仓库
  ```

  ```sh
  Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
  $ git push origin --tags
  Enumerating objects: 7, done.
  Counting objects: 100% (7/7), done.
  Delta compression using up to 6 threads
  Compressing objects: 100% (4/4), done.
  Writing objects: 100% (5/5), 607 bytes | 202.00 KiB/s, done.
  Total 5 (delta 1), reused 0 (delta 0), pack-reused 0
  remote: Powered by GITEE.COM [GNK-6.4]
  To gitee.com:abin_z/git-demo.git
   * [new tag]         v0.1 -> v0.1
   * [new tag]         v0.11 -> v0.11
   * [new tag]         v1.13_lw -> v1.13_lw
  
  # 效果如下图:
  ```

  ![image-20230810233911858](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20230810233911858.png)

4. ### 删除标签

   要删除掉你本地仓库上的标签，可以使用命令 `git tag -d <tagname>`。

   ```sh
   git tag -d <tagname>				# 删除本地仓库上的标签, 此命令不会删除远程仓库中已存在的标签
   ```

    例如，可以使用以下命令删除一个轻量标签：

   ```sh
   Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
   $ git tag -d v1.13_lw
   Deleted tag 'v1.13_lw' (was ced5c08)
   
   Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
   $ git tag
   v0.1
   v0.11
   v1.12
   ```

   ![image-20230810234606577](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20230810234606577.png)

   - 注意: **上述命令并不会从任何远程仓库中移除这个标签**，你必须用 `git push <remote> :refs/tags/<tagname>` 来更新你的远程仓库：

   ```sh
   git push <remote> :refs/tags/<tagname>
   ```

   ```sh
   Abin@DESKTOP-TFU43J6 MINGW64 /f/gitDemo (master)
   $ git push origin :refs/tags/v1.13_lw
   
   remote: Powered by GITEE.COM [GNK-6.4]
   To gitee.com:abin_z/git-demo.git
    - [deleted]         v1.13_lw
   ```

   ![image-20230810234935768](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20230810234935768.png)





### 6. git基础操作指令

Git工作目录下对于文件的修改(增加、删除、更新)会存在几个状态，这些修改的状态会随着我们执行Git的命令而
发生变化。

![image-20211130230947835](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202111302309959.png)

##  git基础指令练习

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

- 演示tag指令,  tag是git版本库的一个标记，指向某个commit的指针。

```sh
git tag 			# 查看本地所有 tag
```





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

运行如下类似的命令:

```bash
git rm -r --cached .    # 取消文件跟踪
git add .				# 添加跟踪(新增的.gitignore文件会生效)	
git commit -m "add gitignore"	# 提交代码
git push origin master			# 推送代码至远程仓库
```





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



### 8. git revert (还原)

git revert 撤销某次操作，**此次操作之前和之后的commit和history都会保留，并且把这次撤销作为一次最新的提交**

git revert命令可以被认为是“撤消”命令。但是它不是传统的撤消操作。不是从项目历史中删除提交，而是计算出如何反转要撤销的提交所引入的更改，并附加一个新的提交及生成的反向内容。这种方式可以防止 Git 丢失历史记录，这对于我们的修订历史记录的完整性和可靠的协作非常重要。

当想要应用项目历史中提交的逆向时，应该使用 revert。如果我们正在跟踪错误并发现它是由单个提交引入的。此时我们无需手动进入、修复并提交新快照，而是可以使用git revert自动为我们完成所有这些工作。



revert分为 revert 普通commit 和 revert merge commit

- **对于普通的commit**，使用 `git revert <commit id>` 即可，git 会生成一个新的 commit，将指定的 commit 内容从当前分支上撤除

- **对于merge commit，需要添加 `-m` 选项以代表这次 revert 的是一个 merge commit**,  但如果直接使用 `git revert <commit id>`，git 也不知道到底要撤除哪一条分支上的内容，这时需要指定一个 parent number 标识出"主线"，主线的内容将会保留，而另一条分支的内容将被 revert。 如上面的例子中，从 git show 命令的结果中可以看到，merge commit 的 parent 分别为 `d98dc` 和 `ca82c`，其中 `d98dc` 代表 master 分支（从图中可以看出），`ca82c` 代表 will-be-revert 分支。需要注意的是 -m 选项接收的参数是一个数字，数字取值为 1 和 2，也就是 Merge 行里面列出来的第一个还是第二个，其含义用来保留某个分支。

- git revert的注意事项:  [关于git revert的一点坑](https://juejin.cn/post/7145677983578062861)

  ![image-20240523230820541](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523230820541.png)

```sh
git revert <commit id> #还原某些现有提交
```

![image-20240523224654700](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523224654700.png)

```sh
# 执行撤销 5f09a20 的提交
git revert 5f09a20
```

![image-20240523225033020](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523225033020.png)

再次查看`git-log`

![image-20240523225601724](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523225601724.png)



### 9. git cherry-pick 

通过 `cherry-pick` 命令，Git 可以将其他任何分支中的选定提交合并到**当前的 Git HEAD 分支**中。

```sh
git cherry-pick <commit sha>	# 将其他分支的commitID的提交合并到当前分支
```

在执行 `git merge` 或 `git rebase` 时，一个分支的所有提交都会被合并。而 `cherry-pick` 命令则允许你选择单个提交进行整合。

区别图示如下:

```sh
使用 merge 的情况: 在执行 merge 或 rebase 时，一个分支的所有提交都会被整合。
```

![使用 merge 或 rebase 的情况](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/3034537-20230812113520489-1069727001.png)

```sh
使用 cherry-pick 的情况: 允许你选择个别提交进行整合。在本例中，只有 C2 被整合到主分支，而不是 C4。
```

![使用 cherry-pick 的情况](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/3034537-20230812113520658-544623595.png)

案例:

当前在master分支上

![image-20240523232821561](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523232821561.png)

```sh
# 执行 git cherry-pick 0ee5634, 从develop分支上合并0ee5634这一次提交
git cherry-pick 0ee5634
# 合并后的结果如下图
```

![image-20240523233508301](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240523233508301.png)

**什么时候用 Cherry-pick?**

简而言之就是：**尽量少用**。之所以要尽量少用 cherry-pick，是因为它很容易产生 "重复"提交：当你使用 cherry-pick 将一个提交整合到 HEAD 分支时，Git 必须创建一个内容完全相同的新提交。不过，这是一个全新的提交对象，有自己的 SHA 标识符。同时也会失去跟踪提交历史的能力。

如果你不按顺序提交了很多提交，这些提交就会被记录在你的分支中，这可能会导致你的 Git 分支出现不理想的结果。

只要能用传统的合并或重置来整合，就应该这么做。Cherry-pick 应保留给不可能这样做的情况，例如必须创建 Hotfix 或只想从一个废弃的分支中保存一个或几个提交。



### 10. git stash (暂存) 

git stash：将本地没提交的内容进行缓存并从当前分支移除。缓存的数据结构为堆栈，先进后出。

> **注意**：git commit的内容不会被缓存， 但git add的内容会被缓存。**stash 只会操作被git追踪的文件**，也就是说，如果有新增的文件，需要进行git add [文件名]让git追踪该文件，再进行stash就可以了。

| 命令名                          | 作用                                                        |
| ------------------------------- | ----------------------------------------------------------- |
| git stash                       | 隐藏当前的工作现场, 此时, git status的结果是 clean          |
| git stash list                  | 查看所有隐藏, 每一行的冒号前面的字符串就是标识此隐藏的id    |
| git stash pop                   | 恢复最新的stash进度到工作区, 并删除栈中的stash              |
| git stash pop stash@{stash_id}  | 恢复指定的stash进度到工作区, 并删除栈中的stash              |
| git stash apply                 | 恢复最新的进度到工作区, 不会删除栈中的stash                 |
| git stash drop stash@{stash_id} | 从暂存列表中删除一个特定的暂存。                            |
| git stash clear                 | 清空暂存区的所有stash, **谨慎使用(不当使用会导致更改丢失)** |

[git stash 命令实用指南](https://linux.cn/article-13293-1.html)

- 我们经常会遇到这样的情况：

> 正在dev分支开发新功能，做到一半时有人过来反馈一个bug，让马上解决，但是新功能做到了一半你又不想提交，这时就可以使用git stash命令先把当前进度保存起来，然后切换到另一个分支去修改bug，修改完提交后，再切回dev分支，使用git stash pop来恢复之前的进度继续开发新功能。

分支有改变时不提交又不能切换分支，如下：

![image-20240524220548423](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240524220548423.png)

使用 `git stash` 保存当前工作进度，会把暂存区和工作区的改动保存起来。执行完这个命令后，在运行git status命令，就会发现当前是一个干净的工作区，没有任何改动。使用`git stash save 'message...'`可以添加一些注释

![image-20240524221947716](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240524221947716.png)

它会保存当前工作进度，会把暂存区和工作区的改动保存到一个未完结变更的堆栈中；执行完这个命令后，在运行 `git status` 命令，就会发现当前是一个干净的工作区，没有任何改动。

> 1. `git stash` 是本地的，不会上传到服务器上；
> 2. 可以通过使用`git stash save 'message...'`可以添加一些注释。

下面是使用 `git stash` 时要遵循的顺序：

1. 将修改保存到分支 A。
2. 运行 `git stash`。
3. 签出分支 B。
4. 修正 B 分支的错误。
5. 提交并（可选）推送到远程。
6. 回到分支 A
7. 运行 `git stash pop` 来取回你的暂存的改动。

![image-20240524225511153](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240524225511153.png)



### 11. git rebase (谨慎使用) 

#### 理解rebase命令

`git rebase` 命令的文档描述是 `Reapply commits on top of another base tip`，从字面上理解是「在另一个基端之上重新应用提交」，这个定义听起来有点抽象，换个角度可以理解为「将分支的基础从一个提交改成另一个提交，使其看起来就像是从另一个提交中创建了分支一样」，如下图：

![git-rebase-visual](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/git-rebase-visual.png)

假设我们从 `Master` 的提交 A 创建了 `Feature` 分支进行新的功能开发，这时 A 就是 `Feature` 的基端。接着 `Matser` 新增了两个提交 B 和 C， `Feature` 新增了两个提交 D 和 E。现在我们出于某种原因，比如新功能的开发依赖 B、C 提交，需要将 `Master` 的两个新提交整合到 `Feature` 分支，为了保持提交历史的整洁，我们可以切换到 `Feature` 分支执行 `rebase` 操作：

```sh
git rebase master		# 在Feature分支上执行 git rebase master 操作
```

`rebase` 的执行过程是首先找到这两个分支（即当前分支 `Feature`、 `rebase` 操作的目标基底分支 `Master`） 的最近共同祖先提交 A，然后对比当前分支相对于该祖先提交的历次提交（D 和 E），提取相应的修改并存为临时文件，然后将当前分支指向目标基底 `Master` 所指向的提交 C, 最后以此作为新的基端将之前另存为临时文件的修改依序应用。

我们也可以按上文理解成将 `Feature` 分支的基础从提交 A 改成了提交 C，看起来就像是从提交 C 创建了该分支，并提交了 D 和 E。但实际上这只是「看起来」，在内部 Git 复制了提交 D 和 E 的内容，创建新的提交 D' 和 E' 并将其应用到特定基础上（A→B→C）。尽管新的 `Feature` 分支和之前看起来是一样的，但它是由全新的提交组成的。

**`rebase` 操作的实质是丢弃一些现有的提交，然后相应地新建一些内容一样但实际上不同的提交(commitID不同)。**

![image-20240524234743698](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240524234743698.png)

```sh
# 在develop分支上执行rebase操作
git rebase master
```

![image-20240524234755267](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20240524234755267.png)



#### rebase主要用途

`rebase` 通常用于重写提交历史。下面的使用场景在大多数 Git 工作流中是十分常见的：

- 我们从 `master` 分支拉取了一条 `feature` 分支在本地进行功能开发
- 远程的 `master` 分支在之后又合并了一些新的提交
- 我们想在 `feature` 分支集成 `master` 的最新更改



#### rebase 和 merge 的区别

以上场景同样可以使用 `merge` 来达成目的，但使用 `rebase` 可以使我们保持一个线性且更加整洁的提交历史。假设我们有如下分支：

```sh
  D---E feature
 /
A---B---C master
```

现在我们将分别使用 `merge` 和 `rebase`，把 `master` 分支的 B、C 提交集成到 `feature` 分支，并在 `feature` 分支新增一个提交 F，然后再将 `feature` 分支合入 `master` ，最后对比两种方法所形成的提交历史的区别。

- **使用 `merge`**

  1. 切换到 `feature` 分支： `git checkout feature`。
  2. 合并 `master` 分支的更新： `git merge master`。
  3. 新增一个提交 F： `git add . && git commit -m "commit F"` 。
  4. 切回 `master` 分支并执行快进合并： `git chekcout master && git merge feature`。

  执行过程如下图所示：

![Dec-30-2020-merge-example](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/Dec-30-2020-merge-example.gif)

我们将得到如下提交历史：

```sh
* 6fa5484 (HEAD -> master, feature) commit F
*   875906b Merge branch 'master' into feature
|\  
| | 5b05585 commit E
| | f5b0fc0 commit D
* * d017dff commit C
* * 9df916f commit B
|/  
* cb932a6 commit A
```

- **使用 `rebase`**

步骤与使用 `merge` 基本相同，唯一的区别是第 2 步的命令替换成： `git rebase master`。

执行过程如下图所示：

![Dec-30-2020-rebase-example](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/Dec-30-2020-rebase-example.gif)

我们将得到如下提交历史：

```sh
* 74199ce (HEAD -> master, feature) commit F
* e7c7111 commit E
* d9623b0 commit D
* 73deeed commit C
* c50221f commit B
* ef13725 commit A
```

可以看到，使用 `rebase` 方法形成的提交历史是完全线性的，同时相比 `merge` 方法少了一次 `merge` 提交，看上去更加整洁。



#### rebase上潜在弊端和反对意见

从以上场景来看 `rebase` 功能非常强大，但我们也需要意识到它不是万能的，甚至对新手来说有些危险，稍有不慎就会发现 `git log` 里的提交不见了，或者卡在 `rebase` 的某个步骤不知道如何恢复。

我们上面已经提到了 `rebase` 有保持整洁的线性提交历史的优点，但也需要意识到它有以下潜在的弊端：

- 如果涉及到已经推送过的提交，需要**强制推送**才能将本地 `rebase` 后的提交推送到远程。**因此绝对不要在一个公共分支（也就是说还有其他人基于这个分支进行开发）执行 `rebase`**，否则其他人之后执行 `git pull` 会合并出一条令人困惑的本地提交历史，进一步推送回远程分支后又会将远程的提交历史打乱，较严重的情况下可能会对你的人身安全带来风险。
- 对新手不友好，新手很有可能在交互模式中误操作「丢失」某些提交（但其实是能够找回的）。
- 假如你频繁的使用 `rebase` 来集成主分支的更新，一个潜在的后果是你会遇到越来越多需要合并的冲突。尽管你可以在 `rebase` 过程中处理这些冲突，但这并非长久之计，更推荐的做法是频繁的合入主分支然后创建新的功能分支，而不是使用一个长时间存在的功能分支。

另外有一些观点是我们应该尽量避免重写提交历史：

> 有一种观点认为，仓库的提交历史即是 记录实际发生过什么。 它是针对历史的文档，本身就有价值，不能乱改。 从这个角度看来，改变提交历史是一种亵渎，你使用 谎言 掩盖了实际发生过的事情。 如果由合并产生的提交历史是一团糟怎么办？ 既然事实就是如此，那么这些痕迹就应该被保留下来，让后人能够查阅。

以及频繁的使用 `rebase` 可能会使从历史提交中定位 bug 变得更加困难，详见 [Why you should stop using Git rebase](https://medium.com/@fredrikmorken/why-you-should-stop-using-git-rebase-5552bee4fed1)。

[git rebase 用法详解与工作原理](https://waynerv.com/posts/git-rebase-intro/)

[git rebase 变基](https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%8F%98%E5%9F%BA)





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
git push origin [分支名称] --force		#强制推送到分支，谨慎使用
```



# 七. Git远程仓库

## 常见的代码托管服务

**GitHub**（ 地址：https://github.com/ ）是一个面向开源及私有软件项目的托管平台，因为只支持Git 作为唯一的版本库格式进行托管，故名GitHub
**Gitee**（地址： https://gitee.com/ ）是国内的一个代码托管平台，由于服务器在国内，所以相比于GitHub，码云速度会更快
**GitLab** （地址： https://about.gitlab.com/ ）是一个用于仓库管理系统的开源项目，使用Git作为代码管理工具，并在此基础上搭建起来的web服务，一般用于在企业、学校等内部网络搭建git私服。

**Gitea** (地址: https://about.gitea.com/)是一个轻量级的DevOps平台软件，它支持Git托管、代码审查、团队协作、软件包注册和CI/CD等功能。与GitHub和GitLab相比，Gitea的一个显著特点是它提供了自托管的能力，这意味着用户可以完全控制自己的仓库和基础设施，而不需要依赖外部服务提供商。此外，Gitea的设计目标是易于安装和使用，它的性能出色，能够快速响应各种请求，保证用户体验



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
git remote add [远端仓库名] [https远程仓库地址]    #一般远端仓库名都为 origin
```

```sh
git remote add origin git@gitee.com:abin_z/git-demo.git		#origin仅仅是远端仓库名, 还没有远端分支名
```

![image-20211205224848724](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/202112052248800.png)



- **取消本地目录下关联的远程库**

  ```sh
  git remote remove [远程仓库名]    # 案例: git remote remove origin, 会取消本地仓库与远程仓库的关联
  ```



### 2.查看远程仓库

```sh
git remote 				#查看当前所有的远程仓库的名称
git remote -v			#查看远程仓库的名称和远程仓库的网址
```

![image-20221226233205747](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20221226233205747.png)

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

### 8.配置git代理(访问github)

#### 1. 配置 HTTP/HTTPS 代理

**配置步骤**

1. 打开终端（Command Prompt、PowerShell 或 Git Bash）。

2. 配置 HTTP 和 HTTPS 代理：

   ```bash
   git config --global http.proxy http://127.0.0.1:10809
   git config --global https.proxy http://127.0.0.1:10809
   ```

   - `127.0.0.1:10809` 为代理服务器的地址和端口。

3. 验证配置：

   ```bash
   git config --global --get http.proxy
   git config --global --get https.proxy
   ```

   - 应返回 `http://127.0.0.1:10809`。

4. 测试代理是否生效：

   ```bash
   git clone https://github.com/git/git.git
   ```

   - 如果可以正常克隆，说明代理配置成功。

**取消代理配置**

- 如果需要取消代理配置，执行以下命令：

  ```sh
  git config --global --unset http.proxy
  git config --global --unset https.proxy
  ```

- 或者清除所有代理配置：

  ```sh
  git config --global --remove-section http
  git config --global --remove-section https
  ```



#### 2. 仅对 GitHub 使用代理

**配置步骤**

1. 配置 GitHub 专用代理：

   ```sh
   git config --global http.https://github.com.proxy http://127.0.0.1:10809
   ```

   - 此配置仅对 `https://github.com` 的请求启用代理。

2. 验证配置：

   ```sh
   git config --global --get http.https://github.com.proxy
   ```

   - 应返回 `http://127.0.0.1:10809`。

3. 测试：

   - 克隆 GitHub 仓库：

     ```sh
     git clone https://github.com/git/git.git
     ```

   - 克隆其他仓库（如 GitLab）测试是否不使用代理：

     ```sh
     git clone https://gitlab.com/gitlab-org/git.git
     ```

4. 取消 GitHub 专用代理：

   ```sh
   git config --global --unset http.https://github.com.proxy
   ```

   

#### 3. 配置 SSH 协议通过代理

**SSH 默认行为**

- Git 使用 SSH 协议（如 `git@github.com:username/repository.git`）时，不会走 HTTP/HTTPS 代理。
- 需配置 SSH 客户端单独使用代理。

**配置步骤**

1. **检查代理类型**

   - 确认你的代理服务支持的协议（HTTP 或 SOCKS5）。
   - 如果是 SOCKS5 代理，配置可能会有所不同。

2. **编辑 SSH 配置文件**

   - 打开或创建 SSH 配置文件：

     ```sh
     vim ~/.ssh/config
     ```

   - 添加以下内容：

     ```sh
     Host github.com
         Hostname github.com
         User git
         ProxyCommand nc -X connect -x 127.0.0.1:10808 %h %p
     ```

     - `ProxyCommand` 表示通过代理连接目标主机。
     - `-X connect` 指定使用 HTTP CONNECT 模式。
     - `-x 127.0.0.1:10809` 是代理服务器的地址和端口。
     - `%h` 和 `%p` 分别代表目标主机和端口。

   - 如果使用的是 SOCKS5 代理，改为：

     ```sh
     ProxyCommand nc -X 5 -x 127.0.0.1:10808 %h %p
     ```

     - `-X 5` 指定使用 SOCKS5 协议。

3. **安装 netcat 工具（如需要）**

   - 某些系统可能需要安装 `netcat` 工具（如 `nc`）。

   - 在 Debian/Ubuntu 系统上安装：

     ```sh
     sudo apt-get install netcat
     ```

   - 在 CentOS/RHEL 系统上安装：

     ```sh
     sudo yum install nc
     ```

4. **测试 SSH 配置**

   - 测试 SSH 是否通过代理连接：

     ```sh
     ssh -T git@github.com
     ```

     - 返回 `Hi username! You've successfully authenticated` 说明配置成功。

5. **代理调试**

   - 如果连接失败：
     - 确认代理服务是否运行正常。
     - 检查 SSH 配置文件路径和语法是否正确。
     - 查看代理日志，排查问题。

**取消 SSH 代理配置**

- 删除或注释掉 `~/.ssh/config` 中的相关配置。

- 示例：

  ```sh
  # Host github.com
  #     Hostname github.com
  #     User git
  #     ProxyCommand nc -X connect -x 127.0.0.1:10808 %h %p
  ```

**高级配置（可选）**

1. **为多个主机设置代理**

   - 如果需要为多个主机配置代理，可以使用通配符：

     ```sh
     Host *.example.com
         ProxyCommand nc -X connect -x 127.0.0.1:10808 %h %p
     ```

2. **仅特定网络环境启用代理**

   - 可以使用脚本动态修改 `~/.ssh/config`，根据网络环境启用或禁用代理。

#### 4. 注意事项

1. **SOCKS5 代理**

   - 如果使用 SOCKS5 代理：

     - Git 配置：

       ```sh
       git config --global http.proxy socks5h://127.0.0.1:10808
       git config --global https.proxy socks5h://127.0.0.1:10808
       ```

     - SSH 配置：

       ```sh
       ProxyCommand nc -X 5 -x 127.0.0.1:10808 %h %p
       ```

2. **按需配置**

   - 为特定域名设置代理（如 GitHub），其他域名不走代理。
   - 避免为所有流量配置代理，减少不必要的延迟。

3. **调试代理**

   - 使用 `curl` 测试代理：

     ```sh
     curl -x http://127.0.0.1:10808 https://www.google.com
     ```

   - 检查代理服务日志，确保流量通过代理。





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

## 8.一个git项目多个远程仓库

在我们的git项目中，操作远程仓库信息的命令为

```bash
$ git remote  # 查看当前所有的远程仓库的名称
$ git remote -v # 查看远程仓库的名称和远程仓库的网址
```

一般情况下，当我们从远程仓库中克隆下一个项目来之后。默认的远程仓库名是 `origin`

```bash
$ git clone https://github.com/onmpw/JYGO.git
$ cd JYGO
$ git remote
origin

$ git remote -v
origin https://github.com/onmpw/JYGO.git (fetch)
origin https://github.com/onmpw/JYGO.git (push)
```

当`pull` 或者 `push` 的时候默认使用的都是`origin`远程仓库

```bash
$ git pull origin master # 或者 git pull

$ git push origin master # 或者 git push
```

怎么给这个项目再添加一个远程仓库呢？使用`git remote add` 命令。

### 方法一、 git remote add

------

```bash
$ git remote add local git@localhost:workspace/repo/JYGO2.git
```

上面的`local` 和 `origin`一样，也是远程仓库的名称

```bash
$ git remote -v
origin https://github.com/onmpw/JYGO.git (fetch)
origin https://github.com/onmpw/JYGO.git
local git@localhost:workspace/repo/JYGO2.git (fetch)
local git@localhost:workspace/repo/JYGO2.git (push)
```

添加成功之后，以后再使用`git push`的时候，就可以根据需要推送到需要的远程仓库中。如果需要推送到两个仓库中，则执行两边 `git push`

```bash
$ git push origin master # 默认的origin远程仓库
$ git push local master  # 新添加的 local 远程仓库
To git@localhost:workspace/repo/JYGO2.git
 ! [rejected]        master -> master (fetch first)
error: failed to push some refs to 'git@localhost:workspace/repo/JYGO2.git'
hint: Updates were rejected because the remote contains work that you do
hint: not have locally. This is usually caused by another repository pushing
hint: to the same ref. You may want to first integrate the remote changes
hint: (e.g., 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

`puah`没有成功！怎么会出现这种情况呢。原来在使用`git remote add` 添加完远程仓库之后，其实是不能直接推送到远程仓库的。也就是说开始的时候，上面第二条命令是执行不成功的。因为这时候你本地的版本和`local`远程仓库的版本是不一致的，需要从`local`上获取最新的代码。也就是说在执行 `push` 之前需要先从`local`上拉取最新的内容。

```bash
$ git pull local master
Unpacking objects: 100% (3/3), done.
From git@localhost:workspace/repo/JYGO2.git
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> github/master
fatal: refusing to merge unrelated histories
```

是的，仅仅使用上面的命令也是不会成功的。需要使用下面的命令

```bash
$ git pull --allow-unrelated-histories local master
```

顺利执行成功。然后再使用 `push` 就可以推送到远程仓库了。

```bash
$ git push local master
```

成功了。 很好。不过问题也随之而来了。如果有多个远程仓库都需要提交，那我们要每个远程仓库都执行一次 `git push`。有没有一种方法一次`push`就提交到多个远程仓库呢？答案当然是：这个真有！

### 方法二、 git remote set-url --add 命令

------

```bash
$ git remote set-url --add origin git@localhost:workspace/repo/JYGO2.git
```

上面命令就是给远程仓库`origin` 再新增一个远程仓库的地址。网上有很多文章写到这就认为，添加完成之后就可以直接使用 `git push` 命令一次性提交到多个远程仓库了。其实不然，最初始的那个远程仓库`push`成功是没问题的。但是到了新增的这个地址的时候就会出现推送失败的情况。

```bash
$ git push --all # 或者 git push origin master 或者直接使用 git push， 都可以。
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (6/6), 931 bytes | 931.00 KiB/s, done.
Total 6 (delta 0), reused 0 (delta 0)
To https://github.com/onmpw/JYGO.git
   c1857d1..ff94cf0  master -> master
To git@localhost:workspace/repo/JYGO2.git
 ! [rejected]        master -> master (fetch first)
error: failed to push some refs to 'git@localhost:workspace/repo/JYGO2.git'
hint: Updates were rejected because the remote contains work that you do
hint: not have locally. This is usually caused by another repository pushing
hint: to the same ref. You may want to first integrate the remote changes
hint: (e.g., 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

很明显，还是因为本地和远程版本不同步的问题。也就是说在`push` 之前需要先 `pull` 内容。

```bash
$ git pull 
Already up to date.
```

很奇怪，已经是最新的内容了。但是新添加的远程仓库并没有获取过。 其实问题的原因是在同一仓库名称下如果有多个远程仓库地址的话，`pull` 的时候只会去第一个仓库地址中拉取内容。所以说，我们新添加的远程仓库的内容是不会被获取到的。也就是不能`push`的。 那这个问题要怎么解决呢？很简单，换成第一种方法，使用 `git remote add` 来添加远程仓库，从而进行管理。但是，`push`的时候是比较麻烦。 有没有其他的方法呢？答案还是：这个真有。

#### 1. 修改配置文件 .git/config

首先，我们知道不管是 `git remote add` 还是 `git remote set-url --add` 其实都是来操作项目中的`.git/config`配置文件(有兴趣可以去看一下该配置文件的内容)。对于 `git remote set-url --add` 来说，config配置文件的主要部分内容如下

```ini
[remote "origin"]
        url = https://github.com/onmpw/JYGO.git
        fetch = +refs/heads/*:refs/remotes/github/*
        url = git@localhost:workspace/repo/JYGO2.git
```

看到内容了吗，很简单明了。既然`pull`只是获取第一个远程仓库的内容，那还不好说吗，直接交换二者的位置，改动如下

```ini
[remote "origin"]
        url = git@localhost:workspace/repo/JYGO2.git
        fetch = +refs/heads/*:refs/remotes/github/*
        url = https://github.com/onmpw/JYGO.git
```

然后再使用`git pull`

> 这里需要注意的是，使用`git pull`的时候，和第一种方法是一样的，也要加上 `--allow-unrelated-histories` 参数

```bash
$ git pull
$ git push --all
```

很开心，终于成功了。

#### 2. 空仓库方法

这种方法很简单。既然内容版本不同步，那就不要有内容。我们新添加的远程仓库要是一个空仓库，不要有任何的文件内容。 网上有人说是因为`README.md` 文件的问题。其实只是说对了一半。因为在github或者gitlab等平台上，新建仓库的时候可能有些会默认初始化一个`README.md`文件。像github在新建仓库的时候是会让你选择是否初始化`README.md`文件的，我们只要不初始化这个文件就行了。当然除了这个默认文件。在我们将这个远程仓库加到我们项目中之前，该仓库中就不要有任何的文件了。只有这样，当我们将远程仓库加到项目中之后才不需要`pull`就可以直接推送本地内容到该远程仓库了。



更多更详细教程参考易百教程： https://www.yiibai.com/git

迹忆客Git教程: https://www.jiyik.com/w/git

