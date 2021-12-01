# Web前端+JavaScript

### Web中常见状态码浅析



**HTTP的响应状态码由5段组成：** 

**1xx** 消息，一般是告诉客户端，请求已经收到了，正在处理，别急...

**2xx** ==处理成功==，一般表示：请求收悉、我明白你要的、请求已受理、已经处理完成等信息.

**3xx** ==重定向到其它地方==。它让客户端再发起一个请求以完成整个处理。

**4xx** ==处理发生错误，责任在客户端==，如客户端的请求一个不存在的资源，客户端未被授权，禁止访问等。

**5xx** ==处理发生错误，责任在服务端==，如服务端抛出异常，路由出错，HTTP版本不支持等。



#### **HTTP常见响应状态码：**

**1XX——信息类（Information），表示收到http请求，正在进行下一步处理，通常是一种瞬间的响应状态**



**2XX——成功类（Successful），表示用户请求被正确接收、理解和处理**

200（OK）：请求成功。一般用于GET与POST请求
201（Created）：已创建。成功请求并创建了新的资源



**3XX——重定向类（Redirection），表示没有请求成功，必须采取进一步的动作**

301（Moved Permanently）：资源被永久移动。请求的资源已被永久的移动到新URI，返回信息会包括新的URI，浏览器会自动定向到新URI。今后任何新的请求都应使用新的URI

302（Found）：资源临时移动。资源只是临时被移动，客户端应继续使用原有URI

304：用其他策略获取资源



**4XX——客户端错误（Client Error），表示客户端提交的请求包含语法错误或不能正确执行**

400（Bad Requests）：客户端请求的地址不存在或者包含不支持的参数

401（Unauthorized）：未授权，或认证失败。对于需要登录的网页，服务器可能返回此响应

403（Forbidden）：没权限。服务器收到请求，但拒绝提供服务

404（Not Found）：请求的资源不存在。遇到404首先检查请求url是否正确



**5XX——服务端错误（Server Error），表示服务器不能正确执行一个正确的请求（客户端请求的方法及参数是正确的，服务端不能正确执行，如网络超时、服务僵死，可以查看服务端日志再进一步解决）**

500（Internal Server Error）：服务器内部错误，无法完成请求

503（Service Unavailable）：由于超载或系统维护（一般是访问人数过多），服务器无法处理客户端的请求 ，通常这只是暂时状态









# JavaScript知识点(一)：

### 01、谈谈你对Ajax的理解？(概念、特点、作用)

Ajax是什么:
	Ajax是异步的 JavaScript 和 XML，是一种用于创建快速动态网页的技术；
	Ajax不需要刷新整个页面，就能够更新部分网页内容 ;

使用Ajax的好处:
	Ajax使用异步传输，实现页面局部刷新，优化用户体验
	优化了浏览器和服务器之间的传输，减少不必要的数据往返，减少了带宽占用
	Ajax在客户端运行，承担了一部分本来由服务器承担的工作，从而减少了大用户量下的服务器负载

### 02、JavaScript是一门什么样的语言，它有哪些特点？

	依赖于js引擎的脚本语言, 属于是弱语言,一个解释性的语言, 特点是: JavaScript不需要编译,是可以直接被js引擎边解释边运行.

### 03、JavaScript的数据类型有哪些？

```JavaScript
6种基本数据类型: number, string, boolean, null, undefined, object;   其中object可以再分为: array, function, date....
```

### 04、已知ID的Input输入框，如何获取这个输入框的输入值？(不使用第三方框架)

```JavaScript 
var txt = document.getElementByID("ID").value;
```

### 05、根据你的理解,请简述JavaScript脚本的执行原理?

​		JS的执行机制就是一个主线程 + 一个任务队列。同步任务就是放在主线程上执行的任务，异步任务就是放在任务队列的任务。所有的同步任务都在主线程执行，这构成了一个执行栈，异步任务有了运行结果会在任务队列中放置一个事件，比如定时2秒，到2秒后才能放进任务队列（callback放进任务队列，而不是setTimeout函数放进队列）。脚本运行时，先依次运行执行栈，然后从队列中提取事件来运行任务队列中的任务，这个过程是不断重复的。所以叫事件循环（Event Loop）。

### 06、DOM操作怎样添加、移除、移动、复制、创建和查找节点?

```javascript
(1)创建新节点

　　createDocumentFragment() //创建一个DOM片段

　　createElement() //创建一个具体的元素

　　createTextNode() //创建一个文本节点

(2) 添加、移除、替换、插入

　　appendChild()

　　removeChild()

　　redplaceChild()

　　insertBefore() //在已有的子节点前插入一个新的子节点

(3) 查找

　　getElementsByTagName() //通过标签名称

　　getElementsByName() //通过元素的Name属性的值(IE容错能力较强会得到一个数组，其中包括id等于name值的)

　　getElementById() //通过元素Id，唯一性
```

### 07、说说你对json的理解?

json是一个==轻量级的数据交换格式==, 有基本的数组/集合, 对象. 完全独立于编程语言的文本格式来存储和表示数据和交换数据。采用完全独立于编程语言的文本格式来存储和表示数据。易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

### 08、谈谈你This对象的理解?

1. this是js 的一个关键字，随着函数的使用场合的不同，this 的值会发生变化。
2.一个总原则：即this指的是调用函数的那个对象。
3.一般情况下，this 是全局对象，可以作为方法调用。

### 09、JavaScript对象的几种创建方式?

​	工厂
​	构造函数
​	直接定义---原型模式

### 10、get和post的区别,何时使用post

get用于从服务器获取数据；通过地址栏传值；对发送信息的数量有限制

post可以修改服务器端的数据；通过提交表单传值；对发送信息的数量没有限制向服务器发送大量数据

### 11、null和undefined的区别？

null： Null类型，代表“空值”，代表一个空对象指针，使用typeof运算得到 “object”，所以你可以认为它是一个特殊的对象值。
      undefined： Undefined类型，当一个声明了一个变量未初始化时，得到的就是undefined。
实际上，undefined值是派生自null值的，ECMAScript标准规定对二者进行相等性测试要返回true，

### 12、请你说说split()与join() 函数的区别?

前者是切割成数组的形式，后者是将数组转换成字符串join函数获取一批字符串，然后用分隔符字符串将它们连接起来，从而返回一个字符串。Split函数获取一个字符串，然后再分隔符处将其断开，从而返回一批字符串。但是，这两个函数之间的主要区别在于join可以使用任何分隔符字符串将多个字符串连接起来，而split只能使用一个字符分隔符将字符串断开
简单地说，如果你用split，是把一串字符（根据某个分隔符）分成若干个元素存放在一个数组里。
而join是把数组中的字符串连成一个长串，可以大体上认为是split的逆操作

### 13、typeof与instanceof的区别是什么？

在javascript中，判断一个变量的类型可以用typeof
　　(1) 数字类型、typeof返回的值是number。比如说：typeof(1)，返回值是number
　　(2) 字符串类型，typeof返回的值是string。比如typeof(“123”返回值时string)
　　(3) 布尔类型，typeof返回的值是boolean。比如typeof(true)返回值时boolean
　　(4) 对象、数组、null返回的值是object。比如typeof(window)，typeof(document)，typeof(null)返回的值都是object
　　(5) 函数类型，返回的值是function。比如：typeof(eval)，typeof(Date)返回的值都是function。
　　(6) 不存在的变量、函数或者undefined，将返回undefined。比如：typeof(abc)、typeof(undefined)都返回undefined

在javascript中，instanceof用于判断某个对象是否被另一个函数构造。	使用typeof运算符时采用引用类型存储值会出现一个问题，无论引用的是什么类型的对象，它都返回”object”。ECMAScript引入了另一个Java运算符instanceof来解决这个问题。Instanceof运算符与typeof运算符相似，用于识别正在处理的对象的类型。与typeof方法不同的是，instanceof方法要求开发者明确地确认对象为某特定类型



# JavaScript知识点(二)：

### 1、基本数据类型有哪些？

**基本数据类型：**

指的是简单的数据段，有5种，包括null、undefined、string、boolean、number；

**引用数据类型：**

指的是有多个值构成的对象，包括object、array、date、regexp、function等

**主要区别：**

**声明变量时不同的内存分配：**

基本数据类型由于占据的空间大小固定且较小，会被存储在栈当中，也就是变量访问的位置；

引用数据类型则存储在堆当中，变量访问的其实是一个指针，它指向存储对象的内存地址。

**也正是因为内存分配不同，在复制变量时也不一样。**前者复制后2个变量是独立的，因为是把值拷贝了一份；

后者则是复制了一个指针，2个变量指向的值是该指针所指向的内容，一旦一方修改，另一方也会受到影响。



**参数传递不同**：虽然函数的参数都是按值传递的，但是引用值传递的值是一个内存地址，实参和形参指向的是同一个对象，所以函数内部对这个参数的修改会体现在外部。原始值只是把变量里的值传递给参数，之后参数和这个变量互不影响。



### 2、数据类型的判断方法？

下面将对如下数据进行判断它们的类型

```JavaScript
var bool = true
var num = 1
var str = 'abc'
var und = undefined
var nul = null
var arr = [1,2,3]
var obj = {name:'haoxl',age:18}
var fun = function(){console.log('I am a function')}
```

#### 1.使用typeof

```JavaScript
console.log(typeof bool); //boolean
console.log(typeof num);//number
console.log(typeof str);//string
console.log(typeof und);//undefined
console.log(typeof nul);//object
console.log(typeof arr);//object
console.log(typeof obj);//object
console.log(typeof fun);//function
```

> 由结果可知typeof可以测试出`number`、`string`、`boolean`、`undefined`及`function`，而对于`null`及数组、对象，typeof均检测出为object，不能进一步判断它们的类型。

### 2.使用instanceof

```javascript
console.log(bool instanceof Boolean);// false
console.log(num instanceof Number);// false
console.log(str instanceof String);// false
console.log(und instanceof Object);// false
console.log(arr instanceof Array);// true
console.log(nul instanceof Object);// false
console.log(obj instanceof Object);// true
console.log(fun instanceof Function);// true

var bool2 = new Boolean()
console.log(bool2 instanceof Boolean);// true

var num2 = new Number()
console.log(num2 instanceof Number);// true

var str2 = new String()
console.log(str2 instanceof String);//  true

function Person(){}
var per = new Person()
console.log(per instanceof Person);// true

function Student(){}
Student.prototype = new Person()			//继承
var haoxl = new Student()
console.log(haoxl instanceof Student);// true
console.log(haoxl instanceof Person);// true
```

> 从结果中看出instanceof不能区别undefined和null，而且对于基本类型如果不是用new声明的则也测试不出来，对于是使用new声明的类型，它还可以检测出多层继承关系。

#### 3.使用constructor

> **undefined和null没有contructor属性**

```JavaScript
console.log(bool.constructor === Boolean);// true
console.log(num.constructor === Number);// true
console.log(str.constructor === String);// true
console.log(arr.constructor === Array);// true
console.log(obj.constructor === Object);// true
console.log(fun.constructor === Function);// true

console.log(haoxl.constructor === Student);// false
console.log(haoxl.constructor === Person);// true
```

> constructor不能判断undefined和null，并且使用它是不安全的，因为contructor的指向是可以改变的

#### 4.使用Object.prototype.toString.call

```JavaScript
console.log(Object.prototype.toString.call(bool));//[object Boolean]
console.log(Object.prototype.toString.call(num));//[object Number]
console.log(Object.prototype.toString.call(str));//[object String]
console.log(Object.prototype.toString.call(und));//[object Undefined]
console.log(Object.prototype.toString.call(nul));//[object Null]
console.log(Object.prototype.toString.call(arr));//[object Array]
console.log(Object.prototype.toString.call(obj));//[object Object]
console.log(Object.prototype.toString.call(fun));//[object Function]

function Person(){}
function Student(){}
Student.prototype = new Person()
var haoxl = new Student()
console.log(Object.prototype.toString.call(haoxl));//[object Object]
```

> 原理(摘自高级程序设计3)：在任何值上调用 Object 原生的 toString() 方法，都会返回一个 [object NativeConstructorName] 格式的字符串。每个类在内部都有一个 [[Class]] 属性，这个属性中就指定了上述字符串中的构造函数名。
> 但是它不能检测非原生构造函数的构造函数名。

#### 5.使用jquery中的$.type

```javascript
console.log($.type(bool));//boolean
console.log($.type(num));//number
console.log($.type(str));//string
console.log($.type(und));//undefined
console.log($.type(nul));//null
console.log($.type(arr));//array
console.log($.type(obj));//object
console.log($.type(fun));//function

function Person(){}
function Student(){}
Student.prototype = new Person()
var haoxl = new Student()
console.log($.type(haoxl));//object
```

> $.type()内部原理就是用的Object.prototype.toString.call()



### 3、JavaScript中var、let、const的区别？

使用var声明的变量，其作用域为该语句所在的函数内，且存在变量提升现象；
使用let声明的变量，其作用域为该语句所在的代码块内，不存在变量提升；
使用const声明的是常量，在后面出现的代码中不能再修改该常量的值。

**const**不能从字面上来理解，他不能修改的是栈内存在的值和地址。

怎么理解栈内存在的值和地址呢？就要从javascript的类型说起：
基本类型 Boolen, Number, String 是把直接值直接存在栈内
引用类型 Object（Function, Array ....）是把值存在对应的地址中

### 4、获取对象键值对中key值的方法？

使用Object.keys

![image-20211012143403612](F:\Images\image-20211012143403612.png)

Object.keys( ) 会返回一个数组，数组中是这个对象的key值列表

所以只要Object.keys(a)[0]， 就可以得只包含一个键值对的key值

### 5、字符串处理的方法有哪些？

```JavaScript
<script>
    var str = 'abcdefg';
    // charAt() 返回字符串中指定索引的字符
    console.log(str.charAt(1))

    var str1 = '你好'
    var str2 = 'String'
        //concat() 合并多个字符串
    console.log(str1.concat(str2))
        //返回该字符串在字符串中出现的索引，若不存在字符串中返回-1
    console.log(str.indexOf('p')) //-1
    console.log(str.indexOf('d')) //3
        // replace() 替换字符串中的字符，参数一：要替换的字符，参数二：替换的最终字符
    var str3 = str1.replace("你", '真')
    console.log(str3)

    var str4 = 'abcdefghijklmnopqrstuvwxyz'
        // slice()截取字符串 参数一：从第几个索引开始截取(包括当前索引)，参数二：截取到第几个索引（不包括当前索引），若不传，默认截取字符串最后。
    console.log(str4.slice(2)) //cdefghijklmnopqrstuvwxyz
    console.log(str4.slice(2, 7)) //cdefg
        //substr()截取字符串 参数一：从第几个索引开始截取，参数二：截取几个字符，若不传默认截取到最后
    console.log(str4.substr(4)) //efghijklmnopqrstuvwxyz
    console.log(str4.substr(4, 6)) //efghij
</script>

```

### 6、数组处理的方法有哪些？

##### 1. join()

功能：将数组中所有元素都转化为字符串并连接在一起。

##### 2. reverse()

功能：将数组中的元素颠倒顺序。

##### 3. concat()

功能：数组拼接的功能 ,返回新数组，原数组不受影响。

##### 4. slice()

截取数组生成新数组，原数组不受影响。
 返回的数组包含第一个参数指定的位置和所有到但不含第二个参数指定位置之间的所有元素。如果为负数，表示相对于数组中最后一个元素的位置。如果只有一个参数，表示到数组末尾。



```jsx
var aa = [1,2,3,4,5,6];
console.log(aa.slice(2)); //[3,4,5,6]
console.log(aa.slice(2,8)); //[3,4,5,6] 超过最大长度，只显示到最后结果
console.log(aa.slice(2,5)); //[3,4,5]
console.log(aa.slice(2,-1)); //[3,4,5] 相对于倒数第一个之前
console.log(aa.slice(2,-2)); //[3,4] 相对于倒数第二个之前
console.log(aa.slice(3)); //[4,5,6] 一个参数从第三个到最后
console.log(aa.slice(-2));//[5,6] 一个参数负值从倒数第二个到最后
```

##### 5. splice()

功能：从数组中删除元素、插入元素到数组中或者同时完成这两种操作。
 输入：第一个参数为指定插入或删除的起始位置，第二个参数为要删除的个数。之后的参数表示需要插入到数组中的元素 。如果只有一个参数，默认删除参数后边的所有元素。
 输出：返回一个由删除元素组成的数组。
 注意：新建了一个数组，并修改了原数组

```jsx
var aa = [1,2,3,4,5,6];
console.log(aa.splice(4)); //[5,6]  返回删除后的数组
aa; // [1,2,3,4]
console.log(aa.splice(2,2)); //[3,4] 从第二位起删除两个元素
aa; //[1,2]
console.log(aa.splice(1,0,7,8)); //[]从第一位起删除0个元素，添加7,8到原数组
aa;//[1,7,8,2]
```



##### 6. push()

在数组末尾添加一个或多个元素，并返回新数组长度

##### 7. pop()

从数组末尾删除1个元素(删且只删除1个), 并返回 被删除的元素

##### 8. shift()

在数组开始添加一个或多个元素，并返回新数组长度

##### 9. unshift()

在数组开始删除一个元素(删且只删除1个),并返回 被删除的元素

##### 10. toString()和toLocaleString()

将数组的每个元素转化为字符串，并且输入用逗号分隔的字符串列表。功能类似join();

##### 11. indexOf()和lastIndexOf()

indexOf() 两个参数：要查找的项和（可选的）表示查找起点位置的索引。其中， 从数组的开头（位置 0）开始向后查找。没找到返回-1. 返回查找项的索引值
 lastIndexOf() 从数组的末尾开始向前查找。返回查找项的索引值(索引值永远是正序的索引值),没找到返回-1

*在数学中高阶函数听起来很大上，JavaScript中也有的，其实就是把一个函数作为另一个函数的参数，不要被高阶吓到了，下边几种数组方法都属于此。*

##### A. sort();

默认情况下sort()方法没有传比较函数的话，默认按字母升序，如果不是元素不是字符串的话，会调用toString()方法将元素转化为字符串的Unicode(万国码)位点，然后再比较字符。所以用默认方法排序数据是有问题的。

```jsx
var arr = [20,10,2,1,3];
arr.sort();// [1, 10, 2, 20, 3]
arr.sort(function(a,b){
  return a-b;    //升序
}); //[1, 2, 3, 10, 20]
arr.sort(function(a,b){
  return b-a;    //降序
}); //[20,10,3,2,1]
```

##### B. forEach()

从头至尾遍历数组，为每个元素调用指定函数
 输入为一个待遍历函数，函数的参数依次为：数组元素、元素的索引、数组本身

##### C. map()

调用的数组的每一个元素传递给指定的函数，并返回一个新数组 ,不修改原数组。



```jsx
var arr = [2,3,4,5,6];
var bb= arr.map(function(x){
  return x*x;
});
console.log(bb); // [4, 9, 16, 25, 36]
```

##### D. filter()

过滤功能，数组中的每一项运行给定函数，返回满足过滤条件组成的数组。
可以巧妙的用来去重



```php
var a = [1,2,3,4,5,6,3,1];
a.filter(function(v,i,self){
  return self.indexOf(v) == i;
});
//[1, 2, 3, 4, 5, 6]
```

##### E. every()和some()

every() 判断数组中每一项都是否满足条件，只有所有项都满足条件，才会返回true。
some() 判断数组中是否存在满足条件的项，只要有一项满足条件，就会返回true。



```jsx
var arr = [1, 2, 3, 4, 5, 6];
arr.every(x=>x>0);//return true;
arr.every(x=>x>5);//return false;
arr.some(x=>x>5);//return true;
```

##### F. reduce()和reduceRight()

reduce() 两个参数：函数和递归的初始值。从数组的第一项开始，逐个遍历到最后
 reduceRight() 从数组的最后一项开始，向前遍历到第一项

```jsx
//可以用reduce快速求数组之和
var arr=[1,2,3,4];
arr.reduce(function(a,b){
  return a+b;
}); //10
```

### 7、Cookie、LocalStorage、SessionStorage的区别？

https://www.cnblogs.com/pengc/p/8714475.html

#### **Cookie基于HTTP规范，用来识别用户。**

Cookie是服务器发送到浏览器的一小段数据，会在浏览器下次向同一服务器再发起请求时被携带并发送到服务器上。

Cookie诞生之初的作用就是解决HTTP的无状态请求，用来记录一些用户相关的一些状态。

- 会话状态管理（如用户登录状态、购物车、游戏分数或其它需要记录的信息）
- 个性化设置（如用户自定义设置、主题等）
- 浏览器行为跟踪（如跟踪分析用户行为等）

因为一些前端交互的需要，后来cookie也被用于存储一些客户端的数据。

Cookie的原生api不友好，需要自行封装一下。下面是封装后的方法。



#### **webStorage基于HTML5规范**

HTML5 提供了两种在客户端存储数据的新方法：localStorage和sessionStorage，挂载在window对象下。

webStorage是本地存储，数据不是由服务器请求传递的。从而它可以存储大量的数据，而不影响网站的性能。

Web Storage的目的是为了克服由cookie带来的一些限制，当数据需要被严格控制在客户端上时，无须持续地将数据发回服务器。比如客户端需要保存的一些用户行为或数据，或从接口获取的一些短期内不会更新的数据，我们就可以利用Web Storage来存储。

**localStorage**的生命周期是永久性的。localStorage存储的数据，即使关闭浏览器，也不会让数据消失，除非主动的去删除数据。如果 想设置失效时间，需自行封装。

**sessionStorage** 的生命周期是在浏览器关闭前。

　　特性：

- 关闭浏览器sessionStorage 失效；
- 页面刷新不会消除数据；
- 只有在当前页面打开的链接，才可以访sessionStorage的数据，使用window.open打开页面和改变localtion.href方式都可以获 取到sessionStorage内部的数据;



| **存储方式**   | **作用与特性**                                               | **存储数量及大小**                                           | **api**                                                      |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| cookie         | ● 存储用户信息，获取数据需要与服务器建立连接。<br />● 可存储的数据有限，且依赖于服务器，无需请求服务器的数据尽量不要存放在cookie中，以免影响页面性能。<br />● 可设置过期时间。 | ● 最好将cookie控制在4095B以内，超出的数据会被忽略。<br />● IE6或更低版本最多存20个cookie； IE7及以上版本最多可以有50个；Firefox最多50个；chrome和Safari没有做硬性限制。 | 原生、$.cookie（详见上文）                                   |
| localStorage   | ● 存储客户端信息，无需请求服务器。<br />● 数据永久保存，除非用户手动清理客户端缓存。<br />● 开发者可自行封装一个方法，设置失效时间。 | 5M左右，各浏览器的存储空间有差异。（感兴趣的同学可以自己试一下）。 | // 保存数据到 localStoragelocalStorage.setItem('key', 'value');// 从 localStorage 获取数据let data = localStorage.getItem('key');// 从 localStorage 删除保存的数据localStorage.removeItem('key');// 从 localStorage 删除所有保存的数据localStorage.clear(); |
| sessionStorage | ● 存储客户端信息，无需请求服务器。<br />● 数据保存在当前会话，刷新页面数据不会被清除，结束会话（关闭浏览器、关闭页面、跳转页面）数据失效。 | 同localStorage                                               | // 保存数据到 sessionStoragesessionStorage.setItem('key', 'value');// 从 sessionStorage 获取数据let data = sessionStorage.getItem('key');// 从 sessionStorage 删除保存的数据sessionStorage.removeItem('key');// 从 sessionStorage 删除所有保存的数据sessionStorage.clear(); |



### 8、掌握哪些ES语法【ES6、ES7、ES8】？



### 9、有哪些数组去重的方法？

**方法一：**

双层循环，外层循环元素，内层循环时比较值

如果有相同的值则跳过，不相同则push进数组

```JavaScript
Array.prototype.distinct = function(){
 var arr = this,
  result = [],
  i,
  j,
  len = arr.length;
 for(i = 0; i < len; i++){
  for(j = i + 1; j < len; j++){
   if(arr[i] === arr[j]){
    j = ++i;
   }
  }
  result.push(arr[i]);
 }
 return result;
}
var arra = [1,2,3,4,4,1,1,2,1,1,1];
arra.distinct();    //返回[3,4,2,1]
```



**方法二：利用splice直接在原数组进行操作**

双层循环，外层循环元素，内层循环时比较值

值相同时，则删去这个值

注意点:删除元素之后，需要将数组的长度也减1.

```JavaScript
Array.prototype.distinct = function (){
 var arr = this,
  i,
  j,
  len = arr.length;
 for(i = 0; i < len; i++){
  for(j = i + 1; j < len; j++){
   if(arr[i] == arr[j]){
    arr.splice(j,1);
    len--;
    j--;
   }
  }
 }
 return arr;
};
var a = [1,2,3,4,5,6,5,3,2,4,56,4,1,2,1,1,1,1,1,1,];
var b = a.distinct();
console.log(b.toString()); //1,2,3,4,5,6,56
```

优点：简单易懂

缺点：占用内存高，速度慢

**方法三：利用对象的属性不能相同的特点进行去重**

```JavaScript
Array.prototype.distinct = function (){
 var arr = this,
  i,
  obj = {},
  result = [],
  len = arr.length;
 for(i = 0; i< arr.length; i++){
  if(!obj[arr[i]]){ //如果能查找到，证明数组元素重复了
   obj[arr[i]] = 1;
   result.push(arr[i]);
  }
 }
 return result;
};
var a = [1,2,3,4,5,6,5,3,2,4,56,4,1,2,1,1,1,1,1,1,];
var b = a.distinct();
console.log(b.toString()); //1,2,3,4,5,6,56
```

**方法四：数组递归去重**

运用递归的思想

先排序，然后从最后开始比较，遇到相同，则删除

```javascript
Array.prototype.distinct = function (){
 var arr = this,
  len = arr.length;
 arr.sort(function(a,b){  //对数组进行排序才能方便比较
  return a - b;
 })
 function loop(index){
  if(index >= 1){
   if(arr[index] === arr[index-1]){
    arr.splice(index,1);
   }
   loop(index - 1); //递归loop函数进行去重
  }
 }
 loop(len-1);
 return arr;
};
var a = [1,2,3,4,5,6,5,3,2,4,56,4,1,2,1,1,1,1,1,1,56,45,56];
var b = a.distinct();
console.log(b.toString());  //1,2,3,4,5,6,45,56
```

**方法五：利用indexOf以及forEach**

```javascript
Array.prototype.distinct = function (){
 var arr = this,
  result = [],
  len = arr.length;
 arr.forEach(function(v, i ,arr){  //这里利用map，filter方法也可以实现
  var bool = arr.indexOf(v,i+1);  //从传入参数的下一个索引值开始寻找是否存在重复
  if(bool === -1){
   result.push(v);
  }
 })
 return result;
};
var a = [1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,2,3,3,2,2,1,23,1,23,2,3,2,3,2,3];
var b = a.distinct();
console.log(b.toString()); //1,23,2,3
```

**方法六：利用ES6的set**

Set数据结构，它类似于数组，其成员的值都是唯一的。

利用Array.from将Set结构转换成数组

```javascript
function dedupe(array){
 return Array.from(new Set(array));
}
dedupe([1,1,2,3]) //[1,2,3]
```

拓展运算符(...)内部使用for...of循环

```javascript
let arr = [1,2,3,3];
let resultarr = [...new Set(arr)]; 
console.log(resultarr); //[1,2,3]
```



### 10、什么是闭包？闭包有哪些好处？解决了什么问题？

https://blog.csdn.net/weixin_39624389/article/details/110906531

一个函数和对其周围状态（**lexical environment，词法环境**）的引用捆绑在一起（或者说函数被引用包围），这样的组合就是**闭包**（**closure**）。也就是说，闭包让你可以在一个内层函数中访问到其外层函数的作用域。在 JavaScript 中，每当创建一个函数，闭包就会在函数创建的同时被创建出来。

**总结：闭包就是一个函数引用另外一个函数的变量，因为变量被引用着所以不会被回收，因此可以用来封装一个私有变量。**

#### (2)闭包的用途

闭包可以用在许多地方。它的最大用处有两个， 一个是前面提到的可以读取函数内部的变量，另一个就是让这些变量的值始终保持在内存中 。

#### (3)闭包的实际应用

使用闭包，我们可以做很多事情。比如模拟面向对象的代码风格；更优雅，更简洁的表达出代码；在某些方面提升代码的执行效率。



### 11、什么是防抖节流？做防抖节流是解决了什么问题？

在进行窗口的resize、scroll，输入框内容校验等操作时，如果事件处理函数调用的频率无限制，会加重浏览器的负担，导致用户体验非常糟糕。
此时我们可以采用debounce（防抖）和throttle（节流）的方式来减少调用频率，同时又不影响实际效果。

#### 函数防抖（debounce）：

当持续触发事件时，一定时间段内没有再触发事件，事件处理函数才会执行一次，如果设定的时间到来之前，又一次触发了事件，就重新开始延时。
如下，持续触发scroll事件时，并不执行handle函数，当1000毫秒内没有触发scroll事件时，才会延时触发scroll事件。

```js
function debounce(fn, wait) { 
 var timeout = null; 
 return function() { 
  if(timeout !== null) clearTimeout(timeout);           
  timeout = setTimeout(fn, wait); 
 } 
} 
// 处理函数 
function handle() {      
 console.log(Math.random()); 
} 
// 滚动事件
window.addEventListener('scroll', debounce(handle, 1000)); //函数节流 
```

#### 函数节流（throttle）：

当持续触发事件时，保证一定时间段内只调用一次事件处理函数。
节流通俗解释就比如我们水龙头放水，阀门一打开，水哗哗的往下流，秉着勤俭节约的优良传统美德，我们要把水龙头关小点，最好是如我们心意按照一定规律在某个时间间隔内一滴一滴的往下滴。
如下，持续触发scroll事件时，并不立即执行handle函数，每隔1000毫秒才会执行一次handle函数。

```js
var throttle =function(func, delay) { 
 var prev = Date.now(); 
 return function() { 
  var context = this;
  var args = arguments; 
  var now = Date.now(); 
  if (now - prev >= delay) { 
   func.apply(context, args);                           
   prev = Date.now();
  } 
 } 
}
function handle() {              
 console.log(Math.random()); 
}         
window.addEventListener('scroll', throttle(handle, 1000)); 
```

#### 总结

#### 函数防抖：

将几次操作合并为一此操作进行。原理是维护一个计时器，规定在delay时间后触发函数，但是在delay时间内再次触发的话，就会取消之前的计时器而重新设置。这样一来，只有最后一次操作能被触发。

#### 函数节流：

使得一定时间内只触发一次函数。原理是通过判断是否到达一定时间来触发函数。 区别：
函数节流不管事件触发有多频繁，都会保证在规定时间内一定会执行一次真正的事件处理函数，而函数防抖只是在最后一次事件后才触发一次函数。比如在页面的无限加载场景下，我们需要用户在滚动页面时，每隔一段时间发一次
Ajax 请求，而不是在用户停下滚动页面操作时才去请求数据。这样的场景，就适合用节流技术来实现。



### 12、什么是深拷贝、浅拷贝，为什么要做数据拷贝？



### 13、让div在父元素中水平垂直居中的方法【CSS相关知识】？



### 14、请谈一谈迭代器？



### 15、对Promise的理解？



### 16、数组、链表的区别？



### 17.理解堆栈溢出和内存泄漏的原理，如何防止

**堆栈溢出**：由于过多的函数调用，导致调用堆栈无法容纳这些调用的返回地址，一般在递归中产生。堆栈溢出很可能由无限递归产生，但也可能仅仅是过多的堆栈层级。

**内存泄漏**：是指你向系统申请分配内存进行使用(new)，可是使用完了以后却不归还(delete)，结果你申请到的那块内存你自己也不能再访问(也许你把它的地址给弄丢了)，而系统也不能再次将它分配给需要的程序。简单的理解就是不再使用的内存，没有及时释放，就是内存泄漏。

如何防止：**对于递归导致的堆栈溢出，常用的方法就是使用闭包或匿名函数；对于内存泄漏常见的方法就是再不实用变量的时候，解除引用，或指向null。**

