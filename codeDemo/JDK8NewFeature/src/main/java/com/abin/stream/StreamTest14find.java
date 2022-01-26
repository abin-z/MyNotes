package com.abin.stream;

import java.util.Optional;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest14find {

  public static void main(String[] args) {
    Optional<String> first = Stream.of("10", "9", "7", "4", "2", "6").findFirst();
    System.out.println("first.get() = " + first.get());

    Optional<String> any = Stream.of("10", "9", "7", "4", "2", "6").findAny();
    System.out.println("any.get() = " + any.get());
  }
}
