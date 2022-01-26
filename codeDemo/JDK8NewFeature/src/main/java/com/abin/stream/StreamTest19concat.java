package com.abin.stream;

import java.util.ArrayList;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest19concat {

  public static void main(String[] args) {
    Integer[] array = {10, 20, 30, 40, 50, 60};
    ArrayList<Integer> doubles = new ArrayList<>();
    doubles.add(12);
    doubles.add(12);
    doubles.add(12);

    Stream<Integer> stream1 = Stream.of(array);
    Stream<Integer> stream2 = doubles.stream();

    Stream<Integer> concat = Stream.concat(stream1, stream2); //合并两个流
    concat
        .mapToInt(Integer::intValue)
        .sorted()
        .filter(i -> i > 40)
        .forEach(System.out::println);
  }
}
