package com.abin.funcref;

import com.abin.funcref.entity.Person;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class FunctionRefTest07 {

  public static void main(String[] args) {
    Function<Integer, String[]> function = (n) -> {
      return new String[n];
    };
    String[] apply1 = function.apply(5);
    System.out.println("apply1.length = " + apply1.length);

    //使用方法引用   类型类名[]::new  返回一个数组
    Function<Integer, String[]> func = String[]::new;
    String[] apply = func.apply(10);
    System.out.println("apply.length = " + apply.length);
  }
}
