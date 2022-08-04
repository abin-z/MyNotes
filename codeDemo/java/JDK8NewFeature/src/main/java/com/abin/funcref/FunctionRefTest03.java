package com.abin.funcref;

import java.util.Date;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class FunctionRefTest03 {

  public static void main(String[] args) {
    Date now  = new Date();
    //使用lambda表达式
    Supplier<Long> supplier = ()-> now.getTime();
    System.out.println("supplier = " + supplier.get());

    //使用方法引用    对象::方法名
    Supplier<Long> supplier1 = now::getTime;
    System.out.println("supplier1 = " + supplier1.get());
  }
}
