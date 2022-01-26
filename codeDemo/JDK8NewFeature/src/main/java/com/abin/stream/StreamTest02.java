package com.abin.stream;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Vector;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest02 {

  public static void main(String[] args) {
   //实现了Collocation接口的集合都可以使用.stream()方式获取流
    ArrayList<String> arrayList = new ArrayList<>();
    Stream<String> stream = arrayList.stream();

    HashSet<String> hashSet = new HashSet<>();
    Stream<String> stream1 = hashSet.stream();

    Vector<Integer> vector = new Vector<>();
    Stream<Integer> stream2 = vector.stream();
  }
}
