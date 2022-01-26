package com.abin.stream;

import com.abin.funcref.entity.Person;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest21collectTomap {

  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 21));
    people.add(new Person("李四", 20));
    people.add(new Person("王五", 17));
    people.add(new Person("麦克", 16));

    //将stream流转化为map集合
    Map<Person, String> map = people.stream()
        .collect(Collectors.toMap(Function.identity(),   //如何生成key
            Person::getName));  //如何生成value

    Set<Person> keySet = map.keySet();
    for (Person person : keySet) {
      System.out.println(person);
    }

    Collection<String> values = map.values();
    for (String value : values) {
      System.out.println(value);
    }

    System.out.println("===============");
    //将人员分为成年和未成年两部分
    Map<Boolean, List<Person>> listMap = people.stream()
        .collect(Collectors.partitioningBy(person -> person.getAge() >= 18));
    System.out.println(listMap);
  }
}
