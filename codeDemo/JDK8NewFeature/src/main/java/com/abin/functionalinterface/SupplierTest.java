package com.abin.functionalinterface;

import java.util.Arrays;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class SupplierTest {

  public static void main(String[] args) {
    printMax(() -> {
      int[] array = {41, 56, 69, 83, 38, 59};
      Arrays.sort(array);
      return array[array.length - 1];
    });
  }

  public static void printMax(Supplier<Integer> supplier) {   //这里的泛型Integer 是指定的返回类型
    System.out.println("supplier.get() = " + supplier.get());
  }
}