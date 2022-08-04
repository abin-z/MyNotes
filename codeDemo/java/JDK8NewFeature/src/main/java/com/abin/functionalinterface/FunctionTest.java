package com.abin.functionalinterface;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class FunctionTest {

  public static void main(String[] args) {
    function(arg -> arg.length(), "hello");
  }

  public static void function(Function<String, Integer> function, String str) {
    Integer apply = function.apply(str);
    System.out.println("apply = " + apply);
  }
}
