package com.abin.funcref;

import com.abin.funcref.entity.Person;
import java.util.Spliterator;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class FunctionRefTest06 {

  public static void main(String[] args) {
    Supplier<Person> supplier = () -> new Person();
    System.out.println("supplier.get() = " + supplier.get());
    //使用方法引用   类名::new    返回一个对象
    Supplier<Person> p = Person::new;
    System.out.println("p.get() = " + p.get());

    //使用全参构造器的方法引用
    BiFunction<String, Integer, Person> personBiFunction = Person::new;
    Person person = personBiFunction.apply("小明", 18);
    System.out.println("person = " + person);
  }
}
