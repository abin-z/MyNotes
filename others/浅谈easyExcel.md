# POI -easyExcel

## 1.POI and easyexcel

POI：

POI是Apache软件基金会的，POI为“Poor Obfuscation Implementation”的首字母缩写，意为“简洁版的模糊实现”。
所以POI的主要功能是可以用Java操作Microsoft Office的相关文件。

POI的依赖：（只需要03和07版本的依赖）

```xml
		<!--excel03版本-->
        <dependency>
            <groupId>org.apache.poi</groupId>
            <artifactId>poi</artifactId>
            <version>3.15</version>
        </dependency>

        <!--excel07版本-->
        <dependency>
            <groupId>org.apache.poi</groupId>
            <artifactId>poi-ooxml</artifactId>
            <version>3.15</version>
        </dependency>

        <!--时间格式-->
        <dependency>
            <groupId>joda-time</groupId>
            <artifactId>joda-time</artifactId>
            <version>2.10.1</version>
        </dependency>

        <!--测试-->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>3.8.2</version>
            <scope>test</scope>
        </dependency>
```

**HSSF：Excel97-2003版本，扩展名为.xls。一个sheet最大行数65536，最大列数256。**

**XSSF：Excel2007版本开始，扩展名为.xlsx。一个sheet最大行数1048576，最大列数16384。**

**SXSSF：是在XSSF基础上，POI3.8版本开始提供的支持低内存占用的操作方式，扩展名为.xlsx。**



## 2.POI-Excel写

**编写思路：**

1.创建工作簿

2.创建表头

3.创建行

4.创建单元格

5.写出

6.关闭输出流

例子：

```java
	String path = "D:\\项目地址\\项目名称";//根据自己的项目地址进行修改

	@Test
    public void testWrite() throws Exception {

        //创建工作簿03版本的excel
        Workbook workbook = new HSSFWorkbook();
        //07版本的excel
        //Workbook workbook = new XSSFWorkbook();
        //创建表头
        Sheet sheet = workbook.createSheet("zz");
        //创建行
        Row row1 = sheet.createRow(0);
        //创建单元格（1，1）
        Cell cell11 = row1.createCell(0);
        //设置值
        cell11.setCellValue("今日日期");
        //创建单元格（1.2）
        Cell cell12 = row1.createCell(1);
        cell12.setCellValue(new DateTime().toString("yyyy-mm-dd HH:mm:ss"));

        //创建第二行
        Row row2 = sheet.createRow(1);
        //创建单元格（2,1）
        Cell cell21 = row2.createCell(0);
        cell21.setCellValue("人数");
        //创建单元格（2,2）
        Cell cell22 = row2.createCell(1);
        cell22.setCellValue(666);

        //生成表03版本文件后缀.xls
        FileOutputStream fileOutputStream = new FileOutputStream(path + "03.xls");
        //07版本文件后缀.xlsx
        //FileOutputStream fileOutputStream = new FileOutputStream(path + "07excel大数据.xlsx")
        
        //输出
        workbook.write(fileOutputStream);

        //关闭流
        fileOutputStream.close();

        System.out.println("03Excel已生成");

    }
```

**注意：创建工作簿的时候需要选择版本（HSSFWorkbook,XSSFWorkbook,SXSSFWorkbook）,通过流写出的时候需要加上后缀（03位.xls，07的为.xlsx）**

## 3.POI-Excel读

**读取思路：**

1.获取文件

2.创建工作簿

3.获取表头

4.获取行

5.获取列

6.关闭流

03版本

```java
 String path = "D:\\ideaworkspace\\com.poi";

    @Test
    public void testRead03() throws Exception {

        //创建文件流
        FileInputStream inputStream = new FileInputStream(path + "03.xls");
        //创建工作簿
        Workbook workbook = new HSSFWorkbook(inputStream);
        //获取表头
        Sheet sheet = workbook.getSheetAt(0);
        //获取行
        Row row = sheet.getRow(0);
        //获取单元格
        Cell cell = row.getCell(0);

        //获取字符串类型
        System.out.println(cell.getStringCellValue());
        inputStream.close();

    }
```

**注意：读取需要看版本类型是否正确**

07版本

```
 @Test
    public void testRead07() throws Exception {

        //创建文件流
        FileInputStream inputStream = new FileInputStream(path + "07.xlsx");
        //创建工作簿
        Workbook workbook = new XSSFWorkbook(inputStream);
        //获取表头
        Sheet sheet = workbook.getSheetAt(0);
        //获取行
        Row row = sheet.getRow(0);
        //获取单元格
        Cell cell = row.getCell(0);

        //获取字符串类型
        System.out.println(cell.getStringCellValue());
        inputStream.close();
    }
```

读取不同数据类型

**思路：**

1.获取表中的数据

2.获取行

3.遍历行

4.获取行的列数

5.遍历列数

6.判断类型（switch）

7.输出每行的值和数据类型

8.关闭流

```java
	 String path = "D:\\ideaworkspace\\com.poi";

@Test
    public void testRead03() throws Exception {

        //创建文件流
        FileInputStream inputStream = new FileInputStream(path + "03测试.xls");
        //创建工作簿
        Workbook workbook = new HSSFWorkbook(inputStream);
        //获取表头
        Sheet sheet = workbook.getSheetAt(0);

        //获取标题内容
        Row rowTitle = sheet.getRow(0);
        if (rowTitle != null) {
            //获取标题长度
            int cellCount = rowTitle.getPhysicalNumberOfCells();
            //遍历每一个标题
            for (int cellNum = 0; cellNum <cellCount; cellNum++) {
                Cell cell = rowTitle.getCell(cellNum);
                if (cell != null) {
                    //获取单元格类型
                    int cellType = cell.getCellType();
                    //获取单元格的值
                    String cellValue = cell.getStringCellValue();
                    System.out.print(cellValue + "|");
                }
            }
            System.out.println();
        }
        //获取表中的数据
        int rowCount = sheet.getPhysicalNumberOfRows();
        for (int rowNum = 1; rowNum < rowCount; rowNum++) {
            //读取某个行
            Row rowData = sheet.getRow(rowNum);
            if (rowData != null) {
                //获取所有的列
                int cellCount = rowTitle.getPhysicalNumberOfCells();
                for (int cellNum = 0; cellNum < cellCount; cellNum++) {
                    System.out.print("[" + (rowNum + 1) + "-" + (cellNum + 1) + "]");

                    Cell cell = rowData.getCell(cellNum);
                    //匹配列的数据类型
                    if (cell != null) {
                        int cellType = cell.getCellType();
                        String cellValue = "";

                        switch (cellType) {
                            case HSSFCell
                                    .CELL_TYPE_STRING: //字符串
                                System.out.print("String:");
                                cellValue = cell.getStringCellValue();
                                break;
                            case HSSFCell
                                    .CELL_TYPE_BOOLEAN: //布尔值
                                System.out.print("boolean:");
                                cellValue = String.valueOf(cell.getBooleanCellValue());
                                break;
                            case HSSFCell
                                    .CELL_TYPE_BLANK: //空
                                System.out.print("bank:");
                                break;
                            case HSSFCell
                                    .CELL_TYPE_NUMERIC: //数字（日期，普通数字）
                                System.out.print("member:");
                                if (HSSFDateUtil.isCellDateFormatted(cell)) {
                                    System.out.println("日期");
                                    Date date = cell.getDateCellValue();
                                    cellValue = new DateTime(date).toString("yyyy-MM-dd");
                                } else {
                                    //不是日期格式，防止数字过长
                                    System.out.println("普通数字转换为字符串:");
                                    cell.setCellType(HSSFCell.CELL_TYPE_STRING);
                                    cellValue = cell.toString();
                                }
                                break;

                            case HSSFCell
                                    .CELL_TYPE_ERROR:
                                System.out.println("数据类型错误:");
                                break;
                            default:
                                break;
                        }
                        System.out.println(cellValue);
                    }
                } 
            }
        }
        inputStream.close();
    }

```

**注意：判断数字的时候有两种，第二种不是日期格式需要设置它的类型，然后在赋值。03版本后缀.xls；07版本后缀.xls。最后不要忘记关闭流了。**

**延伸：可以将这个方法提取出来。**



读取计算公式

**思路：**

1.获取文件

2.创建工作簿

3.获取数据

4.获取计算公式

5.类型判断

6.输出计算公式

7.输出计算好了的值

8.关闭流

```java
@Test
    public void readFormat() throws Exception{
        //获取文件
        FileInputStream inputStream = new FileInputStream(path + "03公式.xls");

        //创建工作簿
        Workbook workbook = new HSSFWorkbook(inputStream);
        //获取总分
        Sheet sheet = workbook.getSheetAt(0);
        Row row = sheet.getRow(4);
        Cell cell = row.getCell(0);

        //获取计算公式
        FormulaEvaluator formulaEvaluator = new HSSFFormulaEvaluator((HSSFWorkbook) workbook);

        //获取单元格的格式
        int cellType = cell.getCellType();
        switch(cellType){
            //公式
            case Cell.CELL_TYPE_FORMULA:
                String cellFormula = cell.getCellFormula();
                System.out.println(cellFormula);
            //计算并输出
            CellValue evaluate = formulaEvaluator.evaluate(cell);
                String cellValue = evaluate.formatAsString();
                System.out.println(cellValue);
                break;
            default:
                break;
        }
        inputStream.close();
```

***注意：获取的文件数据是求和的类型，获取的数据需要准确，不要忘记关闭流。***



## 4.easy-Excel操作

easyExcel网站：https://www.yuque.com/easyexcel



导入依赖

```java
 <!--导入easyExcel-->
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>easyexcel</artifactId>
            <version>2.2.0-beta2</version>
        </dependency>
```

**注意：导入这个依赖之后，需要注释掉之前的poi依赖，避免重复。**



写入测试

 **思路**

1.添加依赖

2.建立实体类

3.模拟遍历数据

4.编写easyExcel写的方法

```java
@Data
public class DemoData {
    @ExcelProperty("字符串标题")
    private String string;
    @ExcelProperty("日期标题")
    private Date date;
    @ExcelProperty("数字标题")
    private Double doubleData;
    /**
     * 忽略这个字段
     */
    @ExcelIgnore
    private String ignore;
}

public class EasyTest {
    private List<DemoData> data() {
        List<DemoData> list = new ArrayList();
        for (int i = 0; i < 10; i++) {
            DemoData data = new DemoData();
            data.setString("字符串" + i);
            data.setDate(new Date());
            data.setDoubleData(0.56);
            list.add(data);
        }
        return list;
    }

    /**
     * 最简单的写
     * <p>1. 创建excel对应的实体对象 参照{@link DemoData}
     * <p>2. 直接写即可
     */
    @Test
    public void simpleWrite() {

        String path = "D:\\ideaworkspace\\com.poi";
        // 写法1
        String fileName = path + "easyTest.xlsx";
        // 这里 需要指定写用哪个class去写，然后写到第一个sheet，名字为模板 然后文件流会自动关闭
        // 如果这里想使用03 则 传入excelType参数即可
        EasyExcel.write(fileName, DemoData.class).sheet("模板").doWrite(data());
    }
}

```

**解释**

fileName:目录名；DemoData.class实体类；sheet("模板")表头名称；doWrite（data()）编写方法，data()编写的内容,这个内容是可以自己定义的。

实例：

![image-20210324094904613](C:\Users\SNT3200G8G512G\AppData\Roaming\Typora\typora-user-images\image-20210324094904613.png)





读取easyExcel：

**思路**：

1.建立dao类，进行数据存储

2.建立easyExcel时间监听器

3.测试

学习网址：https://www.yuque.com/easyexcel/doc/read



**easyExcel规则**：

写入：根据类的格式进行写入。

读取：根据监听设置的规则进行读取。



## 5.总结

掌握面向对象思想、面向接口编程。

理解使用测试api

任务：把easyExcel的所有的api都测试一下。