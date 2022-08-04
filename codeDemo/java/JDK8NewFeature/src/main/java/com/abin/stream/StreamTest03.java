package com.abin.stream;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;
import java.util.Set;
import java.util.Vector;
import java.util.stream.Stream;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest03 {

  public static void main(String[] args) {
    HashMap<String, String> hashMap = new HashMap<>();

    Set<String> keySet = hashMap.keySet();
    Stream<String> stream = keySet.stream();

    Collection<String> values = hashMap.values();
    Stream<String> stream1 = values.stream();

    Set<Entry<String, String>> entrySet = hashMap.entrySet();
    Stream<Entry<String, String>> stream2 = entrySet.stream();
  }
}
