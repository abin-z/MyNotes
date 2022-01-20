package com.abin.functionalinterface;

import java.util.function.Predicate;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class PredicateDefaultTest {

  public static void main(String[] args) {
    function(n1 -> n1 >= 60, n2 -> n2 <= 100, 80);
  }

  public static void function(Predicate<Integer> p1, Predicate<Integer> p2, Integer s) {
    // s 同时满足p1,p2;
    if (p1.and(p2).test(s)) {
      System.out.println("成绩合格");
    } else {
      System.out.println("成绩不合格");
    }
  }
}
