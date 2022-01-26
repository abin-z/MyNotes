package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest13match {

  public static void main(String[] args) {
    Stream<String> stringStream = Stream.of("1", "9", "7", "4", "2", "6");
    boolean match = stringStream
        //.map(s -> Integer.parseInt(s))
        .map(Integer::parseInt)
//        .anyMatch(i -> i > 5);
//        .allMatch(integer -> integer > 5);
        .noneMatch(integer -> integer > 10);
    System.out.println("match = " + match);
  }
}
