package com.abin.stream;

import com.abin.funcref.entity.Person;
import com.abin.stream.pojo.Student;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Optional;
import java.util.stream.Collectors;
import jdk.nashorn.api.scripting.ScriptUtils;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest23polymerize {

  public static void main(String[] args) {
    HashSet<Student> students = new HashSet<>();
    students.add(new Student("zhangsan", 18, 82));
    students.add(new Student("lisi", 16, 92));
    students.add(new Student("jack", 20, 62));
    students.add(new Student("marry", 28, 59));
    students.add(new Student("tom", 26, 80));

    Optional<Student> maxAgePerson = students.stream()
        .map((student) -> {
          student.setScore(student.getScore() + 1); //每人的成绩加1
          return student;
        })
        .collect(Collectors.maxBy((x, y) -> x.getAge() - y.getAge()));
    System.out.println("年龄最大的Person = " + maxAgePerson.get());

    Optional<Student> minAgePerson = students.stream()
        .map((student) -> {
          student.setScore(student.getScore() + 1); //每人的成绩加一
          return student;
        })
        .collect(Collectors.minBy((x, y) -> x.getAge() - y.getAge()));
    System.out.println("年龄最小的Person = " + minAgePerson.get());

    Integer ageSum = students.stream()
        .collect(Collectors.summingInt(s -> s.getAge()));
    System.out.println("年龄之和为: " + ageSum);

    Double average = students.stream()
        .collect(Collectors.averagingInt(Student::getScore));
    System.out.println("平均成绩: " + average);

    Long count = students.stream()
        .collect(Collectors.counting());
    System.out.println("Person人数: " + count);
  }
}
