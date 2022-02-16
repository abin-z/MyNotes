package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional02Test {

  //Optional对象的创建方式
  public static void main(String[] args) {
    Person person = new Person();
    Person p1 = null;

    // 第一种方法: of()方法,  of方法不支持 null, 否则将抛出NullPointerException
    Optional<Person> op1 = Optional.of(person);
    System.out.println("op1 = " + op1.get());
//    Optional<Person> op = Optional.of(p1);

    //第二种方式: ofNullable方法, 支持null
    Optional<Person> op2 = Optional.ofNullable(person);
    Optional<Object> op3 = Optional.ofNullable(null);

    //第三种方式: 使用 empty() 方法, 直接创建一个空的Optional对象
    Optional<Object> empty = Optional.empty();
  }
}
