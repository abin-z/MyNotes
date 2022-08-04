package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest07filter {

  public static void main(String[] args) {
    Stream.of("A1", "a1", "a2", "b3", "f4", "a3", "l5")
        .filter((s) -> s.contains("a"))
        .forEach(System.out::println);
  }
}
