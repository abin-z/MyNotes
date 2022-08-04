package com.abin.functionalinterface;

import java.util.Locale;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class ConsumerTest {

  public static void main(String[] args) {
    String s = "Consumer接口的使用...";
    funTest(arg -> {
      System.out.println("arg = " + arg.toUpperCase(Locale.ROOT));
    }, s);
  }

  public static void funTest(Consumer<String> consumer, String str) { //泛型是指定参数的类型
    consumer.accept(str);     //有参数,没有返回值
  }
}
