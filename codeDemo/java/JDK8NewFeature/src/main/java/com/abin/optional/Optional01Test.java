package com.abin.optional;

import java.util.Optional;
import sun.security.util.Length;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional01Test {

  public static void main(String[] args) {
    //jdk7以前对null的原始操作
    String str = "123456789";
    int length;
    if (str != null) {
      length = str.length();
    } else {
      length = 0;    //0表示字符串为null
    }
    System.out.println("字符串的长度 = " + length);

    System.out.println("使用Optional======================================");
    //使用optional类
    System.out.println(Optional.ofNullable(str).map(String::length).orElse(0));
  }
}
