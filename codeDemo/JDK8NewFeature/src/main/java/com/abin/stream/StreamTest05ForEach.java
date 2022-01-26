package com.abin.stream;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;
import org.w3c.dom.ls.LSException;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest05ForEach {

  public static void main(String[] args) {
    List<String> list = Arrays.asList("xiaoming", "peiqi", "zhangsan");
    Stream<String> stream = list.stream();
    stream.forEach((s) -> {
      System.out.println(s);
    });

    list.stream().forEach(System.out::println);
  }
}
