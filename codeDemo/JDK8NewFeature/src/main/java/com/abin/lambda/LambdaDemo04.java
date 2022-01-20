package com.abin.lambda;

import com.abin.lambda.Entity.Person;
import com.abin.lambda.userService.PersonService;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * @author Abin
 * @date 2022/01/19
 */
public class LambdaDemo04 {

  public static void main(String[] args) {
    Person person = new Person("张三", 19);
    //使用匿名内部类的方式
    Integer age = function(person, new PersonService() {
      @Override
      public Integer getPersonAge(Person person) {
        return person.getAge();
      }
    });
    System.out.println("age = " + age);

    //使用Lambda表达式
    Integer age1 = function(person, p -> p.getAge()); //这里的p 只是形参
    System.out.println("age1 = " + age1);

    Integer integer = function(person, Person::getAge); //方法引用的Lambda表达式
    System.out.println(integer);
  }

  public static Integer function(Person person, PersonService personService) {
    return personService.getPersonAge(person);
  }
}
