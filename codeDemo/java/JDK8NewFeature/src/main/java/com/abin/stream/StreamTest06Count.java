package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest06Count {

  public static void main(String[] args) {
    long count = Stream.of("tom", "java", "mybatis", "marry").count();
    System.out.println("count = " + count);
  }
}
