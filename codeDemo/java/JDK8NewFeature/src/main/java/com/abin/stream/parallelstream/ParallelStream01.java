package com.abin.stream.parallelstream;

import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream01 {

  public static void main(String[] args) {
    System.out.println("串行的stream流");
    Stream.of(10, 20, 3, 40, 5, 6)
        .forEach(item -> {
          System.out.println("Thread id = " + Thread.currentThread().getName() + " v = " + item);
        });

    System.out.println("================");
    System.out.println("并行的stream流");
    Stream.of(10, 20, 3, 40, 5, 6)
        .parallel()   //转化为并行流
        .forEach(item -> {
          System.out.println("Thread id = " + Thread.currentThread().getName() + " v = " + item);
        });
  }
}
