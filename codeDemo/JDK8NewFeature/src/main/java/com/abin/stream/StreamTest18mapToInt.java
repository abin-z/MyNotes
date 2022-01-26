package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest18mapToInt {

  public static void main(String[] args) {
    Integer[] array = {10, 20, 30, 40, 50, 60};
    //Integer占用的内存比int多很多, 在Stream流操作中会频繁的自动拆箱和装箱, 很浪费空间
    Stream.of(array)
        .filter(item -> item > 20)
        .forEach(System.out::println);

    System.out.println("=================");
    //为了提高代码的效率,可以先将流中的Integer数据转换为int数据,然后在操作数据
    Stream.of(array)
        .mapToInt(Integer::intValue)   //先将Integer数据转换为int数据
        .filter(i -> i > 20)
        .forEach(System.out::println);
  }
}
