package com.abin.stream;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Set;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest04 {

  public static void main(String[] args) {
    //当在实际操作过程中, 如果只对数组进行操作, 怎么将数组转化为Stream?

    Stream<String> stream = Stream.of("s1", "s2", "s3", "s4");

    String[] array = {"tom", "jack", "marry"};
    Stream<String> stream1 = Stream.of(array);

    Integer[] arr = {1, 2, 3, 4, 5};
    Stream<Integer> stream2 = Stream.of(arr);

    stream2.forEach(System.out::println);

    //注意, 使用Stream.of()方法的时候,只能使用包装类, 不能使用基本数据类型
    int[] arrays = {55, 66, 77, 88};
    Stream<int[]> stream3 = Stream.of(arrays); // 不能使用基本数据类型

    stream3.forEach(System.out::println);
  }
}
