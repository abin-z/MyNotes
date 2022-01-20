package com.abin.functionalinterface;

import java.util.Locale;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class ConsumerAndThenTest {

  public static void main(String[] args) {
    String s = "Consumer接口的使用...";
    funTest(arg -> {
      System.out.println("arg = " + arg.toUpperCase(Locale.ROOT));
    }, msg -> {
      System.out.println("msg = " + msg.toLowerCase(Locale.ROOT));
    }, s);
  }

  public static void funTest(Consumer<String> c1, Consumer<String> c2, String str) { //泛型是指定参数的类型
//    c1.accept(str);     //有参数,没有返回值
//    c2.accept(str);     //有参数,没有返回值
    c1.andThen(c2).accept(str);     //先执行c1再执行c2
    c2.andThen(c1).accept(str);     //先执行c2再执行c1
  }
}
