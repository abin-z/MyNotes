package com.abin.stream.parallelstream;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream03 {

  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9);
    numbers.parallelStream()
        .forEach(System.out::println);
    System.out.println("+++++++++++++++");
    numbers.parallelStream()
        .forEachOrdered(System.out::println);
  }
}
