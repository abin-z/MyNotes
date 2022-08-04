package com.abin.functionalinterface;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class FunctionAndThenTest {

  public static void main(String[] args) {
    function(arg -> {
      int length = arg.length();
      System.out.println(length);
      return length;
    }, msg -> msg * 10, "hello world");
  }

  public static void function(Function<String, Integer> f1, Function<Integer, Integer> f2,
      String str) {
//    Integer apply = f1.andThen(f2).apply(str); //先执行f1, 然后在执行f2;
    // 默认方法compose和andThen的执行顺序是刚好相反的
    Integer apply = f2.compose(f1).apply(str);  // 同样的是先执行f1, 然后在执行f2;
    System.out.println("apply = " + apply);
  }
}
