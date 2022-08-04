package com.abin.stream;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest20collect {

  public static void main(String[] args) {
    Stream<String> stream = Stream.of("I", "love", "you", "too");
    List<String> list = stream.collect(Collectors.toList());    //将stream流转化为list集合
    ArrayList<Object> arrayList1 = Stream.of("I", "love", "you", "too").collect(ArrayList::new, ArrayList::add, ArrayList::addAll); //方式2

    Set<String> set = Stream.of("I", "love", "you", "too").collect(Collectors.toSet());     //将stream流转化为set集合
    HashSet<Object> hashSet1 = Stream.of("I", "love", "you", "too").collect(HashSet::new, HashSet::add, HashSet::addAll);  //方式2

    // 通过Collectors.toCollection(Supplier<C> collectionFactory)转化为集合
    ArrayList<String> arrayList = Stream.of("I", "love", "you", "too").collect(Collectors.toCollection(ArrayList::new));  //转化为ArrayList
    HashSet<String> hashSet = Stream.of("I", "love", "you", "too").collect(Collectors.toCollection(HashSet::new));   //转化为HashSet
  }
}
