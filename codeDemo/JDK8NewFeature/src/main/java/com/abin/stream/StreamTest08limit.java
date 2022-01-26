package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest08limit {

  public static void main(String[] args) {
    Stream.of("A1", "a1", "a2", "b3", "f4", "a3", "l5")
        .skip(4)     //跳过前面4个数字
        .forEach(System.out::println);
  }
}
