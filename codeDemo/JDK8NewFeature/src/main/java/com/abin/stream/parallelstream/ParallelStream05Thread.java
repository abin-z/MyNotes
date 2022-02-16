package com.abin.stream.parallelstream;

import java.util.ArrayList;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream05Thread {

  public static void main(String[] args) {
    ArrayList<Integer> list = new ArrayList<>();
    for (int i = 0; i < 1000; i++) {
      list.add(i);
    }
    System.out.println(list.size());

    //将list中的数据转移到另一个list中,
    ArrayList<Integer> newList = new ArrayList<>();
    Object obj = new Object();
    list.parallelStream()     //添加同步代码块
        .forEach(item -> {
          synchronized (obj) {    //添加同步代码块实现线程安全
            newList.add(item);
          }
        });
    System.out.println(newList.size());
  }
} 
