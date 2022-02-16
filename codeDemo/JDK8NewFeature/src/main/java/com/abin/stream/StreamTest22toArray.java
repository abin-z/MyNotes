package com.abin.stream;

import com.abin.funcref.entity.Person;
import java.util.ArrayList;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest22toArray {

  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三丰", 21));
    people.add(new Person("李四", 20));
    people.add(new Person("王五", 17));
    people.add(new Person("麦克", 16));

    //将stream流转化为数组, toArray()没有指定类型直接转为Object
    Object[] objects = people.stream().toArray();
    for (Object o : objects) {
      if (o instanceof Person) {
        Person person = (Person) o;
        System.out.println("person.getName() = " + person.getName());
      }
    }

    //将stream流转化为指定类型的数组,
    Person[] people1 = people.stream().toArray(Person[]::new);
    for (Person person : people1) {
      System.out.println(person);
    }
  }
}
