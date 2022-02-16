package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.IntStream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream07Thread {

  public static void main(String[] args) {
    ArrayList<Integer> list = new ArrayList<>(); //arrayList是线程不安全的容器
    //将线程不安全的arrayList转化为线程安全的
    List<Integer> synchronizedList = Collections.synchronizedList(list);
    IntStream.rangeClosed(1, 1000).parallel()
        .forEach(synchronizedList::add);
    System.out.println(synchronizedList.size());
  }
} 
