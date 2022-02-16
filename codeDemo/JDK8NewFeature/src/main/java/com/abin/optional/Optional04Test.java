package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional04Test {

  public static void main(String[] args) {
    Person person1 = new Person();
    Person person2 = null;

    Optional<Person> op1 = Optional.of(person1);
    Optional<Person> op2 = Optional.empty();

    if (op1.isPresent()) {
      System.out.println("op1.get() = " + op1.get());
    } else {
      System.out.println("op1 是一个空Optional对象");
    }

    if (op2.isPresent()) {
      System.out.println("op2.get() = " + op2.get());
    } else {
      System.out.println("op2 是一个空Optional对象");
    }
  }
}
