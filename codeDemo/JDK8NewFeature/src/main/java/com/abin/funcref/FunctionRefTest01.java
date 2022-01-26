package com.abin.funcref;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/21
 */
public class FunctionRefTest01 {

  // TODO: 2022/1/21 计算数组的和

  public static void main(String[] args) {
    int[] array = {10, 20, 30};

    getSum(arg -> {
      int sum = 0;
      for (int item : arg) {
        sum += item;
      }
      return sum;
    }, array);
  }


  public static void getSum(Function<int[], Integer> function, int[] array) {
    Integer sum = function.apply(array);
    System.out.println("sum = " + sum);
  }
}
