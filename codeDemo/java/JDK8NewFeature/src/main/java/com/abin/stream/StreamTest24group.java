package com.abin.stream;

import com.abin.stream.pojo.Student;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest24group {

  public static void main(String[] args) {
    HashSet<Student> students = new HashSet<>();
    students.add(new Student("zhangsan", 20, 48));
    students.add(new Student("lisi", 16, 92));
    students.add(new Student("jack", 16, 62));
    students.add(new Student("marry", 20, 59));
    students.add(new Student("tom", 16, 82));

    Map<String, List<Student>> map = students.stream()
        .collect(Collectors.groupingBy(s -> s.getAge() >= 18 ? "成年" : "未成年"));
    map.forEach((k, v) -> System.out.println("K=" + k + " v=" + v));
    System.out.println("============");
    Map<String, List<Student>> map1 = students.stream()
        .collect(Collectors.groupingBy(student -> student.getScore() >= 60 ? "成绩合格" : "成绩不合格"));
    map1.forEach((k, v) -> System.out.println("K=" + k + " v=" + v));

    System.out.println("==========多级分组==========");
    Map<Integer, Map<String, List<Student>>> mapMap = students.stream()
        .collect(Collectors.groupingBy(
            Student::getAge,
            Collectors.groupingBy(s -> s.getScore() >= 60 ? "及格" : "不及格")));
    mapMap.forEach(
        (k1, v1) -> {
          System.out.println(k1);
          v1.forEach(
              (k2, v2) -> System.out.println(k2 + ": v2 = " + v2)
          );
        }
    );

  }
}
