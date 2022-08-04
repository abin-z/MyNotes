package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream04Thread {

  public static void main(String[] args) {
    ArrayList<Integer> list = new ArrayList<>();
    for (int i = 0; i < 1000; i++) {
      list.add(i);
    }
    System.out.println(list.size());

    //将list中的数据转移到另一个list中,
    ArrayList<Integer> newList = new ArrayList<>();
    list.parallelStream()     //这种情况下使用并行流, 会出现线程安全问题
        .forEach(newList::add);
    System.out.println(newList.size());
  }
} 
