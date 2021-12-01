# Qt 中正则表达式的使用



### 可以查看Qt帮助文档

```C++
//首先需要包含正则表达式的头文件
//这里推荐使用QRegularExpression类
#include <QRegularExpression>
#include <QRegularExpressionMatch>


	//定义正则表达式
    QRegularExpression time_rgx("name=.+time=\\d+");
    QRegularExpressionMatch time_Match;
    int index = 0;//偏移量
    QList<QString> list_time;
    while (index < alltxt_import.length())
    {
        time_Match = time_rgx.match(alltxt_import, index);
        //如果匹配成功
        if (time_Match.hasMatch()){
             //将本次匹配末尾作为下一次匹配的开始,更改偏移量
            index = time_Match.capturedEnd();
            list_time.append(time_Match.captured());
        }
        else
        {
            break;
        }
    }

//作用是用于匹配整个字符串
captured();//可以给相应的参数,默认是0 是按照组号来分辨的
```



## 链接:  [Qt5.0正则表达式的使用](https://blog.csdn.net/qq_33266987/article/details/71479671)

