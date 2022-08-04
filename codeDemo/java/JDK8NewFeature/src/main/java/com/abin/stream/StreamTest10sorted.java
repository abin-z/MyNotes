package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest10sorted {

  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6")
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
//        .sorted()
        .sorted((a1, a2) -> a2 - a1)        //传入一个Comparator的函数式接口,可以自定义排序规则
        .forEach(System.out::println);
  }
}
