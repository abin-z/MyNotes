package com.abin.stream;

import com.abin.funcref.entity.Person;
import java.util.ArrayList;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest17mapANDreduce {

  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("小明", 19));
    people.add(new Person("小明亮", 18));
    people.add(new Person("小红", 16));
    people.add(new Person("汤姆", 26));
    people.add(new Person("佩奇", 20));

    //求出所有人员的年龄中和
    Integer maxAge = people.stream()
//        .map(p -> p.getAge())
        .map(Person::getAge)    //map对数据类型进行转换
        .reduce(0, (x, y) -> x > y ? x : y);  //reduce对数据进行归约
    System.out.println("maxAge = " + maxAge);

    //求出所有人员的年龄总和
    Integer sumAge = people.stream()
        .map(Person::getAge)
        .reduce(0, Integer::sum);
    System.out.println("sumAge = " + sumAge);

    //获取"a"出现的次数
    Integer count = Stream.of("a", "c", "v", "s", "a", "a")
        .map(s -> "a".equals(s) ? 1 : 0)
        .reduce(0, Integer::sum);
    System.out.println("count = " + count);
  }
}
