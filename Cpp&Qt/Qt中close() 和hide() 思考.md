# close()和hide()的思考



### 1. close()函数的梳理

`close()`在不设定窗口属性为`Qt::WA_DeleteOnClose`时（`QWidget::setAttribute(Qt::WidgetAttribute attribute, bool on = true)`），就是调用`hide()`函数。



`Qt`的窗口`close()`之后，**不是**马上就不存在了（`看对窗口属性的设置`），指向窗口的指针**还不一定**马上调用它的`析构函数`。



#### QWidget的close()函数在帮助文档中是这样的：

Closes this widget. Returns true if the widget was closed; otherwise returns false.
**关闭窗口，当窗口关闭了返回true，否则false**

First it sends the widget a QCloseEvent. The widget is hidden if it accepts the close event. If it ignores the event, nothing happens. The default implementation of QWidget::closeEvent() accepts the close event.
**首先这个函数会产生一个QCloseEvent事件，如果接受了这个事件（默认调用QWidget::closeEvent()接受这个关闭事件），它就调用hide()函数，隐藏界面。如果忽略这个事件，什么事情都不会发生。**

If the widget has the Qt::WA_DeleteOnClose flag, the widget is also deleted. A close events is delivered to the widget no matter if the widget is visible or not.
**如果窗口设置过标记位：Qt::WA_DeleteOnClose（关闭时销毁窗口），则出来调用hide()外，还会调用deleteLater()函数。不管窗口显示或者不显示，关闭事件都会发送给窗体。**



### 2. QWidget 的 show()、hide()、setVisible()、setHidden()



**QWidget 的show()、hide()、setVisible()、setHidden()** 这4个函数最终调用的只是一个函数：**setVisible(bool visible)**。

这4个函数中只有 setVisible 是独立的，它使得一个Widget可见或不可见，其他3个函数都在调用它。

**setVisible(false)代表Widget不在界面上显示，但是对象还存在，没有被销毁析构。**



### 3.QDialog 的 exec()、open()、done()、reject ()和 accept ()

```C++
QDialog::show()
//非模态窗口显示，但是如果在窗口中显示设置为模态对话框：setModal (true)，则显示半模态对话框。

QDailog::open()
//模态(窗口级)窗口显示。

QDialog::exec()
//模态(应用程序级)窗口显示。exec() 先设置modal属性，而后调用 show() 显示对话框，
//最后启用事件循环。在用户关闭这个对话框之前，不能和同一应用程序中的其它窗口交互。

QDialog::done(int)
//和close比较类似，因为它调用了close所调用的 close_helper 函数。
//只不过不同于close函数，它始终会先让Widget不可见，然后close操作，最后根据参数发射信号。

QDialog::reject()
//调用done()函数，源码为：done(Rejected)。

QDialog::accept()
//调用done()函数，源码为：done(Accepted)。

```



## close()和hide()的区别

hide只是隐藏窗体。不会发送任何信号。
close一般也是隐藏窗口。但是它会发送QCloseEvent事件。你可以重写void QWidget::closeEvent(QCloseEvent * event) [virtual protected]，可以隐藏widget或者不隐藏。

Qt::WA_DeleteOnClose标志还会影响窗体在内存中的状态，如果设置了该标志，窗体就会被删除，而hide则不会。最后主窗体的close会导致整个程序的退出，而hide明显不会。

*PS：再对一个窗体调用close函数后，如果再调用show()，这个窗体又会被显示出来。***?**

