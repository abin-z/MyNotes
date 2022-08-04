package com.abin.stream;


import com.abin.funcref.entity.Person;
import java.util.ArrayList;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest12distinct02 {

  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 19));
    people.add(new Person("李四", 19));
    people.add(new Person("张三", 19));
    people.add(new Person("小明", 23));
    people.add(new Person("张三", 19, 175.0));

    people.stream()
        .distinct()    //自定义类型没有重写equals和hashcode方法时可能不是自己想要的去重
        .forEach(System.out::println);
  }
}
