package com.abin.funcref;

import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/21
 */
public class FunctionRefTest02 {

  public static void main(String[] args) {
    getTotal(FunctionRefTest02::getSum);
  }

  public static void getSum(int[] array) {
    int sum = 0;
    for (int item : array) {
      sum += item;
    }
    System.out.println("sum = " + sum);
  }

  public static void getTotal(Consumer<int[]> consumer) {
    int[] array = {10, 20, 30};
    consumer.accept(array);
  }
}
