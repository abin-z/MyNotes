package com.abin.functionalinterface;

import java.util.function.Predicate;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class PredicateTest {

  public static void main(String[] args) {
    function(arg -> {
      boolean equals = arg.equals(1000);
      return equals;
    });
  }

  public static void function(Predicate<Integer> pred) {
    System.out.println("pred.test(100) = " + pred.test(100));
  }
}
