package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional05TestOrElse {

  public static void main(String[] args) {
    Person person = new Person();

    Optional<Person> op1 = Optional.of(person);
    Optional<Person> op2 = Optional.empty();

    Person person1 = op1.orElse(new Person("张三", 18));
    Person person2 = op2.orElse(new Person("李四", 20));

    System.out.println("person1 = " + person1);
    System.out.println("person2 = " + person2);
  }
}
