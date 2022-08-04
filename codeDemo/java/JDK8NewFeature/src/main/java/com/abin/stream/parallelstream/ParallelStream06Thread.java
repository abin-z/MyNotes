package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.Vector;
import java.util.stream.IntStream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream06Thread {

  public static void main(String[] args) {
    Vector<Integer> newList = new Vector<>();
    IntStream.rangeClosed(1, 1000).parallel()
//        .forEach(newList::add);
        .forEach(item -> {
          newList.add(item);
        });
    System.out.println(newList.size());
  }
} 
