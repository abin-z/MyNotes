package com.abin.stream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest09map {

  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6")
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
        .forEach(System.out::println);
  }
}
