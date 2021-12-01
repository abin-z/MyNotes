# jQuery

JavaScript的基础知识:https://www.w3school.com.cn/js/index.asp



**jQuery是一个快速、简洁优秀的JavaScript代码库**（框架）jQuery设计的宗旨是“write Less，Do More”，即倡导写更少的代码，做更多的事情。**它封装JavaScript常用的功能代码，提供一种简便的JavaScript[设计模式](https://baike.baidu.com/item/设计模式/1212549)，优化DOM操作、事件处理、动画设计和[Ajax](https://baike.baidu.com/item/Ajax/8425)交互**。具有独特的链式语法和短小清晰的多功能接口；具有高效灵活的[CSS选择器](https://baike.baidu.com/item/CSS选择器/2819686)，并且可对[CSS](https://baike.baidu.com/item/CSS/5457)选择器进行扩展；拥有便捷的插件扩展机制和丰富的插件



## jQuery的使用

jQuery有开发版, 也有压缩后的生产版

***.min.js

项目中首先导入jQuery的js文件(一般是在head标签中)

```Javas
<script src="./js/jquery.min.js"></script>
```

![image-20210929104558089](F:\Images\image-20210929104558089.png)

在企业级开发中, 开发推荐使用网络镜像加载

我们的实例中的所有 jQuery 函数位于一个 document ready 函数中： 加载页面时,首先绘制对象树.

```JavaScript
//文档就绪事件
//方式一
$(document).ready(function(){	
	//--- jQuery functions go here ----
});

//方式二
$(function(){

});
```

**快速入门:**

通过失去焦点获取输入框的值

test.html:

```javascript
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="./js/jquery.min.js"></script>
    <script src="./js/my.js"></script>
    <title>Document</title>
</head>
<body>
    <div id="bigbox">
        <input type="text" id="username" name="username" value="" onblur="func()">
    </div>
</body>
</html>
```

使用原生态的JavaScript实现my.js:

```JavaScript
//JavaScript原生态的实现方式
function func(){
    var n = document.getElementById("username").value;
    alert('hello, username = ' + n);
}
```

使用jQuery实现该功能:

```JavaScript
//使用jQuery实现
$(document).ready(function()
{
    //id 选择器: #ID
    $("#username").blur(function ()		//注意#号,不能缺少
    {
        alert("username = " + $("#username").val());
    });
});
```

需求: 当文本框失去焦点时将一个文本框的内容传到另外一个文本框

html:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="./js/jquery.min.js"></script>
    <script src="./js/my.js"></script>
    <title>Document</title>
</head>
<body>
    <div id="bigbox">
        <input type="text" id="username" name="username" value="">
        <input type="text" id="name", name="name" value="">
    </div>
</body>
</html>
```

js:

```javascript
$(document).ready(function()            //加载DOM树
{
    //id 选择器: #ID
    $("#username").blur(function ()     //失去焦点事件绑定
    {
        var txt =  $("#username").val();    //获取username的值
        $("#name").val(txt);                //设置name的值
        $("#username").val("");             //清空uaername的值
    });
});
```

![image-20210929114703757](F:\Images\image-20210929114703757.png)



## jQuery选择器

ID选择器:

```JavaScript 
$("#id名")		#id选择器,一定要有#
```

标签选择器:

```JavaScript
$("p")			#$("p") 选取 <p> 元素。
```

类选择器:

```JavaScript
$(".class类名")	#类选择器,一定要有 .
```

### jQuery 元素选择器

jQuery 使用 CSS 选择器来选取 HTML 元素。

$("p") 选取 <p> 元素。

$("p.intro") 选取所有 class="intro" 的 <p> 元素。

$("p#demo") 选取所有 id="demo" 的 <p> 元素。

### jQuery 属性选择器

jQuery 使用 XPath 表达式来选择带有给定属性的元素。

$("[href]") 选取所有带有 href 属性的元素。

$("[href='#']") 选取所有带有 href 值等于 "#" 的元素。

$("[href!='#']") 选取所有带有 href 值不等于 "#" 的元素。

$("[href$='.jpg']") 选取所有 href 值以 ".jpg" 结尾的元素。

### jQuery CSS 选择器

jQuery CSS 选择器可用于改变 HTML 元素的 CSS 属性。

下面的例子把所有 p 元素的背景颜色更改为红色：

```
$("p").css("background-color","red");
```

**选择器之间可以进行组合** 完成复杂的业务

| 语法                 | 描述                                                 |
| :------------------- | :--------------------------------------------------- |
| $(this)              | 当前 HTML 元素                                       |
| $("p")               | 所有 <p> 元素                                        |
| $("p.intro")         | 所有 class="intro" 的 <p> 元素                       |
| $(".intro")          | 所有 class="intro" 的元素                            |
| $("#intro")          | id="intro" 的元素                                    |
| $("ul li:first")     | 每个 <ul> 的第一个 <li> 元素                         |
| $("[href$='.jpg']")  | 所有带有以 ".jpg" 结尾的属性值的 href 属性           |
| $("div#intro .head") | id="intro" 的 <div> 元素中的所有 class="head" 的元素 |

更多jQuery的选择器: https://www.w3school.com.cn/jquery/jquery_ref_selectors.asp



## jQuery事件

### jQuery 事件函数

jQuery 事件处理方法是 jQuery 中的核心函数。

事件处理程序指的是当 HTML 中发生某些事件时所调用的方法。术语由事件“触发”（或“激发”）经常会被使用。

| Event 函数                      | 绑定函数至                                     |
| :------------------------------ | :--------------------------------------------- |
| $(document).ready(function)     | 将函数绑定到文档的就绪事件（当文档完成加载时） |
| $(selector).click(function)     | 触发或将函数绑定到被选元素的点击事件           |
| $(selector).dblclick(function)  | 触发或将函数绑定到被选元素的双击事件           |
| $(selector).focus(function)     | 触发或将函数绑定到被选元素的获得焦点事件       |
| $(selector).mouseover(function) | 触发或将函数绑定到被选元素的鼠标悬停事件       |

**通过选择器找到元素----绑定事件----事件驱动函数**

更多jQuery事件:https://www.w3school.com.cn/jquery/jquery_ref_events.asp



## XMLHttpRequest 对象

https://www.w3school.com.cn/js/js_ajax_http.asp

**Ajax 的核心是 XMLHttpRequest 对象。**

所有现代浏览器都支持 XMLHttpRequest 对象。

XMLHttpRequest 对象用于同幕后服务器交换数据。这意味着可以更新网页的部分，而不需要重新加载整个页面。

```JavaScript
if (window.XMLHttpRequest) {
    // 用于现代浏览器的代码
     xmlhttp = new XMLHttpRequest();
 } else {
    // 应对老版本 IE 浏览器的代码
     xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
 }
```

### XMLHttpRequest 对象方法

| 方法                                          | 描述                                                         |
| :-------------------------------------------- | :----------------------------------------------------------- |
| new XMLHttpRequest()                          | 创建新的 XMLHttpRequest 对象                                 |
| abort()                                       | 取消当前请求                                                 |
| getAllResponseHeaders()                       | 返回头部信息                                                 |
| getResponseHeader()                           | 返回特定的头部信息                                           |
| open(*method*, *url*, *async*, *user*, *psw*) | 规定请求method：请求类型 GET 或 POSTurl：文件位置async：true（异步）或 false（同步）user：可选的用户名称psw：可选的密码 |
| send()                                        | 将请求发送到服务器，用于 GET 请求                            |
| send(*string*)                                | 将请求发送到服务器，用于 POST 请求                           |
| setRequestHeader()                            | 向要发送的报头添加标签/值对                                  |

### XMLHttpRequest 对象属性

| 属性               | 描述                                                         |
| :----------------- | :----------------------------------------------------------- |
| onreadystatechange | 定义当 readyState 属性发生变化时被调用的函数                 |
| readyState         | 保存 XMLHttpRequest 的状态。0：请求未初始化1：服务器连接已建立2：请求已收到3：正在处理请求4：请求已完成且响应已就绪 |
| responseText       | 以字符串返回响应数据                                         |
| responseXML        | 以 XML 数据返回响应数据                                      |
| status             | 返回请求的状态号200: "OK"403: "Forbidden"404: "Not Found"如需完整列表请访问 [Http 消息参考手册](https://www.w3school.com.cn/tags/ref_httpmessages.asp) |
| statusText         | 返回状态文本（比如 "OK" 或 "Not Found"）                     |



## AJAX简介

AJAX 是开发者的梦想，因为您能够：

- 不刷新页面更新网页

- 在页面加载后从服务器请求数据

- 在页面加载后从服务器接收数据

- 在后台向服务器发送数据

  

### 什么是 AJAX？

AJAX = *A*synchronous *J*avaScript *A*nd *X*ML.

AJAX 并非编程语言。

AJAX 仅仅组合了：

- 浏览器内建的 XMLHttpRequest 对象（从 web 服务器请求数据）
- JavaScript 和 HTML DOM（显示或使用数据）

Ajax 是一个令人误导的名称。Ajax 应用程序可能使用 XML 来传输数据，但将数据作为纯文本或 JSON 文本传输也同样常见。

Ajax 允许通过与场景后面的 Web 服务器交换数据来异步更新网页。这意味着可以更新网页的部分，而不需要重新加载整个页面。



### AJAX如何工作

![image-20210930094747883](F:\Images\image-20210930094747883.png)

1. **网页中发生一个事件（页面加载、按钮点击）**
2. **由 JavaScript 创建 XMLHttpRequest 对象**
3. **XMLHttpRequest 对象向 web 服务器发送请求**
4. **服务器处理该请求**
5. **服务器将响应发送回网页**
6. **由 JavaScript 读取响应**
7. **由 JavaScript 执行正确的动作（比如更新页面）**



JavaScript原生的AJAX代码示例:

```JavaScript
<script>
function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/demo/js/ajax_info.txt", true);
  xhttp.send();
}
</script>
```

我们不推荐同步的 XMLHttpRequest (async = false)，因为 JavaScript 将停止执行直到服务器响应就绪。如果服务器繁忙或缓慢，应用程序将挂起或停止。



## jQuery的AJAX

### jQuery load() 方法

jQuery load() 方法是简单但强大的 AJAX 方法。

load() 方法从服务器加载数据，并把返回的数据放入被选元素中。

### 语法：

```JavaScript
$(selector).load(URL,data,callback);		//必须要有选择器
```

必需的 *URL* 参数规定您希望加载的 URL。

可选的 *data* 参数规定与请求一同发送的查询字符串键/值对集合。

可选的 *callback* 参数是 load() 方法完成后所执行的函数名称。

```JavaScript
var requestURL = "http://127.0.0.1:8080/ajaxFunc";
var data = {empno: 7788, ename: "SCOTT", sal: 8000.00};
$(document).ready(function (){
   $("#button").click(function () { 
        console.log("123456789");
        $("#text").load(requestURL, data,function (map_t){
            alert(map_t);
            var map = JSON.parse(map_t);        //需要将返回的json字符串装换为js对象
            $("#name0").val(map.name);          //填充相应的值
            $("#gender").val(map.gender);
            $("#age").val(map.age);
        });
    });
});
```

### jQuery get()和post() 方法

**get()语法:**

```JavaScript
$.get(URL,data,callback);
```

必需的 *URL* 参数规定您希望请求的 URL。

可选的 *data* 参数规定连同请求发送的数据。

可选的 *callback* 参数是请求成功后所执行的函数名。

```JavaScript
var requestURL = "http://127.0.0.1:8080/ajaxFunc";
var data = {empno: 7788, ename: "SCOTT", sal: 8000.00};
$(document).ready(function (){
    $("#button").click(function () { 
         console.log("123456789");
         $.get(requestURL, data,function (map_t){
             alert(map_t);
             $("#name0").val(map_t.name);
             $("#gender").val(map_t.gender);
             $("#age").val(map_t.age);
         });
     });
 });
```

**post()方法:**

```JavaScript
$.post(URL,data,callback);
```

必需的 *URL* 参数规定您希望请求的 URL。

可选的 *data* 参数规定连同请求发送的数据。

可选的 *callback* 参数是请求成功后所执行的函数名。

```JavaScript
$(document).ready(function (){
    $("#button").click(function () { 
         console.log("123456789");
         $.post(requestURL, data,function (map_t){
             alert(map_t);
             $("#name0").val(map_t.name);//可以不用JSON.parse()方法
             $("#gender").val(map_t.gender);
             $("#age").val(map_t.age);
         });
     });
 });
```

