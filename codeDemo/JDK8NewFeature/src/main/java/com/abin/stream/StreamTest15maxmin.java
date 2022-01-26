package com.abin.stream;

import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest15maxmin {

  public static void main(String[] args) {
    Optional<Integer> max = Stream.of("10", "90", "7", "4", "2", "6")
        .map(Integer::parseInt)
        .max((o1, o2) -> o1 - o2);      //需要传入一个Comparator, 可以自定义规则
    System.out.println("max.get() = " + max.get());

    Optional<Integer> min = Stream.of("10", "90", "7", "4", "2", "6")
        .map(Integer::parseInt)
        .max((o1, o2) -> o2 - o1);      //需要传入一个Comparator, 可以自定义规则
    System.out.println("min.get() = " + min.get());

    List<String> list = Arrays.asList("adnm", "admmt", "pot", "xbangd", "weoujgsd");

    Optional<String> m = list.stream().max(Comparator.comparing(String::length));
    System.out.println("最长的字符串：" + m.get());
  }
}
