# Qt中限制用户的输入



### 限制LineEdit禁止输入中文字符

**可以向lineEdit中添加QValidator验证器**

```c++
QRegExp regx("[^\u4e00-\u9fa5]*");  //不能是中文字符, 正则表达式
QValidator *validator = new QRegExpValidator(regx);//创建一个验证器, 父类指针指向子类对象地址
ui.txt_name->setValidator(validator);//name,var1,var2不能为中文
ui.txt_var1->setValidator(validator);
ui.txt_var2->setValidator(validator);
```



# QTableWidget 的相关设置



​		**QTableWidget是QT程序中常用的显示数据表格的空间，很类似于VC、C#中的DataGrid。说到QTableWidget，就必须讲一下它跟QTabelView的区别了。QTableWidget是QTableView的子类，主要的区别是QTableView可以使用自定义的数据模型来显示内容(也就是先要通过setModel来绑定数据源)，而QTableWidget则只能使用标准的数据模型，并且其单元格数据是QTableWidgetItem的对象来实现的(也就是不需要数据源，将逐个单元格内的信息填好即可)。这主要体现在QTableView类中有setModel成员函数，而到了QTableWidget类中，该成员函数变成了私有。使用QTableWidget就离不开QTableWidgetItem。QTableWidgetItem用来表示表格中的一个单元格，正个表格都需要用逐个单元格构建起来。**





```C++ 
	//目的是去除换行符,保证能够文字能够居中显示
	QStringList title_list = QString(openFile.readLine()).replace("\n", " ").split("\t", QString::SkipEmptyParts);
	int col = title_list.count();
	ui.tableWidget->setRowCount(row);//设置行数
	ui.tableWidget->setColumnCount(col);//设置列数
	ui.tableWidget->setHorizontalHeaderLabels(title_list);//设置表头
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头自动撑满
	ui.tableWidget->horizontalHeader()->setMinimumHeight(30);//设置表头高度
	ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//表头内容居中
	ui.tableWidget->horizontalHeader()->
		setStyleSheet("QHeaderView::section{background:#0078d7;border:1px solid #6c6c6c;color:#ffffff}");//设置表头颜色
	ui.tableWidget->setAlternatingRowColors(true);//设置相邻行颜色交替

	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置禁止编辑
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中整行
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能单选
	ui.tableWidget->verticalHeader()->setVisible(false);//隐藏垂直表头


	//一行一行的添加数据
		for (int i = 0; i < col; i++){
			QTableWidgetItem *item = new QTableWidgetItem();//Qt中tableWidget的每一单元格都是用QTableWidgetItem来管理的(也可以用QWidget其他控件代理)
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置字体居中
			ui.tableWidget->setItem(row - 1, i, item);
			ui.tableWidget->item(row - 1, i)->setText(temp_list[i]);
		}
```



### 使用LineEdit代理QTableWidgetItem, 需要注意的是要向下转型(父类->子类)

```c++
	//当m_item里面没有数据是则进入初始化操作
	if (row_num == 0)
	{
		//为table时给第一列数据添加相应的数据
		if (type == "table")
		{
			for (int i = 0; i < row; i++)
			{
				//ui.tableWidget->item(i, 0)->setText("7.889e-31");
				QWidget* item_t = ui.tableWidget->cellWidget(i, 0);//返回的是一个QWidget* 
				QLineEdit* edit_t = qobject_cast<QLineEdit*>(item_t);//需要向下转型为QLineEdit* 
				edit_t->setText("0.00000");
			}
		}
	}
	else//当m_item里面存在数据则进入回显操作
	{
		for (int i = 0; i < row_num; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//ui.tableWidget->item(i, j)->setText(m_item->m_table[i][j]);
				QWidget* item_t = ui.tableWidget->cellWidget(i, j);
				QLineEdit* edit_t = qobject_cast<QLineEdit*>(item_t);
				edit_t->setText(m_item->m_table[i][j]);
			}
		}
	}
```









### QTableWidget相关链接



[**1.QTableWidget用法**](https://blog.csdn.net/qq_35040828/article/details/70208240)

[**2.Qt控件之QTableWidget**](https://www.cnblogs.com/retry/p/9329397.html)

