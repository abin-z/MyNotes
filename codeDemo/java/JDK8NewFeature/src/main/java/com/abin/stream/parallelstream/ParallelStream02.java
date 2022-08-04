package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream02 {

  public static void main(String[] args) {
    List<Integer> arrayList = new ArrayList<>();
    //通过Collection接口中的 .parallelStream()方法获取并行流
    Stream<Integer> parallelStream = arrayList.parallelStream();

    //将已有的串行流转化为并行流.parallel()方法
    Stream<Integer> parallel = Stream.of(1, 2, 3, 4, 5).parallel();
  }
}
