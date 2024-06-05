# Linux系统







## vim编辑器

#### vi与vim的不同

vi类似于windows的记事本，比较适合编辑普通文本，但是用于编写脚本代码就不太合适了，缺少高亮显示代码、自动缩进等重要功能；而vim类似于windows下的高级编辑器，为了提高开发效率，需要使用vim而不是vi。
因此，首先做如下调整，以便只使用vim作为开发脚本的功能工具：

```bash
[root@dabiaoge ~]$ echo ‘alias vi=vim’ >> /etc/profile
[root@dabiaoge ~]$ tail -1 /etc/profile
alias vi=vim
[root@dabiaoge ~]$ source /etc/profile
```

经过上述调整后，当用vi命令时，会自动被vim替代。



![20191219104939654](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/20191219104939654.jpg)

![20180815232620931](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/20180815232620931.gif)

![20160907135321944](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/20160907135321944.png)







### vim的基本配置

全局路径：`/etc/vimrc`
用户个人路径：`home/username/.vimrc`
建议：放在用户个人路径`home/username/.vimrc`

设置终端支持的256颜色, 修改`~/.bashrc`文件, 添加以下内容:

```sh
# 终端支持 256 色
export TERM=xterm-256color
```

然后再bash命令行输入:`echo $TERM`, 查看是否设置成功

```sh
[root@rocky ~]$ echo $TERM
xterm-256color
```

#### vim安装插件

Vim-plug 是一个自由、开源、速度非常快的、极简的 vim 插件管理器。它可以并行地安装或更新插件。你还可以回滚更新。它创建shallow clone最小化磁盘空间使用和下载时间。它支持按需加载插件以加快启动时间。其他值得注意的特性是支持分支/标签/提交、post-update 钩子、支持外部管理的插件等。

vim插件管理器: [vim-plug](https://github.com/junegunn/vim-plug)

```sh
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

vim插件推荐: [vimawesome](https://vimawesome.com/)







### vim光标移动

在 Vim 中，光标操作是非常基础且重要的技能。掌握各种光标移动的命令和技巧可以显著提高你的编辑效率。以下是 Vim 中光标操作的详细指南。

#### 基本光标移动命令

- **h**：左移一个字符。
- **j**：下移一行。
- **k**：上移一行。
- **l**：右移一个字符。

#### 单词移动

- **w**：移动到下一个单词的开头。
- **b**：移动到上一个单词的开头。
- **e**：移动到当前或下一个单词的结尾。
- **ge**：移动到当前或上一个单词的结尾。

#### 行内移动

- **0**：移动到当前行的开头。
- **^**：移动到当前行的第一个非空白字符。
- **$**：移动到当前行的末尾。
- **g_**：移动到当前行最后一个非空白字符。

#### 跳转到特定行

- **G**：移动到文件的末尾。

- **gg**：移动到文件的开头。

- **nG**：移动到第 n 行，例如 `10G` 移动到第 10 行。

- ：移动到第 n 行，例如 

  ```sh
  :10	  			# 移动到第 10 行。
  ```



### 屏幕跳转

- **H**：移动到屏幕的顶部行。
- **M**：移动到屏幕的中间行。
- **L**：移动到屏幕的底部行。
- **Ctrl+e**：向下滚动一行。
- **Ctrl+y**：向上滚动一行。
- **Ctrl+f**：向下滚动一页。
- **Ctrl+b**：向上滚动一页。
- **Ctrl+d**：向下滚动半页。
- **Ctrl+u**：向上滚动半页。



### 搜索与查找

- **/**：向前搜索。例如，输入 `/pattern` 后按 `Enter`，光标将跳到下一个匹配的地方。
- **?**：向后搜索。例如，输入 `?pattern` 后按 `Enter`，光标将跳到上一个匹配的地方。
- **n**：跳转到下一个搜索匹配项。
- **N**：跳转到上一个搜索匹配项。
- **f<char>**：在当前行向右查找字符 `<char>`。
- **F<char>**：在当前行向左查找字符 `<char>`。
- **t<char>**：在当前行向右查找字符 `<char>` 的前一个位置。
- **T<char>**：在当前行向左查找字符 `<char>` 的后一个位置。
- *****: 向前查找字，类似 `/pattern` 
- **#**: 向后查找字，类似`?pattern` 



### 标记与跳转

- **m<char>**：在当前光标位置设置标记 `<char>`。
- **'<char>**：跳转到标记 `<char>` 位置的行首。
- **`<char>`**：跳转到标记 `<char>` 位置的确切位置。

### 相对行号

启用相对行号可以帮助你更方便地进行上下移动。你可以在 `.vimrc` 文件中添加以下内容：

```sh
set relativenumber
```

这样，你可以使用行号进行移动，例如：

- **5j**：向下移动 5 行。
- **10k**：向上移动 10 行。

### 可视模式

- **v**：进入字符可视模式。
- **V**：进入行可视模式。
- **Ctrl+v**：进入块可视模式。





#### .vimrc文件的配置

以下是我的`home/username/.vimrc`配置:

```sh
""""""""""""""""""""""""""""""""""""""""""""""
" 下面是vim插件管理器: vim-plug 的配置
" Begin the section with call plug#begin()
" List the plugins with Plug commands
" End the section with call plug#end()
"
" Reload the file or restart Vim, then you can,
" :PlugInstall to install the plugins
" :PlugUpdate to install or update the plugins
" :PlugDiff to review the changes from the last update
" :PlugClean to remove plugins no longer in the list
""""""""""""""""""""""""""""""""""""""""""""""
call plug#begin()

" List your plugins here
Plug 'tpope/vim-sensible'

Plug 'altercation/vim-colors-solarized'

Plug 'morhetz/gruvbox'

Plug 'scrooloose/nerdtree'

Plug 'octol/vim-cpp-enhanced-highlight'

Plug 'luochen1990/rainbow'

Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

Plug 'elzr/vim-json'


call plug#end()
""""""""""""""""""""""""""""""""""""""""""""""
" vim插件管理器: vim-plug 配置结束
""""""""""""""""""""""""""""""""""""""""""""""

"================= 插件的配置 begin ==================="
" NERDTree 配置
" Start NERDTree and put the cursor back in the other window.
autocmd VimEnter * NERDTree | wincmd p

" 如果 NERDTree 是唯一的窗口且文件被打开，自动关闭 Vim
" Exit Vim if NERDTree is the only window remaining in the only tab.
autocmd BufEnter * if tabpagenr('$') == 1 && winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree() | call feedkeys(":quit\<CR>:\<BS>") | endif

" 快捷键设置
nnoremap <C-n> :NERDTreeToggle<CR>   " Ctrl+n 切换 NERDTree 显示/隐藏
nnoremap <leader>n :NERDTreeFind<CR> " 使用 <leader>n 在 NERDTree 中定位当前文件

" NERDTree 配置选项
let NERDTreeShowHidden=1             " 显示隐藏文件
let NERDTreeMinimalUI=1              " 启用最小化 UI
let NERDTreeDirArrows=1              " 目录前显示箭头

" 自定义 NERDTree 显示图标
let g:NERDTreeMapOpenSplit = 's'     " 使用 's' 键在水平分割窗口中打开文件
let g:NERDTreeMapOpenVSplit = 'v'    " 使用 'v' 键在垂直分割窗口中打开文件

" 文件过滤器
let NERDTreeIgnore=['\.pyc$', '\~$'] " 忽略 .pyc 和临时文件

" 启用 rainbow 插件
let g:rainbow_active = 1

" 启用 vim-airline
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#formatter = 'unique_tail'

" 配置 vim-airline 主题
let g:airline_theme='dark'

" JSON 文件相关设置
let g:vim_json_conceal = 0 " 禁用 JSON conceal 功能，以便于查看所有字符

" 启用 gruvbox 主题
set background=dark " 或者 set background=light 选择浅色背景, dark 深色背景
colorscheme gruvbox

" 配置 gruvbox 选项
let g:gruvbox_contrast_dark = 'medium' " 选择对比度（可以是 'soft', 'medium', 'hard'）
let g:gruvbox_invert_selection = 1 " 0 禁用反向选择, 1 启用反向选择

" 启用 solarized 主题
" set background=dark " 或者 set background=light 选择浅色背景
" let g:solarized_termcolors=256
" colorscheme solarized

" vim-cpp-enhanced-highlight 插件的可选配置
" 这些配置项可以根据你的需求进行调整
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_experimental_simple_template_highlight = 1

"=================  插件的配置 end  ==================="

"关闭vi兼容模式"
set nocompatible

" 显示行号
set number

"当文件在外部被修改时，自动更新该文件"
set autoread

" 渲染支持 256 色的配色方案
set t_Co=256

" 使用系统剪贴板, vim复制粘贴和系统剪贴板集成
set clipboard=unnamedplus

" .vimrc 中的配置示例
set relativenumber          " 启用相对行号

" 启用快速滚动的快捷键
nnoremap <C-e> 5j          " Ctrl+e 快速向下移动 5 行
nnoremap <C-y> 5k          " Ctrl+y 快速向上移动 5 行

"侦测文件类型"
filetype on

"载入文件类型插件"
filetype plugin on

"为特定文件类型载入相关缩进文件"
filetype indent on

"设置历史记录步数"
set history=1000

" 1=启动显示状态行, 2=总是显示状态行.
" 设置总是显示状态行,方便看到当前文件名.
set laststatus=2

" 高亮当前行
set cursorline

" 高亮显示匹配的括号
set showmatch

" 默认按下Esc后,需要等待1秒才生效,
" 设置Esc超时时间为100ms,尽快生效
set ttimeout
set ttimeoutlen=100

" 开启语法高亮
syntax enable

" 显示还没有输入完整的命令.例如yy命令,输入第一个y会在右下角显示y.
set showcmd

" 自动缩进时,缩进长度为4
set shiftwidth=4

"设置所有的Tab和缩进为4个空格"
set tabstop=4

"距离顶部和底部3行"
set scrolloff=3

"高亮显示匹配的括号([{和}])"
set showmatch

"高亮搜索项"
set hlsearch
```



 .vimrc 配置文件中的其他基本配置如下

```sh
"""""""""""""""""""""""""""""""""""
"""=>全局配置<="""
"""""""""""""""""""""""""""""""""""
"关闭vi兼容模式"
set nocompatible
"设置历史记录步数"
set history=1000
"开启相关插件"
"侦测文件类型"
filetype on
"载入文件类型插件"
filetype plugin on
"为特定文件类型载入相关缩进文件"
filetype indent on
"当文件在外部被修改时，自动更新该文件"
set autoread
"激活鼠标的使用"
set mouse=a
set selection=exclusive
set selectmode=mouse,key
"保存全局变量"
set viminfo+=!
"带有如下符号的单词不要被换行分割"
set iskeyword+=_,$,@,%,#,-
"通过使用: commands命令，告诉我们文件的哪一行被改变过"
set report=0
"被分割的窗口间显示空白，便于阅读"
set fillchars=vert:\ ,stl:\ ,stlnc:\
"""""""""""""""""""""""""""""""""
"""=>字体和颜色<="""
"""""""""""""""""""""""""""""""""
"自动开启语法高亮"
syntax enable
"设置字体"
"set guifont=dejaVu\ Sans\ MONO\ 10
set guifont=Courier_New:h10:cANSI
"设置颜色"
"colorscheme desert
"高亮显示当前行"
set cursorline
hi cursorline guibg=#00ff00
hi CursorColumn guibg=#00ff00
"高亮显示普通txt文件（需要txt.vim脚本）"
au BufRead,BufNewFile * setfiletype txt
"""""""""""""""""""""""""""""""
"""=>代码折叠功能<="""
"""""""""""""""""""""""""""""""
"激活折叠功能"
01/06/2024, 20:37 vimrc文件配置的全文收录（史上最全，附带中文解释）_51CTO博客_vimrc文件颜色配置
https://blog.51cto.com/zpf666/2335640 1/5
set foldenable
"set nofen（这个是关闭折叠功能）"
"设置按照语法方式折叠（可简写set fdm=XX）"
"有6种折叠方法：
"manual 手工定义折叠"
"indent 更多的缩进表示更高级别的折叠"
"expr 用表达式来定义折叠"
"syntax 用语法高亮来定义折叠"
"diff 对没有更改的文本进行折叠"
"marker 对文中的标志进行折叠"
set foldmethod=manual
"set fdl=0（这个是不选用任何折叠方法）"
"设置折叠区域的宽度"
"如果不为0，则在屏幕左侧显示一个折叠标识列
"分别用“-”和“+”来表示打开和关闭的折叠
set foldcolumn=0
"设置折叠层数为3"
setlocal foldlevel=3
"设置为自动关闭折叠"
set foldclose=all
"用空格键来代替zo和zc快捷键实现开关折叠"
"zo O-pen a fold (打开折叠)
"zc C-lose a fold (关闭折叠)
"zf F-old creation (创建折叠)
"nnoremap <space > @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo') <CR >
"""""""""""""""""""""""""""""""""""
"""=>文字处理<="""
"""""""""""""""""""""""""""""""""""
"使用空格来替换Tab"
set expandtab
"设置所有的Tab和缩进为4个空格"
set tabstop=4
"设定< <和 > >命令移动时的宽度为4"
set shiftwidth=4
"使得按退格键时可以一次删除4个空格"
set softtabstop=4
set smarttab
"缩进，自动缩进（继承前一行的缩进）"
"set autoindent 命令打开自动缩进，是下面配置的缩写
"可使用autoindent命令的简写，即“:set ai”和“:set noai”
"还可以使用“:set ai sw=4”在一个命令中打开缩进并设置缩进级别
set ai
set cindent
"智能缩进"
set si
"自动换行”
set wrap
"设置软宽度"
set sw=4
"行内替换"
set gdefault
01/06/2024, 20:37 vimrc文件配置的全文收录（史上最全，附带中文解释）_51CTO博客_vimrc文件颜色配置
https://blog.51cto.com/zpf666/2335640 2/5
""""""""""""""""""""""""""""""""""
"""=>Vim 界面<="""
""""""""""""""""""""""""""""""""""
"增强模式中的命令行自动完成操作"
set wildmenu
"显示标尺"
set ruler
"设置命令行的高度"
set cmdheight=1
"显示行数"
set nu
"不要图形按钮"
set go=
"在执行宏命令时，不进行显示重绘；在宏命令执行完成后，一次性重绘，以便提高性能"
set lz
"使回格键（backspace）正常处理indent, eol, start等"
set backspace=eol,start,indent
"允许空格键和光标键跨越行边界"
set whichwrap+= <, > ,h,l
"设置魔术"
set magic
"关闭遇到错误时的声音提示"
"关闭错误信息响铃"
set noerrorbells
"关闭使用可视响铃代替呼叫"
set novisualbell
"高亮显示匹配的括号([{和}])"
set showmatch
"匹配括号高亮的时间（单位是十分之一秒）"
set mat=2
"光标移动到buffer的顶部和底部时保持3行距离"
set scrolloff=3
"搜索逐字符高亮"
set hlsearch
set incsearch
"搜索时不区分大小写"
"还可以使用简写（“:set ic”和“:set noic”）"
set ignorecase
"用浅色高亮显示当前行"
autocmd InsertLeave * se nocul
autocmd InsertEnter * se cul
"输入的命令显示出来，看的清楚"
set showcmd
""""""""""""""""""""""""""""""""""""
"""=>编码设置<="""
""""""""""""""""""""""""""""""""""""
"设置编码"
set encoding=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
01/06/2024, 20:37 vimrc文件配置的全文收录（史上最全，附带中文解释）_51CTO博客_vimrc文件颜色配置
https://blog.51cto.com/zpf666/2335640 3/5
"设置文件编码"
set fileencodings=utf-8
"设置终端编码"
set termencoding=utf-8
"设置语言编码"
set langmenu=zh_CN.UTF-8
set helplang=cn
"""""""""""""""""""""""""""""
"""=>其他设置<="""
"""""""""""""""""""""""""""""
"开启新行时使用智能自动缩进"
set smartindent
set cin
set showmatch
"在处理未保存或只读文件的时候，弹出确认"
set confirm
"隐藏工具栏"
set guioptions-=T
"隐藏菜单栏"
set guioptions-=m
"置空错误铃声的终端代码"
set vb t_vb=
"显示状态栏（默认值为1，表示无法显示状态栏）"
set laststatus=2
"状态行显示的内容"
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}
"粘贴不换行问题的解决方法"
set pastetoggle= <F9 >
"设置背景颜色"
set background=dark
"文件类型自动检测，代码智能补全"
set completeopt=longest,preview,menu
"共享剪切板"
set clipboard+=unnamed
"从不备份"
set nobackup
set noswapfile
"自动保存"
set autowrite

"距离顶部和底部5行"
set scrolloff=5

"高亮搜索项"
set hlsearch

"显示中文帮助"
if version >= 603
 set helplang=cn
 set encoding=utf-8
endif
"设置高亮相关项"
highlight Search ctermbg=black ctermfg=white guifg=white guibg=black
""""""""""""""""""""""""""""""""
"""=>在shell脚本开头自动增加解释器以及作者等版权信息<="""
""""""""""""""""""""""""""""""""
"新建.py,.cc,.sh,.java文件，自动插入文件头"
autocmd BufNewFile *.py,*.cc,*.sh,*.java exec ":call SetTitle()"
"定义函数SetTitle，自动插入文件头"
func SetTitle()
 if expand ("%:e") == 'sh'
 call setline(1, "#!/bin/bash")
 call setline(2, "#Author:bert")
 call setline(3, "#Blog:http://blog.51cto.com/zpf666")
 call setline(4, "#Time:".strftime("%F %T"))
 call setline(5, "#Name:".expand("%"))
 call setline(6, "#Version:V1.0")
 call setline(7, "#Description:This is a production script.")
 endif
endfunc

```
