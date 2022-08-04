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
public class StreamTest16reduce {

  public static void main(String[] args) {
    Integer sum = Stream.of(1, 2, 3, 4, 5)
        //identity是默认值
        //第一次的时候会将默认值给x
        //之后的每一次操作会将上一次操作的结果赋值给x, y就只是从数据中获取元素
        .reduce(0, (x, y) -> {
          System.out.println("x = " + x + " y = " + y);
          return x + y;     //求和操作
        });
    System.out.println("sum = " + sum);

    Integer max = Stream.of(1, 2, 3, 4, 50, 3, 1)
        .reduce(0, (x, y) -> {
          return x > y ? x : y;     //获取最大值
        });
    System.out.println("max = " + max);
  }
}
