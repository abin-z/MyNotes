package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream08Thread {

  public static void main(String[] args) {
    ArrayList<Integer> list = new ArrayList<>(); //arrayList是线程不安全的容器
    List<Integer> collect = IntStream.rangeClosed(1, 1000).parallel()
        .boxed()
        .collect(Collectors.toList());
    System.out.println(collect.size());
    // 注意: IntStream是存的是int类型的stream,而Steam是一个存了Integer的stream。
    // boxed的作用就是将int类型的stream转成了Integer类型的Stream。
  }
} 
