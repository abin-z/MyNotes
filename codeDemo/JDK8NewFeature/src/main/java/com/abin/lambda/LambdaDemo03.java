package com.abin.lambda;

import com.abin.lambda.Entity.Person;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/19
 */
public class LambdaDemo03 {

  public static void main(String[] args) {
    List<Person> persons = new ArrayList<>();
    persons.add(new Person("tom", 18));
    persons.add(new Person("jack", 13));
    persons.add(new Person("marry", 16));
    persons.add(new Person("tony", 28));
    persons.add(new Person("keb", 26));

    //使用匿名内部类实现进行排序输出, 升序
    Collections.sort(persons, new Comparator<Person>() {
      @Override
      public int compare(Person o1, Person o2) {
        return o1.getAge() - o2.getAge();
      }
    });
    //使用Lambda表达式实现, 降序
    Collections.sort(persons, (o1, o2) -> o2.getAge() - o1.getAge());

    //??? 升序
    Collections.sort(persons, Comparator.comparingInt(Person::getAge));
    //遍历输出
    for (Person person : persons) {
      System.out.println(person);
    }
  }
}
