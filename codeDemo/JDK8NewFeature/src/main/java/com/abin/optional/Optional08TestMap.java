package com.abin.optional;

import com.abin.funcref.entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional08TestMap {

  public static void main(String[] args) {
    Person person = new Person("ZhangSan", 18);
    String upperName = getUpperName(person);
    System.out.println(upperName);
  }

  public static String getUpperName(Person p) {
    Optional<Person> person = Optional.ofNullable(p);   //先将参数存放在Optional容器中
    if (person.isPresent()) {
      //如果Optional对象person 存在值执行以下的操作
      return person.map(Person::getName)  //获取name
          .map(String::toUpperCase)   //将name转化为大写
          .orElse("警告: p.name为null");   //为null就返回参数内容
    } else {
      //如果Optional对象person 为null执行以下的操作
      return null;
    }
  }
}
