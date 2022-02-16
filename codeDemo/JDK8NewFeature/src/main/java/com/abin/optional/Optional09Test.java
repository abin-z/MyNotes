package com.abin.optional;

import com.abin.funcref.entity.Person;
import java.time.Period;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional09Test {

  public static void main(String[] args) {
    //演示orElse和orElseGet 的区别
    Person person = new Person("ZhangSan", 18);
    Person nullPerson = null;

    // 空Optional
    System.out.println("都传入空的Optional对象-----");
    System.out.println("orElse方法");
    Person res01 = Optional.ofNullable(nullPerson).orElse(createPerson());
    System.out.println("获得的值: " + res01);
    System.out.println("orElseGet方法");
    Person res02 = Optional.ofNullable(nullPerson).orElseGet(() -> createPerson());
    System.out.println("获得的值: " + res02);

    System.out.println("++++++++++++++++++++++++++++++++");
    // 不为空的Optional
    System.out.println("都传入有值的Optional对象-----");
    System.out.println("orElse方法");
    Person res03 = Optional.of(person).orElse(createPerson());
    System.out.println("获得的值: " + res03);
    System.out.println("orElseGet方法");
    Person res04 = Optional.ofNullable(person).orElseGet(() -> createPerson());
    System.out.println("获得的值: " + res04);
  }

  public static Person createPerson() {
    System.out.println("$$创建默认的人员$$");
    return new Person("default", 18);
  }
}
