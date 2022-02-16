package com.abin.stream;

import com.abin.stream.pojo.Student;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest25partitioningBy {

  public static void main(String[] args) {
    ArrayList<Student> students = new ArrayList<>();
    students.add(new Student("zhangsan", 20, 48));
    students.add(new Student("lisi", 16, 92));
    students.add(new Student("jack", 16, 62));
    students.add(new Student("marry", 20, 59));
    students.add(new Student("xiaoming", 16, 82));

    Map<Boolean, List<Student>> map = students.stream()
        .collect(Collectors.partitioningBy(student -> student.getAge() >= 18));
    map.forEach((k, v) -> System.out.println("k = " + k + "  v = " + v));
  }
}
