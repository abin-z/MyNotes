package com.abin.funcref;

import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class FunctionRefTest05 {

  public static void main(String[] args) {
    Function<String, Integer> function = (s -> s.length());
    System.out.println("function.apply(\"hello\") = " + function.apply("hello"));

    Function<String, Integer> function1 = (String::length);
    System.out.println("function1.apply(\"str\") = " + function1.apply("str"));

    BiFunction<String, String, String> biFunction = String::concat;
    String apply = biFunction.apply("hello ", "world");
    System.out.println("apply = " + apply);
  }
}
