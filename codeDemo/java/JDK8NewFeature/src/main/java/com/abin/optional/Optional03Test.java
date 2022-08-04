package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional03Test {

  public static void main(String[] args) {
    Person person = new Person();
    Person p1 = null;
    Optional<Person> op1 = Optional.of(person);
    Optional<Object> empty = Optional.empty();

    System.out.println("op1.get() = " + op1.get());     //获取person的值
    System.out.println("empty.get() = " + empty.get()); //抛异常
  }
}
