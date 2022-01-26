package com.abin.stream;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;

/**
 * @author Abin
 * @date 2022/01/24
 */
public class StreamTest01 {

  public static void main(String[] args) {
    List<String> list = Arrays.asList("张三", "张三丰", "小明", "佩奇", "爱迪生", "张培培");
    List<String> tempList = new ArrayList<>();
    //获取姓张的用户
    for (String s : list) {
      if (s.startsWith("张")){
        tempList.add(s);
      }
    }
    ArrayList<String> tempList2 = new ArrayList<>();
    //获取名称长度为3的用户
    for (String s : tempList) {
      if(s.length() == 3){
        tempList2.add(s);
      }
    }

    //遍历输出
    for (String s : tempList2) {
      System.out.println(s);
    }

    System.out.println("======================");

    //使用Java8中的stream流
    list.stream()
        .filter(s -> s.startsWith("张"))
        .filter(s->s.length() == 3)
        .forEach(System.out::println);
  }
}
