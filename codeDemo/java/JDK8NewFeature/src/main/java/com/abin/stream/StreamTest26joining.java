package com.abin.stream;

import com.abin.stream.pojo.Student;
import java.util.ArrayList;
import java.util.stream.Collectors;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest26joining {

  public static void main(String[] args) {
    ArrayList<Student> students = new ArrayList<>();
    students.add(new Student("zhangsan", 20, 48));
    students.add(new Student("lisi", 16, 92));
    students.add(new Student("jack", 16, 62));
    students.add(new Student("marry", 20, 59));
    students.add(new Student("xiaoming", 16, 82));

    String all = students.stream()
        .map(Student::getName)
        .collect(Collectors.joining());   //直接拼接
    System.out.println(all);

    String all2 = students.stream()
        .map(Student::getName)
        .collect(Collectors.joining("_"));  //使用 _ 作为分隔符拼接
    System.out.println(all2);

    String all3 = students.stream()
        .map(Student::getName)
        .collect(Collectors.joining("_", "***", "&&&")); //分隔符, 前缀, 后缀
    System.out.println(all3);

  }
}
