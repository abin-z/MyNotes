package com.abin.funcref;

import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class FunctionRefTest04 {

  public static void main(String[] args) {
    //使用lambda表达式
    Supplier<Long> currentTime = ()->System.currentTimeMillis();
    System.out.println("currentTime.get() = " + currentTime.get());
    //使用方法引用     类名::方法名
    Supplier<Long> currentTime1 = System::currentTimeMillis;
    System.out.println("currentTime1.get() = " + currentTime1.get());
  }
}
