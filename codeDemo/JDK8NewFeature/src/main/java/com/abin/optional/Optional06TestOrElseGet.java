package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional06TestOrElseGet {

  public static void main(String[] args) {
    Person person = new Person();

    Optional<Person> op1 = Optional.of(person);
    Optional<Person> op2 = Optional.empty();

    Person person1 = op1.orElseGet(() -> {
      System.out.println("默认操作pppp1");
      return new Person("test", 20);
    });

    Person person2 = op2.orElseGet(() -> {
      System.out.println("默认操作pppp2");
      return new Person("test", 10);
    });

    System.out.println("person1 = " + person1);
    System.out.println("person2 = " + person2);
  }
}
